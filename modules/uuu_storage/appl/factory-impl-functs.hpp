//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       factory-impl-functs.hpp
\date       11.08.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl {
/**
  \brief  Фабрика создания реализации хранения бинарных данных.
  \return актуальную реализацию хранения данных.
  */
inline impl::IStorageImpl::ptr
get_storage_impl ()
{
  impl::IStorageImpl::ptr _ret = std::make_shared<impl::storage::test::TestStorageImpl> ("test path2data");
  return _ret;
}
/**
  \brief  Фабрика создания реализации индексирования бинарныз данных.
  \return актуальную реализацию индексирования.
  */
inline impl::IIndexerImpl::ptr
get_indexer_impl ()
{
  impl::IIndexerImpl::ptr _ret = std::make_shared<impl::indexer::test::TestIndexerImpl> ();
  return _ret;
}

}}}      // namespace modules::uuu_storage::appl
