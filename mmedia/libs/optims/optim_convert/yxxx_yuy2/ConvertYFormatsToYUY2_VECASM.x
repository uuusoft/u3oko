#pragma once
/**
\file	???
\brief	Convertion funct Yformats to YUY2
\author	Erashov A.
\date	01.01.2005.
*/

namespace optim {

	bool UYVYtoYUY2FunctMMX (
		unsigned char* dest,
		const unsigned char* source,
		int stride_dest,
		int stride_source,
		int width_element,
		int height_element);

	bool UYVYtoYUY2FunctSSE (
		unsigned char* dest,
		const unsigned char* source,
		int stride_dest,
		int stride_source,
		int width_element,
		int height_element);

	bool UYVYtoYUY2FunctSSE2 (
		unsigned char* dest,
		const unsigned char* source,
		int stride_dest,
		int stride_source,
		int width_element,
		int height_element);

	bool YVYUtoYUY2FunctMMX (
		unsigned char* dest,
		const unsigned char* source,
		int stride_dest,
		int stride_source,
		int width_element,
		int height_element);

	bool YVYUtoYUY2FunctSSE (
		unsigned char* dest,
		const unsigned char* source,
		int stride_dest,
		int stride_source,
		int width_element,
		int height_element);

	bool YVYUtoYUY2FunctSSE2 (
		unsigned char* dest,
		const unsigned char* source,
		int stride_dest,
		int stride_source,
		int width_element,
		int height_element);
}
