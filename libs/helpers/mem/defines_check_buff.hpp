#pragma once
/**
\file       defines_check_buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#if defined(UUU_ENABLE_CHECK_RW_MEM)

#ifndef UUU_CHECK_MEM_RW
#define UUU_CHECK_MEM_RW(_buff, _size) CHECK_CALL (::libs::helpers::mem::check_buff (_buff, _size), "failed check buff");
#endif
#ifndef UUU_CHECK_MEM_RX
#define UUU_CHECK_MEM_RX(_buff, _size) CHECK_CALL (::libs::helpers::mem::check_read_buff (_buff, _size), "failed read check buff");
#endif

#else

#ifndef UUU_CHECK_MEM_RW
#define UUU_CHECK_MEM_RW(_buff, _size)
#endif
#ifndef UUU_CHECK_MEM_RX
#define UUU_CHECK_MEM_RX(_buff, _size)
#endif

#endif
