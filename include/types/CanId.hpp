/*********************************************************************
 * @file   CanId.hpp
 * @brief  Contains the implementation of the CanId data type.
 * 
 * @author Simon Cahill
 * @date   May 2021
 *********************************************************************/

#pragma once

///////////////////////////////////////
///			SYSTEM INCLUDES
///////////////////////////////////////
#include <stdint.h>

// Get Linux CAN header(s)
#if defined(__linux__)
	#include <linux/can.h>
#else
	// We're not operating on a Linux system, so we'll need to typedef our own
	// canid_t, so the code below still works.
	// You could theoretically just compile said code only on Linux, but we want to keep it similar
	// on all potential platforms
	typedef uint32_t canid_t; // typedef __u32 canid_t from linux/can.h

	// Seeming as we're not on Linux, we will also need to set some consts
	// I don't like #defines if I can avoid them and this is pure C++,
	// so I'll be using actual consts.
	// Source: linux/can.h
	const uint32_t CAN_EFF_FLAG 0x80000000U ///!< CAN extended frame format
	const uint32_t CAN_RTR_FLAG 0x40000000U ///!< CAN remote transmission request
	const uint32_t CAN_ERR_FLAG 0x20000000U ///!< CAN error frame flag

	const uint32_t CAN_SFF_MASK 0x000007FFU ///!< CAN standard frame format (SFF)
	const uint32_t CAN_EFF_MASK 0x1FFFFFFFU ///!< CAN extended frame format (EFF)
	const uint32_t CAN_ERR_MASK 0x1FFFFFFFU ///!< CAN omit EFF, RTR, ERR flags

	const uint32_t CAN_SFF_ID_BITS	11
	const uint32_t CAN_EFF_ID_BITS	29

	
	const uint32_t CAN_MAX_DLC 		8
	const uint32_t CAN_MAX_DLEN 	8
	const uint32_t CANFD_MAX_DLC 	15
	const uint32_t CANFD_MAX_DLEN 	64

#endif

namespace isotpp { namespace types {

	/**
	 * @brief The actual struct representing a CAN ID.
	 * This struct transparently handles both standard and extended IDs used for CAN frames.
	 */
	struct CanId {
		explicit CanId(uint32_t id) { m_canId = id; } // Smaller integer types can be implicitely casted
		explicit CanId(int32_t id) { m_canId = static_cast<uint32_t>(id); } // Smaller integer types can be implicitely casted

		#pragma region "Implicit type casts"
		operator uint32_t() { return m_canId; }
		operator int32_t()  { return static_cast<int32_t>(m_canId); }
		// operator canid_t()  { return static_cast<canid_t>(m_canId); }

		CanId operator =(const uint32_t id) { return CanId(id); }
		CanId operator =(const int32_t id)  { return CanId(id); }
		#pragma endregion

		#pragma region "Flag detection"
		bool isExtendedFrame() 	{ return (m_canId & CAN_EFF_FLAG); }
		bool isRemoteTrFrame() 	{ return (m_canId & CAN_RTR_FLAG); }
		bool isErrorFrame()		{ return (m_canId & CAN_ERR_FLAG); }
		#pragma endregion

		#pragma region "Flag setting"
		void setExtendedFrame() { m_canId |= CAN_EFF_FLAG; }
		void setRemoteTrFrame() { m_canId |= CAN_RTR_FLAG; }
		void setErrorFrame()	{ m_canId |= CAN_ERR_FLAG; }
		#pragma endregion

		#pragma region "Getters"
		CanId getStandardFormat() { return CanId(m_canId & CAN_SFF_MASK); }
		CanId getExtendedFormat() { return CanId(m_canId & CAN_EFF_MASK); }
		#pragma endregion

		private:
          uint32_t m_canId; ///!< The CAN ID stored in this instance
	};

} /* namespace types */ } /* namespace isotpp */
