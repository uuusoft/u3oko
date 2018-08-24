//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       zip-data-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "zip-data-event.hpp"

namespace libs { namespace ievents { namespace runtime { namespace mem {
/**
\brief  
*/
void
copy_buff2vector (IVideoBuff::raw_ptr _buff, std::vector<unsigned char>& _out)
{
  CHECK_STATE (_buff, "failed, empty zip buff");
  auto const _raw_buff  = _buff->get_cbuff ();
  const auto _size_buff = (*_buff)[utils::dbuffs::TypeMemVar::size_data];
  UASSERT (_raw_buff);
  UASSERT (_size_buff);

  if (!_raw_buff || !_size_buff)
    {
      return;
    }

  _out.resize (_size_buff);
  ::libs::helpers::mem::acopy (_raw_buff, &_out[0], _size_buff);
  return;
}


ZipDataEvent::ZipDataEvent (const Acessor& _ph) :
  size_ (0)
{
  property_name_ = gen_get_type_text_id ();
}


ZipDataEvent::ZipDataEvent (zip_buff_type&& _buff, std::size_t _size, const number_buff_type& _number_buff, const id_buff_type& _id) :
  buff_ (std::move (_buff)),
  size_ (_size),
  id_buff_ (_id),
  number_buff_ (_number_buff)
{
  property_name_ = gen_get_type_text_id ();
}


ZipDataEvent::ZipDataEvent (IVideoBuff::raw_ptr _buff, const number_buff_type& _number_buff, const id_buff_type& _id) :
  id_buff_ (_id),
  number_buff_ (_number_buff)
{
  property_name_ = gen_get_type_text_id ();
  copy_buff2vector (_buff, buff_);
  size_ = buff_.size ();
}

#if 0
ZipDataEvent::ZipDataEvent (const ZipDataEvent& _src) :
  size_ (0)
{
  property_name_ = gen_get_type_text_id ();
  super::operator= (_src);

  if (_src.get_size ())
    {
      size_ = _src.get_size ();
      buff_.resize (size_);
      ::libs::helpers::mem::acopy (&_src.get_zip ()[0], &buff_[0], size_);
    }
}
#endif
#if 0
ZipDataEvent&
ZipDataEvent::operator= (const ZipDataEvent& _src)
{
  ZipDataEvent _temp (_src);
  std::swap (*this, _temp);

  id_buff_     = _src.id_buff_;
  number_buff_ = _src.number_buff_;
  return *this;
}
#endif

const ZipDataEvent::zip_buff_type&
ZipDataEvent::get_zip () const
{
  return buff_;
}


ZipDataEvent::zip_buff_type&
ZipDataEvent::update_zip ()
{
  return buff_;
}


void
ZipDataEvent::update_zip (IVideoBuff::raw_ptr& _buff)
{
  copy_buff2vector (_buff, buff_);
  size_ = buff_.size ();
  return;
}


std::size_t
ZipDataEvent::get_size () const
{
  return size_;
}


const ZipDataEvent::id_buff_type&
ZipDataEvent::get_id () const
{
  return id_buff_;
}


void
ZipDataEvent::set_id (const id_buff_type& _id)
{
  id_buff_ = _id;
  return;
}


const ZipDataEvent::number_buff_type&
ZipDataEvent::get_number () const
{
  return number_buff_;
}


void
ZipDataEvent::set_number (const number_buff_type& _number_buff)
{
  number_buff_ = _number_buff;
  return;
}


::libs::events::IEvent::ptr
ZipDataEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<ZipDataEvent> (this, _deep);
}


void
ZipDataEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ZipDataEvent);
  super::copy_int (_src);
  buff_        = _dsrc->buff_;
  id_buff_     = _dsrc->id_buff_;
  number_buff_ = _dsrc->number_buff_;
  return;
}


template <class Archive>
void
ZipDataEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buff_);
  ar& BOOST_SERIALIZATION_NVP (id_buff_);
  ar& BOOST_SERIALIZATION_NVP (number_buff_);
  return;
}

}}}}      // namespace libs::ievents::runtime::mem

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::mem::ZipDataEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::runtime::mem::ZipDataEvent);
