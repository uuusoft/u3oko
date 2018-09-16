#pragma once
/**
\file       u3oko-appl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    u3oko
\brief      empty brief
*/

namespace appls { namespace u3oko { namespace appl {
/**
\brief  Реализация модуля приложения для тестирования производительности системы.
*/
class U3OkoAppl final : public ::libs::ilink::appl::root::RootModule
{
  public:
  U3OkoAppl ();

  virtual ~U3OkoAppl ();


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::root::RootModule);

  //  ::libs::ilink::appl::root::RootModule override
  virtual void            init_int (const ::libs::link::appl::InitApplication& _info) override;
  virtual void            init_links_int (const ::libs::link::appl::InitApplication& _info) override;
  virtual void            update_catch_functs_int () override;
  virtual bool            deinit_int () override;
  virtual recv_links_type get_recv_link () override;

  std::size_t count_cycles_;      //< ???
};

}}}      // namespace appls::u3oko::appl
