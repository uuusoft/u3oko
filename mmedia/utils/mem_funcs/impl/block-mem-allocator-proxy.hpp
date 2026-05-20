#pragma once
/**
\file       block-mem-allocator-proxy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mem_funcs
*/
extern "C" BOOST_SYMBOL_EXPORT utils::mem_funcs::IBlockMemAllocator::raw_ptr create_mem_impl ();

namespace utils::mem_funcs::impl
{
/// Одиночка в широком смысле. (для всего процесса, т.е. в том числе и для загружаемых модулей (dll/so))
/// Точка доступа к интерфейсу по выделению блоков памяти
class BlockMemAllocatorProxy final
{
  public:
  //  ext types
  using create_func_type  = IBlockMemAllocator::raw_ptr ();
  using bcreate_func_type = boost::function< create_func_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BlockMemAllocatorProxy)

  BlockMemAllocatorProxy (const BlockMemAllocatorProxy& src)            = delete;
  BlockMemAllocatorProxy& operator= (const BlockMemAllocatorProxy& src) = delete;

  static BlockMemAllocatorProxy::raw_ptr
  instance (const std::string& dll_path = std::string (""))
  {
    static BlockMemAllocatorProxy g_inst (dll_path);
    return &g_inst;
  }

  IBlockMemAllocator::raw_ptr
  impl ()
  {
    U3_ASSERT (creator_);
    IBlockMemAllocator::raw_ptr _ret = creator_ ();
    U3_ASSERT (_ret);
    return _ret;
  }

  private:
  BlockMemAllocatorProxy (const std::string& dll_path)
  {
#ifdef U3_BUILD_MODULES_AS_LIBS
    U3_MARK_UNUSED_HERE (lib_);
    creator_ = create_mem_impl;
#else
    boost::filesystem::path _cpath (dll_path);
    _cpath /= ::libs::helpers::dlls::decorate_dll_name ("mem_funcs");

    try
    {
      lib_.load (_cpath, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);
    }
    catch (U3_MARK_UNUSED boost::exception& _e)
    {
      U3_XLOG_ERROR ("try load memory lib " + _cpath.string () + std::string (boost::diagnostic_information_what (_e, true)));
    }

#  if defined(U3_OS_ANDROID)
    creator_ = reinterpret_cast< create_func_type* > (dlsym (lib_.native (), "create_mem_impl"));
#  else
    creator_ = ::boost::dll::import_symbol< create_func_type > (_cpath, "create_mem_impl");
#  endif
#endif
    U3_ASSERT (creator_);
  }

  ~BlockMemAllocatorProxy ()
  {
  }

  ::libs::helpers::dlls::dll_type lib_;       //< Загруженная библиотека по работе с памятью
  bcreate_func_type               creator_;   //< Функция создания реализации функционала в dll/so
};
}   // namespace utils::mem_funcs::impl
