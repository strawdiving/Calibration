// MESSAGE EXTRA_FUNTION PACKING

#define MAVLINK_MSG_ID_EXTRA_FUNTION 236

typedef struct __mavlink_extra_funtion_t
{
 uint8_t obs_avoid_enable; /*< obs_avoid_enable*/
 uint8_t laser_height_enable; /*< laser_height_enable*/
 uint8_t add_one; /*< add_one*/
 uint8_t add_two; /*< add_one*/
 uint8_t add_three; /*< add_one*/
} mavlink_extra_funtion_t;

#define MAVLINK_MSG_ID_EXTRA_FUNTION_LEN 5
#define MAVLINK_MSG_ID_236_LEN 5

#define MAVLINK_MSG_ID_EXTRA_FUNTION_CRC 148
#define MAVLINK_MSG_ID_236_CRC 148



#define MAVLINK_MESSAGE_INFO_EXTRA_FUNTION { \
	"EXTRA_FUNTION", \
	5, \
	{  { "obs_avoid_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_extra_funtion_t, obs_avoid_enable) }, \
         { "laser_height_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_extra_funtion_t, laser_height_enable) }, \
         { "add_one", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_extra_funtion_t, add_one) }, \
         { "add_two", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_extra_funtion_t, add_two) }, \
         { "add_three", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_extra_funtion_t, add_three) }, \
         } \
}


/**
 * @brief Pack a extra_funtion message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param obs_avoid_enable obs_avoid_enable
 * @param laser_height_enable laser_height_enable
 * @param add_one add_one
 * @param add_two add_one
 * @param add_three add_one
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_extra_funtion_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t obs_avoid_enable, uint8_t laser_height_enable, uint8_t add_one, uint8_t add_two, uint8_t add_three)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_EXTRA_FUNTION_LEN];
	_mav_put_uint8_t(buf, 0, obs_avoid_enable);
	_mav_put_uint8_t(buf, 1, laser_height_enable);
	_mav_put_uint8_t(buf, 2, add_one);
	_mav_put_uint8_t(buf, 3, add_two);
	_mav_put_uint8_t(buf, 4, add_three);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#else
	mavlink_extra_funtion_t packet;
	packet.obs_avoid_enable = obs_avoid_enable;
	packet.laser_height_enable = laser_height_enable;
	packet.add_one = add_one;
	packet.add_two = add_two;
	packet.add_three = add_three;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_EXTRA_FUNTION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN, MAVLINK_MSG_ID_EXTRA_FUNTION_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif
}

/**
 * @brief Pack a extra_funtion message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param obs_avoid_enable obs_avoid_enable
 * @param laser_height_enable laser_height_enable
 * @param add_one add_one
 * @param add_two add_one
 * @param add_three add_one
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_extra_funtion_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t obs_avoid_enable,uint8_t laser_height_enable,uint8_t add_one,uint8_t add_two,uint8_t add_three)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_EXTRA_FUNTION_LEN];
	_mav_put_uint8_t(buf, 0, obs_avoid_enable);
	_mav_put_uint8_t(buf, 1, laser_height_enable);
	_mav_put_uint8_t(buf, 2, add_one);
	_mav_put_uint8_t(buf, 3, add_two);
	_mav_put_uint8_t(buf, 4, add_three);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#else
	mavlink_extra_funtion_t packet;
	packet.obs_avoid_enable = obs_avoid_enable;
	packet.laser_height_enable = laser_height_enable;
	packet.add_one = add_one;
	packet.add_two = add_two;
	packet.add_three = add_three;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_EXTRA_FUNTION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN, MAVLINK_MSG_ID_EXTRA_FUNTION_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif
}

/**
 * @brief Encode a extra_funtion struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param extra_funtion C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_extra_funtion_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_extra_funtion_t* extra_funtion)
{
	return mavlink_msg_extra_funtion_pack(system_id, component_id, msg, extra_funtion->obs_avoid_enable, extra_funtion->laser_height_enable, extra_funtion->add_one, extra_funtion->add_two, extra_funtion->add_three);
}

/**
 * @brief Encode a extra_funtion struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param extra_funtion C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_extra_funtion_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_extra_funtion_t* extra_funtion)
{
	return mavlink_msg_extra_funtion_pack_chan(system_id, component_id, chan, msg, extra_funtion->obs_avoid_enable, extra_funtion->laser_height_enable, extra_funtion->add_one, extra_funtion->add_two, extra_funtion->add_three);
}

/**
 * @brief Send a extra_funtion message
 * @param chan MAVLink channel to send the message
 *
 * @param obs_avoid_enable obs_avoid_enable
 * @param laser_height_enable laser_height_enable
 * @param add_one add_one
 * @param add_two add_one
 * @param add_three add_one
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_extra_funtion_send(mavlink_channel_t chan, uint8_t obs_avoid_enable, uint8_t laser_height_enable, uint8_t add_one, uint8_t add_two, uint8_t add_three)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_EXTRA_FUNTION_LEN];
	_mav_put_uint8_t(buf, 0, obs_avoid_enable);
	_mav_put_uint8_t(buf, 1, laser_height_enable);
	_mav_put_uint8_t(buf, 2, add_one);
	_mav_put_uint8_t(buf, 3, add_two);
	_mav_put_uint8_t(buf, 4, add_three);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, buf, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN, MAVLINK_MSG_ID_EXTRA_FUNTION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, buf, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif
#else
	mavlink_extra_funtion_t packet;
	packet.obs_avoid_enable = obs_avoid_enable;
	packet.laser_height_enable = laser_height_enable;
	packet.add_one = add_one;
	packet.add_two = add_two;
	packet.add_three = add_three;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, (const char *)&packet, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN, MAVLINK_MSG_ID_EXTRA_FUNTION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, (const char *)&packet, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_EXTRA_FUNTION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_extra_funtion_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t obs_avoid_enable, uint8_t laser_height_enable, uint8_t add_one, uint8_t add_two, uint8_t add_three)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, obs_avoid_enable);
	_mav_put_uint8_t(buf, 1, laser_height_enable);
	_mav_put_uint8_t(buf, 2, add_one);
	_mav_put_uint8_t(buf, 3, add_two);
	_mav_put_uint8_t(buf, 4, add_three);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, buf, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN, MAVLINK_MSG_ID_EXTRA_FUNTION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, buf, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif
#else
	mavlink_extra_funtion_t *packet = (mavlink_extra_funtion_t *)msgbuf;
	packet->obs_avoid_enable = obs_avoid_enable;
	packet->laser_height_enable = laser_height_enable;
	packet->add_one = add_one;
	packet->add_two = add_two;
	packet->add_three = add_three;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, (const char *)packet, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN, MAVLINK_MSG_ID_EXTRA_FUNTION_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXTRA_FUNTION, (const char *)packet, MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE EXTRA_FUNTION UNPACKING


/**
 * @brief Get field obs_avoid_enable from extra_funtion message
 *
 * @return obs_avoid_enable
 */
