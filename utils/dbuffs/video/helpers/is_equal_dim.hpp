#pragma once
/**
\file       is_equal_dim.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief
*/

namespace utils { namespace dbuffs { namespace video { namespace helpers {

inline bool
is_equal_dim (const IVideoBuff& _isrc2, const IVideoBuff& _isrc1)
{
  const bool _width_equal  = _isrc2.get_dim_var (TypeDimVar::width) == _isrc1.get_dim_var (TypeDimVar::width) ? true : false;
  const bool _height_equal = _isrc2.get_dim_var (TypeDimVar::height) == _isrc1.get_dim_var (TypeDimVar::height) ? true : false;

  return _width_equal && _height_equal && _isrc2.get_dim_var (TypeDimVar::stride) == _isrc1.get_dim_var (TypeDimVar::stride);
}

}}}}      // namespace utils::dbuffs::video::helpers
