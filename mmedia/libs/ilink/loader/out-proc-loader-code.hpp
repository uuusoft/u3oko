#pragma once
/**
\file       out-proc-loader-code.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/

namespace libs::ilink::loader
{
/// Загрузчик кода в пространство процесса
class OutProcLoaderCode final : public ILoaderCodeImpl
{
  public:
  OutProcLoaderCode ();
  ~OutProcLoaderCode ();

  private:
  //  internal typess
  using iappl_uptr_type = std::unique_ptr< ::libs::link::appl::IApplicationProxy >;

  //  ILoaderCodeImpl
  virtual void load_int (const ::libs::link::CreateInfo*, const std::string&, const std::string&, const args_type&) override;
  virtual bool is_load_int () const override;
  virtual bool unload_int (bool force) override;

  /// Вспомогательная функция, для установки имени библиотеки с кодом
  /// Выделена в отдельный код для проверок
  /// \param[in]  name_lib имя библиотеки
  void set_name_lib (const std::string& name_lib);

  const ::libs::link::CreateInfo* info_;       //< Данные объекта при создании
  std::string                     lib_name_;   //< Имя библиотеки с кодом объекта
};
}   // namespace libs::ilink::loader
