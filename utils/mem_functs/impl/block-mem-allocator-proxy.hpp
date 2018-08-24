#pragma once
/**
\file       block-mem-allocator-proxy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      empty brief
*/

namespace utils { namespace mem_functs { namespace impl {
/**
  \brief  Одиночка в широком смысле. (для всего процесса, т.е. в том числе и для загружаемых модулей (dll/so)).
          Точка доступа к интерфейсу по выделению блоков памяти.
  */
class BlockMemAllocatorProxy
{
  public:
  //  ext types
  using create_funct_type  = IBlockMemAllocator::raw_ptr ();
  using bcreate_funct_type = boost::function<create_funct_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BlockMemAllocatorProxy);

  BlockMemAllocatorProxy (const BlockMemAllocatorProxy& _src) = delete;
  BlockMemAllocatorProxy& operator= (const BlockMemAllocatorProxy& _src) = delete;

  static BlockMemAllocatorProxy::raw_ptr
  instance (const std::string& _dll_path = std::string (""))
  {
    static BlockMemAllocatorProxy g_inst (_dll_path);
    return &g_inst;
  }

  IBlockMemAllocator::raw_ptr
  impl ()
  {
    UASSERT (creator_);
    IBlockMemAllocator::raw_ptr _ret = creator_ ();
    UASSERT (_ret);
    return _ret;
  }


  private:
  BlockMemAllocatorProxy (const std::string& _dll_path)
  {
    boost::filesystem::path _cpath (_dll_path);
    _cpath /= ::utils::mem_functs::files::decorate_dll_name ("mem_functs");
    creator_ = boost::dll::import_alias<create_funct_type> (_cpath, "instance_block_mem");
    UASSERT (creator_);
    return;
  }

  ~BlockMemAllocatorProxy ()
  {}

  bcreate_funct_type creator_;      //< Функция создания реализации функционала в dll/so.
};

}}}      // namespace utils::mem_functs::impl
