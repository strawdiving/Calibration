// MESSAGE ARRAY_TEST_5 PACKING

#define MAVLINK_MSG_ID_ARRAY_TEST_5 155

typedef struct __mavlink_array_test_5_t
{
 char c1[5]; /*< Value array*/
 char c2[5]; /*< Value array*/
} mavlink_array_test_5_t;

#define MAVLINK_MSG_ID_ARRAY_TEST_5_LEN 10
#define MAVLINK_MSG_ID_155_LEN 10

#define MAVLINK_MSG_ID_ARRAY_TEST_5_CRC 27
#define MAVLINK_MSG_ID_155_CRC 27

#define MAVLINK_MSG_ARRAY_TEST_5_FIELD_C1_LEN 5
#define MAVLINK_MSG_ARRAY_TEST_5_FIELD_C2_LEN 5

#define MAVLINK_MESSAGE_INFO_ARRAY_TEST_5 { \
	"ARRAY_TEST_5", \
	2, \
	{  { "c1", NULL, MAVLINK_TYPE_CHAR, 5, 0, offsetof(mavlink_array_test_5_t, c1) }, \
         { "c2", NULL, MAVLINK_TYPE_CHAR, 5, 5, offsetof(mavlink_array_test_5_t, c2) }, \
         } \
}


/**
 * @brief Pack a array_test_5 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param c1 Value array
 * @param c2 Value array
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_array_test_5_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       const char *c1, const char *c2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ARRAY_TEST_5_LEN];

	_mav_put_char_array(buf, 0, c1, 5);
	_mav_put_char_array(buf, 5, c2, 5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#else
	mavlink_array_test_5_t packet;

	mav_array_memcpy(packet.c1, c1, sizeof(char)*5);
	mav_array_memcpy(packet.c2, c2, sizeof(char)*5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ARRAY_TEST_5;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN, MAVLINK_MSG_ID_ARRAY_TEST_5_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif
}

/**
 * @brief Pack a array_test_5 message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param c1 Value array
 * @param c2 Value array
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_array_test_5_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           const char *c1,const char *c2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ARRAY_TEST_5_LEN];

	_mav_put_char_array(buf, 0, c1, 5);
	_mav_put_char_array(buf, 5, c2, 5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#else
	mavlink_array_test_5_t packet;

	mav_array_memcpy(packet.c1, c1, sizeof(char)*5);
	mav_array_memcpy(packet.c2, c2, sizeof(char)*5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ARRAY_TEST_5;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN, MAVLINK_MSG_ID_ARRAY_TEST_5_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif
}

/**
 * @brief Encode a array_test_5 struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param array_test_5 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_array_test_5_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_array_test_5_t* array_test_5)
{
	return mavlink_msg_array_test_5_pack(system_id, component_id, msg, array_test_5->c1, array_test_5->c2);
}

/**
 * @brief Encode a array_test_5 struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param array_test_5 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_array_test_5_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_array_test_5_t* array_test_5)
{
	return mavlink_msg_array_test_5_pack_chan(system_id, component_id, chan, msg, array_test_5->c1, array_test_5->c2);
}

/**
 * @brief Send a array_test_5 message
 * @param chan MAVLink channel to send the message
 *
 * @param c1 Value array
 * @param c2 Value array
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_array_test_5_send(mavlink_channel_t chan, const char *c1, const char *c2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ARRAY_TEST_5_LEN];

	_mav_put_char_array(buf, 0, c1, 5);
	_mav_put_char_array(buf, 5, c2, 5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, buf, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN, MAVLINK_MSG_ID_ARRAY_TEST_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, buf, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif
#else
	mavlink_array_test_5_t packet;

	mav_array_memcpy(packet.c1, c1, sizeof(char)*5);
	mav_array_memcpy(packet.c2, c2, sizeof(char)*5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, (const char *)&packet, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN, MAVLINK_MSG_ID_ARRAY_TEST_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, (const char *)&packet, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ARRAY_TEST_5_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_array_test_5_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *c1, const char *c2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;

	_mav_put_char_array(buf, 0, c1, 5);
	_mav_put_char_array(buf, 5, c2, 5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, buf, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN, MAVLINK_MSG_ID_ARRAY_TEST_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, buf, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif
#else
	mavlink_array_test_5_t *packet = (mavlink_array_test_5_t *)msgbuf;

	mav_array_memcpy(packet->c1, c1, sizeof(char)*5);
	mav_array_memcpy(packet->c2, c2, sizeof(char)*5);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, (const char *)packet, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN, MAVLINK_MSG_ID_ARRAY_TEST_5_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ARRAY_TEST_5, (const char *)packet, MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ARRAY_TEST_5 UNPACKING


/**
 * @brief Get field c1 from array_test_5 message
 *
 * @return Value array
 */
static inline uint16_t mavlink_msg_array_test_5_get_c1(const mavlink_message_t* msg, char *c1)
{
	return _MAV_RETURN_char_array(msg, c1, 5,  0);
}

/**
 * @brief Get field c2 from array_test_5 message
 *
 * @return Value array
 */
static inline uint16_t mavlink_msg_array_test_5_get_c2(const mavlink_message_t* msg, char *c2)
{
	return _MAV_RETURN_char_array(msg, c2, 5,  5);
}

/**
 * @brief Decode a array_test_5 message into a struct
 *
 * @param msg The message to decode
 * @param array_test_5 C-struct to decode the message contents into
 */
static inline void mavlink_msg_array_test_5_decode(const mavlink_message_t* msg, mavlink_array_test_5_t* array_test_5)
{
#if MAVLINK_NEED_BYTE_SWAP
	mavlink_msg_array_test_5_get_c1(msg, array_test_5->c1);
	mavlink_msg_array_test_5_get_c2(msg, array_test_5->c2);
#else
	memcpy(array_test_5, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ARRAY_TEST_5_LEN);
#endif
}
