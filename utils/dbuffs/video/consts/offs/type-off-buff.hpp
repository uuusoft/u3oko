//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-off-buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief
*/

namespace utils { namespace dbuffs { namespace video { namespace consts { namespace offs {

class off_buff_typeBase;
/// Тип-индекс для определения назначения буфера.
//using ::libs::helpers::utils::Int2Type<int, ::libs::helpers::consts::iinvalid, off_buff_typeBase>       off_buff_type;

}}}}}      // namespace utils::dbuffs::video::consts::offs

#if 0
namespace std
{

  template<> struct hash<::utils::dbuffs::video::consts::offs::off_buff_type>
  {
    using ::utils::dbuffs::video::consts::offs::off_buff_type argument_type;
    using std::size_t result_type;

    result_type operator()( argument_type const& _s ) const noexcept
    {
      return static_cast<result_type>(_s.to_val());
    }
  };

}

#endif
