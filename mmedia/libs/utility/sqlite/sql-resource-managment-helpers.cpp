/**
\file       sqlite-call-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.06.2022
\project    mevents
*/
#include "../utility-lib-includes_int.hpp"
#include "sqlite3.h"
#include "sql-resource-managment-helpers.hpp"

// old shit
namespace libs::utility::sqlite
{
MemoryHandler::~MemoryHandler ()
{
  if (buf_)
  {
    sqlite3_free (buf_);
  }
}


auto
MemoryHandler::update () -> void**
{
  if (buf_)
  {
    sqlite3_free (buf_);
    buf_ = nullptr;
  }
  return &buf_;
}


auto
MemoryHandler::get () -> void*
{
  return buf_;
}
}   // namespace libs::utility::sqlite
