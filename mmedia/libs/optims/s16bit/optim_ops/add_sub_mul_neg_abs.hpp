#pragma once
/**
\file       add_sub_mul_neg_abs.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_ops
*/

namespace libs::optim::s16bit::ops
{
void add_alu (::libs::optim::io::MCallInfo& info);
void add_sse2 (::libs::optim::io::MCallInfo& info);
void add_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void add_avx1 (::libs::optim::io::MCallInfo& info);
void add_avx2 (::libs::optim::io::MCallInfo& info);


void sub_alu (::libs::optim::io::MCallInfo& info);
void sub_sse2 (::libs::optim::io::MCallInfo& info);
void sub_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void sub_avx1 (::libs::optim::io::MCallInfo& info);
void sub_avx2 (::libs::optim::io::MCallInfo& info);


void sub_abs_diff_alu (::libs::optim::io::MCallInfo& info);
void sub_abs_diff_sse2 (::libs::optim::io::MCallInfo& info);
void sub_abs_diff_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void sub_abs_diff_avx1 (::libs::optim::io::MCallInfo& info);
void sub_abs_diff_avx2 (::libs::optim::io::MCallInfo& info);


void mul_alu (::libs::optim::io::MCallInfo& info);
void mul_sse2 (::libs::optim::io::MCallInfo& info);
void mul_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void mul_avx1 (::libs::optim::io::MCallInfo& info);
void mul_avx2 (::libs::optim::io::MCallInfo& info);


void mul_rshift_alu (::libs::optim::io::MCallInfo& info);
void mul_rshift_sse2 (::libs::optim::io::MCallInfo& info);
void mul_rshift_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void mul_rshift_avx1 (::libs::optim::io::MCallInfo& info);
void mul_rshift_avx2 (::libs::optim::io::MCallInfo& info);


void mul_neg_rshift_alu (::libs::optim::io::MCallInfo& info);
void mul_neg_rshift_sse2 (::libs::optim::io::MCallInfo& info);
void mul_neg_rshift_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void mul_neg_rshift_avx1 (::libs::optim::io::MCallInfo& info);
void mul_neg_rshift_avx2 (::libs::optim::io::MCallInfo& info);


void mul_neg2_rshift_alu (::libs::optim::io::MCallInfo& info);
void mul_neg2_rshift_sse2 (::libs::optim::io::MCallInfo& info);
void mul_neg2_rshift_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info);
void mul_neg2_rshift_avx1 (::libs::optim::io::MCallInfo& info);
void mul_neg2_rshift_avx2 (::libs::optim::io::MCallInfo& info);
}   // namespace libs::optim::s16bit::ops
