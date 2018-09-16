#pragma once
/**
\file       ioptim-proxy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief    
*/

namespace libs { namespace optim { namespace io {
/**
\brief  Тип для доступа к реализации интерфейса по управлению оптимизированными алгоритмами.
        Реализован через шаблон проектирования "одиночка в строго смысле слова в пределах процесса".
*/
class IOptimProxy
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IOptimProxy);
  using create_ioptim_funct_type=IOptim::raw_ptr();

  IOptimProxy (const IOptimProxy& _src) = delete;
  IOptimProxy& operator= (const IOptimProxy& _src) = delete;

  static IOptimProxy::raw_ptr
  instance (const std::string& _dll_path)
  {
    static IOptimProxy g_inst (_dll_path);
    return &g_inst;
  }

  IOptim::raw_ptr
  impl ()
  {
    UASSERT (creator_);
    IOptim::raw_ptr _ret = creator_ ();
    UASSERT (_ret);
    return _ret;
  }


  private:
  explicit IOptimProxy (const std::string& _dll_path)
  {
    boost::filesystem::path _cpath (_dll_path);
    _cpath /= ::utils::mem_functs::files::decorate_dll_name ("vdd_doptim");

    creator_ = boost::dll::import_alias<create_ioptim_funct_type> (_cpath, "instance_doptim");
    UASSERT (creator_);
    return;
  }

  ~IOptimProxy ()
  {}

  boost::function<create_ioptim_funct_type> creator_;      //< ???
};

}}}      // namespace libs::optim::io
