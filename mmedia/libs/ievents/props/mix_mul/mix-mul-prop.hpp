#pragma once
/**
\file       mix-mul-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::mix_mul
{
class MixMulProp final : public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using out_channels_type = std::array< OutChannelInfo, consts::max_output_points >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (MixMulProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (MixMulProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (MixMulProp)

  explicit MixMulProp (const Acessor& = Acessor (0));
  virtual ~MixMulProp () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/mix_mul/mix-mul-prop";
    return ret;
  }

  out_channels_type outs_;   //< У фильтра-размножителя можно задать для каждой выходной точки свой уникальный список умножения буферов. Эта структура и хранит их

  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::ievents::props::mix_mul

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::mix_mul::MixMulProp);
