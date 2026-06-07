/**
\file       gradient-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "gradient-prop.hpp"

namespace libs::ievents::props::videos::generic::gradient
{
GradientProp::GradientProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();

  channels_.push_back ({ ::utils::dbufs::video::consts::offs::lit, ChannelGradient () });
  channels_.push_back ({ ::utils::dbufs::video::consts::offs::sat, ChannelGradient () });
  channels_.push_back ({ ::utils::dbufs::video::consts::offs::hue, ChannelGradient () });
}


::libs::events::IEvent::ptr
GradientProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GradientProp > (this, deep);
}


void
GradientProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  channels_ = ::boost::json::value_to< channels_type > (obj.at ("channells"));
}


void
GradientProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["channells"] = ::boost::json::value_from (channels_);
}


Gradients
text2grad_type (const std::string& text)
{
  static const std::pair< std::string, Gradients > text2val[] = {
    std::pair< std::string, Gradients > ("skip", Gradients::skip),
    std::pair< std::string, Gradients > ("def", Gradients::usual),
    std::pair< std::string, Gradients > ("min", Gradients::set2min),
    std::pair< std::string, Gradients > ("max", Gradients::set2max),
    std::pair< std::string, Gradients > ("load", Gradients::load_from_file),
    std::pair< std::string, Gradients > ("string", Gradients::load_from_string),
    std::pair< std::string, Gradients > ("rnd", Gradients::rnd),
    std::pair< std::string, Gradients > ("auto", Gradients::increment),
    std::pair< std::string, Gradients > ("direct", Gradients::direct)
  };

  for (auto& val : text2val)
  {
    if (val.first == text)
    {
      return val.second;
    }
  }

  U3_XLOG_ERROR ("unknown text for Gradients " + text);
  return Gradients::usual;
}


void
GradientProp::load_layer_from_xml (const ::pugi::xml_named_node_iterator& node, ChannelGradient* prop)
{
  U3_ASSERT (prop);

  ::pugi::xml_object_range< ::pugi::xml_named_node_iterator > params = node->children ("param");
  ::pugi::xml_named_node_iterator                             param  = params.begin ();

  while (param != params.end ())
  {
    pugi::xml_attribute name_param = param->attribute ("name");
    pugi::xml_attribute val_param  = param->attribute ("val");
    std::string         placeholder_str;

    if (::libs::iproperties::xml::helpers::load< std::string > (param, "type", placeholder_str))
    {
      prop->gradient_type_ = text2grad_type (placeholder_str);
    }

    ::libs::iproperties::xml::helpers::load< bool > (param, "blure", prop->blure_);
    ::libs::iproperties::xml::helpers::load< bool > (param, "animation", prop->animation_);
    ::libs::iproperties::xml::helpers::load< std::string > (param, "future_ext", prop->future_ext_);

    if (std::string ("numbers") == name_param.as_string ())
    {
      std::string                all_valls = val_param.as_string ();
      std::vector< std::string > vals;

      boost::algorithm::split (vals, all_valls, boost::is_any_of (","));

      const std::size_t max_val = std::min< std::size_t > (vals.size (), prop->vals_.size ());

      for (std::size_t indx = 0; indx < max_val; ++indx)
      {
        std::string val = vals[indx];

        boost::algorithm::erase_all (val, " ");

        prop->vals_[indx] = boost::lexical_cast< std::int16_t, std::string > (val);
      }
    }

    if (std::string ("range") == name_param.as_string ())
    {
      std::string all_valls = val_param.as_string ();

      boost::algorithm::erase_all (all_valls, " ");

      std::vector< std::string > vals;

      boost::algorithm::split (vals, all_valls, boost::is_any_of ("-"));

      if (vals.size () >= 2)
      {
        const std::size_t          beg = std::min< size_t > (boost::lexical_cast< std::size_t, std::string > (vals[0]), prop->vals_.size () - 1);
        std::vector< std::string > vals_after;

        boost::algorithm::split (vals_after, vals[1], boost::is_any_of (","));

        if (vals_after.size () >= 2)
        {
          const std::size_t  end = std::min< size_t > (boost::lexical_cast< std::size_t, std::string > (vals_after[0]), prop->vals_.size ());
          const std::int16_t hue = boost::lexical_cast< std::int16_t, std::string > (vals_after[1]);

          for (std::size_t indx = beg; indx < end; ++indx)
          {
            prop->vals_[indx] = hue;
          }
        }
      }
    }

    ++param;
  }
}


void
GradientProp::load_layer (const std::string& vals, ChannelGradient* prop)
{
  // TODO
}


void
GradientProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GradientProp > (src);
  super::copy_int (src);
  channels_ = dsrc->channels_;
}


template< class Archive >
void
GradientProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (channels_);

  self_correct ();
}

}   // namespace libs::ievents::props::videos::generic::gradient

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::gradient::GradientProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::gradient::GradientProp);
