/**
 * @file IsoTpFrame.hpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the declaration of a full ISOTP CAN frame.
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022 Simon Cahill
 */

#ifndef ISOTPP_INCLUDE_TYPES_ISOTPFRAME_HPP
#define ISOTPP_INCLUDE_TYPES_ISOTPFRAME_HPP

#include "types/CanId.hpp"
#include "types/BigEndianFrames.hpp"
#include "types/LittleEndianFrames.hpp"
#include "types/FrameFlags.hpp"

#include <stdint.h>

#include <algorithm>
#include <vector>

namespace isotpp { namespace types {

    using std::vector;

    union FrameUnion {
        uint8_t raw[8];
        BaseFrame common;
        SingleFrame singleFrame;
        FirstFrame firstFrame;
        ConsecutiveFrame consecutiveFrame;
        FlowControlFrame flowControlFrame;
    };

    /**
     * @brief A union of all the possible frames types available with ISOTP.
     */
    struct IsoTpFrame {
        FrameUnion frameTypes;
    } __attribute__((packed));

    /**
     * @brief Transforms a byte pointer (@see uint8_t) to a vector containing the same data.
     * 
     * @remarks This function correctly handles CAN frame data lengths, but @b NOT CAN-FD data lengths!
     * 
     * @param data A pointer to the data. If nullptr, will return empty vector.
     * @param len The length of the array pointed to by @see data. If > CAN_MAX_DLEN && truncate, will be truncated to CAN_MAX_DLEN
     * @param truncate Whether or not to truncate the length of the array to CAN_MAX_DLEN
     * 
     * @return vector<uint8_t> A new vector containing the data
     */
    inline vector<uint8_t> bytePtrToVector(const uint8_t* data, const uint8_t len, const bool truncate = false) {
        vector<uint8_t> returnVal{};

        if (data == nullptr) { return returnVal; }
        const uint8_t sanitisedLen = len > CAN_MAX_DLEN && truncate ? CAN_MAX_DLEN : len;

        std::transform(data, data + sanitisedLen, std::back_inserter(returnVal), [](const auto) { return true; });

        return returnVal;
    }

} /* namespace types */ } /* namespace isotpp */

#endif // ISOTPP_INCLUDE_TYPES_ISOTPFRAME_HPP