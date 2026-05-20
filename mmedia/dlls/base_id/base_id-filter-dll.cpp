/**
\file       base_id-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
\project    u3_base_id_dll
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "base_id-includes_int.hpp"
#include "base_id-filter-dll.hpp"

namespace dlls::base_id
{
Filter::Filter () :
  counter_frames_ (0),
  base_interf_ (std::make_shared< BaseIdInterf > ()),
  send_base_interf_ (false)
{
}


Filter::~Filter ()
{
}


void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);
  base_interf_->update_property (finfo_.ef_props_.front ().get ());
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
  base_interf_->update_property (finfo_.ef_props_.front ().get ());
}


void
Filter::run_int ()
{
  send_base_interf_ = false;
}


void
Filter::stop_int ()
{
  send_base_interf_ = false;
}


void
Filter::init_pts (syn::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);
  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}
}   // namespace dlls::base_id
