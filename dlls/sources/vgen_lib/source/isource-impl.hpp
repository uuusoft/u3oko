#pragma once
/**
\file       isource-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.06.2016.
\copyright  www.uuusoft.com
\project    uuu_gen_lib
\brief      Class for incapsulate acess to driver
*/

namespace dlls { namespace sources { namespace gen_lib {
/**
  \brief  Интерфейс, который должна поддерживать любая реализация захвата данных из устройства.
  */
class ISourceImpl
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ISourceImpl);

  ISourceImpl ();

  virtual ~ISourceImpl ();

  ISourceImpl (const ISourceImpl& _src) = delete;
  ISourceImpl& operator= (const ISourceImpl& _src) = delete;

  void init ();

  void start ();

  void stop ();

  void get_raw_data (keys2buffs_ptr_type& _buffs, transform_events_type* _events);

  void set_cpu (TypeExtCpu current_optim);

  void update_dinfo (const SourceInfo& _info);

  bool is_started ();


  protected:
  SourceInfo props_info_;      //< ???
  bool       started_;         //< Флаг запуска процесса захвата.
  TypeExtCpu simd_;            //< Используемое расширение CPU.


  private:
  // ISourceImpl
  virtual void init_int ()                                                                    = 0;
  virtual void start_int ()                                                                   = 0;
  virtual void stop_int ()                                                                    = 0;
  virtual void get_raw_data_int (keys2buffs_ptr_type& _buffs, transform_events_type* _events) = 0;
  virtual void set_cpu_int (TypeExtCpu current_optim)                                         = 0;
  virtual void update_dinfo_int (const SourceInfo& _info)                                     = 0;
  virtual bool is_started_int ();
};

}}}      // namespace dlls::sources::gen_lib
