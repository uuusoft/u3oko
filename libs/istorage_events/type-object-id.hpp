#pragma once
/**
\file       type-object-id.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.08.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events {
/**
brief Тип идентификатора объекта в потоке данных.
*/
class TypeObjectId
{
  public:
  // ext types
  using id_type = std::string;

  explicit TypeObjectId (const id_type& _val = consts::empty_object_id)
  {}

  bool
  is_valid () const
  {
    return consts::empty_object_id == val_ ? false : true;
  }

  void
  reset ()
  {
    val_ = consts::empty_object_id;
    return;
  }

  bool
  operator== (const TypeObjectId& _obj) const
  {
    return val_ == _obj.val_;
  }

  id_type val_;      //< Поле значения идентификатора объекта.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (val_);
    return;
  }
};

}}      // namespace libs::istorage_events


namespace std {

template <>
struct hash<::libs::istorage_events::TypeObjectId>
{
  size_t
  operator() (const ::libs::istorage_events::TypeObjectId& _val) const noexcept
  {
    return hash<typename ::libs::istorage_events::TypeObjectId::id_type> () (_val.val_);
  }
};

}      // namespace std
