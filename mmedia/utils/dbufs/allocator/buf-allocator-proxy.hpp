#pragma once
/**
\file       buf-allocator-proxy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_dbufs
*/

#if (U3_BUILD_MODULES_AS_LIBS == 1)
extern "C" BOOST_SYMBOL_EXPORT utils::dbufs::allocator::IBufAllocator::raw_ptr create_dbufs_impl ();
#endif

namespace utils::dbufs::allocator
{
/// Заместитель для доступа к реализации по управлению буферами для данных
/// Является одиночкой только для статически линкуемых модулей (но сильнее этого и не требуется)
class BufAllocatorProxy final
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (BufAllocatorProxy)
  U3_ADD_DELETE_MOVE_COPY (BufAllocatorProxy)

  using create_func_type = IBufAllocator::raw_ptr ();

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
#if (U3_BUILD_MODULES_AS_LIBS == 1)
    U3_MARK_UNUSED_HERE (lib_);
    creator_ = create_dbufs_impl;
#else
    boost::filesystem::path cpath (dll_path);

    cpath /= ::libs::utility::dlls::decorate_dll_name ("dbufs");
    lib_.load (cpath.string (), boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#  ifdef U3_OS_ANDROID
    creator_ = ::libs::utility::casts::reinterpret_cast_helper< create_func_type* > (dlsym (lib_.native (), "create_dbufs_impl"));
#  else
    creator_ = boost::dll::import_symbol< create_func_type > (lib_, "create_dbufs_impl");
#  endif
#endif
    U3_ASSERT (creator_);
  }

  ~BufAllocatorProxy () = default;

  ::libs::utility::dlls::dll_type   lib_;       //< Разделяемый код (dll/so), который содержит в себе реализацию некого интерфейса
  std::function< create_func_type > creator_;   //< Собственно полученная из dll реализация
};
}   // namespace utils::dbufs::allocator
