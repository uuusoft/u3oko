#pragma once
/**
\file       check-copy-state-event-defines.hpp
\date       10.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/

#ifndef U3_CHECK_COPY_EVENT
#  define U3_CHECK_COPY_EVENT(u3def_event_type)                                           \
    const auto dsrc = ::libs::iproperties::helpers::cast_event< u3def_event_type > (src); \
    U3_CHECK (dsrc, std::string ("invalid event type") + PTR_TOLOG (src) + " empty " + PTR_TOLOG (dsrc) + #u3def_event_type);
#endif
