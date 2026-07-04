#pragma once
/**
\file       factory_about_sys.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::sys
{
ISysInfo::raw_ptr get_impl ();
}
