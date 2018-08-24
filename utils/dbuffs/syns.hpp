//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syns.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Различные синонимы к типам для данного модуля (для сокращения записи).
*/

namespace utils {
/// Пространство имен для функционала буферов памяти в ОЗУ.
namespace dbuffs {
/// Пространство имен функционала буферов памяти для кадра с видеоданными.
namespace video {
//  syn
using ::libs::helpers::utils::cuuid;

namespace cs16buffs = ::libs::optim::s16bit::conv::consts::buffs;
namespace smem      = ::libs::helpers::mem;

}      // namespace video
}      // namespace dbuffs
}      // namespace utils