static inline uint8_t mavlink_msg_extra_funtion_get_obs_avoid_enable(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field laser_height_enable from extra_funtion message
 *
 * @return laser_height_enable
 */
static inline uint8_t mavlink_msg_extra_funtion_get_laser_height_enable(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field add_one from extra_funtion message
 *
 * @return add_one
 */
static inline uint8_t mavlink_msg_extra_funtion_get_add_one(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field add_two from extra_funtion message
 *
 * @return add_one
 */
static inline uint8_t mavlink_msg_extra_funtion_get_add_two(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field add_three from extra_funtion message
 *
 * @return add_one
 */
static inline uint8_t mavlink_msg_extra_funtion_get_add_three(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Decode a extra_funtion message into a struct
 *
 * @param msg The message to decode
 * @param extra_funtion C-struct to decode the message contents into
 */
static inline void mavlink_msg_extra_funtion_decode(const mavlink_message_t* msg, mavlink_extra_funtion_t* extra_funtion)
{
#if MAVLINK_NEED_BYTE_SWAP
	extra_funtion->obs_avoid_enable = mavlink_msg_extra_funtion_get_obs_avoid_enable(msg);
	extra_funtion->laser_height_enable = mavlink_msg_extra_funtion_get_laser_height_enable(msg);
	extra_funtion->add_one = mavlink_msg_extra_funtion_get_add_one(msg);
	extra_funtion->add_two = mavlink_msg_extra_funtion_get_add_two(msg);
	extra_funtion->add_three = mavlink_msg_extra_funtion_get_add_three(msg);
#else
	memcpy(extra_funtion, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_EXTRA_FUNTION_LEN);
#endif
}
