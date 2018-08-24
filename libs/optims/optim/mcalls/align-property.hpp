//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       align-property.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace mcalls {
/**
  \brief  empty brief
  */
struct AlignProperty
{
  AlignProperty () :
    px_x_ (16), px_y_ (1)
  {}

  void
  reset ()
  {
    px_x_ = 16;
    px_y_ = 1;
    return;
  }

  bool
  self_test () const
  {
    return check_align (px_x_) && check_align (px_y_);
  }

  std::size_t px_x_;      //< Выравнивание  по горизонтали в пикселях для всех буферов.
  std::size_t px_y_;      //< Выравнивае по вертикали в пикселях для всех буферов.
};

}}}      // namespace libs::optim::mcalls
