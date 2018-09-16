//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Внешний интерфейс включения модуля.
*/
#include "syns.hpp"

#include "type-flags-buff.hpp"
#include "type-mem-var.hpp"
#include "ibuff.hpp"
#include "imem-buff.hpp"

#include "video/consts/vals.hpp"
#include "video/consts/offs/off-buff-type.hpp"
#include "video/consts/offs/consts_offs.hpp"
#include "video/consts/offs/is_valid.hpp"
#include "video/consts/offs/str2eoffbuff.hpp"

#include "video/type-dim-var.hpp"
#include "video/type-check-dim.hpp"
#include "video/type-sub-sample.hpp"
#include "video/alloc-buff-info.hpp"
#include "video/ivideo-buff.hpp"

#include "allocator/ibuff-allocator.hpp"
#include "allocator/buff-allocator.hpp"
#include "allocator/buff-allocator-proxy.hpp"

#include "video/helpers/override_data.hpp"
#include "video/helpers/is_equal_dim.hpp"
#include "video/helpers/buff_get_data_functs.hpp"
#include "video/helpers/buff-filling-functs.hpp"
#include "video/helpers/fill_convolution_edges.hpp"
#include "video/helpers/reset_edges.hpp"
#include "video/helpers/invert_rows.hpp"

#include "video/helpers/dump-buff-funct.hpp"
