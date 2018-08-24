//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       in-proc-loader-code.hpp
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
class InProcLoaderCode : public ILoaderCodeImpl
{
  public:
  InProcLoaderCode ();

  ~InProcLoaderCode ();

  void thread_funct_impl (std::size_t _indx_thread);

  void thread_postfunct_impl ();


  private:
  //  int types
  using iappl_uptr_type = std::unique_ptr<::libs::link::appl::IApplicationProxy>;

  //  ILoaderCodeImpl
  virtual bool is_load_int () const override;
  virtual bool unload_int (bool _force) override;
  virtual void load_int (const CreateInfo* _info, const std::string& _name_proc, const std::string& _name_lib, const args_type& _args) override;
  /**
    \brief      Вспомогательная функция, для установки имени библиотеки с кодом.
                Выделена в отдельный код для проверок.
    \param[in]  _name_lib имя библиотеки.
    */
  void set_name_lib (const std::string& _name_lib);

  const CreateInfo* info_;              //< Информация, использовання при создании объекта типа.
  std::thread       child_thread_;      //< Рабочий поток испольнения кода для текущего процесса.
  iappl_uptr_type   thread_appl_;       //< ???
  std::string       name_lib_;          //< Имя библиотеки, содержащей загружаемый код.
  std::atomic_bool  thread_done_;       //< Флаг инициализации рабочего потока для теущего процесса.
};

}}}      // namespace libs::ilink::loader
