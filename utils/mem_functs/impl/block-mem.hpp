#pragma once
/**
\file       block-mem.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief    
*/

namespace utils { namespace mem_functs { namespace impl {
/**
\brief  Реализация работы с блоком памяти.
*/
class BlockMem : public IBlockMem
{
  public:
  BlockMem (const std::size_t _size);

  virtual ~BlockMem ();


  private:
  //  IBlockMem overrides
  virtual unsigned char*       get_int () override;
  virtual const unsigned char* get_int () const override;
  virtual std::size_t          get_buff_size_int () const override;
  virtual std::size_t          get_data_size_int () const override;
  virtual void                 set_data_size_int (std::size_t _data_size) override;
  virtual void                 resize_int (const std::size_t _size) override;

  void reset_memory();

  unsigned char* buff_;           //< Сырой блок памяти.
  std::size_t    size_;           //< Размер сырого блока памяти.
  std::size_t    data_size_;      //< Размер данных в блоке.
};

}}}      // namespace utils::mem_functs::impl
