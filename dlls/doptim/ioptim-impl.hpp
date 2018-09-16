#pragma once
/**
\file       ioptim-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      empty brief
*/

namespace dlls { namespace doptim { namespace impl {
/**
\brief  Реализация модуля по работе с различными оптимизированнами версиями алгоритмов обработки данных.
*/
class IOptimImpl : public ::libs::optim::io::IOptim
{
  public:
  //  ext types
  using str2functs_type = std::unordered_map<std::string, IOptimAlg::ptr>;
  using sync_type       = std::mutex;
  using guard_type      = std::lock_guard<sync_type>;

  IOptimImpl ();

  virtual ~IOptimImpl ();

  //  ::libs::optim::io::IOptim overrides
  virtual ::libs::optim::io::hioptim get (const ::libs::optim::io::qoptim& _query) override;
  virtual void                       update (const ::libs::optim::io::TInit& _iinfo) override;


  private:
  void construct ();

  str2functs_type algs_;      /// Массив для быстрого поиска алгоритма по строке.
  sync_type       mtx_;       /// Синхронизирующий примитив.
};

}}}      // namespace dlls::doptim::impl
