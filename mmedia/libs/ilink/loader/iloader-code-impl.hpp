#pragma once
/**
\file       iloader-code-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/

namespace libs::ilink::loader
{
/// Загрузчик кода в пространство процесса
/// В зависимости от параметров или в отдельный процесс, или в текущий
class ILoaderCodeImpl
{
  public:
  // ext types
  using args_type = std::vector< std::string >;

  U3_ADD_POINTERS_TO_SELF (ILoaderCodeImpl)

  virtual ~ILoaderCodeImpl () = default;

  /// Функция загрузки кода (dll) в процесс
  /// \param[in]  info       общая информация о параметрах
  /// \param[in]  name_proc  имя процесса
  /// \param[in]  name_lib   имя библиотеки
  /// \param[in]  args       аргументы
  /// \param[in]  cntx
  void
  load (
    const ::libs::link::CreateInfo* info,
    const std::string&              name_proc,
    const std::string&              name_lib,
    const args_type&                args)
  {
    load_int (info, name_proc, name_lib, args);
  }

  bool
  is_load () const
  {
    return is_load_int ();
  }

  bool
  unload (bool force)
  {
    return unload_int (force);
  }

  protected:
  ILoaderCodeImpl ()
  {
  }

  private:
  //  ILoaderCodeImpl interface
  virtual void load_int (const ::libs::link::CreateInfo*, const std::string&, const std::string&, const args_type&) = 0;
  virtual bool is_load_int () const                                                                                 = 0;
  virtual bool unload_int (bool)                                                                                    = 0;
};
}   // namespace libs::ilink::loader
