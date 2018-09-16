#pragma once
/**
\file       imme-buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       11.08.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      empty brief.
*/
namespace utils { namespace dbuffs { namespace allocator {
//  forward
class BuffAllocator;
}}}      // namespace utils::dbuffs::allocator


namespace utils { namespace dbuffs {
// syn
using ::utils::mem_functs::impl::BlockMemAllocatorProxy;
using ::utils::mem_functs::IBlockMem;
using ::libs::helpers::utils::cuuid;
/**
\brief  Базовый интерфейс хранения буфера в ОЗУ под кадр (звук/видео).
*/
class IMemBuff : public IBuff
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IMemBuff);
  using fragments_type = std::list<mem_type>;

  virtual ~IMemBuff ();

  IMemBuff (const IMemBuff& _rsc) = delete;
  IMemBuff& operator= (const IMemBuff& _src) = delete;

  IBlockMem::ptr
  get_raw_buff () const
  {
    return raw_;
  }

  const fragments_type&
  get_fragments () const
  {
    return fragments_;
  }

  void
  set_fragments (const fragments_type& _src)
  {
    fragments_ = _src;
    return;
  }


  protected:
  //  int types
  using mem_vars_type = libs::helpers::utils::ValuesStorage<TypeMemVar, mem_type, UUU_ICAST_SIZE_T (TypeMemVar::max_bound)>;
  //  IBuff overrides
  virtual void                 set_mem_var_int (const TypeMemVar& _type, mem_type _val) override;
  virtual mem_type             get_mem_var_int (const TypeMemVar& _type) const override;
  virtual void                 clone_int (IBuff::craw_ptr _isrc, float _percent) override;
  virtual void                 swap_int (IBuff& _isrc) override;
  virtual unsigned char*       get_buff_int () override;
  virtual const unsigned char* get_cbuff_int () const override;
  /**
  \brief      Функция выделения блока памяти.
  \param[in]  _size размер блока в байтах.
  */
  void ialloc (const mem_type& _size);

  void flush ();

  IMemBuff ();


  private:
  mutable IBlockMem::ptr raw_;            //< Сырой, выровненный блок памяти для данных.
  mem_vars_type          mem_vars_;       //< Массив для переменных геометрии кадра.
  fragments_type         fragments_;      //< Опциональный список фрагментов в буфере, если их количество больше 1. Например для случая обработки данных от x264 кодека.
};

}}      // namespace utils::dbuffs
