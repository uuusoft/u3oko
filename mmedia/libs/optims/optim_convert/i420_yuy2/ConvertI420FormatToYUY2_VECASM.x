#pragma once
/**
\file	ConvertI420FormatToYUY2_VECASM.h
\brief	Convertion funct I420 to YUY2
\author	Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date	01.01.2016
*/
#include "../..???/int_optim_typedefs.hpp"

//old shit
namespace optim {
#if 0
	typedef bool (*TypeFunctonI420toYUY2FunctXXX)(
	  std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );

	bool I420toYUY2FunctALU (
		std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );

	bool I420toYUY2FunctMMX (
		std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );

	bool I420toYUY2FunctSSE (
		std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );

	bool I420toYUY2FunctSSE2 (
		std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool YV12toYUY2FunctMMX (
		std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );

	bool YV12toYUY2FunctSSE (
		std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );

	bool YV12toYUY2FunctSSE2 (
		std::uint8_t* dest,
		const std::uint8_t* source,
		int stride_dest,
		int width_element,
		int height_element,
		uint32_t full_size_source_buf );
#endif
}
