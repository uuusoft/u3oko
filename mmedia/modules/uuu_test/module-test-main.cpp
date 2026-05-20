/**
\file       module-test-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       07.04.2026
\project    u3_module_test
\brief      Базовый файл системы, для загрузки всех связанных с ней модулей.
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"

#if defined(U3_OS_WIN32_DESKTOP)
#  include <shellscalingapi.h>
#endif

#include <regex>
#include "module-test.hpp"

extern "C" BOOST_SYMBOL_EXPORT int
main_impl_test (int argc, char* argv[])
{
  try
  {
    // ub test
    volatile std::int32_t t1;

    std::int32_t t2 = 10;
    std::int32_t t3 = t1;
    t2 += t1;
    t3 += t2;
    U3_XLOG_DEV ("check ub1" + VTOLOG (t1) + VTOLOG (t2) + VTOLOG (t3));

    t2 = 0xFFFFFFFF;
    t3 = 0xFFFFFFFF;
    t1 = t2 + t3;
    U3_XLOG_DEV ("check ub1" + VTOLOG (t1) + VTOLOG (t2) + VTOLOG (t3));

    t2 = 0x7FFFFFFF;
    t3 = 0x7FFFFFFF;
    t1 = t2 + t3;
    U3_XLOG_DEV ("check ub1" + VTOLOG (t1) + VTOLOG (t2) + VTOLOG (t3));

#if 0    
    setup_signals_catch ();
    prepare_process ();
    init_process (argc, argv);
    work_process ();
#endif
  }
  catch (boost::interprocess::interprocess_exception& e)
  {
    U3_XLOG_ERROR ("exception interprocess: " + std::string (boost::diagnostic_information (e)));
  }
  catch (boost::exception& e)
  {
    U3_XLOG_ERROR ("exception boost: " + std::string (boost::diagnostic_information (e)));
  }
  catch (std::exception& e)
  {
    U3_XLOG_ERROR ("exception: " + std::string (e.what ()));
  }
  catch (...)
  {
    U3_XLOG_ERROR ("unknown exception");
  }
#if 0
  deinit_process ();
#endif
  U3_XLOG_DEV ("STOP test");
  return 0;
}


int
main (int argc, char* argv[])
{
  return main_impl_test (argc, argv);
}
