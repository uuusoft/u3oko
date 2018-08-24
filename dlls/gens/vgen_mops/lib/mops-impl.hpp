#pragma once
/**
\file       mops-impl.hpp
\date       01.10.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
\brief      Объявление фильтра морфологических операций (МО).
*/

namespace dlls { namespace gens { namespace vgen_mops { namespace lib {
/**
  \brief  Фильтр морфологических операций над изображением.
  */
class MopsImpl final
{
  public:
  MopsImpl ();

  ~MopsImpl ();

  void init ();

  void set_props (VideoMorphologyProp::craw_ptr _info);

  void itransform (Buffs& _pbuffs);

  void alloc_buffs ();
  /**
    \brief            Функция бинаризации буфера.
    \param[in]        _b2b  буфер. 
    \param[in]        _bound  граница для пикселя
    \param[in]        _val  значение, которое приобретает пиксель, если его начальное значение меньше _bound
    \param[in, out ]  _pdst буфер.
    \noreturn
    */
  void bin_buff (
    const OffBuff2Info& _b2b,
    const short         _bound,
    const short         _val,
    IVideoBuff*         _pdst);


  private:
  VideoMorphologyProp::craw_ptr props_;              //< ???
  helpers::MorphOperator        morph_helper_;       //< Вспомогательный объект, для реализации функционала МО, т.к возможно он будет использован в ряде лругих фильтров.
  ::libs::optim::io::hioptim    cmp_get_const_;      //< Функция сравнения для бинаризации изображения (подготовка буфера к МО через свертку).
  CallerImpl::ptr               pthreads_;           //< Пул потоков для обработки данных.
};

}}}}      // namespace dlls::gens::vgen_mops::lib
