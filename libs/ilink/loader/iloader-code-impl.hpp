//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       iloader-code-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace loader {
/**
  \brief  Загрузчик кода в пространство процесса.
          В зависимости от параметров или в отдельный процесс, или в текущий.
  */
class ILoaderCodeImpl
{
  public:
  // ext types
  using args_type = std::vector<std::string>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ILoaderCodeImpl);

  virtual ~ILoaderCodeImpl ()
  {}
  /**
    \brief      Функция загрузки кода.
    \param[in]  _info       общая информация о параметрах.
    \param[in]  _name_proc  имя процесса.
    \param[in]  _name_lib   имя библиотеки.
    \param[in]  _args       аргументы
    \param[in]  _cntx   
    */
  void
  load (
    const CreateInfo*  _info,
    const std::string& _name_proc,
    const std::string& _name_lib,
    const args_type&   _args)
  {
    XULOG_INFO ("ILoaderCodeImpl: beg, " << _name_proc << ", " << _name_lib);
    load_int (_info, _name_proc, _name_lib, _args);
    XULOG_INFO ("ILoaderCodeImpl: end");
    return;
  }

  bool
  is_load () const
  {
    return is_load_int ();
  }

  bool
  unload (bool _force)
  {
    return unload_int (_force);
  }


  protected:
  ILoaderCodeImpl ()
  {}


  private:
  virtual void load_int (const CreateInfo* _info, const std::string& _name_proc, const std::string& _name_lib, const args_type& _args) = 0;
  virtual bool is_load_int () const                                                                                                    = 0;
  virtual bool unload_int (bool _force)                                                                                                = 0;
};

}}}      // namespace libs::ilink::loader
