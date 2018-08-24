#pragma once
/**
\file       iindexer-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       09.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl {
/**
  \brief  Интерфейс для реализаций индексации данных подсистемы хранения данных.
  */
class IIndexerImpl
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IIndexerImpl);

  virtual ~IIndexerImpl ()
  {}

  void
  set_info (const PathInfo::craw_ptr _info)
  {
    //UASSERT (_info);
    return set_info_int (_info);
  }

  void
  change_state (const StateImplsType& _state)
  {
    XULOG_TRACE ("IIndexerImpl::change_state, beg")
    if (!change_state_int (_state))
      {
        XULOG_ERROR ("failed change state storage impl," << to_str (_state));
        XULOG_TRACE ("IIndexerImpl::change_state, end")
        return;
      }
    status_ = _state;
    XULOG_TRACE ("IIndexerImpl::change_state, end")
    return;
  }

  void
  update_stream (UpdateStream::raw_ptr _info)
  {
    UASSERT (_info);
    update_stream_int (_info);
    return;
  }

  void
  get_objects (std::vector<TypeObjectId>& _objs)
  {
    get_objects_int (_objs);
    return;
  }


  protected:
  IIndexerImpl () :
    status_ (StateImplsType::stop)
  {}


  private:
  // IIndexerImpl
  virtual void get_objects_int (std::vector<TypeObjectId>& _objs) = 0;
  virtual bool change_state_int (const StateImplsType& _state)    = 0;
  virtual void set_info_int (const PathInfo::craw_ptr _info)      = 0;
  virtual void update_stream_int (UpdateStream::raw_ptr)          = 0;

  StateImplsType status_;      //< Текущие состояние реализации.
};

}}}}      // namespace modules::uuu_storage::appl::impl
