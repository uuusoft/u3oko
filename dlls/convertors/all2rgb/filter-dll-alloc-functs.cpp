//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll-alloc-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_all2rgb
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace convertors { namespace all2rgb {

void
Filter::alloc_buffs ()
{
  return;
}


void
Filter::alloc_temp_buffs ()
{
  XULOG_TRACE ("Filter::alloc_temp_buffs: beg");
  const IVideoBuff::raw_ptr _sbuff      = (*pbuff_)[finfo_.rprops_->buff_.indx_sbuff_];
  const cuuid               _px_format  = finfo_.rprops_->strip_color_ ? ::libs::helpers::uids::minor::y16 : ::libs::helpers::uids::minor::rgb24;
  const std::size_t         _byte2px    = ::libs::helpers::uids::helpers::get_count_bytes_from_format (_px_format);
  const auto                _swidth     = _sbuff->get_dim_var (svideo::TypeDimVar::width);
  const auto                _sheight    = _sbuff->get_dim_var (svideo::TypeDimVar::height);
  const std::size_t         _req_stride = ::libs::helpers::mem::get_align64 (_swidth * _byte2px, true);
  const std::size_t         _req_size   = _req_stride * _sheight;

  const off_buff_type _indx_buffs[] = {
    svideo::consts::offs::temp1
  };

  XULOG_TRACE ("Filter::alloc_temp_buffs: " << finfo_.rprops_->buff_.indx_sbuff_ << ", " << _swidth << ", " << _sheight);

  for (const off_buff_type& _indx_buff : _indx_buffs)
    {
      IVideoBuff::raw_ptr _tbuff = (*pbuff_)[_indx_buff];

      //  буфер Y16 напрямую используется далее, поэтому выделяем сразу со всеми отступами.
      if (finfo_.rprops_->strip_color_)
        {
          _tbuff->balloc (
            svideo::AllocBuffInfo (
              { _swidth,
                _sheight,
                0,      //  auto
                ::libs::helpers::uids::minor::y16,
                svideo::TypeCheckDim::enable_check,
                ::utils::dbuffs::TypeFlagsBuff::convolution_support }));

          //???svideo::helpers::override_data( *_tbuff, 0, _req_size );
          _tbuff->set_mem_var (::utils::dbuffs::TypeMemVar::size_data, _req_size);
        }
      else
        {
          _tbuff->balloc (svideo::AllocBuffInfo (_swidth, _sheight, _req_stride, _px_format));
          svideo::helpers::override_data (*_tbuff, 0, _req_size);
        }
    }

  XULOG_TRACE ("Filter::alloc_temp_buffs: end");
  return;
}

}}}      // namespace dlls::convertors::all2rgb
