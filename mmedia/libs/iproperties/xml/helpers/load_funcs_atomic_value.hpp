#pragma once
/**
\file       load_funcs_atomic_value.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
\brief      Набор свободных функций для загрузки примитивных типов из узла xml
*/

// EAI-REFACT
namespace libs::iproperties::xml::helpers
{
inline std::string
get_node_name (const ::pugi::xml_named_node_iterator& param)
{
  pugi::xml_attribute name_param = param->attribute ("name");
  if (!name_param)
  {
    return "";
  }
  return name_param.as_string ();
}


inline bool
load_generic (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  pugi::xml_attribute&                   val_param)
{
  const std::string name_node = get_node_name (param);
  if ("" == name_node)
  {
    return false;
  }

  val_param = param->attribute ("val");

  if (!val_param)
  {
    return false;
  }

  if (id != name_node)
  {
    return false;
  }
  return true;
}


template< typename TTVal >
bool
load (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  TTVal&                                 val)
{
  U3_THROW_EXCEPTION ("try load bad type from xml");
}


template<>
inline bool
load< bool > (const ::pugi::xml_named_node_iterator& param, const std::string& id, bool& val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_bool ();
  return true;
}


template<>
inline bool
load< std::string > (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  std::string&                           val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_string ();
  return true;
}


template<>
inline bool
load< float > (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  float&                                 val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_float ();
  return true;
}


template<>
inline bool
load< int > (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  std::int32_t&                          val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_int ();
  return true;
}


template<>
inline bool
load< std::uint32_t > (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  std::uint32_t&                         val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_uint ();
  return true;
}


template<>
inline bool
load< std::uint64_t > (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  std::uint64_t&                         val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_uint ();
  return true;
}


template<>
inline bool
load< long long > (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  long long&                             val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_int ();
  return true;
}


template<>
inline bool
load< std::uint16_t > (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  std::uint16_t&                         val)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  val = val_param.as_uint ();
  return true;
}

using loader_func_type = std::function< void (const std::string&) >;

inline bool
load (
  const ::pugi::xml_named_node_iterator& param,
  const std::string&                     id,
  const loader_func_type&                loader)
{
  pugi::xml_attribute val_param;
  if (!load_generic (param, id, val_param))
  {
    return false;
  }

  loader (val_param.as_string ());
  return true;
}
}   // namespace libs::iproperties::xml::helpers
