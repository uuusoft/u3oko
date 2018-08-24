//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       vals_size.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      Набор констат для максимальных размеров данных, передваемых между подсистемами за один раз.
*/

namespace libs { namespace link { namespace consts { namespace size {

const std::size_t buff_all2log    = 1 * 1024 * 1024;      //< ???
const std::size_t buff_all2events = 1 * 1024 * 1024;      //< ???

const std::size_t max_width_one_frame  = 3 * 1024;                                                                           //< ???
const std::size_t max_height_one_frame = 2 * 1024;                                                                           //< ???
const std::size_t buff_for_one_frame   = max_width_one_frame * max_height_one_frame * 2 * 3 + max_width_one_frame * 64;      //< ???

#if defined(UUU_OS_WIN32_DESKTOP)

const std::size_t buff_appl2gul     = 2 * buff_for_one_frame;      //< ???
const std::size_t buff_appl2appl    = 20 * 1024 * 1024;            //< ???
const std::size_t buff_appl2data    = 20 * 1024 * 1024;            //< ???
const std::size_t buff_appl2http    = 20 * 1024 * 1024;            //< ???
const std::size_t buff_appl2storage = 10 * 1024 * 1024;            //< ???

#elif defined(UUU_OS_GNU_LINUX)

const std::size_t buff_appl2gul     = 2 * buff_for_one_frame;
const std::size_t buff_appl2appl    = 20 * 1024 * 1024;
const std::size_t buff_appl2data    = 20 * 1024 * 1024;
const std::size_t buff_appl2http    = 20 * 1024 * 1024;      //< ???
const std::size_t buff_appl2storage = 10 * 1024 * 1024;      //< ???

#elif defined(UUU_OS_RASPBERRY)

const std::size_t buff_appl2gul     = 1024 * 1024;      //  В данном случае фактически ничего не передается.
const std::size_t buff_appl2appl    = 5 * 1024 * 1024;
const std::size_t buff_appl2data    = 5 * 1024 * 1024;
const std::size_t buff_appl2http    = 5 * 1024 * 1024;      //< ???
const std::size_t buff_appl2storage = 5 * 1024 * 1024;      //< ???

#elif defined(UUU_OS_ANDROID)

const std::size_t buff_appl2gul     = 1 * buff_for_one_frame;
const std::size_t buff_appl2appl    = 10 * 1024 * 1024;
const std::size_t buff_appl2data    = 10 * 1024 * 1024;
const std::size_t buff_appl2http    = 10 * 1024 * 1024;      //< ???
const std::size_t buff_appl2storage = 5 * 1024 * 1024;       //< ???

#else
#error select OS
#endif

}}}}      // namespace libs::link::consts::size
