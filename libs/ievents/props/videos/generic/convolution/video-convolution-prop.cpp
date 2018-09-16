//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-convolution-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-convolution-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace convolution {

VideoConvolutionProp::VideoConvolutionProp (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


VideoConvolutionProp::~VideoConvolutionProp ()
{}


::libs::events::IEvent::ptr
VideoConvolutionProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<VideoConvolutionProp> (this, _deep);
}


void
VideoConvolutionProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
  base_functs::xml::itn  _param  = _params.begin ();

  buffs_.clear ();
  buffs_.reserve (16);

  while (_param != _params.end ())
    {
      pugi::xml_attribute _sindx  = _param->attribute ("sindx");
      pugi::xml_attribute _dindx  = _param->attribute ("dindx");
      pugi::xml_attribute _size   = _param->attribute ("size");
      pugi::xml_attribute _pvals  = _param->attribute ("vals");
      pugi::xml_attribute _pkoeff = _param->attribute ("koeff");
      pugi::xml_attribute _pname  = _param->attribute ("name");
      pugi::xml_attribute _pmod   = _param->attribute ("mod");

      std::string              _all_valls;
      std::vector<std::string> _vals;
      BuffVideoConvolutionProp _add;

      if (_pname)
        {
          _add.name_ = _pname.as_string ();
        }

      if (_pmod)
        {
          _add.mod_ = _pmod.as_bool ();
        }

      if (_sindx && _dindx && _size && _pvals)
        {
          _add.indx_sbuff_ = utils::dbuffs::video::consts::offs::str2eoffbuff (_sindx.as_string ());
          _add.indx_dbuff_ = utils::dbuffs::video::consts::offs::str2eoffbuff (_dindx.as_string ());
          _add.size_       = static_cast<short> (_size.as_int ());

          if (_pkoeff)
            {
              _add.koeff_ = _pkoeff.as_int ();
            }

          _all_valls = _pvals.as_string ();

          boost::algorithm::split (_vals, _all_valls, boost::is_any_of (","));

          _add.vals_.reserve (_vals.size ());

          for (std::string& _val : _vals)
            {
              boost::algorithm::erase_all (_val, " ");

              short _ival = -1;

              _ival = boost::lexical_cast<short, std::string> (_val);

              _add.vals_.push_back (_ival);
            }

          _add.check ();
          buffs_.push_back (_add);
        }

      ++_param;
    }

  self_correct ();
  return;
}


void
VideoConvolutionProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoConvolutionProp);
  super::copy_int (_src);
  buffs_ = _dsrc->buffs_;
  return;
}


template <class Archive>
void
VideoConvolutionProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buffs_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::convolution

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::convolution::VideoConvolutionProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::convolution::VideoConvolutionProp);
