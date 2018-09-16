#pragma once
/**
\file       syn.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.09.2018
\copyright  www.uuusoft.com
\project    uuu_vgen_conv
\brief      empty brief
*/

namespace dlls { namespace gens { namespace vgen_conv3_11 {
//  syn
using ::libs::ievents::props::videos::generics::convolution::VideoConvolutionProp;
using ::libs::ievents::props::videos::generics::convolution::BuffVideoConvolutionProp;

using utils::dbuffs::video::IVideoBuff;

using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;

using ::libs::optim::io::hioptim;

using TCore3x3   = ::libs::optim::s16bit::conv::base::c3x3::cores::TCore;
using TCore5x5   = ::libs::optim::s16bit::conv::base::c5x5::cores::TCore;
using TCore7x7   = ::libs::optim::s16bit::conv::base::c7x7::cores::TCore;
using TCore9x9   = ::libs::optim::s16bit::conv::base::c9x9::cores::TCore;
using TCore11x11 = ::libs::optim::s16bit::conv::base::c11x11::cores::TCore;

}}}      // namespace dlls::gens::vgen_conv3_11
