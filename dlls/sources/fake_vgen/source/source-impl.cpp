//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       source-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.06.2016.
\copyright  www.uuusoft.com
\project    uuu_fake_vgen
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "source-impl.hpp"
#include "color_helpers_functs.hpp"

namespace dlls { namespace sources { namespace fake_vgen {

SourceImpl::SourceImpl () :
  indx_bcomp_ (0),
  counter_frames_ (0)
{
  fill_rand_vals ();
  init_make_buff_functs ();
}


SourceImpl::~SourceImpl ()
{
  CHECK_CALL_NO_THROW (free_int ());
}


void
SourceImpl::init_int ()
{
  return;
}


void
SourceImpl::start_int ()
{
  counter_frames_ = 0;
  return;
}


void
SourceImpl::stop_int ()
{
  return;
}


void
SourceImpl::get_raw_data_int (keys2buffs_ptr_type& _buffs, transform_events_type* _events)
{
  XULOG_TRACE ("fake_vgen::SourceImpl::get_raw_data::beg");
  auto& _buff = (*_buffs)[::utils::dbuffs::video::consts::offs::raw];
  UASSERT (_buff);

  _buff->set_flag (::utils::dbuffs::TypeFlagsBuff::empty, true);

  boost::posix_time::ptime _now_time = boost::posix_time::microsec_clock::universal_time ();

  if (counter_frames_)
    {
      auto _diff = _now_time - time_last_frame_;

      if (boost::posix_time::seconds (1) > _diff)
        {
          XULOG_TRACE (boost::posix_time::to_simple_string (_diff));
          XULOG_TRACE ("fake_vgen::SourceImpl::get_raw_data::end1");
          return;
        }
    }

  XULOG_TRACE ("fake_vgen::SourceImpl::get_raw_data::alloc buff");
  const auto& _props = props_info_.capture_props_;

  _buff->balloc (::utils::dbuffs::video::AllocBuffInfo (_props->width_, _props->height_, 0, _props->px_format_));
  _buff->set_format (_props->px_format_);

  make_buff_functs_[_props->px_format_](
    _buff->get_dim_var (TypeDimVar::width),
    _buff->get_dim_var (TypeDimVar::height),
    _buff->get_dim_var (TypeDimVar::stride),
    utils::dbuffs::video::helpers::get_data (_buff.get ()));

  _buff->set_mem_var (TypeMemVar::size_data, _buff->get_dim_var (TypeDimVar::stride) * _props->height_);
  ++indx_bcomp_;
  ++counter_frames_;
  time_last_frame_ = _now_time;
  XULOG_TRACE ("fake_vgen::SourceImpl::get_raw_data::end2");
  return;
}


void
SourceImpl::set_cpu_int (::libs::helpers::sys::cpu::TypeExtCpu current_optim)
{
  return;
}


bool
SourceImpl::free_int ()
{
  stop ();
  return true;
}


void
SourceImpl::update_dinfo_int (const gen_lib::SourceInfo& _info)
{
  auto& _px_format = props_info_.capture_props_->px_format_;
  if (!make_buff_functs_[_px_format])
    {
      XULOG_WARNING ("try use unsupported format fake came, " << ::libs::helpers::uids::helpers::get_readable_name (_px_format));
      //_px_format = ::libs::helpers::uids::minor::rgb24;
    }
  return;
}


void
SourceImpl::fill_rand_vals ()
{
  std::random_device               _seed;
  std::default_random_engine       _eng (_seed ());
  std::uniform_real_distribution<> _dist (0, 1);

  rand_bcomp_.fill (0);
  for (unsigned char& _val : rand_bcomp_)
    {
      _val = UUU_ICAST_UCHAR (128 + _dist (_eng) * 127);
    }
  return;
}


void
SourceImpl::init_make_buff_functs ()
{
  //  Функция для генерации изображений в формате yuy2
  make_buff_functs_[::libs::helpers::uids::minor::yuy2] = [this](std::size_t _width, std::size_t _height, std::size_t _stride, unsigned char* _beg_buff) {
    const unsigned char _bcomp = rand_bcomp_[indx_bcomp_ % rand_bcomp_.size ()];

    for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
      {
        unsigned char* _prow = _beg_buff + _indxy * _stride;

        for (std::size_t _indxx = 0; _indxx < _width; ++_indxx)
          {
            const std::size_t _indx_to_30 = _indxx % 20;

            _prow[2 * _indxx + 0] = 100;      //( /*_indx_to_30 >= 0 &&*/ _indx_to_30 <= 9 ? _bcomp : 0);
            _prow[2 * _indxx + 1] = (_indx_to_30 >= 10 && _indx_to_30 <= 19 ? _bcomp : 0);
          }
      }
    return;
  };

  // Фyнкция для генерации изображений в формате rgb24
  make_buff_functs_[::libs::helpers::uids::minor::rgb24] = [this](std::size_t _width, std::size_t _height, std::size_t _stride, unsigned char* _beg_buff) {
    const unsigned char _bcomp = rand_bcomp_[indx_bcomp_ % rand_bcomp_.size ()];

    for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
      {
        unsigned char* _prow = _beg_buff + _indxy * _stride;

        for (std::size_t _indxx = 0; _indxx < _width; ++_indxx)
          {
            const std::size_t _indx_to_30 = _indxx % 30;

            _prow[3 * _indxx + 0] = (/*_indx_to_30 >= 0 &&*/ _indx_to_30 <= 9 ? _bcomp : 0);
            _prow[3 * _indxx + 1] = (_indx_to_30 >= 10 && _indx_to_30 <= 19 ? _bcomp : 0);
            _prow[3 * _indxx + 2] = (_indx_to_30 >= 20 && _indx_to_30 <= 29 ? _bcomp : 0);
          }
      }
    return;
  };

  return;
}

}}}      // namespace dlls::sources::fake_vgen
