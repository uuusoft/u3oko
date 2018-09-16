#pragma once
/**
\file       runtime-info-seance.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       05.09.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace storage { namespace test {
/**
  \brief  Структура для группировки информации, относящейся к каждой открытой сессии.
  */
struct RuntimeInfoSeance
{
  RuntimeInfoSeance () :
    size_data_file_ (0)
  {}

  void
  reset ()
  {
    state_.reset ();
    cursor_.reset ();
    index_state_.reset ();
    data_file_.close ();
    size_data_file_ = 0;
    return;
  }

  StoredInfoSeance            state_;               //< Хранимое состояние всего сенаса обработки данных.
  IStorageImpl::id_chunk_type cursor_;              //< Указатель на текущую позиции записи/чтения, связанную с сеансом обработки данных.
  IndexDataFileState          index_state_;         //< Текущее состояние информации связанной с текущем файлом данных данного сеанса обработки данных.
  std::ofstream               data_file_;           //< Открытый файл данных сеанса обработки данных.
  std::size_t                 size_data_file_;      //< Текущий размер файла данных сеанса. Используется для хранения смещения текущего вставляемого фрагмента.
};

}}}}}}      // namespace modules::uuu_storage::appl::impl::storage::test
