#pragma once
/**
\file       const_add_sub_mul_neg_abs.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_ops
*/

namespace libs::optim::s16bit::ops
{
void fill_func_abs_sub_alu (::libs::optim::io::MCallInfo& info);
void fill_func_abs_sub_sse2 (::libs::optim::io::MCallInfo& info);
void fill_func_abs_sub_avx1 (::libs::optim::io::MCallInfo& info);
void fill_func_abs_sub_avx2 (::libs::optim::io::MCallInfo& info);


void sat_2byte_alu (::libs::optim::io::MCallInfo& info);
void sat_2byte_sse2 (::libs::optim::io::MCallInfo& info);
void sat_2byte_avx1 (::libs::optim::io::MCallInfo& info);
void sat_2byte_avx2 (::libs::optim::io::MCallInfo& info);


void add_const_alu (::libs::optim::io::MCallInfo& info);
void add_const_sse2 (::libs::optim::io::MCallInfo& info);
void add_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void add_const_avx1 (::libs::optim::io::MCallInfo& info);
void add_const_avx2 (::libs::optim::io::MCallInfo& info);


void sub_const_alu (::libs::optim::io::MCallInfo& info);
void sub_const_sse2 (::libs::optim::io::MCallInfo& info);
void sub_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void sub_const_avx1 (::libs::optim::io::MCallInfo& info);
void sub_const_avx2 (::libs::optim::io::MCallInfo& info);


void mul_const_alu (::libs::optim::io::MCallInfo& info);
void mul_const_sse2 (::libs::optim::io::MCallInfo& info);
void mul_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void mul_const_avx1 (::libs::optim::io::MCallInfo& info);
void mul_const_avx2 (::libs::optim::io::MCallInfo& info);


void mul_rshift_const_alu (::libs::optim::io::MCallInfo& info);
void mul_rshift_const_sse2 (::libs::optim::io::MCallInfo& info);
void mul_rshift_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void mul_rshift_const_avx1 (::libs::optim::io::MCallInfo& info);
void mul_rshift_const_avx2 (::libs::optim::io::MCallInfo& info);


void sub_mul_rshift_add_const_alu (::libs::optim::io::MCallInfo& info);
void sub_mul_rshift_add_const_sse2 (::libs::optim::io::MCallInfo& info);
void sub_mul_rshift_add_const_unmask_dest_sse2 (::libs::optim::io::MCallInfo& info);
void sub_mul_rshift_add_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void sub_mul_rshift_add_const_unmask_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);


void comp_gt_const_alu (::libs::optim::io::MCallInfo& info);
void comp_gt_const_sse2 (::libs::optim::io::MCallInfo& info);
void comp_gt_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::ops
