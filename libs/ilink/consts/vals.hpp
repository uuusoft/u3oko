//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       vals.hpp
\date       17.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

namespace libs { namespace ilink { namespace consts {
// syn
using ::libs::ievents::props::base_id::id_link_module_type;

const id_link_module_type id_any     = "";
const id_link_module_type id_appl    = "module_appl";
const id_link_module_type id_http    = "module_http";
const id_link_module_type id_gui     = "module_gui";
const id_link_module_type id_storage = "module_storage";
const id_link_module_type id_rtp     = "module_rtp";
const id_link_module_type id_events  = "module_events";
const id_link_module_type id_log     = "module_log";
const id_link_module_type id_data    = "module_data";

const id_link_module_type id_yduff   = "module_yduff";
const id_link_module_type id_bench   = "module_bench";
const id_link_module_type id_u3ipcam = "module_u3ipcam";
const id_link_module_type id_u3drv   = "module_u3drv";
const id_link_module_type id_u3watch = "module_u3watch";
const id_link_module_type id_u3oko   = "module_u3oko";
const id_link_module_type id_u3mask  = "module_u3mask";

}}}      // namespace libs::ilink::consts
