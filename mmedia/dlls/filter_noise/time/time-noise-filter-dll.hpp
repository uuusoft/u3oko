#pragma once
/**
\brief      Filter for corrected image
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/

namespace dlls::filter_noise::time
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info) override;
  virtual void run_int () override;
  virtual void stop_int () override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void itransform ();
  /// Вспомогательная функция для обновления текущей реализации фильтрации. Выбор делается на основе свойства, загруженного из xml
  void update_impl ();
};
}   // namespace dlls::filter_noise::time
