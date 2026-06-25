#pragma once
/**
\file       ivideo-buf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_dbufs
*/

namespace utils::dbufs::video
{
/// Уточненние интерфейса для управления буфером с видео данными
class IVideoBuf : public IMemBuf
{
  public:
  //  ext types
  using dim_type = AllocBufInfo::dim_type;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IVideoBuf)

  /// Тип функции проверки буфера Сама функция задается пользователем и в общем случае не определена
  /// \param[in]  x    позиция пикселя по горизонтали
  /// \param[in]  y    позиция пикселя по вертикали
  /// \param[in]  val  значение пикселя
  using check_func_type = std::function< bool (dim_type, dim_type, std::int16_t) >;

  /// Открытый деструктор базового класса, т.е пользователь может удалять такие объекты полиморфно
  virtual ~IVideoBuf () = default;

  /// Функция установки формата пикселя в буфере
  /// \param[in]  idv формат пикселей
  void
  set_format (const libs::helpers::uids::minor::id_val& idv)
  {
    std::scoped_lock lock (threadsan_mtx_);
    set_format_int (idv);
  }

  /// Функция получения  формата пикселя в буфере
  /// \return   формат пикселей
  libs::helpers::uids::minor::id_val
  get_format () const
  {
    std::scoped_lock lock (threadsan_mtx_);
    return get_format_int ();
  }

  /// Функция установки значения переменной геометрии кадра
  /// \param[in]  type тип переменной
  /// \param[in]  val  значение переменной
  void
  set_dim_var (const Dims& type, dim_type val)
  {
    std::scoped_lock lock (threadsan_mtx_);
    set_dim_var_int (type, val);
  }

  /// Функция получения значения переменной геометрии кадра
  /// \param[in]  type тип переменной
  /// \return     значение переменной
  dim_type
  get_dim_var (const Dims& type) const
  {
    std::scoped_lock lock (threadsan_mtx_);
    return get_dim_var_int (type);
  }

  /// Функция получения значений всех переменных геометрии кадра
  /// \return     значение переменной
  const ::utils::dbufs::video::DimVars&
  get_dim_vars () const
  {
    std::scoped_lock lock (threadsan_mtx_);
    return get_dim_vars_int ();
  }

  /// Функция установки значения признака к кадру в целом
  /// \param[in]  type тип признака
  /// \param[in]  val  значение признака
  void
  set_flag (const BufFlags& type, bool val)
  {
    std::scoped_lock lock (threadsan_mtx_);
    set_flag_int (type, val);
  }

  /// Функция получения значения признака к кадру в целом
  /// \param[in]  type тип признака
  /// \return     значение признака
  bool
  get_flag (const BufFlags& type) const
  {
    std::scoped_lock lock (threadsan_mtx_);
    return get_flag_int (type);
  }

  /// Функция выделения памяти под буфер
  /// \param[in]  info параметры выделения памяти
  void
  buf_alloc (const AllocBufInfo& info)
  {
    std::scoped_lock lock (threadsan_mtx_);
    buf_alloc_int (info);
  }

  /// Функция сброса буфера в значение по умолчанию
  void
  flush ()
  {
    std::scoped_lock lock (threadsan_mtx_);
    flush_int ();
  }

  /// Функция тестирования буфера с помощью специализированной функции
  /// \param[in]  _obj  функция тестирования
  /// \return     true, при успехе, иначе false
  bool
  check (const check_func_type& _obj) const
  {
    std::scoped_lock lock (threadsan_mtx_);
    return check_int (_obj);
  }

  protected:
  /// Защищенный конструктор базового класса, т.е. объекты этого типа не могут существовать и тип предназначен для наследования
  IVideoBuf () = default;

  private:
  // int types
#ifdef U3_FORCE_SYNC_FOR_THREAD_SANITIZER
  using sync_type = std::mutex;
#else
  using sync_type = ::libs::helpers::thread::EmptyMutex;
#endif

  //  IVideoBuf interface
  virtual auto set_format_int (const libs::helpers::uids::minor::id_val&) -> void = 0;
  virtual auto get_format_int () const -> libs::helpers::uids::minor::id_val      = 0;
  virtual auto set_dim_var_int (const Dims&, dim_type) -> void                    = 0;
  virtual auto get_dim_var_int (const Dims&) const -> dim_type                    = 0;
  virtual auto get_dim_vars_int () const -> const DimVars&                        = 0;
  virtual auto set_flag_int (const BufFlags&, bool) -> void                       = 0;
  virtual auto get_flag_int (const BufFlags&) const -> bool                       = 0;
  virtual auto buf_alloc_int (const AllocBufInfo&) -> void                        = 0;
  virtual auto flush_int () -> void                                               = 0;
  virtual auto check_int (const check_func_type&) const -> bool                   = 0;

  mutable sync_type threadsan_mtx_;   //< чтобы успокоить thread sanitizer, т.к. объекты этого типа могут использоваться повторно то и в разных потоках но с разделением по времени Оно этого не понимает
};
}   // namespace utils::dbufs::video
