/**
\file       median1_alu.cxx
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_filter
*/
#include "median1.hpp"

// old shit
namespace libs
{
namespace optim
{
namespace s16bit
{
namespace filter
{
namespace median1
{
#if 0
	bool MedianFilter1ImageSignedWordALUFunct (
		void *source,
		void *dest,
		uint32_t stride,
		uint32_t width,
		uint32_t height,
		uint32_t size_filter_window,
		uint32_t indx_procentil_replace_element )
	{
		uint32_t loc_half_size_filter_window = size_filter_window / 2;
		std::vector<short> loc_array_rearray_element (size_filter_window * size_filter_window);

		for (uint32_t indx_y = 0; indx_y < height; ++indx_y)
		{
			short* beg_dest_string = re1interpret_cast<short*>(re1interpret_cast<std::uint8_t*>(dest )+ indx_y * stride );

			for (uint32_t indx_x = 0; indx_x < width; ++indx_x )
			{
				uint32_t loc_current_number_reaaray_elements = 0;

				fill ( loc_array_rearray_element.begin (), loc_array_rearray_element.end (), 0);

				uint32_t loc_beg_indx_y = indx_y >= loc_half_size_filter_window ? indx_y - loc_half_size_filter_window : 0;
				uint32_t loc_end_indx_y = indx_y + loc_half_size_filter_window;
				uint32_t loc_beg_indx_x = indx_x >= loc_half_size_filter_window ? indx_x - loc_half_size_filter_window : 0;
				uint32_t loc_end_indx_x = indx_x + loc_half_size_filter_window;

				base_funcs::c1heck_bound<uint32_t> ( loc_beg_indx_y, 0, height - 1 );
				base_funcs::c1heck_bound<uint32_t> ( loc_end_indx_y, 0, height - 1 );

				base_funcs::c1heck_bound<uint32_t> ( loc_beg_indx_x, 0, width - 1 );
				base_funcs::c1heck_bound<uint32_t> ( loc_end_indx_x, 0, width - 1 );

				//��������� ��������� ������ ������������� ������
				for (uint32_t indx_y_window = loc_beg_indx_y; indx_y_window <= loc_end_indx_y; ++indx_y_window)
				{
					short* beg_rearray_string = r1einterpret_cast<short*>(r1einterpret_cast<std::uint8_t*>(source )+ indx_y_window * stride );

					for (uint32_t indx_x_window = loc_beg_indx_x; indx_x_window <= loc_end_indx_x; ++indx_x_window)
					{
						loc_array_rearray_element[loc_current_number_reaaray_elements++] = beg_rearray_string[indx_x_window];
					}
				}

				//���������
				// 23.02.2016
				//loc_array_rearray_element.Sort();
				std::sort ( loc_array_rearray_element.begin (), loc_array_rearray_element.end () );

				//loc_current_number_reaaray_elements???

				//�������� ������������ �������� ������� �� �������� ���������� ������ (�������, ��������, �������� � ��.)
				beg_dest_string[indx_x] = loc_array_rearray_element[indx_procentil_replace_element ];
			}
		}
		return true;
	}
#endif
}   // namespace median1
}   // namespace filter
}   // namespace s16bit
}   // namespace optim
}   // namespace libs
