//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       out-proc-loader-code.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace loader {
/**
  \brief  Загрузчик кода в пространство процесса.
  */
class OutProcLoaderCode : public ILoaderCodeImpl
{
  public:
  OutProcLoaderCode ();

  ~OutProcLoaderCode ();


  private:
  //  int types
  using iappl_uptr_type = std::unique_ptr<::libs::link::appl::IApplicationProxy>;

  //  ILoaderCodeImpl
  virtual void load_int (const CreateInfo* _info, const std::string& _name_proc, const std::string& _name_lib, const args_type& _args) override;
  virtual bool is_load_int () const override;
  virtual bool unload_int (bool _force) override;
  /**
    \brief      Вспомогательная функция, для установки имени библиотеки с кодом.
                Выделена в отдельный код для проверок.
    \param[in]  _name_lib имя библиотеки.
    */
  void set_name_lib (const std::string& _name_lib);

  const CreateInfo* info_;          //< Информация, использовання при создании объекта типа.
  std::string       name_lib_;      //< Имя библиотеки, содержащей загружаемый код.
};

}}}      // namespace libs::ilink::loader
