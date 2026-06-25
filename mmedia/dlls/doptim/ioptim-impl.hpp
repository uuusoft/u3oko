#pragma once
/**
\file       ioptim-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl
{
/// Реализация модуля по работе с различными оптимизированнами версиями алгоритмов обработки данных
class IOptimImpl final : public ::libs::optim::io::IOptim
{
  public:
  //  ext types
  using str2funcs_type = std::unordered_map< std::string, IOptimAlg::ptr >;
  using sync_type      = std::mutex;
  using lock_type      = std::scoped_lock< sync_type >;

  IOptimImpl ();
  virtual ~IOptimImpl () = default;

  //  ::libs::optim::io::IOptim overrides
  virtual ::libs::optim::io::hioptim get (const ::libs::optim::io::qoptim& query) override;
  virtual void                       sync_impl (const ::libs::optim::io::TInit& iinfo) override;

  private:
  void construct ();

  template< typename TTAlg >
  void
  add_alg ()
  {
    const auto& key = TTAlg::val_key;
    U3_ASSERT (algs_.end () == algs_.find (key));
    algs_.insert (str2funcs_type::value_type (key, std::make_shared< TTAlg > ()));
  }

  str2funcs_type algs_;   //< Массив для быстрого поиска алгоритма по строке
  sync_type      mtx_;    //< Синхронизирующий примитив
};
}   // namespace dlls::doptim::impl
