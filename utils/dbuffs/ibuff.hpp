#pragma once
/**
\file       ibuff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление интерфейса выделения буфера в ОЗУ под кадр.
*/

namespace utils { namespace dbuffs {
/**
\brief  Базовый интерфейс хранения буфера в ОЗУ под кадр (звук/видео).
*/
class IBuff
{
  public:
  //  ext types
  using mem_type = int;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IBuff);

  virtual ~IBuff ()
  {}

  IBuff (const IBuff& _rsc) = delete;
  IBuff& operator= (const IBuff& _src) = delete;
  /**
  \brief      Функция установки значения переменной, для описания данные с точки зрения используемой памяти.
  \param[in]  _type тип переменной.
  \param[in]  _val  значение переменной.
  */
  void
  set_mem_var (const TypeMemVar& _type, mem_type _val)
  {
    return set_mem_var_int (_type, _val);
  }
  /**
  \brief      Функция получения значения переменной для описания данные с точки зрения используемой памяти.
  \param[in]  _type тип переменной.
  \return     значение переменной.
  */
  mem_type
  operator[] (const TypeMemVar& _type) const
  {
    return get_mem_var_int (_type);
  }
  /**
  \brief      Функция клонирования буфера.
  \param[in]  _source   источник данных.
  \param[in]  _perc_copy  проценты копирования по вертикали [0.0f..100.0f].
  \return   .
  */
  void
  clone (IBuff::ptr& _source, float _perc_copy)
  {
    return clone_int (_source.get (), _perc_copy);
  }
  /**
  \brief      Функция клонирования буфера.
  \param[in]  _source   источник данных.
  \param[in]  _perc_copy  проценты копирования по вертикали [0.0f..100.0f].
  \return   .
  */
  void
  clone (IBuff::craw_ptr _source, float _perc_copy)
  {
    return clone_int (_source, _perc_copy);
  }
  /**
  \brief      Функция обмена содержимого буферов.
  \param[in]  _buff буфер обмена.
  */
  void
  swap (IBuff& _buff)
  {
    return swap_int (_buff);
  }
  /**
  \brief    Функция получения буфера.
  \return   буфер.
  */
  unsigned char*
  get_buff ()
  {
    return get_buff_int ();
  }
  /**
  \brief    Функция получения константного буфера.
  \return   буфер.
  */
  const unsigned char*
  get_cbuff () const
  {
    return get_cbuff_int ();
  }


  protected:
  IBuff ()
  {}


  private:
  //  IBuff interface
  virtual void                 set_mem_var_int (const TypeMemVar& _type, mem_type _val) = 0;
  virtual mem_type             get_mem_var_int (const TypeMemVar& _type) const          = 0;
  virtual unsigned char*       get_buff_int ()                                          = 0;
  virtual const unsigned char* get_cbuff_int () const                                   = 0;
  virtual void                 clone_int (IBuff::craw_ptr source, float _perc_copy)     = 0;
  virtual void                 swap_int (IBuff& _buff)                                  = 0;
};

}}      // namespace utils::dbuffs
