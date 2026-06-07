#pragma once
/**
\file       loader-code.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::loader
{
/// Загрузчик кода в пространство процесса. В зависимости от параметров или в отдельный процесс, или в текущий
class LoaderCode final
{
  public:
  LoaderCode () = default;
  ~LoaderCode ();

  /// Функция загрузки кода
  /// \param[in]  type       тип загрузки
  /// \param[in]  info       общая информация о параметрах
  /// \param[in]  name_proc  имя процесса
  /// \param[in]  name_lib   имя библиотеки
  /// \param[in]  args       аргументы
  /// \param[in]  cntx
  void load (
    const ::libs::link::details::CodeRuns& type,
    const ::libs::link::CreateInfo*        info,
    const std::string&                     name_proc,
    const std::string&                     name_lib,
    const std::vector< std::string >&      args);

  /// Функция проверки успешности загруженности кода в процесс
  /// \return true, если загрузка прошла успешно
  bool is_load () const;

  /// Функция выгрузки кода из процесса
  /// \param[in]  force  флаг принудительной (безусловной) выгрузки кода
  /// \return true, если выгрузка прошла успешно
  bool unload (bool force);

  private:
  ILoaderCodeImpl::uniq_ptr impl_;   //< Реализация, выбранная в зависимости от способа загрузки кода относительно процесса
};
}   // namespace libs::ilink::loader
