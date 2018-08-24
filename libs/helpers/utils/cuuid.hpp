#pragma once
/**
\file       cuuid.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace utils {
/**
  \brief  Расширение boost::uuids::uuid необходимым мне функционалом.
  */
class cuuid
{
  public:
  //  ext types
  using value_type = boost::uuids::uuid::value_type;

  cuuid ();

  explicit cuuid (const value_type val_array[16]);

  explicit cuuid (const boost::uuids::uuid& _base);

#if defined(UUU_OS_WIN32_DESKTOP)
  explicit cuuid (const GUID& _guid);

  const GUID* get_guid () const;
#endif

  cuuid& operator= (const boost::uuids::uuid& left);

  cuuid& operator= (const cuuid& left);

  void reset ();

  std::string name () const;

  bool empty () const;

  const boost::uuids::uuid& get_vals () const;


  private:
  boost::uuids::uuid id_;      //< Поле, которые мы функционально расширяем.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

bool operator< (const cuuid& _l, const cuuid& _r);

bool operator== (const cuuid& _l, const cuuid& _r);

bool operator!= (const cuuid& _l, const cuuid& _r);

}}}      // namespace libs::helpers::utils


// Specialize std::hash
namespace std {

template <>
struct hash<::libs::helpers::utils::cuuid>
{
  size_t
  operator() (const ::libs::helpers::utils::cuuid& _guid) const noexcept
  {
    boost::hash<boost::uuids::uuid> _hasher;
    return _hasher (_guid.get_vals ());
  }
};

}      // namespace std

BOOST_CLASS_EXPORT_KEY (::libs::helpers::utils::cuuid);
