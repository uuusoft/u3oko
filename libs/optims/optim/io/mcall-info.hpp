#pragma once
/**
\file       mcall-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace io {
/**
  \brief  Структрура для группировки параметров, которые передаются функции при вызове в рабочем потоке.
  */
struct MCallInfo
{
  //  ext types
  typedef std::vector<ProxyBuff> sources_type;
  typedef std::vector<ProxyBuff> dests_type;

  MCallInfo () :
    indx_thread_ (0),
    count_threads_ (0),
    //psrc_heights_(0),
    full_height_src_ (0),
    full_height_dst_ (0)
  {
    srcs_.reserve (4);
    dsts_.reserve (4);
  }
#if 0
  explicit MCallInfo (const ProxyBuff& _pdst) :
    indx_thread_ (0),
    count_threads_ (0),
    full_height_src_ (0),
    full_height_dst_ (0)
  {
    srcs_.reserve (4);
    dsts_.reserve (4);

    if (_pdst.self_test ())
      {
        dsts_.push_back (_pdst);
      }
  }
#endif
  ~MCallInfo ()
  {}

  std::size_t  indx_thread_;          //< Индекс потока, которому принадлежит данная копия структуры.
  std::size_t  count_threads_;        //< Количество рабочих потоков, используемых при данном вызове.
  std::size_t  full_height_src_;      //< Полная высота буфера источника, не может быть получена простым перемножением количества потоков на высоту части, т.к. высоты разные.
  std::size_t  full_height_dst_;      //< Полная высота буфера назначения, не может быть получена простым перемножением количества потоков на высоту части, т.к. высоты разные.
  sources_type srcs_;                 //< Список буферов-источников данного потока.
  dests_type   dsts_;                 //< Список буферов-назначений данного потока.
  MFunctParams params_;               //< Дополнительные параметры к потоку.
};
/**
  \brief  Тип функции для вызова алгоритма в рабочем потоке.
  */
typedef void (*funct_mcall_type) (MCallInfo& _info);

}}}      // namespace libs::optim::io
