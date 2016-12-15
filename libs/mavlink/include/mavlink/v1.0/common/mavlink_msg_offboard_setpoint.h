// MESSAGE OFFBOARD_SETPOINT PACKING

#define MAVLINK_MSG_ID_OFFBOARD_SETPOINT 224

typedef struct __mavlink_offboard_setpoint_t
{
 float px_1; /*< 1,x*/
 float py_1; /*< 1,x*/
 float ph_1; /*< 1,x*/
 float px_2; /*< 1,x*/
 float py_2; /*< 1,x*/
 float ph_2; /*< 1,x*/
 float yaw; /*< 1,x*/
 uint8_t seq; /*< sequence*/
 uint8_t total; /*< total*/
} mavlink_offboard_setpoint_t;

#define MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN 30
#define MAVLINK_MSG_ID_224_LEN 30

#define MAVLINK_MSG_ID_OFFBOARD_SETPOINT_CRC 101
#define MAVLINK_MSG_ID_224_CRC 101



#define MAVLINK_MESSAGE_INFO_OFFBOARD_SETPOINT { \
	"OFFBOARD_SETPOINT", \
	9, \
	{  { "px_1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_offboard_setpoint_t, px_1) }, \
         { "py_1", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_offboard_setpoint_t, py_1) }, \
         { "ph_1", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_offboard_setpoint_t, ph_1) }, \
         { "px_2", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_offboard_setpoint_t, px_2) }, \
         { "py_2", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_offboard_setpoint_t, py_2) }, \
         { "ph_2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_offboard_setpoint_t, ph_2) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_offboard_setpoint_t, yaw) }, \
         { "seq", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_offboard_setpoint_t, seq) }, \
         { "total", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_offboard_setpoint_t, total) }, \
         } \
}


/**
 * @brief Pack a offboard_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param px_1 1,x
 * @param py_1 1,x
 * @param ph_1 1,x
 * @param px_2 1,x
 * @param py_2 1,x
 * @param ph_2 1,x
 * @param yaw 1,x
 * @param seq sequence
 * @param total total
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_offboard_setpoint_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float px_1, float py_1, float ph_1, float px_2, float py_2, float ph_2, float yaw, uint8_t seq, uint8_t total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN];
	_mav_put_float(buf, 0, px_1);
	_mav_put_float(buf, 4, py_1);
	_mav_put_float(buf, 8, ph_1);
	_mav_put_float(buf, 12, px_2);
	_mav_put_float(buf, 16, py_2);
	_mav_put_float(buf, 20, ph_2);
	_mav_put_float(buf, 24, yaw);
	_mav_put_uint8_t(buf, 28, seq);
	_mav_put_uint8_t(buf, 29, total);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#else
	mavlink_offboard_setpoint_t packet;
	packet.px_1 = px_1;
	packet.py_1 = py_1;
	packet.ph_1 = ph_1;
	packet.px_2 = px_2;
	packet.py_2 = py_2;
	packet.ph_2 = ph_2;
	packet.yaw = yaw;
	packet.seq = seq;
	packet.total = total;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_OFFBOARD_SETPOINT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif
}

/**
 * @brief Pack a offboard_setpoint message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param px_1 1,x
 * @param py_1 1,x
 * @param ph_1 1,x
 * @param px_2 1,x
 * @param py_2 1,x
 * @param ph_2 1,x
 * @param yaw 1,x
 * @param seq sequence
 * @param total total
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_offboard_setpoint_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float px_1,float py_1,float ph_1,float px_2,float py_2,float ph_2,float yaw,uint8_t seq,uint8_t total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN];
	_mav_put_float(buf, 0, px_1);
	_mav_put_float(buf, 4, py_1);
	_mav_put_float(buf, 8, ph_1);
	_mav_put_float(buf, 12, px_2);
	_mav_put_float(buf, 16, py_2);
	_mav_put_float(buf, 20, ph_2);
	_mav_put_float(buf, 24, yaw);
	_mav_put_uint8_t(buf, 28, seq);
	_mav_put_uint8_t(buf, 29, total);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#else
	mavlink_offboard_setpoint_t packet;
	packet.px_1 = px_1;
	packet.py_1 = py_1;
	packet.ph_1 = ph_1;
	packet.px_2 = px_2;
	packet.py_2 = py_2;
	packet.ph_2 = ph_2;
	packet.yaw = yaw;
	packet.seq = seq;
	packet.total = total;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_OFFBOARD_SETPOINT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif
}

/**
 * @brief Encode a offboard_setpoint struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param offboard_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_offboard_setpoint_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_offboard_setpoint_t* offboard_setpoint)
{
	return mavlink_msg_offboard_setpoint_pack(system_id, component_id, msg, offboard_setpoint->px_1, offboard_setpoint->py_1, offboard_setpoint->ph_1, offboard_setpoint->px_2, offboard_setpoint->py_2, offboard_setpoint->ph_2, offboard_setpoint->yaw, offboard_setpoint->seq, offboard_setpoint->total);
}

/**
 * @brief Encode a offboard_setpoint struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param offboard_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_offboard_setpoint_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_offboard_setpoint_t* offboard_setpoint)
{
	return mavlink_msg_offboard_setpoint_pack_chan(system_id, component_id, chan, msg, offboard_setpoint->px_1, offboard_setpoint->py_1, offboard_setpoint->ph_1, offboard_setpoint->px_2, offboard_setpoint->py_2, offboard_setpoint->ph_2, offboard_setpoint->yaw, offboard_setpoint->seq, offboard_setpoint->total);
}

/**
 * @brief Send a offboard_setpoint message
 * @param chan MAVLink channel to send the message
 *
 * @param px_1 1,x
 * @param py_1 1,x
 * @param ph_1 1,x
 * @param px_2 1,x
 * @param py_2 1,x
 * @param ph_2 1,x
 * @param yaw 1,x
 * @param seq sequence
 * @param total total
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_offboard_setpoint_send(mavlink_channel_t chan, float px_1, float py_1, float ph_1, float px_2, float py_2, float ph_2, float yaw, uint8_t seq, uint8_t total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN];
	_mav_put_float(buf, 0, px_1);
	_mav_put_float(buf, 4, py_1);
	_mav_put_float(buf, 8, ph_1);
	_mav_put_float(buf, 12, px_2);
	_mav_put_float(buf, 16, py_2);
	_mav_put_float(buf, 20, ph_2);
	_mav_put_float(buf, 24, yaw);
	_mav_put_uint8_t(buf, 28, seq);
	_mav_put_uint8_t(buf, 29, total);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, buf, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, buf, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif
#else
	mavlink_offboard_setpoint_t packet;
	packet.px_1 = px_1;
	packet.py_1 = py_1;
	packet.ph_1 = ph_1;
	packet.px_2 = px_2;
	packet.py_2 = py_2;
	packet.ph_2 = ph_2;
	packet.yaw = yaw;
	packet.seq = seq;
	packet.total = total;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, (const char *)&packet, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, (const char *)&packet, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_offboard_setpoint_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float px_1, float py_1, float ph_1, float px_2, float py_2, float ph_2, float yaw, uint8_t seq, uint8_t total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, px_1);
	_mav_put_float(buf, 4, py_1);
	_mav_put_float(buf, 8, ph_1);
	_mav_put_float(buf, 12, px_2);
	_mav_put_float(buf, 16, py_2);
	_mav_put_float(buf, 20, ph_2);
	_mav_put_float(buf, 24, yaw);
	_mav_put_uint8_t(buf, 28, seq);
	_mav_put_uint8_t(buf, 29, total);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, buf, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, buf, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif
#else
	mavlink_offboard_setpoint_t *packet = (mavlink_offboard_setpoint_t *)msgbuf;
	packet->px_1 = px_1;
	packet->py_1 = py_1;
	packet->ph_1 = ph_1;
	packet->px_2 = px_2;
	packet->py_2 = py_2;
	packet->ph_2 = ph_2;
	packet->yaw = yaw;
	packet->seq = seq;
	packet->total = total;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, (const char *)packet, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OFFBOARD_SETPOINT, (const char *)packet, MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE OFFBOARD_SETPOINT UNPACKING


/**
 * @brief Get field px_1 from offboard_setpoint message
 *
 * @return 1,x
 */
