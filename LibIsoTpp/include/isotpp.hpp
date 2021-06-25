// LibIsoTpp.h : Include file for standard system include files,
// or project specific include files.

#ifndef LIBISOTPP_INCLUDE_ISOTPP_HPP
#define LIBISOTPP_INCLUDE_ISOTPP_HPP

///////////////////////////////////////
///			SYSTEM INCLUDES
///////////////////////////////////////
#include <cstring>
#include <functional>
#include <string>
#include <vector>

///////////////////////////////////////
///			LOCAL  INCLUDES
///////////////////////////////////////
#include "LogLevel.hpp"
#include "types/LinkData.hpp"

namespace isotpp {

    #pragma region Usings
    using std::function;
    using std::memset;
    using std::string;
    using std::vector;

    using types::CanId;
    using types::LinkData;
    using types::MessageBuffer;
    using types::MultiFrameControl;
    using types::MultiFrameFlags;
    #pragma endregion


    #pragma region Typedefs
        typedef function<bool(uint8_t[8], uint8_t)> WriteCanDelegate;
        typedef function<time_t()> GetEpocDelegate;
        typedef function<void(LogLevel, string)> LogDelegate;
    #pragma endregion

    /**
     * @brief Class handling actual ISOTP communication.
     * This class contains all the fields and members required for communicating via ISOTP.
     * 
     * Inspired by my fork of lishen's isotp-c library.
     */
    class IsoTpLink {

        public: // +++ Constructor / Destructor +++
            IsoTpLink(CanId txId): m_rxLinkData(LinkData<ReceiveStatus>(ReceiveStatus::IDLE)),
                         m_txLinkData(LinkData<TransmitStatus>(TransmitStatus::IDLE, txId)) {
                memset(&m_rxLinkData, 0, sizeof(m_rxLinkData));
                memset(&m_rxLinkData, 0, sizeof(m_rxLinkData));
                memset(&m_rxMessageBuffer, 0, sizeof(m_rxMessageBuffer));
                memset(&m_txMessageBuffer, 0, sizeof(m_txMessageBuffer));
                memset(&m_rxMultiFrameFlags, 0, sizeof(m_rxMultiFrameFlags));
                memset(&m_txMultiFrameControl, 0, sizeof(m_txMultiFrameControl));
            }
            virtual ~IsoTpLink() {}

        public: // +++ Getter / Setter +++
            const LinkData<ReceiveStatus> 	getRxLinkData()        const { return m_rxLinkData; }
            const LinkData<TransmitStatus> 	getTxLinkData()        const { return m_txLinkData; }

            const MessageBuffer 			getRxMessageBuffer()   const { return m_rxMessageBuffer; }
            const MessageBuffer 			getTxMessageBuffer()   const { return m_txMessageBuffer; }
            const MultiFrameControl 		getTxMultiFrameCtrl()  const { return m_txMultiFrameControl; }
            const MultiFrameFlags 			getRxMultiFrameFlags() const { return m_rxMultiFrameFlags; }

            void                            setRxLinkData(const LinkData<ReceiveStatus>& val)       { m_rxLinkData = val; }
            void                            setTxCanId(const CanId& val)                            { m_txLinkData.arbitrationId = val; }
            void                            setTxLinkData(const LinkData<TransmitStatus>& val)      { m_txLinkData = val; }

            void                            setRxMessageBuffer(const MessageBuffer& val)            { m_rxMessageBuffer = val; }
            void                            setTxMessageBuffer(const MessageBuffer& val)            { m_txMessageBuffer = val; }

            void                            setTxMultiFrameControl(const MultiFrameControl& val)    { m_txMultiFrameControl = val; }
            void                            setRxMultiFrameFlags(const MultiFrameFlags& val)        { m_rxMultiFrameFlags = val; }

        public: // +++ Message handling +++
            void        pollMessages(); ///!< Polls for messages to be sent/received
            void        onFrameReceived(const vector<uint8_t>&); ///!< Handles an incoming CAN frame
            void        onFrameReceived(const uint8_t*, const uint16_t&); ///!< Handles an incoming CAN frame
            void        sendMessage(const vector<uint8_t>&); ///!< Sends a CAN message via ISOTP
            void        sendMessage(const vector<uint8_t>&, const CanId&); ///!< Sends a CAN message via ISOTP

        protected: // +++ Internal methods +++
            void        receiveMessage(const vector<uint8_t>&); ///!< Handles an incoming CAN message
            void        receiveMessage(const uint8_t*, const uint16_t); ///!< Handles an incoming CAN message

        private:
            LinkData<ReceiveStatus>			m_rxLinkData;
            LinkData<TransmitStatus>		m_txLinkData;
            
            MessageBuffer 					m_rxMessageBuffer;
            MessageBuffer 					m_txMessageBuffer;
            MultiFrameControl 				m_txMultiFrameControl;
            MultiFrameFlags 				m_rxMultiFrameFlags;
    };

}  /* namespace isotpp */

#endif // LIBISOTPP_INCLUDE_ISOTPP_HPP