#pragma once
/**
\file       istorage-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       25.07.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl {
/**
  \brief  Интерфейс для реализаций хранения бинарных данных подсистемы хранения данных.
          Реализует (желательно лучше чем sqlite) удаление/сохранение/чтение больших блоков blob и больше ничего.
          Ничего не знает, что из себя представлют конкретные данные и прочее.
  */
class IStorageImpl
{
  public:
  //  ext types
  using id_chunk_type  = IdStorageChunk;                  //<  Тип идентификатора фрагмента в хранилище бинарных данных
  using seance_type    = std::string;                     //<  Тип идентификатора сессии фрагмента в хранилище бинарных данных.
  using ids_chunk_type = std::vector<id_chunk_type>;      //<  Тип массива идентификаторов фрагментов в хранилище бинарных данных.
  using id_locker_type = std::string;                     //<  Тип блокировщика фрагментов для гарантирования атомарности операций над ними
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IStorageImpl);

  virtual ~IStorageImpl ()
  {}

  void
  set_info (const PathInfo::craw_ptr _info)
  {
    return set_info_int (_info);
  }

  void
  change_state (const StateImplsType& _state)
  {
    XULOG_TRACE ("IStorageImpl::change_state, beg")
    if (!change_state_int (_state))
      {
        XULOG_ERROR ("failed change state storage impl, " << to_str (_state));
        XULOG_TRACE ("IStorageImpl::change_state, end")
        return;
      }
    status_ = _state;
    XULOG_TRACE ("IStorageImpl::change_state, end")
    return;
  }

  void
  load (const seance_type& _seance, const id_chunk_type& _id, IBlockMem::raw_ptr _mem)
  {
    XULOG_TRACE ("IStorageImpl::load, beg");
    check_state_for_ops ("load");
    UASSERT (_id.is_valid ());
    load_int (_seance, _id, _mem);
    XULOG_TRACE ("IStorageImpl::load, end");
    return;
  }

  id_chunk_type
  save (const seance_type& _seance, IBlockMem::craw_ptr _mem)
  {
    XULOG_TRACE ("IStorageImpl::save, beg");
    check_state_for_ops ("save");
    const auto _res = save_int (_seance, _mem);
    UASSERT (_res.is_valid ());
    XULOG_TRACE ("IStorageImpl::save, end, " << _res);
    return _res;
  }

  id_chunk_type
  save (const seance_type& _seance, const unsigned char* _mem, const std::size_t _size_mem)
  {
    XULOG_TRACE ("IStorageImpl::save, beg");
    check_state_for_ops ("save");
    const auto _res = save_int (_seance, _mem, _size_mem);
    UASSERT (_res.is_valid ());
    XULOG_TRACE ("IStorageImpl::save, end, " << _res);
    return _res;
  }

  id_chunk_type
  save (const seance_type& _seance, IMemBuff::craw_ptr _mem)
  {
    XULOG_TRACE ("IStorageImpl::save, beg");
    check_state_for_ops ("save");
    const auto _res = save_int (_seance, _mem->get_raw_buff ().get ());
    UASSERT (_res.is_valid ());
    XULOG_TRACE ("IStorageImpl::save, end, " << _res);
    return _res;
  }
#if 0
  void
  get_all_ids (ids_chunk_type& _ids)
  {
    XULOG_TRACE ("IStorageImpl::get_all_ids, beg");
    get_all_ids_int (_ids);
    XULOG_TRACE ("IStorageImpl::get_all_ids, end");
    return;
  }
#endif
#if 0
  id_locker_type
  lock_ids (const ids_chunk_type& _ids)
  {
    XULOG_TRACE ("IStorageImpl::lock_ids, beg");
    auto _res = lock_ids_int (_ids);
    XULOG_TRACE ("IStorageImpl::lock_ids, end, " << _res);
    return _res;
  }

  void
  unlock_ids (const id_locker_type& _lid)
  {
    XULOG_TRACE ("IStorageImpl::unlock_ids, beg");
    unlock_ids_int (_lid);
    XULOG_TRACE ("IStorageImpl::unlock_ids, end");
    return;
  }

  void
  remove_ids (const id_locker_type& _lid)
  {
    XULOG_TRACE ("IStorageImpl::remove_ids, beg");
    remove_ids (_lid);
    XULOG_TRACE ("IStorageImpl::remove_ids, end");
    return;
  }

  void
  get_info_ids (const id_locker_type& _lid)
  {
    XULOG_TRACE ("IStorageImpl::get_info_ids, beg");
    get_info_ids_int (_lid);
    XULOG_TRACE ("IStorageImpl::get_info_ids, end");
    return;
  }
#endif

  protected:
  IStorageImpl () :
    status_ (StateImplsType::stop)
  {}

  void
  check_state_for_ops (const std::string& _op) const
  {
    CHECK_STATE (StateImplsType::run == status_, "invalid status for operation " << _op);
    return;
  }


  private:
  //  IStorageImpl interface
  virtual void          set_info_int (const PathInfo::craw_ptr _info)                                                 = 0;
  virtual bool          change_state_int (const StateImplsType& _state)                                               = 0;
  virtual void          load_int (const seance_type& _seance, const id_chunk_type& _id, IBlockMem::raw_ptr _mem)      = 0;
  virtual id_chunk_type save_int (const seance_type& _seance, IBlockMem::craw_ptr _mem)                               = 0;
  virtual id_chunk_type save_int (const seance_type& _seance, const unsigned char* _mem, const std::size_t _size_mem) = 0;
  //virtual void           get_all_ids_int (ids_chunk_type& _ids)                                                        = 0;
  //virtual id_locker_type lock_ids_int (const ids_chunk_type& _ids)     = 0;
  //virtual void           unlock_ids_int (const id_locker_type& _lid)   = 0;
  //virtual void           remove_ids_int (const id_locker_type& _lid)   = 0;
  //virtual void           get_info_ids_int (const id_locker_type& _lid) = 0;

  StateImplsType status_;      //< Текущие состояние реализации.
};

}}}}      // namespace modules::uuu_storage::appl::impl
