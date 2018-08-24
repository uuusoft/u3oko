#pragma once
/**
\file       loader-code.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace loader {
/**
  \brief  Загрузчик кода в пространство процесса.
          В зависимости от параметров или в отдельный процесс, или в текущий.
  */
class LoaderCode
{
  public:
  LoaderCode ();

  ~LoaderCode ();
  /**
    \brief      Функция загрузки кода.
    \param[in]  _type       тип загрузки.  
    \param[in]  _info       общая информация о параметрах.
    \param[in]  _name_proc  имя процесса.
    \param[in]  _name_lib   имя библиотеки.
    \param[in]  _args       аргументы
    \param[in]  _cntx   
    */
  void load (
    const TypeRunCode&              _type,
    const CreateInfo*               _info,
    const std::string&              _name_proc,
    const std::string&              _name_lib,
    const std::vector<std::string>& _args);
  /**
    \brief 
    */
  bool is_load () const;
  /**
    \brief 
    */
  bool unload (bool _force);


  private:
  ILoaderCodeImpl::uniq_ptr impl_;      //< Реализация, выбранная в зависимости от способа загрузки кода относительно процесса.
};

}}}      // namespace libs::ilink::loader
