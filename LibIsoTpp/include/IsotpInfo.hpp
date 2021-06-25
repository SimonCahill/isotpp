/**
 * @file IsotpInfo.hpp
 * @author Simon Cahill (simonc@online.de)
 * @brief Contains the declaration of return values and important structs required by IsoTpp.
 * @version 0.1
 * @date 2021-06-25
 * 
 * @copyright Copyright (c) 2021 Simon Cahill and Contributors
 */

#ifndef ISOTPP_INCLUDE_ISOTPINFO_HPP
#define ISOTPP_INCLUDE_ISOTPINFO_HPP

namespace isotpp {

    /*****************************************
     * OS-specific definitions
     *****************************************/
    #ifdef _WIN32
        #define snprintf _snprintf
    #endif // _WIN32

    #if (BYTE_ORDER == LITTLE_ENDIAN) || defined(_WIN32)
        #define ENDIAN_LITTLE // clever little shit
    #elif (BYTE_ORDER == BIG_ENDIAN)
        #define BIG_ENDIAN
    #endif // BYTE_ORDER == LITTLE_ENDIAN

    #pragma region "Enums"
    enum class IsoTpReturnValue {
        OKAY = 0,

        UNKNOWN_ERROR = 1,

        TRANSCEPTION_IN_PROGRESS = 2,

        MESSAGE_BUFFER_OVERFLOW = 3,

        INCORRECT_MSG_INDEX = 4,

        MISSING_PAYLOAD = 5,

        MESSAGE_TIMEOUT = 6,

        INCORRECT_FRAME_LENGTH = 7
    };
    #pragma endregion

}

#endif // ISOTPP_INCLUDE_ISOTPINFO_HPP