//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ivideo-buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление интерфейса выделения буфера под видеокадр.
*/

namespace utils { namespace dbuffs { namespace video {
//  syn
using ::libs::helpers::utils::cuuid;
/**
  \brief  Уточненние интерфейса для управления буфером с видео данными.
  */
class IVideoBuff : public IMemBuff
{
  public:
  //  ext types
  using dim_type = AllocBuffInfo::dim_type;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IVideoBuff);
  /**
    \brief      Тип функции проверки буфера. Сама функция задается пользователем и в общем случае не определена.
    \param[in]  _x    позиция пикселя по горизонтали.
    \param[in]  _y    позиция пикселя по вертикали.
    \param[in]  _val  значение пикселя.
    */
  using check_funct_type = boost::function<bool(dim_type _x, dim_type _y, short _val)>;
  /// Открытый деструктор базового класса, т.е. пользователь может удалять такие объекты полиморфно.
  virtual ~IVideoBuff ()
  {}
  /**
    \brief      Функция установки формата пикселя в буфере.
    \param[in]  _id формат пикселей.
    */
  void
  set_format (const cuuid& _id)
  {
    return set_format_int (_id);
  }
  /**
    \brief    Функция получения  формата пикселя в буфере.
    \return   формат пикселей.
    */
  const cuuid&
  get_format () const
  {
    return get_format_int ();
  }
  /**
    \brief      Функция установки значения переменной геометрии кадра.
    \param[in]  _type тип переменной.
    \param[in]  _val  значение переменной.
    */
  void
  set_dim_var (const TypeDimVar& _type, dim_type _val)
  {
    return set_dim_var_int (_type, _val);
  }
  /**
    \brief      Функция получения значения переменной геометрии кадра.
    \param[in]  _type тип переменной.
    \return     значение переменной.
    */
  dim_type
  get_dim_var (const TypeDimVar& _type) const
  {
    return get_dim_var_int (_type);
  }
  /**
    \brief      Функция установки значения признака к кадру в целом.
    \param[in]  _type тип признака.
    \param[in]  _val  значение признака.
    */
  void
  set_flag (const TypeFlagsBuff& _type, bool _val)
  {
    return set_flag_int (_type, _val);
  }
  /**
    \brief      Функция получения значения признака к кадру в целом.
    \param[in]  _type тип признака.
    \return     значение признака.
    */
  bool
  get_flag (const TypeFlagsBuff& _type) const
  {
    return get_flag_int (_type);
  }
  /**
    \brief      Функция переразмещения буфера.
    \param[in]  _info параметры переразмещения.
    */
  void
  balloc (const AllocBuffInfo& _info)
  {
    return balloc_int (_info);
  }
  /// Функция сброса буфера в значение по умолчанию.
  void
  flush ()
  {
    return flush_int ();
  }
  /**
    \brief      Функция тестирования буфера с помощью специализированной функции.
    \param[in]  _obj  функция тестирования.
    \return     true, при успехе, иначе false.
    */
  bool
  check (const check_funct_type& _obj) const
  {
    return check_int (_obj);
  }


  protected:
  /// Защищенный конструктор базового класса, т.е. объекты этого типа не могут существовать и тип предназначен для наследования.
  IVideoBuff ()
  {}


  private:
  //  IVideoBuff interface
  virtual void         set_format_int (const cuuid& _id)                        = 0;
  virtual const cuuid& get_format_int () const                                  = 0;
  virtual void         set_dim_var_int (const TypeDimVar& _type, dim_type _val) = 0;
  virtual dim_type     get_dim_var_int (const TypeDimVar& _type) const          = 0;
  virtual void         set_flag_int (const TypeFlagsBuff& _type, bool _val)     = 0;
  virtual bool         get_flag_int (const TypeFlagsBuff& _type) const          = 0;
  virtual void         balloc_int (const AllocBuffInfo& _info)                  = 0;
  virtual void         flush_int ()                                             = 0;
  virtual bool         check_int (const check_funct_type& _obj) const           = 0;
};

}}}      // namespace utils::dbuffs::video
