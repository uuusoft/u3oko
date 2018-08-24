//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       morph-operator.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
*/

namespace dlls { namespace gens { namespace vgen_mops { namespace lib { namespace helpers {
/**
  \brief  Вспомогательный объект для вычисления МО.
  */
class MorphOperator
{
  public:
  MorphOperator ();

  ~MorphOperator ();

  MorphOperator (const MorphOperator& _src) = delete;
  MorphOperator& operator= (const MorphOperator& _src) = delete;

  void init ();

  void applay_operation2buff (const ParamsOperation& _op, ::libs::buffs::Buffs* _pbuff, IVideoBuff* _pdst);


  private:
  void erosion_buff (const ParamsOperation& _op, ::libs::buffs::Buffs* _pbuff, IVideoBuff* _pdst);
  /**
    \brief        Функция подготовки параметров для МО erosion.
    \param[in]    _size_spot  размер пятна операции.
    \param[out ]  _cinfo      параметры функции.
    \param[out ]  _tfunct     возвращаемая функция.
    */
  void fill_koeffs_for_erosion_operation (
    const short                        _size_spot,
    ::libs::optim::io::MCallInfo&      _cinfo,
    ::libs::optim::mcalls::InfoMFunct& _tfunct);

  void dilation_buff (
    const ParamsOperation& _op,
    ::libs::buffs::Buffs*  _pbuff,
    IVideoBuff*            _pdst);
  /**
    \brief        Функция подготовки параметров для МО dilation.
    \param[in]    _size_spot  размер пятна операции.
    \param[out ]  _cinfo    параметры функции.
    \param[out ]  _tfunct   возвращаемая функция.
    */
  void fill_koeffs_for_dilation_operation (
    const short _size_spot,
    MCallInfo&  _cinfo,
    InfoMFunct& _tfunct);

  CallerImpl::ptr            pthreads_;            //< Указатель на пул потоков для вычисления МО.
  ::libs::optim::io::hioptim conv_mod_3x3_;        //< Функция свертки 3х3.
  ::libs::optim::io::hioptim conv_mod_5x5_;        //< Функция свертки 5х5.
  ::libs::optim::io::hioptim conv_mod_7x7_;        //< Функция свертки 7х7.
  ::libs::optim::io::hioptim conv_mod_9x9_;        //< Функция свертки 9х9.
  ::libs::optim::io::hioptim conv_mod_11x11_;      //< Функция свертки 11х11.
};

}}}}}      // namespace dlls::gens::vgen_mops::lib::helpers
