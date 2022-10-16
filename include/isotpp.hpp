/**
 * @file isotpp.hpp
 * @author Simon Cahill (contact@simonc.eu)
 * @brief Contains the declaration of all important structs, functions, etc. for use with IsoTPP
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022 Simon Cahill and Contributors.
 */

#ifndef ISOTPP_INCLUDE_ISOTPP_HPP
#define ISOTPP_INCLUDE_ISOTPP_HPP

/////////////////////
// SYSTEM INCLUDES //
/////////////////////
// stl
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// libc
#include <stdint.h>

/////////////////////
// LOCAL  INCLUDES //
/////////////////////
#include "types/CanId.hpp"
#include "types/IsoTpFrame.hpp"

/**
 * @brief Top-level namespace for the library.
 */
namespace isotpp {

    using std::atomic;
    using std::chrono::duration;
    using std::function;
    using std::mutex;
    using std::shared_ptr;
    using std::string;
    using std::thread;
    using std::unique_lock;
    using std::vector;

    using types::CanId;

    // custom typedefs
    using buf_t = vector<uint8_t>;
    using logcb_t = function<void(const string&)>;
    using sendcancb_t = function<bool(const CanId&, const buf_t&)>;
    using gettickcb_t = function<uint64_t()>;

    /**
     * @brief Contains the most vital functions and information for establishing a link
     * via ISOTP.
     * 
     * This is the library's main class.
     * 
     * @remarks This class is thread safe!
     */
    class IsoTpp {
        public: // +++ Nested Classes +++
            class IsoTppFactory; //!< Factory class for easy instantiation of an instance.

        public: // +++ Constructor / Destructor +++
            explicit        IsoTpp(const IsoTpp&) = delete; //!< Prevents copy-construction
            virtual ~       IsoTpp() {}

        public: // +++ Polling +++
            void            poll(); //!< Handles timeouts, frame sending, etc.
            void            startPolling(const duration& interval); //!< Start a background polling service for you
            void            stopPolling(); //!< Stops the background poller

        public: // +++ CAN message transception +++
            void            handleIncomingCanFrame(const buf_t&); //!< Handle an incoming CAN frame from your application
            void            handleIncomingCanFrame(const buf_t&, uint16_t&); //!< Handle an incoming CAN frame and output the actual amount of data

            void            sendCanFrame(const buf_t&); //!< Sends one or more CAN frames
            void            sendCanFrame(const buf_t&, const CanId); //!< Sends one or more CAN frames using the passed CAN ID

        public: // +++ ISOTP Frame Sending +++
            

        protected: // +++ Protected Constructor +++
            explicit        IsoTpp();

        private:
            atomic<bool>    m_keepPollerAlive;

            buf_t           m_receiveBuffer;
            buf_t           m_sendBuffer;

            CanId           m_canId;

            duration        m_pollInterval;

            gettickcb_t     m_getSysTickCallback;
            
            logcb_t         m_logCallback;

            sendcancb_t     m_sendCanCallback;
    };

    /**
     * @brief Declaration of the factory class for @see IsoTpp.
     * This factory allows the user to easily setup a new instance of the IsoTpp class.
     */
    class IsoTpp::IsoTppFactory final {
        public: // +++ Constructor / Destructor +++
                            IsoTppFactory(): m_instance(new IsoTpp()) {} //!< Default constructor
            explicit        IsoTppFactory(const IsoTppFactory&) = delete; //!< Prevents copy-construction
            virtual ~       IsoTppFactory() {}

        public: // +++ Getter / Setter +++
            IsoTppFactory&  getCanId(const CanId& val) { m_instance-> }

        private:
            using instance_t = shared_ptr<IsoTpp>;
            instance_t      m_instance;
    };

};

#endif // ISOTPP_INCLUDE_ISOTPP_HPP