#pragma once
/**
\file       in-proc-loader-code.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/

namespace libs::ilink::loader
{
/// Загрузчик кода в пространство процесса
class InProcLoaderCode final : public ILoaderCodeImpl
{
  public:
  InProcLoaderCode ();
  ~InProcLoaderCode ();

  void thread_func_impl (std::uint32_t);
  void thread_postfunc_impl (std::uint32_t);

  private:
  //  internal typess
  using iappl_uptr_type = std::unique_ptr< ::libs::link::appl::IApplicationProxy >;

  //  ILoaderCodeImpl overrides
  virtual bool is_load_int () const override;
  virtual bool unload_int (bool force) override;
  virtual void load_int (const syn::CreateInfo*, const std::string&, const std::string&) override;

  /// Вспомогательная функция, для установки имени библиотеки с кодом
  /// Выделена в отдельный код для проверок
  /// \param[in]  name_lib имя библиотеки
  void set_name_lib (const std::string& name_lib);

  const syn::CreateInfo* info_ = nullptr;   //< Информация, использовання при создании объекта типа
  std::thread            child_thread_;     //< Рабочий поток испольнения кода для текущего процесса
  iappl_uptr_type        thread_appl_;      //< Прокси для доступа к функциям загруженного кода
  std::string            lib_name_;         //< Имя библиотеки, содержащей загружаемый код
  std::atomic_bool       thread_done_;      //< Флаг инициализации рабочего потока для теущего процесса
};
}   // namespace libs::ilink::loader