static inline float mavlink_msg_offboard_setpoint_get_px_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field py_1 from offboard_setpoint message
 *
 * @return 1,x
 */
static inline float mavlink_msg_offboard_setpoint_get_py_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field ph_1 from offboard_setpoint message
 *
 * @return 1,x
 */
static inline float mavlink_msg_offboard_setpoint_get_ph_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field px_2 from offboard_setpoint message
 *
 * @return 1,x
 */
static inline float mavlink_msg_offboard_setpoint_get_px_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field py_2 from offboard_setpoint message
 *
 * @return 1,x
 */
static inline float mavlink_msg_offboard_setpoint_get_py_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field ph_2 from offboard_setpoint message
 *
 * @return 1,x
 */
static inline float mavlink_msg_offboard_setpoint_get_ph_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field yaw from offboard_setpoint message
 *
 * @return 1,x
 */
static inline float mavlink_msg_offboard_setpoint_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field seq from offboard_setpoint message
 *
 * @return sequence
 */
static inline uint8_t mavlink_msg_offboard_setpoint_get_seq(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Get field total from offboard_setpoint message
 *
 * @return total
 */
static inline uint8_t mavlink_msg_offboard_setpoint_get_total(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  29);
}

/**
 * @brief Decode a offboard_setpoint message into a struct
 *
 * @param msg The message to decode
 * @param offboard_setpoint C-struct to decode the message contents into
 */
static inline void mavlink_msg_offboard_setpoint_decode(const mavlink_message_t* msg, mavlink_offboard_setpoint_t* offboard_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP
	offboard_setpoint->px_1 = mavlink_msg_offboard_setpoint_get_px_1(msg);
	offboard_setpoint->py_1 = mavlink_msg_offboard_setpoint_get_py_1(msg);
	offboard_setpoint->ph_1 = mavlink_msg_offboard_setpoint_get_ph_1(msg);
	offboard_setpoint->px_2 = mavlink_msg_offboard_setpoint_get_px_2(msg);
	offboard_setpoint->py_2 = mavlink_msg_offboard_setpoint_get_py_2(msg);
	offboard_setpoint->ph_2 = mavlink_msg_offboard_setpoint_get_ph_2(msg);
	offboard_setpoint->yaw = mavlink_msg_offboard_setpoint_get_yaw(msg);
	offboard_setpoint->seq = mavlink_msg_offboard_setpoint_get_seq(msg);
	offboard_setpoint->total = mavlink_msg_offboard_setpoint_get_total(msg);
#else
	memcpy(offboard_setpoint, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_OFFBOARD_SETPOINT_LEN);
#endif
}
