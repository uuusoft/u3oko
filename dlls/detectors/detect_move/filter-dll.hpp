#pragma once
/**
\file       filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_detect_move
\brief      empty brief
*/

namespace dlls { namespace detectors { namespace detect_move {
/**
  \brief  Фильтр детектирования движения.
  */
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  public:
  Filter ();

  ~Filter ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter override
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void itransform (TransformInfo& _info);

  DiffImpl                   diff_impl_;        //< Реализация вычисления разности между двумя кадрами.
  VideoDiffProp              diff_props_;       //< Свойства вычисления разности.
  MopsImpl                   mops_impl_;        //< Реализация фильтрации (морфологической) разности.
  VideoMorphologyProp        mops_props_;       //< Свойства фильтрации (морфологической) разности.
  ::libs::optim::io::hioptim count_if_ge_;      //< Быстрая функция вычисления "если больше".
};

}}}      // namespace dlls::detectors::detect_move
