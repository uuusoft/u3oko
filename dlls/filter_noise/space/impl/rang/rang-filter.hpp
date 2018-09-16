//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       rang-filter.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_time_filter_noise
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang {
//  syn
using ::libs::optim::io::hioptim;
/**
\brief  Ранговая фильтрация в пространственной области.
        Стандартное решение.
*/
class RangFilter : public IFilterImpl
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (RangFilter);

  RangFilter ();

  virtual ~RangFilter ();


  private:
  // IFilterImpl overrides
  virtual void transform_int (InfoFilter& _finfo, ::libs::buffs::Buffs* _pbuff) override;
  virtual void load_int () override;
  /**
  \brief  Функция выбора наиболее подходящего алгоритма сортировки.
          Учитывается длина сортируемой последовательности и ранг числа.
  \return реализация
  */
  IAlgImpl::ptr make_impl (InfoFilter& _finfo);

  CallerImpl::ptr            pthreads_;           //< Пул рабочих потоков
  hioptim::store_funct_type  store_call_;         //< Поле для многопоточного вызова.
  hioptim                    ext_call_;           //< Поле для многопоточного вызова.
  IVideoBuff::ptr            temp_src_buff_;      //< Временный буфер, для хранения буфера-источника.
  std::vector<IAlgImpl::ptr> algs_;               //< Массив реализации для каждого рабочего потока.
};

}}}}}      // namespace dlls::filter_noise::space::impl::rang
