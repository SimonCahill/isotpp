/**
 * @file LinkData.hpp
 * @author Simon Cahill (simonc@online.de)
 * @brief Contains the implementation of the ISOTP link data container required for ISOTP communication.
 * This outsources this data from the main object and keeps the code cleaner and modular.
 * 
 * @version 0.1
 * @date 2021-05-24
 * 
 * @copyright Copyright (c) 2021 Simon Cahill
 */

#pragma once

///////////////////////////////////////
///			SYSTEM INCLUDES
///////////////////////////////////////
#include <stdint.h>
#include <time.h>

#include <vector>

///////////////////////////////////////
///			LOCAL  INCLUDES
///////////////////////////////////////
#include "CanId.hpp"

#include "IsotpInfo.hpp"

namespace isotpp { namespace types {

    using std::vector;

    /**
     * @brief Struct containing the link data required for ISOTP communication.
     * This contains values only and is not intended for use outside this library!
     */
    template<class T>
    struct LinkData {
        LinkData(T status): transceiveStatus(status), arbitrationId(0) { }
        LinkData(T status, CanId id): transceiveStatus(status), arbitrationId(id) { }

        CanId               arbitrationId; ///!< The ID used for sending frames

        IsoTpReturnValue    protocolResult; ///!< The protocol result for the current/last tranception
        T                   transceiveStatus; ///!< The status of the current transception
    };

    /**
     * @brief Struct containing information about the message buffer used for communication.
     * This buffer is applicable for both TX and RX.
     */
    struct MessageBuffer {
        uint16_t            messageSize; ///!< The size of the message to be sent/received
        uint16_t            dataOffset; ///!< The offset in the buffer from which to continue sending/receiving
        vector<uint8_t>     dataBuffer; ///!< A vector containing the data sent/received
    };

    /**
     * @brief Struct containing information about sending multi-frame messages
     */
    struct MultiFrameFlags {
        time_t              lastCfReceivedTimestamp; ///!< Timestamp of the last time a consecutive frame was received
        time_t              nextExpectedFcFrameTimestamp; ///!< Timestamp of when the next flow control frame is expected

        uint8_t             msgId; ///!< The ID of the message to send next
        uint8_t             separationTime; ///!< The separation time in MS between sending messages
        uint8_t             maxWaitFrames; ///!< The maximum amount of wait frames to send
        uint16_t            remainingBlockSize; ///!< The remaining size (in bytes) of the current message
    };

    struct MultiFrameControl {
        time_t              lastCfSentTimestamp; ///!< Timestamp of the last time a consecutive frame was sent

        uint8_t             msgId; ///!< The ID of the current/last message
        uint8_t             maxWaitFrames; ///!< The maximum number of wait frames
    };

} /* namespace types */ } /* namespace isotpp */