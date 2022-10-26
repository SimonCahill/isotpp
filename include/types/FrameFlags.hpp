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

#include "FrameType.hpp"

namespace isotpp { namespace types {

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