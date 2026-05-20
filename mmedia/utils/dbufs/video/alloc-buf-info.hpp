#pragma once
/**
\file       alloc-buf-info.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_dbufs
*/

namespace utils::dbufs::video::syn
{
using cuuid  = ::libs::helpers::utils::cuuid;
using id_val = libs::helpers::uids::minor::id_val;
}   // namespace utils::dbufs::video::syn

namespace utils::dbufs::video
{
/// Структура для группировки параметров вызова по перераспределению памяти буфера
struct AllocBufInfo {
  // ext types
  using dim_type   = ::utils::dbufs::video::DimVars::dim_type;                                              //< REFACT
  using flags_type = ::libs::helpers::utils::ValuesStorage< BufFlags, bool, BufFlags::max_bound, false >;   //<

  AllocBufInfo () :
    check_dims_ (utils::dbufs::video::DimChecks::enable),
    force_size_ (0),
    subsample_ (Subs::sub_444)
  {
  }

  explicit AllocBufInfo (
    const dim_type&    _width,
    const dim_type&    _height,
    const dim_type&    _stride,
    const syn::id_val& _minor,
    const DimChecks&   _check_dims = DimChecks::enable,
    const Subs&        _subsample  = Subs::sub_444) :

    minor_ (_minor),
    force_size_ (0),
    check_dims_ (_check_dims),
    subsample_ (_subsample)
  {
    geom_dims_[::utils::dbufs::video::Dims::width]  = _width;
    geom_dims_[::utils::dbufs::video::Dims::height] = _height;
    geom_dims_[::utils::dbufs::video::Dims::stride] = _stride;
  }

  explicit AllocBufInfo (
    const DimVars&     _geom_dims,
    const syn::id_val& _minor,
    const DimChecks&   _check_dims = DimChecks::enable,
    const Subs&        _subsample  = Subs::sub_444) :

    geom_dims_ (_geom_dims),
    minor_ (_minor),
    force_size_ (0),
    check_dims_ (_check_dims),
    subsample_ (_subsample)
  {
  }
  /// Конструктор для создания буфера под сжатые данные
  /// EAI-REFACT: compressed buf
  explicit AllocBufInfo (
    const dim_type&    _width,
    const dim_type&    _height,
    const syn::id_val& _minor,
    const dim_type&    size) :

    minor_ (_minor),
    force_size_ (size),
    check_dims_ (DimChecks::disable),
    subsample_ (Subs::sub_444)
  {
    U3_ASSERT (size > 0);
    geom_dims_[::utils::dbufs::video::Dims::width]  = _width;
    geom_dims_[::utils::dbufs::video::Dims::height] = _height;
    geom_dims_[::utils::dbufs::video::Dims::stride] = _width;   //  Это верное присваивание. Т.к. коструктор используется для конструрования буфера для сжатых данных, шаг не имеет смысла.
  }

  explicit AllocBufInfo (const dim_type& size) :
    force_size_ (size),
    minor_ (::libs::helpers::uids::minor::id_val::unknown),
    check_dims_ (DimChecks::disable),
    subsample_ (Subs::sub_444)
  {
    U3_ASSERT (size > 0);
  }
  /// Функция проверки корректности параметров вызова
  /// \return   true, если параметры консистентны
  bool
  check_alloc_info () const
  {
    // EAI-BREAK-CHANGE 22.03.2026
    // if (minor_.empty ())
    if (syn::id_val::unknown == minor_)
    {
      U3_XLOG_WARN ("empty minor format");
      return false;
    }

    const auto _count_bytes = force_size_ ? 0 : ::libs::helpers::uids::helpers::get_count_bytes_from_format (minor_);
    const auto _stride      = force_size_ ? geom_dims_[::utils::dbufs::video::Dims::stride] : geom_dims_[::utils::dbufs::video::Dims::width] * _count_bytes;

    return geom_dims_[::utils::dbufs::video::Dims::width] > 0 &&
           geom_dims_[::utils::dbufs::video::Dims::height] > 0 &&
           geom_dims_[::utils::dbufs::video::Dims::stride] >= _stride;
  }
  /// Функция сброса параметров в начальное состояние,
  /// например для повторного использования или для синхронизации состояния с владельцем при использовании в композиции
  void
  reset ()
  {
    // EAI-BREAK-CHANGE 22.03.2026
    // minor_.reset ();
    minor_ = syn::id_val::unknown;
    geom_dims_.reset ();
    flags_.fill (false);

    check_dims_ = utils::dbufs::video::DimChecks::enable;
    force_size_ = 0;
    subsample_  = Subs::sub_444;
  }
  /// Функция быстрого обмена полями между двумя объектами типа
  /// \param[in, out] src  второй объект обмена
  void
  swap (AllocBufInfo& src)
  {
    if (this == &src)
    {
      U3_XLOG_WARN (std::string ("try swap AllocBufInfo with self") + PTR_TOLOG (this));
      return;
    }

    std::swap (geom_dims_, src.geom_dims_);
    std::swap (minor_, src.minor_);
    std::swap (force_size_, src.force_size_);
    std::swap (check_dims_, src.check_dims_);
    std::swap (flags_, src.flags_);
    std::swap (subsample_, src.subsample_);
  }

  DimVars     geom_dims_;    //< Размерности буфера
  flags_type  flags_;        //< Признаки, общие для буфера в целом
  syn::id_val minor_;        //< Формат пикселей буфера
  dim_type    force_size_;   //< Размер буфера в байтах, когда его нельзя вычислить от minor_ и прочего
  DimChecks   check_dims_;   //< Требование проверки размеров при выделении буфера. Т.к. в некоторых случаях (операция свертка), размеры могут превышать явно указанные
  Subs        subsample_;    //<
};
}   // namespace utils::dbufs::video
