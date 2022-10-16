/**
 * @file FrameFlags.hpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the declaration of flags usable by all frames and machine types.
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022 Simon Cahill
 */

#ifndef ISOTPP_INCLUDE_TYPES_FRAMEFLAGS_HPP
#define ISOTPP_INCLUDE_TYPES_FRAMEFLAGS_HPP

#include <stdint.h>

namespace isotpp { namespace types {

    /**
     * @brief Enum type containing the different frame types available for ISOTP communication.
     */
    enum class FrameType: uint8_t {
        /**
         * @brief The entire message consists of a single frame.
         */
        SINGLE_FRAME        = 0,

        /**
         * @brief First frame; this frame is one of many.
         */
        FIRST_FRAME         = 1,

        /**
         * @brief Consecutive frame; this is one frame in an array of N frames.
         */
        CONSECUTIVE_FRAME   = 2,

        /**
         * @brief The flow control frame allows the transmitter and receiver to exchange information on how to proceed with transmission of the data.
         */
        FLOW_CONTROL_FRAME  = 3

        // type 4-15 are reserved for future use!
    };

    /**
     * @brief Enum type containing the different possible flow control flags for ISOTP communication.
     */
    enum class FlowControlFlag: uint8_t {
        /**
         * @brief Continue with transmission of data.
         */
        CONTINUE = 0,

        /**
         * @brief Wait for client to handle data.
         */
        WAIT = 1,

        /**
         * @brief The client has aborted the operation.
         */
        ABORT_TRANSMISSION = 2
    };

} /* namespace types */ } /* namespace isotpp */

#endif // ISOTPP_INCLUDE_TYPES_FRAMEFLAGS_HPP