// MESSAGE LASER_DISTANCE PACKING

#define MAVLINK_MSG_ID_LASER_DISTANCE 213

typedef struct __mavlink_laser_distance_t
{
 float min_distance; /*< mini distance measured by avoid_laser*/
 float angle; /*< obstacle angle*/
 float laser_x; /*< distance measured by height_laser*/
 float laser_y; /*< saved*/
} mavlink_laser_distance_t;

#define MAVLINK_MSG_ID_LASER_DISTANCE_LEN 16
#define MAVLINK_MSG_ID_213_LEN 16

#define MAVLINK_MSG_ID_LASER_DISTANCE_CRC 216
#define MAVLINK_MSG_ID_213_CRC 216



#define MAVLINK_MESSAGE_INFO_LASER_DISTANCE { \
	"LASER_DISTANCE", \
	4, \
	{  { "min_distance", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_laser_distance_t, min_distance) }, \
         { "angle", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_laser_distance_t, angle) }, \
         { "laser_x", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_laser_distance_t, laser_x) }, \
         { "laser_y", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_laser_distance_t, laser_y) }, \
         } \
}


/**
 * @brief Pack a laser_distance message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param min_distance mini distance measured by avoid_laser
 * @param angle obstacle angle
 * @param laser_x distance measured by height_laser
 * @param laser_y saved
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_laser_distance_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float min_distance, float angle, float laser_x, float laser_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LASER_DISTANCE_LEN];
	_mav_put_float(buf, 0, min_distance);
	_mav_put_float(buf, 4, angle);
	_mav_put_float(buf, 8, laser_x);
	_mav_put_float(buf, 12, laser_y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#else
	mavlink_laser_distance_t packet;
	packet.min_distance = min_distance;
	packet.angle = angle;
	packet.laser_x = laser_x;
	packet.laser_y = laser_y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LASER_DISTANCE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LASER_DISTANCE_LEN, MAVLINK_MSG_ID_LASER_DISTANCE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif
}

/**
 * @brief Pack a laser_distance message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param min_distance mini distance measured by avoid_laser
 * @param angle obstacle angle
 * @param laser_x distance measured by height_laser
 * @param laser_y saved
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_laser_distance_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float min_distance,float angle,float laser_x,float laser_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LASER_DISTANCE_LEN];
	_mav_put_float(buf, 0, min_distance);
	_mav_put_float(buf, 4, angle);
	_mav_put_float(buf, 8, laser_x);
	_mav_put_float(buf, 12, laser_y);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#else
	mavlink_laser_distance_t packet;
	packet.min_distance = min_distance;
	packet.angle = angle;
	packet.laser_x = laser_x;
	packet.laser_y = laser_y;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LASER_DISTANCE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LASER_DISTANCE_LEN, MAVLINK_MSG_ID_LASER_DISTANCE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif
}

/**
 * @brief Encode a laser_distance struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param laser_distance C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_laser_distance_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_laser_distance_t* laser_distance)
{
	return mavlink_msg_laser_distance_pack(system_id, component_id, msg, laser_distance->min_distance, laser_distance->angle, laser_distance->laser_x, laser_distance->laser_y);
}

/**
 * @brief Encode a laser_distance struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param laser_distance C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_laser_distance_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_laser_distance_t* laser_distance)
{
	return mavlink_msg_laser_distance_pack_chan(system_id, component_id, chan, msg, laser_distance->min_distance, laser_distance->angle, laser_distance->laser_x, laser_distance->laser_y);
}

/**
 * @brief Send a laser_distance message
 * @param chan MAVLink channel to send the message
 *
 * @param min_distance mini distance measured by avoid_laser
 * @param angle obstacle angle
 * @param laser_x distance measured by height_laser
 * @param laser_y saved
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_laser_distance_send(mavlink_channel_t chan, float min_distance, float angle, float laser_x, float laser_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LASER_DISTANCE_LEN];
	_mav_put_float(buf, 0, min_distance);
	_mav_put_float(buf, 4, angle);
	_mav_put_float(buf, 8, laser_x);
	_mav_put_float(buf, 12, laser_y);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, buf, MAVLINK_MSG_ID_LASER_DISTANCE_LEN, MAVLINK_MSG_ID_LASER_DISTANCE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, buf, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif
#else
	mavlink_laser_distance_t packet;
	packet.min_distance = min_distance;
	packet.angle = angle;
	packet.laser_x = laser_x;
	packet.laser_y = laser_y;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, (const char *)&packet, MAVLINK_MSG_ID_LASER_DISTANCE_LEN, MAVLINK_MSG_ID_LASER_DISTANCE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, (const char *)&packet, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_LASER_DISTANCE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_laser_distance_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float min_distance, float angle, float laser_x, float laser_y)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, min_distance);
	_mav_put_float(buf, 4, angle);
	_mav_put_float(buf, 8, laser_x);
	_mav_put_float(buf, 12, laser_y);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, buf, MAVLINK_MSG_ID_LASER_DISTANCE_LEN, MAVLINK_MSG_ID_LASER_DISTANCE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, buf, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif
#else
	mavlink_laser_distance_t *packet = (mavlink_laser_distance_t *)msgbuf;
	packet->min_distance = min_distance;
	packet->angle = angle;
	packet->laser_x = laser_x;
	packet->laser_y = laser_y;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, (const char *)packet, MAVLINK_MSG_ID_LASER_DISTANCE_LEN, MAVLINK_MSG_ID_LASER_DISTANCE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LASER_DISTANCE, (const char *)packet, MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE LASER_DISTANCE UNPACKING


/**
 * @brief Get field min_distance from laser_distance message
 *
 * @return mini distance measured by avoid_laser
 */
static inline float mavlink_msg_laser_distance_get_min_distance(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field angle from laser_distance message
 *
 * @return obstacle angle
 */
static inline float mavlink_msg_laser_distance_get_angle(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field laser_x from laser_distance message
 *
 * @return distance measured by height_laser
 */
static inline float mavlink_msg_laser_distance_get_laser_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field laser_y from laser_distance message
 *
 * @return saved
 */
static inline float mavlink_msg_laser_distance_get_laser_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a laser_distance message into a struct
 *
 * @param msg The message to decode
 * @param laser_distance C-struct to decode the message contents into
 */
static inline void mavlink_msg_laser_distance_decode(const mavlink_message_t* msg, mavlink_laser_distance_t* laser_distance)
{
#if MAVLINK_NEED_BYTE_SWAP
	laser_distance->min_distance = mavlink_msg_laser_distance_get_min_distance(msg);
	laser_distance->angle = mavlink_msg_laser_distance_get_angle(msg);
	laser_distance->laser_x = mavlink_msg_laser_distance_get_laser_x(msg);
	laser_distance->laser_y = mavlink_msg_laser_distance_get_laser_y(msg);
#else
	memcpy(laser_distance, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_LASER_DISTANCE_LEN);
#endif
}
