#pragma once
/**
\file       load_functs_atomic_value.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Набор свободных функций для загрузки примитивных типов из узла xml.
*/

namespace libs { namespace icore { namespace xml { namespace helpers {

inline std::string
get_node_name (const base_functs::xml::itn& _param)
{
  pugi::xml_attribute _name_param = _param->attribute ("name");
  if (!_name_param)
    {
      return "";
    }
  return _name_param.as_string ();
}


inline bool
load_generic (const base_functs::xml::itn& _param, const std::string& _id, pugi::xml_attribute& _val_param)
{
  const std::string _name_node = get_node_name (_param);
  if ("" == _name_node)
    {
      return false;
    }

  _val_param = _param->attribute ("val");

  if (!_val_param)
    {
      return false;
    }
  if (_id != _name_node)
    {
      return false;
    }
  return true;
}


template <typename TTVal>
bool
load (const base_functs::xml::itn& _param, const std::string& _id, TTVal& _val)
{
  UUU_THROW_EXCEPTION ("try load bad type from xml");
}


template <>
inline bool
load<bool> (const base_functs::xml::itn& _param, const std::string& _id, bool& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_bool ();
  return true;
}


template <>
inline bool
load<std::string> (const base_functs::xml::itn& _param, const std::string& _id, std::string& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_string ();
  return true;
}


template <>
inline bool
load<float> (const base_functs::xml::itn& _param, const std::string& _id, float& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_float ();
  return true;
}


template <>
inline bool
load<int> (const base_functs::xml::itn& _param, const std::string& _id, int& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_int ();
  return true;
}


template <>
inline bool
load<unsigned int> (const base_functs::xml::itn& _param, const std::string& _id, unsigned int& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_uint ();
  return true;
}


template <>
inline bool
load<unsigned long long> (const base_functs::xml::itn& _param, const std::string& _id, unsigned long long& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_uint ();
  return true;
}


template <>
inline bool
load<long long> (const base_functs::xml::itn& _param, const std::string& _id, long long& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_int ();
  return true;
}


template <>
inline bool
load<unsigned short> (const base_functs::xml::itn& _param, const std::string& _id, unsigned short& _val)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _val = _val_param.as_uint ();
  return true;
}

using loader_funct_type = std::function<void(const std::string&)>;

inline bool
load (const base_functs::xml::itn& _param, const std::string& _id, const loader_funct_type& _loader)
{
  pugi::xml_attribute _val_param;
  if (!load_generic (_param, _id, _val_param))
    {
      return false;
    }

  _loader (_val_param.as_string ());
  return true;
}

}}}}      // namespace libs::icore::xml::helpers
