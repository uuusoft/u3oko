#pragma once
/**
\file       buffs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.05.2016.
\copyright  www.uuusoft.com
\project    uuu_buffs
\brief      Обявление структуры для группировки связанных буферов с данными.
*/

namespace libs {
/// Пространство имен для функционала по работе с видеобуферами в ОЗУ.
namespace buffs {
//  syn
typedef ::utils::dbuffs::video::consts::offs::off_buff_type off_buff_type;
typedef ::utils::dbuffs::video::IVideoBuff                  IVideoBuff;
typedef ::utils::dbuffs::allocator::BuffAllocatorProxy      BuffAllocatorProxy;
typedef ::utils::dbuffs::video::consts::offs::off_buff_type off_buff_type;
/**
  \brief  Структура для группировки различных вспомогательных буферов, связанным с реальным кадром.
          Например буфера сжатого кадра, буфер разности, буфер оценки движения и прочее.
  */
class Buffs final
{
  public:
  // ext types
  typedef std::function<void(const off_buff_type& _indx, const IVideoBuff::cptr& _buff)> enum_buffs_funct_type;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (Buffs);

  Buffs ();

  ~Buffs ();

  void set_buff (const off_buff_type& _indx, IVideoBuff::ptr& _buff);

  IVideoBuff::raw_ptr operator[] (const off_buff_type& _indx);

  IVideoBuff::craw_ptr operator[] (const off_buff_type& _indx) const;

  void set_indx_base_buff (const off_buff_type& _indx);

  off_buff_type get_indx_base_buff () const;

  void set_flag (const TypeBuffsFlags& _key, bool _val);

  bool get_flag (const TypeBuffsFlags& _key) const;

  void swap (Buffs& _obj);

  void clone (const Buffs& _src);

  void reset (bool _only_indxs);

  void enum_buffs (enum_buffs_funct_type _funct) const;


  private:
  //  int types
  typedef std::unordered_map<off_buff_type, IVideoBuff::ptr>                                                        video_buffs_type;
  typedef ::libs::helpers::utils::ValuesStorage<TypeBuffsFlags, bool, UUU_ICAST_SIZE_T (TypeBuffsFlags::max_bound)> flags_type;

  off_buff_type            indx_base_buff_;      //< Индекс базового буфера, который будет ответственен за свойства, общие для всего списка.
  mutable video_buffs_type childs_;              //< Набор дочерних буферов.
  flags_type               flags_;               //< флаги, общие для всех буферов.
};

}      // namespace buffs
}      // namespace libs
