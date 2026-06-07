/**
\file       sqlite-call-helper-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       06.06.2022
\project    mevents
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "sqlite3.h"
#include "../helpers-lib-includes_int.hpp"
#include "sql-resource-managment-helpers.hpp"

namespace libs::helpers::sqlite
{
MemoryHandler::~MemoryHandler ()
{
  if (buf_)
  {
    sqlite3_free (buf_);
  }
}


void**
MemoryHandler::update ()
{
  if (buf_)
  {
    sqlite3_free (buf_);
    buf_ = nullptr;
  }
  return &buf_;
}


void*
MemoryHandler::get ()
{
  return buf_;
}
}   // namespace libs::helpers::sqlite
