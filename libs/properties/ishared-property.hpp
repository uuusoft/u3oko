#pragma once
/**
\file       ishared-property.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_properties
\brief      empty brief
*/

namespace libs { namespace properties {
/**
  \brief  empty brief
  */
class ISharedProperty
{
  public:
  //  ext types
  using sync_type  = std::mutex;
  using guard_type = std::lock_guard<sync_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ISharedProperty);

  ISharedProperty ();

  ISharedProperty (const ISharedProperty& _src) = delete;
  ISharedProperty& operator= (const ISharedProperty& _src) = delete;

  virtual ~ISharedProperty ();

  bool self_test () const;

  void* cast2top ();

  sync_type& get_sync ();


  protected:
  virtual bool  self_test_int () const = 0;
  virtual void* cast2top_int ()        = 0;


  private:
  mutable sync_type mtx_;      //< ???
};

}}      // namespace libs::properties
