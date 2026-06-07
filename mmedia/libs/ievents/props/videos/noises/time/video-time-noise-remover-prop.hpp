#pragma once
/**
\file       video-time-noise-remover-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::noises::time::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;
}

namespace libs::ievents::props::videos::noises::time
{
/// Свойства фильтрации во временной области
class VideoTimeNoiseRemoverProp final : public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using source_bufs_type = std::vector< syn::off_buf_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoTimeNoiseRemoverProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoTimeNoiseRemoverProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoTimeNoiseRemoverProp)

  explicit VideoTimeNoiseRemoverProp (const Acessor& = Acessor (0));
  virtual ~VideoTimeNoiseRemoverProp () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/noises/time/video-time-noise-remover-prop";
    return ret;
  }

  std::string                 name_impl_          = "median2";                                            //< Имя реализации, которая будет использованя для фильтрации
  syn::off_buf_type           indx_diff_buf_      = utils::dbufs::video::consts::offs::move_detect_res;   //<
  std::int32_t                dump_counter_frame_ = 0;                                                    //< Вывода времени работы через заданное количество кадров. 0 - отключение вывода (по умолчанию)
  ::libs::events::IEvent::ptr impl_info_;                                                                 //< Расширенные свойства, связанные с конкретной реализацией фильтрации
  source_bufs_type            bufs_;                                                                      //< Список буферов с настройками для фильтрации

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // overrides ievents::Event
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
  virtual void                        self_correct_int () override;
};
}   // namespace libs::ievents::props::videos::noises::time

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
