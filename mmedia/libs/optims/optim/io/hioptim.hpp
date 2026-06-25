#pragma once
/**
\file       hioptim.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::io
{
/// Структура для хранения параметров и функции алгоритма для работы в рабочем потоке
class hioptim final
{
  public:
  //  ext types
  using func_type = std::atomic< ::libs::optim::io::mtcall_func >;

  explicit hioptim (
    func_type*    pfunct        = nullptr,
    std::uint32_t block_align_x = 1,
    std::uint32_t block_align_y = 1) :
    pfunc_ (pfunct),
    block_align_x_ (block_align_x),
    block_align_y_ (block_align_y)
  {
  }

  ~hioptim () = default;

  bool
  self_test () const
  {
    return pfunc_ ? true : false;
  }

  ::libs::optim::io::mtcall_func
  get () const
  {
    U3_ASSERT (self_test ());
    const ::libs::optim::io::mtcall_func ret = pfunc_->load ();
    return ret;
  }

  void
  set (::libs::optim::io::mtcall_func pfunct)
  {
    U3_ASSERT (self_test ());
    pfunc_->store (pfunct);
  }

  void
  set_algoritm_name (const std::string& id)
  {
    U3_ASSERT (!id.empty ());
    id_func_ = id;
  }

  std::string
  get_algoritm_name () const
  {
    U3_ASSERT (!id_func_.empty ());
    return id_func_;
  }

  std::uint32_t
  get_block_align_x () const
  {
    return block_align_x_;
  }

  void
  set_block_align_x (std::uint32_t val)
  {
    block_align_x_ = val;
  }

  std::uint32_t
  get_block_align_y () const
  {
    return block_align_y_;
  }

  void
  set_block_align_y (std::uint32_t val)
  {
    block_align_y_ = val;
  }

  private:
  func_type*    pfunc_         = nullptr;         //< Указатель на функцию
  std::uint32_t block_align_x_ = 1;               //< Выравнение блока по оси X
  std::uint32_t block_align_y_ = 1;               //< Выравнение блока по оси Y
  std::string   id_func_       = "unknown alg";   //< Текстовый идентификатор алгоритма функции
};
}   // namespace libs::optim::io
