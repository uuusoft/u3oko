//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       core-int-functs.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Реализация внутренних функций ядра.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "includes.hpp"
#include "core.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 {

void
Core::get_paths_int (out_wpaths_type& _paths)
{
  guard_type _grd (mtx_);
  _paths.clear ();
  std::copy (paths_.begin (), paths_.end (), std::back_inserter (_paths));
  return;
}


IPath::weak_ptr
Core::create_path_int ()
{
  guard_type _grd (mtx_);
  paths_.push_back (std::make_shared<impl::var1::path::Path> ());      // ::ptr( new impl::var1::path::Path ) );
  return IPath::weak_ptr (paths_.back ());
}


bool
Core::delete_path_int (IPath::weak_ptr _obj)
{
  guard_type _grd (mtx_);
  auto       _iobj = _obj.lock ();
  if (!_iobj)
    {
      return false;
    }

  auto _ofind = std::find (paths_.begin (), paths_.end (), _iobj);
  if (_ofind == paths_.end ())
    {
      XULOG_WARNING ("failed delete, path not found");
      UASSERT_SIGNAL ("failed");
      return false;
    }

  paths_.erase (_ofind);
  _iobj.reset ();
  return true;
}


void
Core::delete_paths ()
{
  guard_type _grd (mtx_);
  for (auto& _path : paths_)
    {
      const auto _count = _path.use_count ();
      if (1 != _count)
        {
          XULOG_WARNING ("Core::delete_paths, try delete path with ref count, " << _count);
          UASSERT (1 == _count);      //  внешних ссылок не должно быть.
        }
      _path.reset ();
    }
  return;
}

}}}}      // namespace libs::icore::impl::var1
