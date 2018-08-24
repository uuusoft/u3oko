//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mjpeg-impl-decoder-generic.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_vcodec_mjpg
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buff_helpers_functs.hpp"

namespace dlls { namespace codecs { namespace vcodec_mjpg {

void
MjpegImpl::decode_int (const Buffs* _src, Buffs* _dst, events_type* _events)
{
  XULOG_TRACE ("MjpegImpl::decode_int: beg, source buff=" << cinfo_.buffs_.indx_sbuff_);
  const IVideoBuff::craw_ptr _compbuff  = (*_src)[cinfo_.buffs_.indx_sbuff_];
  const int                  _compsize  = (*_compbuff)[::utils::dbuffs::TypeMemVar::size_data];
  const HeaderIFrame*        _head      = UUU_CODECS_CAST<const HeaderIFrame*> (utils::dbuffs::video::helpers::get_const_data (_compbuff));
  const bool                 _use_color = !_head->cinfo_.monochrome_;
  const auto&                _base_head = _head->base_part_;
  const auto&                _info_head = _base_head.sinfo_;

  //::dlls::codecs::codec_gen::dump (_head);            //  debug
  //::utils::dbuffs::video::helpers::dump( _compbuff ); //  debug

  XULOG_TRACE ("MjpegImpl::decode_int: _head->cinfo_.monochrome_=" << _head->cinfo_.monochrome_);
  CHECK_STATE_VRET (_compsize >= sizeof (HeaderIFrame), "failed, data less header, " << _compsize << "<" << sizeof (HeaderIFrame));
  CHECK_STATE_VRET (_head->check (), "invalid header compress frame");

  auto _dbuff = (*_dst)[cinfo_.buffs_.indx_dbuff_];
  if (!_dbuff)
    {
      XULOG_WARNING ("receive invalid destination buffer, skip, " << cinfo_.buffs_.indx_dbuff_);
      return;
    }

  const auto _stride_alloc = _info_head.width_ * ::libs::helpers::uids::helpers::get_count_bytes_from_format (::libs::helpers::uids::minor::rgb32);      // выделяем максимум под выходной буфер.
  const auto _px_preformat = _use_color ? ::libs::helpers::uids::minor::rgb24 : ::libs::helpers::uids::minor::y8;

  XULOG_TRACE ("MjpegImpl::decode_int: prepare alloc temp buff");
  temp_buff_->balloc (::utils::dbuffs::video::AllocBuffInfo (_info_head.width_, _info_head.height_, _stride_alloc, _px_preformat));
  temp_buff_->set_flag (utils::dbuffs::TypeFlagsBuff::empty, true);
  _dbuff->set_flag (utils::dbuffs::TypeFlagsBuff::empty, true);
  //::utils::dbuffs::video::helpers::dump (&*temp_buff_);      // debug

  ProxyBuff _tsrc (_compbuff);
  _tsrc.check ();
  // debug
  //::utils::dbuffs::video::helpers::fill (temp_buff_.get (), 0);
  //temp_buff_->set_flag (utils::dbuffs::TypeFlagsBuff::empty, false);
  //::utils::dbuffs::video::helpers::fill_buffer<char> (temp_buff_.get (), [](long long _indx, char& _val) {
  //_val = 0 + UUU_ICAST_CHAR (rand () % 101);
  //_val = UUU_ICAST_CHAR (_indx);
  //return;
  //});
  //temp_buff_->set_flag (utils::dbuffs::TypeFlagsBuff::empty, true);
  decomp_iframe (_head, _tsrc, _compsize);

  XULOG_TRACE ("MjpegImpl::decode_int: check result buff");
  if (temp_buff_->get_flag (utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_WARNING ("failed decompress buffer, skip");
      return;
    }
  // debug
  //::utils::dbuffs::video::helpers::fill (temp_buff_.get (), 0);
  //temp_buff_->set_flag (utils::dbuffs::TypeFlagsBuff::empty, false);
  //::utils::dbuffs::video::helpers::fill_buffer<char> (temp_buff_.get (), [](long long _indx, char& _val) {
  //_val = 155 + UUU_ICAST_CHAR (rand () % 101);
  //_val = UUU_ICAST_CHAR (_indx);
  //return;
  //});
  //::utils::dbuffs::video::helpers::fill (temp_buff_.get (), 0);
  //::utils::dbuffs::video::helpers::fill<char> (temp_buff_.get (), [](int _x, int _y, char& _val) {
  //_val = 155 + UUU_ICAST_CHAR (rand () % 101);
  //return;
  //});
  _dbuff->clone (temp_buff_.get (), 100.0f);
  _dst->set_flag (::libs::buffs::TypeBuffsFlags::request_convert2hsl, true);
  //  debug
  //::utils::dbuffs::video::helpers::dump (&*temp_buff_);
  //::utils::dbuffs::video::helpers::dump (_dbuff);
  //utils::dbuffs::video::helpers::fill( _braw, rand() % 256 );
  //::utils::dbuffs::video::helpers::fill (_dbuff, 0);      //   debug
  //::utils::dbuffs::video::helpers::fill<char> (_dbuff, [](int _x, int _y, char& _val) {
  //_val = 155 + UUU_ICAST_CHAR (rand () % 101);
  //return;
  //});
  XULOG_TRACE ("MjpegImpl::decode_int: end");
  return;
}

}}}      // namespace dlls::codecs::vcodec_mjpg
