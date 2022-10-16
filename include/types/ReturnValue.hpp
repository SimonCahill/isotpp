/**
 * @file ReturnValue.hpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the different return values possible with isotpp
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022 Simon Cahill
 */

#ifndef ISOTPP_INCLUDE_TYPES_RETURNVALUE_HPP
#define ISOTPP_INCLUDE_TYPES_RETURNVALUE_HPP

namespace isotpp { namespace types {

    /**
     * @brief Enumerations of return values for the IsoTpp class.
     */
    enum class ReturnValue {
        /**
         * @brief Everything went to plan.
         */
        SUCCESS             = 0,

        /**
         * @brief A generic/system error has occurred. Please check @see errno
         */
        ERROR               = 1,

        /**
         * @brief A transmission is currently already in progress.
         */
        IN_PROGRESS         = 2,

        /**
         * @brief The current operation has overflowed.
         * E.g.: The client is trying to send a message too large for the current buffer.
         * 
         * @remarks This error should never occur because of the use of STL containers
         */
        OVERFLOW            = 3,

        /**
         * @brief Received an unexpected consecutive frame ID.
         * The client has sent the frame in the wrong order.
         */
        UNEXPECTED_FRAME    = 4,

        /**
         * @brief The input buffer is full and can no longer accept data.
         */
        BUFFER_FULL         = 5,

        /**
         * @brief A timeout error has occurred. The client no longer responded.
         */
        TIMEOUT_OCCURRED    = 6,

        /**
         * @brief The frame was an unexpected size.
         */
        INVALID_LENGTH      = 7
    };

} /* namespace types */ } /* namespace isotpp */

#endif // ISOTPP_INCLUDE_TYPES_RETURNVALUE_HPP