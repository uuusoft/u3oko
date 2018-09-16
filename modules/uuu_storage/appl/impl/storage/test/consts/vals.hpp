#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       05.09.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace storage { namespace test { namespace consts {

using consts_val_type = int;

const consts_val_type max_count_session_data_files          = 1 * 1024 * 1024;        //< Максимально количество файлов данных в одной сессии
const consts_val_type max_size_session_data_file            = 256 * 1024 * 1024;      //< Максимальный размер одного файла данных сессии в байтах
const consts_val_type max_count_fragments_session_data_file = 32 * 1024;              //< Максимальное количество фрагментов в одном файле данных конкретной сессии

const std::string name_seance_info_file    = "seance_state";      //< Имя файла для сохранения состояния сеанса записи в целом.
const std::string name_ext_index_data_file = "indx";              //< Имя файла для сохранения индексов данных из одного файла данных.
const std::string name_ext_data_file       = "bin";               //< Имя файла для сохранения данных.

}}}}}}}      // namespace modules::uuu_storage::appl::impl::storage::test::consts
