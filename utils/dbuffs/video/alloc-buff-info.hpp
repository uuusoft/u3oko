//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       alloc-buff-info.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Файл структуры для группировки параметров вызова по выделению буфера.
*/

namespace utils { namespace dbuffs { namespace video {
//  syn
using ::libs::helpers::utils::cuuid;
/**
  \brief  Структура для группировки параметров вызова по перераспределению памяти буфера.
  */
struct AllocBuffInfo
{
  //  ext types
  using dim_type = int;
  /// Конструктор по умолчанию для создания "пустого" объекта.
  AllocBuffInfo () :
    width_ (0),
    height_ (0),
    stride_ (0),
    check_dims_ (utils::dbuffs::video::TypeCheckDim::enable_check),
    flag_ (utils::dbuffs::TypeFlagsBuff::zero),
    force_size_ (0),
    subsample_ (TypeSubSample::full_444)
  {}
  /**
    \brief      Основной рабочий конструктор.
    \param[in]  _width  
    \param[in]  _height 
    \param[in]  _stride 
    \param[in]  _minor  
    \param[in]  _check_dims 
    \param[in]  _flag 
    \param[in]  _subsample
    */
  AllocBuffInfo (
    const dim_type&      _width,
    const dim_type&      _height,
    const dim_type&      _stride,
    const cuuid&         _minor,
    const TypeCheckDim&  _check_dims = TypeCheckDim::enable_check,
    const TypeFlagsBuff& _flag       = utils::dbuffs::TypeFlagsBuff::zero,
    const TypeSubSample& _subsample  = TypeSubSample::full_444) :
    width_ (_width),
    height_ (_height),
    stride_ (_stride),
    minor_ (_minor),
    check_dims_ (_check_dims),
    flag_ (_flag),
    force_size_ (0),
    subsample_ (_subsample)
  {}
  /**
    \brief      Рабочий конструктор.
    \param[in]  _width  
    \param[in]  _height 
    \param[in]  _stride 
    \param[in]  _minor  
    \param[in]  _check_dims 
    \param[in]  _flag 
    */
  AllocBuffInfo (
    const dim_type& _width,
    const dim_type& _height,
    const cuuid&    _minor,
    const dim_type& _size) :
    width_ (_width),
    height_ (_height),
    stride_ (_width),      //  Это верное присваивание. Т.к. коструктор используется для конструрования буфера для сжатых данных, шаг не имеет смысла.
    minor_ (_minor),
    check_dims_ (TypeCheckDim::disabled_check),
    flag_ (utils::dbuffs::TypeFlagsBuff::zero),
    force_size_ (_size),
    subsample_ (TypeSubSample::full_444)
  {
    UASSERT (_size > 0);
  }
  /**
    \brief      Конструктор.
    \param[in]  _size ???
    */
  explicit AllocBuffInfo (const dim_type& _size) :
    width_ (0),
    height_ (0),
    stride_ (0),
    force_size_ (_size),
    minor_ (::libs::helpers::uids::minor::unknow),
    check_dims_ (TypeCheckDim::disabled_check),
    flag_ (utils::dbuffs::TypeFlagsBuff::zero),
    subsample_ (TypeSubSample::full_444)
  {
    UASSERT (_size > 0);
  }
  /**
    \brief    Функция проверки корректности параметров вызова.
    \return   true, если параметры консистентны.
    */
  bool
  check_alloc_info () const
  {
    if (minor_.empty ())
      {
        return false;
      }

    const int _count_bytes = force_size_ ? 0 : ::libs::helpers::uids::helpers::get_count_bytes_from_format (minor_);
    const int _stride      = force_size_ ? stride_ : width_ * _count_bytes;
    return width_ > 0 && height_ > 0 && stride_ >= _stride;
  }
  /**
    \brief  Функция сброса параметров в начальное состояние,
            например для повторного использования или для синхронизации состояния с владельцем при использовании в композиции.
    */
  void
  reset ()
  {
    minor_.reset ();
    width_      = 0;
    height_     = 0;
    stride_     = 0;
    check_dims_ = utils::dbuffs::video::TypeCheckDim::enable_check;
    flag_       = utils::dbuffs::TypeFlagsBuff::zero;
    force_size_ = 0;
    subsample_  = TypeSubSample::full_444;
    return;
  }
  /**
    \brief          Функция быстрого обмена полями между двумя объектами типа.
    \param[in, out] _src  второй объект обмена.
    */
  void
  swap (AllocBuffInfo& _src)
  {
    if (this == &_src)
      {
        XULOG_WARNING ("try swap with self, 0x" << this);
        return;
      }

    std::swap (width_, _src.width_);
    std::swap (height_, _src.height_);
    std::swap (stride_, _src.stride_);
    std::swap (minor_, _src.minor_);
    std::swap (force_size_, _src.force_size_);
    std::swap (check_dims_, _src.check_dims_);
    std::swap (flag_, _src.flag_);
    std::swap (subsample_, _src.subsample_);
    return;
  }

  dim_type      width_;           //< Ширина буфера в пикселях.
  dim_type      height_;          //< Высота буфера в пикселях.
  dim_type      stride_;          //< Шаг строки буфера в байтах
  cuuid         minor_;           //< Формат пикселей буфера.
  dim_type      force_size_;      //< Размер буфера в байтах, когда его нельзя вычислить от minor_ и прочего.
  TypeCheckDim  check_dims_;      //< Требование проверки размеров при выделении буфера. Т.к. в некоторых случаях (операция свертка), размеры могут превышать явно указанные.
  TypeFlagsBuff flag_;            //< Признаки, общие для буфера в целом.
  TypeSubSample subsample_;       //< ???
};

}}}      // namespace utils::dbuffs::video
