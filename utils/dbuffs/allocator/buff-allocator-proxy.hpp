#pragma once
/**
\file       buff-allocator-proxy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief
*/

namespace utils { namespace dbuffs { namespace allocator {
/**
\brief  Заместитель для доступа к реализации по управлению буферами для данных.
        Является одиночкой только для статически линкуемых модулей (но сильнее этого и не требуется).
*/
class BuffAllocatorProxy
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BuffAllocatorProxy);
  using create_funct_type = IBuffAllocator::raw_ptr ();

  BuffAllocatorProxy (const BuffAllocatorProxy& _src) = delete;
  BuffAllocatorProxy& operator= (const BuffAllocatorProxy& _src) = delete;
  /**
  \brief      Функция получения экземпляра заместителя.
  \param[in]  _dll_path путь к загружаемому коду системы.
  */
  static BuffAllocatorProxy::raw_ptr
  instance (const std::string& _dll_path)
  {
    static BuffAllocatorProxy g_inst (_dll_path);
    return &g_inst;
  }
  /**
  \brief    Функция получения реализации по управлению буферам (реализации является гарантированно одиночкой для всего процесса системы).
  \return   реализацию.
  */
  IBuffAllocator::raw_ptr
  impl ()
  {
    UASSERT (creator_);
    IBuffAllocator::raw_ptr _ret = creator_ ();
    UASSERT (_ret);
    return _ret;
  }


  private:
  BuffAllocatorProxy (const std::string& _dll_path)
  {
    boost::filesystem::path _cpath (_dll_path);

    _cpath /= ::utils::mem_functs::files::decorate_dll_name ("dbuffs");
    lib_.load (_cpath.string (), boost::dll::load_mode::rtld_now);
    creator_ = boost::dll::import_alias<create_funct_type> (lib_, "instance_buff_allocator");
    UASSERT (creator_);
    return;
  }

  ~BuffAllocatorProxy ()
  {}

  boost::dll::shared_library         lib_;          //< Разделяемый код (dll/so), который содержит в себе реализацию некого интерфейса.
  boost::function<create_funct_type> creator_;      //< Собственно полученная из dll реализация.
};

}}}      // namespace utils::dbuffs::allocator
