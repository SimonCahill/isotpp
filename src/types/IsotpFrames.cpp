/**
 * @file IsotpFrames.cpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the implementation of the CAN frames required for ISOTP communication.
 * @version 0.1
 * @date 2022-10-25
 * 
 * @copyright Copyright (c) 2022 Simon Cahill and Contributors
 */
// stl
#include <algorithm>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

// libc
#include <linux/can.h>

#include "types/IsotpFrames.hpp"

namespace isotpp { namespace types {

    using std::memcpy;
    using std::out_of_range;
    using std::string;
    using std::vector;

    IIsoTpFrame::IIsoTpFrame(const size_t size): m_canFrame({}), m_frameSize(size) {
        if (size > CAN_MAX_DLEN) {
            throw std::out_of_range("Frame size must be less than CAN_MAX_DLEN!");
        }
    }

    IIsoTpFrame::IIsoTpFrame(const canf_t& frame, const size_t size): IIsoTpFrame(size) {
        m_canFrame = frame;
    }

    IIsoTpFrame::operator can_frame() const {
        can_frame frame = {0};
        const size_t bytesToCopy = m_frameSize; // is always <= CAN_MAX_DLEN

        memcpy(&frame, m_canFrame.data(), bytesToCopy);

        return frame;
    }

    IIsoTpFrame::operator string() const {
        string frame{};

        std::transform(m_canFrame.begin(), m_canFrame.end(), std::back_inserter(frame), [&](const char c) {
            return c;
        });

        return frame;
    }

    #pragma region "Single frame"
    void SingleFrame::transfer() {
        memcpy(&m_raw, m_canFrame.data(), m_frameSize);
        m_transferred = true;
    }

    SingleFrame::SingleFrame(const size_t size): IIsoTpFrame(size), m_transferred(false), m_raw({}) {
        transfer();
    }

    SingleFrame::SingleFrame(const IIsoTpFrame& x): IIsoTpFrame(x) {
        transfer();
    }

    canf_t SingleFrame::getFrameData() {
        if (!m_transferred) { transfer(); }
        vector<uint8_t> data{};

        std::transform(m_raw.frameData, m_raw.frameData + getDataLength(), std::back_inserter(data), [](const uint8_t x) { return x; });

        return data;
    }

    uint16_t SingleFrame::getDataLength() {
        if (!m_transferred) { transfer(); }
        return m_raw.dataLength;
    }
    #pragma endregion

    #pragma region "First frame"
    void FirstFrame::transfer() {
        memcpy(&m_raw, m_canFrame.data(), m_frameSize);
        m_transferred = true;
    }

    FirstFrame::FirstFrame(const size_t size): IIsoTpFrame(size), m_transferred(false), m_raw({}) {
        transfer();
    }

    FirstFrame::FirstFrame(const IIsoTpFrame& x): IIsoTpFrame(x) {
        transfer();
    }

    canf_t FirstFrame::getFrameData() {
        if (!m_transferred) { transfer(); }
        vector<uint8_t> data{};

        std::transform(m_raw.frameData, m_raw.frameData + getDataLength(), std::back_inserter(data), [](const uint8_t x) { return x; });

        return data;
    }

    uint16_t FirstFrame::getDataLength() {
        if (!m_transferred) { transfer(); }
        uint16_t length = m_raw.dataLengthHigh;
        length = (length << 8) + m_raw.dataLengthLow;

        return length;
    }
    #pragma endregion

    #pragma region "Consecutive frame"
    void ConsecutiveFrame::transfer() {
        memcpy(&m_raw, m_canFrame.data(), m_frameSize);
        m_transferred = true;
    }

    ConsecutiveFrame::ConsecutiveFrame(const size_t size): IIsoTpFrame(size), m_transferred(false), m_raw({}) {
        transfer();
    }

    ConsecutiveFrame::ConsecutiveFrame(const IIsoTpFrame& x): IIsoTpFrame(x) { transfer(); }

    canf_t ConsecutiveFrame::getFrameData() {
        if (!m_transferred) { transfer(); }
        vector<uint8_t> data{};

        std::transform(m_raw.frameData, m_raw.frameData + getDataLength(), std::back_inserter(data), [](const uint8_t x) { return x; });

        return data;
    }

    uint16_t ConsecutiveFrame::getDataLength() { return 0; }
    #pragma endregion

    #pragma region "Flow control frame"
    void FlowControlFrame::transfer() {
        memcpy(&m_raw, m_canFrame.data(), m_frameSize);
        m_transferred = true;
    }

    FlowControlFrame::FlowControlFrame(const size_t size): IIsoTpFrame(size), m_transferred(false), m_raw({}) { transfer(); }

    FlowControlFrame::FlowControlFrame(const IIsoTpFrame& x): IIsoTpFrame(x) { transfer(); }

    canf_t FlowControlFrame::getFrameData() { return {}; }

    uint16_t FlowControlFrame::getDataLength() { return m_frameSize; }

    uint8_t FlowControlFrame::getNextBlockSize() {
        if (!m_transferred) { transfer(); }

        return m_raw.blockSize;
    }

    uint8_t FlowControlFrame::getFrameSeparationTime() {
        if (!m_transferred) { transfer(); }

        return m_raw.frameSeparationTime;
    }
    #pragma endregion

} /* namespace types */ } /* namespace isotpp */