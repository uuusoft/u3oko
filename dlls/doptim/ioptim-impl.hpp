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
  \brief  Реализация библиотеки по хранению различных оптимизированных версий различных алгоритмов обработки данных.
  */
class IOptimImpl : public ::libs::optim::io::IOptim
{
  public:
  //  ext types
  typedef std::unordered_map<std::string, IOptimAlg::ptr> str2functs_type;
  typedef std::mutex                                      sync_type;
  typedef std::lock_guard<sync_type>                      guard_type;

  IOptimImpl ();

  virtual ~IOptimImpl ();

  //  ::libs::optim::io::IOptim overrides
  virtual ::libs::optim::io::hioptim get (const ::libs::optim::io::qoptim& _query) override;
  virtual void                       update (const ::libs::optim::io::TInit& _iinfo) override;


  private:
  void construct ();

  str2functs_type algs_;      /// ???
  sync_type       mtx_;       /// ???
};

}}}      // namespace dlls::doptim::impl
