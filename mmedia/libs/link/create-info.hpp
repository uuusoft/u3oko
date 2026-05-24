#pragma once
/**
\file       create-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_link
*/

namespace libs::link
{
/// Структура для группировки информации для создания реализации "связь" между модулями
struct CreateInfo {
  //  ext types
  using ids2vals_type = std::unordered_map< std::string, std::string >;
  /// Конструктор по умолчанию для контейнеров и композиции в другом типе
  CreateInfo ();
  /// EAI-REFACT
  /// \brief      Рабочий конструктор
  /// \param[in]  run_as                 тип компоновки кода (в отдельном процессе, в текущем процесса etc)
  /// \param[in]  name_proc              DEFINE
  /// \param[in]  name_lib               имя модуля с кодом
  /// \param[in]  company_name           наименование компании
  /// \param[in]  appl_name              наименование приложения
  /// \param[in]  subsys_name            наименования модуля
  /// \param[in]  type                   тип связи по конечным модулям
  /// \param[in]  size_shared_mem_bytes  размер буфера данных связи
  CreateInfo (
    const details::CodeRuns&    run_as,
    const std::string&          name_proc,
    const std::string&          name_lib,
    const std::string&          company_name,
    const std::string&          appl_name,
    const std::string&          subsys_name,
    const details::ModuleLinks& type,
    std::int32_t                size_shared_mem_bytes);

  virtual ~CreateInfo ();

  void        check () const;
  std::string make_arg (const std::string&, const std::string&);
  std::string get_prefix () const;

  bool operator< (const CreateInfo&) const;
  bool operator== (const CreateInfo&) const;

  details::CodeRuns          run_as_;                  //< Тип требуемого запуска (dll/exe/etc)
  std::vector< std::string > args_;                    //< Аргументы запуска
  details::ModuleLinks       pt2pt_;                   //< Тип канала. Определяет конечные точки канала (основной модуль/http/data/onvif/storage/gui/etc)
  std::int32_t               size_shared_mem_bytes_;   //< Макисмальный размер разделяемой памяти для канала
  mutable ids2vals_type      id_arg2val_;              //<
};

std::string to_string (const CreateInfo& val);
}   // namespace libs::link
