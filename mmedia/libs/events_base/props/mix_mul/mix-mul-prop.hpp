#pragma once
/**
\file       mix-mul-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::mix_mul
{
class MixMulProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  using out_channels_type = std::array< OutChannelInfo, consts::max_output_points >;

  U3_ADD_POINTERS_TO_SELF (MixMulProp)
  U3_ADD_MAKE_SHARED_THIS (MixMulProp)
  U3_ADD_DELETE_MOVE_COPY (MixMulProp)

  explicit MixMulProp (const Acessor& = Acessor (0));
  virtual ~MixMulProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/mix_mul/mix-mul-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  out_channels_type outs_;   //< У фильтра-размножителя можно задать для каждой выходной точки свой уникальный список умножения буферов. Эта структура и хранит их

  protected:
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events_base::props::mix_mul

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::mix_mul::MixMulProp);
