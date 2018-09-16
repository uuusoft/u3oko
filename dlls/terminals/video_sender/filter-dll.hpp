#pragma once
/**
\file       filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       06.03.2016
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief    
*/

namespace dlls { namespace terminals { namespace video_sender {
//  forward
class IsEmptyFrameHelper;
class FillFrameHelper;
/**
\brief  Основной фильтр графа обработки данных для передачи обработанных зображений в другие модули.
        Для примера, http server, gui etc.
*/
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  friend class IsEmptyFrameHelper;
  friend class FillFrameHelper;

  public:
  Filter ();

  virtual ~Filter ();


  private:
  // int types
  using send_funct_type       = std::function<void(TransformInfo&, const Buff2ModuleInfo::craw_ptr)>;
  using send_functs_type      = std::unordered_map<id_link_module_type, send_funct_type>;
  using send_impl_funct_type  = std::function<void(TransformInfo&, const Buff2ModuleInfo::craw_ptr)>;
  using send_impl_functs_type = std::unordered_map<id_link_module_type, IImplSender::ptr>;
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);

  // IFilter overrides
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void send_info_msg (TransformInfo& _info);

  void process_events (TransformInfo& _info);

  void init_send_functs ();

  void default_send_funct (TransformInfo&, const Buff2ModuleInfo::craw_ptr, const id_link_module_type&);

  send_functs_type      functs_;       //< Функции передачи буферов по модулю-назачения.
  send_impl_functs_type senders_;      //< ???
};

}}}      // namespace dlls::terminals::video_sender
