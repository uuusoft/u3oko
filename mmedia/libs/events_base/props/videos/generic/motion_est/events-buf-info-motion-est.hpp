#pragma once
/**
\file       events-buf-info.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::motion_est
{
struct EventBufsMotionEst final : public ::libs::events::buf::EventBufs {
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using vectors_type = std::vector< std::pair< std::int8_t, std::int8_t > >;

  explicit EventBufsMotionEst (
    const ::utils::dbufs::video::consts::offs::off_buf_type& src = utils::dbufs::video::consts::offs::invalid,
    const ::utils::dbufs::video::consts::offs::off_buf_type& dst = utils::dbufs::video::consts::offs::invalid,
    const Acessor&                                               = Acessor (0));

  explicit EventBufsMotionEst (const ::libs::events::buf::EventBufs& buf);

  float         max_error_   = 16.0F * 16.0F * 10.0F;   //< Ошибка блока, больше которой нельзя считать блок найденным
  float         min_error_   = 0.0F;                    //< Минимальная ошибка блока, меньше или равно которой можно считать, что данный блок равен текущему. Т.е. дальнейшний поиск можно не производить
  std::uint16_t size_block_  = 16U;                     //< Размер блока в пикселях, для которого производится оценка движения {8,16,32}
  std::uint16_t size_search_ = 16U;                     //< Размер области поиска в пикселях [0..126]
  vectors_type  search_vecs_;                           //< Вычисленные по области поиска или предзагруженные вектора поиска, которые определяют порядок поиска

  protected:
  virtual void check_int () override;
  virtual void correct_int () override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events::buf::EventBufs)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void               tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const EventBufsMotionEst& src);
EventBufsMotionEst tag_invoke (::boost::json::value_to_tag< EventBufsMotionEst >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::motion_est

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::motion_est::EventBufsMotionEst);
