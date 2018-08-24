#pragma once
/**
\file       ibuff-allocator.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление интерфейса для выделения буферов под видео/аудио данные.
*/

namespace utils { namespace dbuffs { namespace allocator {
/**
  \brief  Интерфейс по выделению буферов под данные. 
          Реализуется как "одиночка" для системы в целом (как для статически линкуемых модулей, так и для динамически загружаемых).
  */
class IBuffAllocator
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IBuffAllocator);

  IBuffAllocator (const IBuffAllocator& _src) = delete;
  IBuffAllocator& operator= (const IBuffAllocator& _src) = delete;
  /**
    \brief    Функция получения (создание нового или возврает ранее созданного и свободного) буфера.
    \return   указатель на выделенный буфер.
    */
  virtual utils::dbuffs::video::IVideoBuff::ptr get () = 0;
  /**
    \brief    Функция трассировки состояния реализации интерфейса. Количество буферов, количество свободных буферов, используемая память и т.п.
    */
  virtual void dump_state () = 0;


  protected:
  IBuffAllocator ()
  {}

  virtual ~IBuffAllocator ()
  {}
};

}}}      // namespace utils::dbuffs::allocator
