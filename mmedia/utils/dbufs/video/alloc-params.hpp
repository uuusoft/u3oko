#pragma once
/**
\file       alloc-params.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_dbufs
*/

namespace utils::dbufs::video
{
/// Структура для группировки параметров вызова по перераспределению памяти буфера
struct AllocParams {
  // ext types
  using dim_type   = ::utils::dbufs::video::DimVars::dim_type;                                              //< REFACT
  using flags_type = ::libs::utility::utils::ValuesStorage< BufFlags, bool, BufFlags::max_bound, false >;   //<

  AllocParams () = default;

  explicit AllocParams (
    const dim_type&    width,
    const dim_type&    height,
    const dim_type&    stride,
    const syn::id_val& minor,
    const DimChecks&   check_dims = DimChecks::enable,
    const Subs&        subsample  = Subs::sub_444) :
    minor_ (minor),
    check_dims_ (check_dims),
    subsample_ (subsample)
  {
    geom_dims_[::utils::dbufs::video::Dims::width]  = width;
    geom_dims_[::utils::dbufs::video::Dims::height] = height;
    geom_dims_[::utils::dbufs::video::Dims::stride] = stride;
  }

  explicit AllocParams (
    const DimVars&     geom_dims,
    const syn::id_val& minor,
    const DimChecks&   check_dims = DimChecks::enable,
    const Subs&        subsample  = Subs::sub_444) :

    geom_dims_ (geom_dims),
    minor_ (minor),
    check_dims_ (check_dims),
    subsample_ (subsample)
  {
  }

  /// Конструктор для создания буфера под сжатые данные
  explicit AllocParams (
    const dim_type&    width,
    const dim_type&    height,
    const syn::id_val& minor,
    const dim_type&    size) :
    minor_ (minor),
    force_size_ (size),
    check_dims_ (DimChecks::disable)
  {
    U3_ASSERT (size > 0);
    geom_dims_[::utils::dbufs::video::Dims::width]  = width;
    geom_dims_[::utils::dbufs::video::Dims::height] = height;
    geom_dims_[::utils::dbufs::video::Dims::stride] = width;   // Это верное присваивание, т.к. коструктор используется для конструрования буфера для сжатых данных, stride не имеет смысла
  }

  explicit AllocParams (const dim_type& size) :
    force_size_ (size),
    minor_ (::libs::utility::uids::minor::id_val::unknown),
    check_dims_ (DimChecks::disable)
  {
    U3_ASSERT (size > 0);
  }

  /// Функция проверки корректности параметров вызова
  /// \return   true, если параметры консистентны
  bool
  check_alloc_info () const
  {
    if (syn::id_val::unknown == minor_)
    {
      U3_XLOG_WARN ("empty minor format");
      return false;
    }

    const auto count_bytes = force_size_ ? 0 : ::libs::utility::uids::helpers::get_count_bytes_from_format (minor_);
    const auto stride      = force_size_ ? geom_dims_[::utils::dbufs::video::Dims::stride] : geom_dims_[::utils::dbufs::video::Dims::width] * count_bytes;

    return geom_dims_[::utils::dbufs::video::Dims::width] > 0 &&
           geom_dims_[::utils::dbufs::video::Dims::height] > 0 &&
           geom_dims_[::utils::dbufs::video::Dims::stride] >= stride;
  }

  /// Функция сброса параметров в начальное состояние,
  /// например для повторного использования или для синхронизации состояния с владельцем при использовании в композиции
  void
  reset ()
  {
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
  swap (AllocParams& src)
  {
    if (this == &src)
    {
      U3_XLOG_WARN (std::string ("selfswap AllocParams") + PTR_TOLOG (this));
      return;
    }

    std::swap (geom_dims_, src.geom_dims_);
    std::swap (minor_, src.minor_);
    std::swap (force_size_, src.force_size_);
    std::swap (check_dims_, src.check_dims_);
    std::swap (flags_, src.flags_);
    std::swap (subsample_, src.subsample_);
  }

  DimVars     geom_dims_;                                             //< Размерности буфера
  flags_type  flags_;                                                 //< Признаки, общие для буфера в целом
  syn::id_val minor_      = syn::id_val::device_specific;             //< Формат пикселей буфера
  dim_type    force_size_ = 0;                                        //< Размер буфера в байтах, когда его нельзя вычислить от minor_ и прочего
  DimChecks   check_dims_ = utils::dbufs::video::DimChecks::enable;   //< Требование проверки размеров при выделении буфера. Т.к. в некоторых случаях (операция свертка), размеры могут превышать явно указанные
  Subs        subsample_  = Subs::sub_444;                            //<
};
}   // namespace utils::dbufs::video
