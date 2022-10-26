/**
 * @file BigEndianFrames.hpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the declaration of the different frame types used for big endian (be) machines.
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022 Simon Cahill
 */

#if BYTE_ORDER == BIG_ENDIAN
#ifndef ISOTPP_INCLUDE_TYPES_BIGENDIANFRAMES_HPP
#define ISOTPP_INCLUDE_TYPES_BIGENDIANFRAMES_HPP

#include <stdint.h>

#include "types/FrameFlags.hpp"
#include "types/FrameType.hpp"

namespace isotpp { namespace types { namespace frames {

    /**
     * @brief Provides the basis for all little endian frames.
     * 
     * @remarks This is the Protocol Control Information (PCI)
     */
    struct BaseFrame_Struct {
        FrameType       frameType: 4; //!< The frame type
        uint8_t         reserved: 4; //!< First nybble of the message.
        uint8_t         reservedData[7]; //!< The rest of the CAN frame
    } __attribute__((packed));

    /**
     * @brief Represents a single frame sent via CAN.
     * 
     * @remarks A single frame has max. 7 data bytes and 1 control byte, containing the data length and frame type.
     */
    struct SingleFrame_Struct {
        FrameType       frameType: 4; //!< The second nybble of the message. Equal to SINGLE_FRAME.
        uint8_t         dataLength: 4; //!< First nybble of the message, containing the data length (0-7)
        uint8_t         frameData[7]; //!< The actual data sent with the frame
    } __attribute__((packed));

    /**
     * @brief Represents the first frame in an array of consecutive frames.
     * Messages sent with multiple frames may be up to 4095 bytes in size.
     * 
     * @remarks Because multiple frames can transmit more data than a single frame (duh), this frame also contains 12 bits
     * dedicated to the actual data length.
     * This means that the first frame can only transmit 6 bytes of actual data.
     */
    struct FirstFrame_Struct {
        FrameType       frameType: 4; //!< The frame type. Equal to FIRST_FRAME.
        uint8_t         dataLengthHigh: 4; //!< First nybble of the message containing the four high-bits of the data length
        uint8_t         dataLengthLow; //!< The low 8 bits of the data length (equaling 12 bits total length)
        uint8_t         frameData[6]; //!< Six bytes of actual possible data. Remember, we lost one byte to the higher capacity
    } __attribute__((packed));

    /**
     * @brief One frame in a sea of many. These frames have ID starting with 0, resetting each time a flow-control message is sent.
     * 
     * These frames contain up to 7 bytes of data.
     */
    struct ConsecutiveFrame_Struct {
        FrameType       frameType: 4; //!< Second nybble of the message. Equal to CONSECUTIVE_FRAME
        uint8_t         frameIndex: 4; //!< First nybble of the message. Contains the frame's index.
        uint8_t         frameData[7]; //!< The next load of data sent with this frame
    } __attribute__((packed));

    /**
     * @brief Flow-control frame. These frames tell the server how to proceed with the transmission.
     */
    struct FlowControlFrame_Struct {
        FrameType       frameType: 4; //!< The frame type. Equal to FLOW_CONTROL_FRAME.
        FlowControlFlag flowControlFlag: 4; //!< First nybble of the message. Contains the flow control flags (continue, wait, overflow/abort)
        uint8_t         blockSize; //!< The amount of frames to send before next flow-control frame.
        uint8_t         frameSeparationTime; //!< The separation time (in ms) between sending frames. <= 127 = millis. 0xf1 - 0xf9 100 to 900 microseconds
    } __attribute__((packed));

} /* namespace frames */ } /* namespace types */ } /* namespace isotpp */

#endif // ISOTPP_INCLUDE_TYPES_BIGENDIANFRAMES_HPP
#endif // BYTE_ORDER == LITTLE_ENDIAN