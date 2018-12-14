# Calibration for PX4 flight controller
Calibration base module of ground control station(GCS) for PX4 FMUv2/ Pixhawk flight controller. Refer to [QGroundControl GCS][1]

[1]: https://github.com/mavlink/qgroundcontrol

## Chapter 1 Firmware Upgrade

本程序针对的是pixhawk，PX4 FMU版本的飞控。

### 程序结构

固件更新的提示及更新进度等信息显示在 **"/SetupWizard/FirmwarePage"** 页面中。

固件更新部分的程序在 **"/FirmwareUpgrade"** 文件夹中：

- **Bootloader**：和飞控board进行交互。读写端口，发送指令，接受响应，获取board和bootloader的信息，向board烧写firmware固件并进行CRC校验（erase , program , verify , reboot）
- **FirmImage**：加载并解析固件（格式为 .px4，以JSON文件的形式传输）
- **PX4FirmwareUpgradeThread**：包括 **PX4FirmUpgradeThreadController** 和 **PX4FirrmUpgradeThreadWorker** 类。
  在PX4FirmUpgradeThreadController中新建固件更新子线程，并让PX4FirmUpgradeThreadWorker工作在子线程中；启动子线程，让PX4FirmUpgradeThreadWorker在子线程中执行寻找飞控board，连接飞控board，下载及更新固件等操作。
  PX4FirmUpgradeThreadController会将子线程中固件更新过程中的提示、进度、警告等信息反馈给FirmwarePage进行显示。

### 固件更新步骤

1. 先在所有可用的端口中查找到正确的飞控board，打开对应的端口
   注意： **在查找飞控板的时候，如果第一次查找时有board连接，必须先unplug，然后再插入**
2. sync成功的话，通过Bootloader获取board的信息（board id, bootloader version， board flash size)
3. FirwarePage上点击update按钮，联网下载board对应的firmware文件
4. FirmwareImage：加载并解析firmware文件，得到最终刷写进board的bin文件
5. 将bin文件刷写进board（erase,program,verify,reboot)

**固件更新示意图**

![固件更新示意图](C:\Users\wurenji.ZKXS\AppData\Roaming\Typora\typora-user-images\1544599498797.png)

**固件更新主流程**

![固件更新主流程](C:\Users\wurenji.ZKXS\AppData\Roaming\Typora\typora-user-images\1544672636046.png)

**_startFindBoard的流程**

![_startFindBoard流程图](C:\Users\wurenji.ZKXS\AppData\Roaming\Typora\typora-user-images\1544671445431.png)

### Bootloader

#### 读写飞控板

**命令格式：[命令字]（[参数]）[结束符]**，结束符为0x20

| protocal bytes |                                   |              |
| -------------- | --------------------------------- | ------------ |
| 0x20           | end of command                    | PROTO_EOC    |
| 0x12           | 'in sync' byte sent before status | PROTO_INSYNC |

**1. 可向board发送的命令字如下：**

| Command bytes |                                                              | enum name in Bootloader |
| ------------- | ------------------------------------------------------------ | ----------------------- |
| 0x21          | NOP for re-establishing sync                                 | PROTO_GET_SYNC          |
| 0x22          | get device ID bytes                                          | PROTO_GET_DEVICE        |
| 0x23          | erase program area and reset program address                 | PROTO_CHIP_ERASE        |
| 0x24          | set next programming address                                 | PROTO_LOAD_ADDRESS      |
| 0x27          | write bytes at program address and increment；command: 0x27 0xNN..... 0x20 , 其中0xNN是4的整数倍，用于SRAM地址对齐，且不大于256 | PROTO_PROG_MULTI        |
| 0x29          | compute & return a CRC                                       | PROTO_GET_CRC           |
| 0x30          | boot the application                                         | PROTO_BOOT              |

**2. sync时发送的命令字为 0x21，返回的响应类型如下：**

| Reply bytes | description                                          | enum name in Bootloader |
| ----------- | ---------------------------------------------------- | ----------------------- |
| 0x10        | INSYNC/OK      - 'ok' response                       | PROTO_OK                |
| 0x11        | INSYNC/FAILED  - 'fail' response                     | PROTO_FAILED            |
| 0x13        | INSYNC/INVALID - 'invalid' response for bad commands | PROTO_INVALID           |
| 0x14        | 'bad silicon' response                               |                         |

**响应状态前会添加'in sync'字节 0x12**

| response  | description                    |
| --------- | ------------------------------ |
| 0x12 0x10 | 成功时返回的数据               |
| 0x12 0x11 | 失败命令返回的数据             |
| 0x12 0x13 | 非法命令返回的数据             |
| 0x12 0x14 | 错误silicon返回的数据（FMUv4） |

**3. 向board请求board信息时发送的命令字——0x22，后面紧跟的是参数**

| command        | get Info                     | enum name in Bootloader                              |
| -------------- | ---------------------------- | ---------------------------------------------------- |
| 0x22 0x01 0x20 | bootloader version           | INFO_BL_REV=1                                        |
|                |                              | BL_REV_MIN= 2, Minimum supported bootlader protocol |
|                |                              | BL_REV_MAX= 5, Maximum supported bootloader protocol  |
| 0x22 0x02 0x20 | board ID                     | INFO_BOARD_ID=2                                      |
| 0x22 0x03 0x20 | board version                | INFO_BOARD_REV=3                                     |
| 0x22 0x04 0x20 | size of flashable area       | INFO_FLASH_SIZE=4                                    |
| 0x22 0x05 0x20 | contents of reserved vectors |                                                      |

### FirmImage

下载的.px4 firmware文件是JSON文件格式，以px4fmu-v2_default.px4为例，主要包括：

| key                                                          | type   |          |
| ------------------------------------------------------------ | ------ | -------- |
| board_id                                                     | double | required |
| airframe_xml                                                 | string |          |
| airframe_xml_size                                            | double |          |
| parameter_xml                                                | string |          |
| parameter_xml_size                                           | double |          |
| image                                                        | string |          |
| image_size                                                   | double | required |
| mav_autopilot                                                | double | required |
| build_time, summary, version, image_maxsize, git_identity, board_revision, magic, description |        |          |

其中board_id，image_size，image是firmware文件必需的key。

要确保board_id和所连接board的id匹配，解压并保存image为.bin文件，这就是最终刷写到board中的文件。