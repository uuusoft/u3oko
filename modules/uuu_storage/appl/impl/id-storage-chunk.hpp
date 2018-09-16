#pragma once
/**
\file       id-storage-chunk.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       03.09.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl {
//  syn
using ::utils::mem_functs::IBlockMem;
using ::libs::helpers::utils::cuuid;
/**
\brief  Идентификатор фрагмента в бинарном хранилище.
*/
struct IdStorageChunk
{
  using id_type = int;

  static const id_type invalid_id = -1;

  IdStorageChunk () :
    id_file_ (invalid_id), id_fragment_ (invalid_id)
  {
    UASSERT (!is_valid ());
  }

  bool
  is_valid () const
  {
    if (invalid_id == id_file_ || invalid_id == id_fragment_)      // || id_session_.empty ())
      {
        return false;
      }
    return true;
  }

  void
  reset ()
  {
    id_file_     = invalid_id;
    id_fragment_ = invalid_id;
    return;
  }

  //cuuid id_session_;       //< Индентификатор сессии, в которой фрагмент был записан.
  id_type id_file_;          //< Идентификатор файла данных.
  id_type id_fragment_;      //< Идентификатор фрагмента.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    //ar& BOOST_SERIALIZATION_NVP (id_session_);
    ar& BOOST_SERIALIZATION_NVP (id_file_);
    ar& BOOST_SERIALIZATION_NVP (id_fragment_);
    return;
  }
};


inline
std::ostream&
operator<< (std::ostream& _stream, const IdStorageChunk& _val)
{
  //_stream << _val.id_session_.name () << "." << _val.id_file_ << "." << _val.id_fragment_;
  _stream << _val.id_file_ << "." << _val.id_fragment_;
  return _stream;
}

}}}}      // namespace modules::uuu_storage::appl::impl
