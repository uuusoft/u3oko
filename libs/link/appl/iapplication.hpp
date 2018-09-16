#pragma once
/**
\file       iapplication.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace appl {
/**
\brief  Интерфейс, который должен поддерживать любой модуль (приложение, htpp, data storage, net, data process etc).
*/
class IApplication
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IApplication);

  IApplication ();

  virtual ~IApplication ();

  IApplication (const IApplication& _src) = delete;
  IApplication& operator= (const IApplication& _src) = delete;
  /**
  \brief      Функция конструирования объекта модуля. По завершению вызова модуль считается готовым к работе.
  \param[in]  _info информация, переданная при создании модуля.
  */
  void ainit (const InitApplication& _info);
  /**
  \brief    Функция рабочего цикла модуля. Вызывается в отдельном потоке.
  */
  void work ();
  /**
  \brief    Функция удаления объекта модуля. По завершению вызова модуль считается готовым к удалению из памяти.
  \return   true, если функция полностью удалила модуль, иначе требуется повторной вызов.
  */
  bool deinit ();
  /**
  \brief    Функция принудительного завершение работы модуля в исключительных ситуациях, например по сигналу Ctlr+C.
  */
  void force_stop ();


  protected:
  /**
  \brief      Функция дополнительное инициализации модуля. Вызывается один раз, при его создании.
  \param[in]  _info информация, переданная при создании модуля.
  */
  virtual void init_int (const InitApplication& _info) = 0;
  /**
  \brief      Функция инициализации связей модуля. Вызывается один раз.
  \param[in]  _info информация, переданная при создании модуля.
  */
  virtual void init_links_int (const InitApplication& _info) = 0;
  /**
  \brief  Функция инициализации рабочих путей модуля.
  */
  virtual void init_appl_folders_int () = 0;
  /**
  \brief  Функция инициализации различных прокси-объектов.
  */
  virtual void init_proxys_int () = 0;
  /**
  \brief  Функция инициализации данных модуля.
  */
  virtual void init_appl_data_int () = 0;
  /**
  \brief  Функция завершения инициализации.
  */
  virtual void init_done_int () = 0;
  /**
  \brief  Функция рабочего цикла модуля в отдельном потоке.
  */
  virtual void work_int () = 0;
  /**
  \brief  Функция завершения рабочего цикла модуля.
  */
  virtual bool deinit_int () = 0;
  /**
  \brief  Функция обновления обработчиков событий в данном модуле.
  */
  virtual void update_catch_functs_int () = 0;

  virtual void force_stop_int () = 0;


  private:
  bool init_;      //< Флаг инициализации объекта.
};

}}}      // namespace libs::link::appl
