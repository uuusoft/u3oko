#pragma once
/**
\file       events-buf-info.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::events_base::props::videos::generic::motion_est::consts
{
const std::pair< std::int8_t, std::int8_t > inv_vec (U3_CAST_INT8 (127), U3_CAST_INT8 (127));
}   // namespace libs::events_base::props::videos::generic::motion_est::consts


namespace libs::events_base::props::videos::generic::motion_est::syn
{
using off_buf_type            = ::utils::dbufs::video::consts::offs::off_buf_type;
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
}   // namespace libs::events_base::props::videos::generic::motion_est::syn


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
    const syn::off_buf_type src = utils::dbufs::video::consts::offs::invalid,
    const syn::off_buf_type dst = utils::dbufs::video::consts::offs::invalid,
    const Acessor&              = Acessor (0));

  explicit EventBufsMotionEst (const ::libs::events::buf::EventBufs& buf);

  float         max_error_ { 16.0F * 16.0F * 10.0F };   //< Ошибка блока, больше которой нельзя считать блок найденным
  float         min_error_ { 0.0F };                    //< Минимальная ошибка блока, меньше или равно которой можно считать, что данный блок равен текущему. Т.е. дальнейшний поиск можно не производить
  std::uint16_t size_block_ { 16U };                    //< Размер блока в пикселях, для которого производится оценка движения {8,16,32}
  std::uint16_t size_search_ { 16U };                   //< Размер области поиска в пикселях [0..126]
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

auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const EventBufsMotionEst& src) -> void;
auto tag_invoke (::boost::json::value_to_tag< EventBufsMotionEst >, const ::boost::json::value& jvs) -> EventBufsMotionEst;
}   // namespace libs::events_base::props::videos::generic::motion_est

U3_BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::motion_est::EventBufsMotionEst);
