/**
 * @file LittleEndianFrames.hpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the declaration of the different frame types used for little endian (el) machines.
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022 Simon Cahill
 */

#if BYTE_ORDER == LITTLE_ENDIAN
#ifndef ISOTPP_INCLUDE_TYPES_ISOTPFRAMES_HPP
#define ISOTPP_INCLUDE_TYPES_ISOTPFRAMES_HPP

// stl
#include <array>
#include <exception>
#include <string>
#include <vector>

#include <stdint.h>

#include "types/FrameFlags.hpp"
#include "types/Helpers.hpp"
#include "types/BigEndianFrames.hpp"
#include "types/LittleEndianFrames.hpp"

namespace isotpp { namespace types {

    using frames::SingleFrame_Struct;
    using frames::FirstFrame_Struct;
    using frames::ConsecutiveFrame_Struct;
    using frames::FlowControlFrame_Struct;
    
    using std::array;
    using std::string;
    using std::vector;

    using canf_t = vector<uint8_t>;

    /**
     * @brief This class represents any and all frames usable with ISO-TP. This base class provides the basis for all
     * other frame types.
     * 
     * @remarks This class is usable with both little endian and big endian machines.
     * Also: big endian is better :)
     */
    class IIsoTpFrame {
        public: // +++ Constructor / Destructor +++
            virtual ~           IIsoTpFrame() = default;

        public: // +++ Pure Virtual +++
            virtual canf_t      getFrameData() = 0; //!< Equivalent to operator*()
            virtual FrameType   getFrameType() = 0;
            virtual uint16_t    getDataLength() = 0;
            virtual void        transfer() = 0;

        public: // +++ Operator overloads +++
            canf_t              operator*() { return getFrameData(); }; //!< Equivalent to getFrameData()
            operator            can_frame() const;
            operator            string() const;

        protected:
            explicit            IIsoTpFrame(const IIsoTpFrame&) = default;
            explicit            IIsoTpFrame(const size_t size);
            explicit            IIsoTpFrame(const canf_t&, const size_t size);

        protected:
            canf_t              getCanFrame() const { return m_canFrame; }
            size_t              getFrameSize() const { return m_frameSize; }

        protected: // +++ Internals +++
            canf_t              m_canFrame;

            size_t              m_frameSize;
    };

    /**
     * @brief Represents an ISOTP single frame message.
     */
    class SingleFrame final: public IIsoTpFrame {
        public: // +++ Constructor / Destructor +++
            explicit            SingleFrame(const size_t size);
            explicit            SingleFrame(const IIsoTpFrame& frame);

        public: // +++ Public API +++
            virtual canf_t      getFrameData() override;
            virtual FrameType   getFrameType() override { return FrameType::SINGLE_FRAME; }
            virtual uint16_t    getDataLength() override;

        private: // +++ Internal Functions +++
            virtual void        transfer() override;

        private: // +++ Internals +++
            bool                m_transferred;
            SingleFrame_Struct  m_raw;
    };

    /**
     * @brief Represents the first of N consecutive frames to be sent via CAN.
     */
    class FirstFrame final: public IIsoTpFrame {
        public: // +++ Constructor / Destructor +++
            explicit            FirstFrame(const size_t size);
            explicit            FirstFrame(const IIsoTpFrame& frame);

        public: // +++ Public API +++
            virtual canf_t      getFrameData() override;
            virtual FrameType   getFrameType() override { return FrameType::FIRST_FRAME; }
            virtual uint16_t    getDataLength() override;

        private: // +++ Internal Functions +++
            virtual void        transfer() override;

        private: // +++ Internals +++
            bool                m_transferred;
            FirstFrame_Struct   m_raw;
    };

    /**
     * @brief Represents the Nth frame in a string of consecutive frames.
     */
    class ConsecutiveFrame final: public IIsoTpFrame {
        public: // +++ Constructor / Destructor +++
            explicit                ConsecutiveFrame(const size_t size);
            explicit                ConsecutiveFrame(const IIsoTpFrame& frame);

        public: // +++ Public API +++
            virtual canf_t          getFrameData() override;
            virtual FrameType       getFrameType() override { return FrameType::CONSECUTIVE_FRAME; }
            virtual uint16_t        getDataLength() override;

        private: // +++ Internal Functions +++
            virtual void            transfer() override;

        private: // +++ Internals +++
            bool                    m_transferred;
            ConsecutiveFrame_Struct m_raw;
    };

    /**
     * @brief Represents a flow-control frame.
     */
    class FlowControlFrame final: public IIsoTpFrame {
        public: // +++ Constructor / Destructor +++
            explicit                FlowControlFrame(const size_t size);
            explicit                FlowControlFrame(const IIsoTpFrame& frame);

        public: // +++ Public API +++
            virtual canf_t          getFrameData() override;
            virtual FrameType       getFrameType() override { return FrameType::FLOW_CONTROL_FRAME; }
            virtual uint16_t        getDataLength() override { return m_frameSize; }
            uint8_t                 getNextBlockSize();
            uint8_t                 getFrameSeparationTime();

        private: // +++ Internal Functions +++
            virtual void            transfer() override;

        private: // +++ Internals +++
            bool                    m_transferred;
            FlowControlFrame_Struct m_raw;
    };

} /* namespace types */ } /* namespace isotpp */

#endif // ISOTPP_INCLUDE_TYPES_LITTLEENDIANFRAMES_HPP
#endif // BYTE_ORDER == LITTLE_ENDIAN