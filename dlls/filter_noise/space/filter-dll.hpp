#pragma once
/**
\file       filter-dll.hpp
\date       01.01.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      Файл интерфейса типа для фильтрации иозображения в пространственной области.
*/

namespace dlls { namespace filter_noise { namespace space {
/**
\brief  Узел графа обработки данных для фильтрации изображения в простраственной области.
*/
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  public:
  Filter ();

  virtual ~Filter ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void load_int (FilterInfo* _info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void itransform ();
  /// Вспомогательная функция для обновления текущей реализации фильтрации. Выбор делается на основе свойства, загруженного из xml.
  void update_impl ();

  IFilterImpl::uniq_ptr impl_;      //< Поле реализация фильтрации, выбирается на основе параметра из xml файла конфигурации.
};

}}}      // namespace dlls::filter_noise::space
