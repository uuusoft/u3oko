#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       15.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace indexer { namespace test {

const std::size_t max_count_records_per_seance = 100 * 1024;      //< Максимальное количеств записей (файлов) в одном сеансе.
const std::size_t max_count_seances_per_object = 1 * 256;         //< Максимальное количество сеансов записи для одного объекта.

}}}}}}      // namespace modules::uuu_storage::appl::impl::indexer::test
