#pragma once
/**
\file       buf-allocator-proxy.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2016
\project    u3_dbufs
*/
extern "C" BOOST_SYMBOL_EXPORT utils::dbufs::allocator::BufAllocator* create_dbufs_impl ();

namespace utils::dbufs::allocator
{
/// Заместитель для доступа к реализации по управлению буферами для данных
/// Является одиночкой только для статически линкуемых модулей (но сильнее этого и не требуется)
class BufAllocatorProxy final
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (BufAllocatorProxy)

  using create_func_type = IBufAllocator::raw_ptr ();

  BufAllocatorProxy (const BufAllocatorProxy& src)            = delete;
  BufAllocatorProxy& operator= (const BufAllocatorProxy& src) = delete;

  /// Функция получения экземпляра заместителя
  /// \param[in]  dll_path путь к загружаемому коду системы
  static BufAllocatorProxy::raw_ptr
  instance (const std::string& dll_path)
  {
    static BufAllocatorProxy g_inst (dll_path);
    return &g_inst;
  }

  /// Функция получения реализации по управлению буферам (реализации является гарантированно одиночкой для всего процесса системы)
  /// \return   реализацию
  IBufAllocator::raw_ptr
  impl ()
  {
    U3_ASSERT (creator_);
    IBufAllocator::raw_ptr _ret = creator_ ();
    U3_ASSERT (_ret);
    return _ret;
  }

  private:
  BufAllocatorProxy (U3_MARK_UNUSED const std::string& dll_path)
  {
#ifdef U3_BUILD_MODULES_AS_LIBS
    U3_MARK_UNUSED_HERE (lib_);
    creator_ = create_dbufs_impl;
#else
    boost::filesystem::path _cpath (dll_path);

    _cpath /= ::libs::helpers::dlls::decorate_dll_name ("dbufs");
    lib_.load (_cpath.string (), boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#  if defined(U3_OS_ANDROID)
    creator_ = reinterpret_cast< create_func_type* > (dlsym (lib_.native (), "create_dbufs_impl"));
#  else
    creator_ = boost::dll::import_symbol< create_func_type > (lib_, "create_dbufs_impl");
#  endif
#endif
    U3_ASSERT (creator_);
  }

  ~BufAllocatorProxy ()
  {
  }

  ::libs::helpers::dlls::dll_type     lib_;       //< Разделяемый код (dll/so), который содержит в себе реализацию некого интерфейса
  boost::function< create_func_type > creator_;   //< Собственно полученная из dll реализация
};
}   // namespace utils::dbufs::allocator
