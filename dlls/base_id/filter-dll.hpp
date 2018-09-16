#pragma once
/**
\file       filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_base_id_dll
\brief      empty brief.
*/

namespace dlls { namespace base_id {
/**
\brief  empty brief
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
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  BaseIdInterf::ptr base_interf_;           //< Интерфейс для взаимодействия с другими фильтрами в графе.
  signed long long  counter_frames_;        //< Счетчик переданных клиентам кадров.
  bool              send_base_interf_;      //< Флаг посылки сообщения с интерфейсам в данной сессии работы графа.
};

}}      // namespace dlls::base_id
