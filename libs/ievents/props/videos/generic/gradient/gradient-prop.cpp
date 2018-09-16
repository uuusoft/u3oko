//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       gradient-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "gradient-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace gradient {

GradientProp::GradientProp (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


GradientProp::~GradientProp ()
{}


::libs::events::IEvent::ptr
GradientProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<GradientProp> (this, _deep);
}


void
GradientProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _layers = _prop->children ("layer");
  base_functs::xml::itn  _layer  = _layers.begin ();

  while (_layer != _layers.end ())
    {
      pugi::xml_attribute _name_layer = _layer->attribute ("name");

      if (_name_layer)
        {
          const off_buff_type _bindx = utils::dbuffs::video::consts::offs::str2eoffbuff (_name_layer.as_string ());

          chls_.push_back (std::pair<off_buff_type, ChannelGradient> (_bindx, ChannelGradient ()));

          load_layer (_layer, &chls_.back ().second);
        }

      ++_layer;
    }

  return;
}


TypeGradient
text2grad_type (const std::string& _text)
{
  static const std::pair<std::string, TypeGradient> _text2val[] = {
    std::pair<std::string, TypeGradient> ("skip", TypeGradient::skip),
    std::pair<std::string, TypeGradient> ("def", TypeGradient::usual),
    std::pair<std::string, TypeGradient> ("min", TypeGradient::set2min),
    std::pair<std::string, TypeGradient> ("max", TypeGradient::set2max),
    std::pair<std::string, TypeGradient> ("load", TypeGradient::load_from_file),
    std::pair<std::string, TypeGradient> ("rnd", TypeGradient::rnd),
    std::pair<std::string, TypeGradient> ("auto", TypeGradient::increment)
  };

  for (auto& _val : _text2val)
    {
      if (_val.first == _text)
        {
          return _val.second;
        }
    }

  UASSERT_SIGNAL ("failed");
  return TypeGradient::usual;
}


void
GradientProp::load_layer (const base_functs::xml::itn& _node, ChannelGradient* _prop)
{
  UASSERT (_prop);

  base_functs::xml::ritn _params = _node->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");
      std::string         _placeholder_str;

      if (::libs::icore::xml::helpers::load<std::string> (_param, "type", _placeholder_str))
        {
          _prop->type_ = text2grad_type (_placeholder_str);
        }

      ::libs::icore::xml::helpers::load<bool> (_param, "blure", _prop->blure_);
      ::libs::icore::xml::helpers::load<bool> (_param, "animation", _prop->animation_);
      ::libs::icore::xml::helpers::load<std::string> (_param, "future_ext", _prop->future_ext_);

      if (std::string ("numbers") == _name_param.as_string ())
        {
          std::string              _all_valls = _val_param.as_string ();
          std::vector<std::string> _vals;

          boost::algorithm::split (_vals, _all_valls, boost::is_any_of (","));

          const std::size_t _max_val = std::min<std::size_t> (_vals.size (), _prop->vals_.size ());

          for (std::size_t _indx = 0; _indx < _max_val; ++_indx)
            {
              std::string _val = _vals[_indx];

              boost::algorithm::erase_all (_val, " ");

              _prop->vals_[_indx] = boost::lexical_cast<short, std::string> (_val);
            }
        }

      if (std::string ("range") == _name_param.as_string ())
        {
          std::string _all_valls = _val_param.as_string ();

          boost::algorithm::erase_all (_all_valls, " ");

          std::vector<std::string> _vals;

          boost::algorithm::split (_vals, _all_valls, boost::is_any_of ("-"));

          if (_vals.size () >= 2)
            {
              const std::size_t        _beg = std::min<size_t> (boost::lexical_cast<std::size_t, std::string> (_vals[0]), _prop->vals_.size () - 1);
              std::vector<std::string> _vals_after;

              boost::algorithm::split (_vals_after, _vals[1], boost::is_any_of (","));

              if (_vals_after.size () >= 2)
                {
                  const std::size_t _end = std::min<size_t> (boost::lexical_cast<std::size_t, std::string> (_vals_after[0]), _prop->vals_.size ());
                  const short       _hue = boost::lexical_cast<short, std::string> (_vals_after[1]);

                  for (std::size_t _indx = _beg; _indx < _end; ++_indx)
                    {
                      _prop->vals_[_indx] = _hue;
                    }
                }
            }
        }

      ++_param;
    }

  return;
}


void
GradientProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (GradientProp);
  super::copy_int (_src);
  chls_ = _dsrc->chls_;
  return;
}


template <class Archive>
void
GradientProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (chls_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::gradient

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::gradient::GradientProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::gradient::GradientProp);
