#pragma once
/**
\file       create-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link {
/**
  \brief  Структура для группировки информации для создания реализации "связь" между модулями.
  */
struct CreateInfo
{
  //  ext types
  using ids2vals_type = std::map<std::string, std::string>;
  /// Конструктор по умолчанию для контейнеров и композиции в другом типе.
  CreateInfo ();
  /**
    \brief      Рабочий конструктор.
    \param[in]  _run_as                 тип компоновки кода (в отдельном процессе, в текущем процесса etc).
    \param[in]  _name_proc              ???
    \param[in]  _name_lib               имя модуля с кодом.
    \param[in]  _company_name           наименование компании???
    \param[in]  _appl_name              наименование приложения.
    \param[in]  _subsys_name            наименования модуля.
    \param[in]  _type                   тип связи по конечным модулям.
    \param[in]  _size_shared_mem_bytes  размер буфера данных связи.
    */
  CreateInfo (
    const details::TypeRunCode&     _run_as,
    const std::string&              _name_proc,
    const std::string&              _name_lib,
    const std::string&              _company_name,
    const std::string&              _appl_name,
    const std::string&              _subsys_name,
    const details::TypeLinkModules& _type,
    int                             _size_shared_mem_bytes);

  ~CreateInfo ();

  void check () const;

  std::string make_arg (const std::string& _id, const std::string& _val);

  std::string get_prefix () const;

  bool operator< (const CreateInfo& _op) const;

  bool operator== (const CreateInfo& _op) const;

  details::TypeRunCode     run_as_;                     //< Тип требуемого запуска (dll/exe/etc).
  std::vector<std::string> args_;                       //< Аргументы запуска.
  details::TypeLinkModules pt2pt_;                      //< Тип канала. Определяет конечные точки канала (основной модуль/http/data/onvif/storage/gui/etc).
  int                      size_shared_mem_bytes_;      //< Макисмальный размер разделяемой памяти для канала.
  mutable ids2vals_type    id2val_;                     //< ???
};


inline std::string
to_str (const CreateInfo& _val)
{
  std::string _res;
  _res += "CreateInfo[" + to_str (_val.run_as_) + " " + to_str (_val.pt2pt_) + " " + ::to_str (_val.size_shared_mem_bytes_) + "]";
  return _res;
}

}}      // namespace libs::link
