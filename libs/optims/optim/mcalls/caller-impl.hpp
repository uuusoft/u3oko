#pragma once
/**
\file       caller-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace mcalls {
//  syn
using ::libs::helpers::statistic::ExpandedTimeStatistic;
using ::libs::helpers::statistic::helpers::functors::AddTimeStatistic;
using ::libs::helpers::sys::cpu::TypeExtCpu;
/**
\brief  РљР»Р°СЃСЃ СЂРµР°Р»РёР·СѓРµС‚ РІС‹Р·РѕРІ РїР°СЂР°Р»Р»РµР»СЊРЅС‹Р№ РІС‹Р·РѕРІ РєРѕРґР° РІ РЅРµСЃРєРѕР»СЊРєРёС… РїРѕС‚РѕРєР°С….
*/
class CallerImpl final
{
  public:
  //  ext types
  using statistic_work_funct_type = std::function<bool(ExpandedTimeStatistic& _obj)>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (CallerImpl);

  CallerImpl ();

  ~CallerImpl ();

  CallerImpl (const CallerImpl& _src) = delete;
  CallerImpl& operator= (const CallerImpl& _src) = delete;
  /**
  \brief      Р¤СѓРЅРєС†РёСЏ СѓСЃС‚Р°РЅРѕРІРєРё РєРѕР»РёС‡РµСЃС‚РІР° СЂР°Р±РѕС‡РёС… РїРѕС‚РѕРєРѕРІ
  \param[in]  _count  РєРѕР»РёС‡РµСЃС‚РІРѕ СЂР°Р±РѕС‡РёС… РїРѕС‚РѕРєРѕРІ.
  */
  void set_count_threads (unsigned short _count);
  /**
  \brief  Р¤СѓРЅРєС†РёСЏ РІРѕР·СЂР°С‰Р°РµС‚ РєРѕР»РёС‡РµСЃС‚РІРѕ СЂР°Р±РѕС‡РёС… РїРѕС‚РѕРєРѕРІ.
  \return РєРѕР»РёС‡РµСЃС‚РІРѕ СЂР°Р±РѕС‡РёС… РїРѕС‚РѕРєРѕРІ
  */
  const unsigned short get_count_threads () const;
  /**
  \brief      Р¤СѓРЅРєС†РёСЏ СѓСЃС‚Р°РЅР°РІР»РёРІР°РµС‚ СЂР°СЃС€РёРµСЂРЅРёРµ РїСЂРѕС†РµСЃСЃРѕСЂР° РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё РґР°РЅРЅС‹С… РІ СЂР°Р±РѕС‡РёС… РїРѕС‚РѕРєР°С….
  \param[in]  _simd СЂР°СЃС€РёСЂРµРЅРёРµ cpu.
  */
  void set_cpu (const TypeExtCpu& _simd);
  /**
  \brief      Р¤СѓРЅРєС†РёСЏ РґР»СЏ 
  \param[in]  _funct    
  \param[in]  _info   
  \param[in]  _athreads 
  */
  void mcall (const InfoMFunct& _funct, io::MCallInfo& _info, const unsigned short _athreads = 0);
  /**
  \brief      Р¤СѓРЅРєС†РёСЏ РґР»СЏ РёР·РјРµРЅРµРЅРёСЏ РІРЅСѓС‚СЂРµРЅРЅРµРіРѕ РѕР±СЉРµРєС‚Р° СЃС‚Р°С‚РёСЃС‚РёРєРё РІСЂРµРјРµРЅРё РІС‹РїРѕР»РЅРµРЅРёСЏ Р°Р»РѕРіСЂРёС‚РјРѕРІ.
  \param[in]  _funct  С„СѓРЅРєС†РёСЏ РёР·РјРµРЅРµРЅРёСЏ РѕР±СЉРµРєС‚Р° СЃС‚Р°С‚РёСЃС‚РёРєРё.
  \return     true, РїСЂРё СѓСЃРїРµС…Рµ.
  */
  bool
  work_with_statistic (statistic_work_funct_type _funct)
  {
    guard_type _grd (mtx_);
    return _funct (expand_time_algs_);
  }

  void thread_funct_impl (const unsigned short _indx_thread);

  void thread_postfunct_impl ();


  private:
  //  int types
  using sync_type         = std::mutex;
  using guard_type        = std::lock_guard<sync_type>;
  using functs_mcall_type = std::vector<io::funct_mcall_type>;

  bool stop_and_wait_threads ();

  void create_threads ();

  bool mcall_int (const InfoMFunct& _funct, io::MCallInfo& _info, unsigned short _athreads);

  SharedInfoMFunct           sinfo_;                 //< Р Р°Р·РґРµР»СЏРµРјР°СЏ РёРЅС„РѕСЂРјС†РёСЏ РјРµР¶РґСѓ РІСЃРµРјРё РїРѕС‚РѕРєР°РјРё.
  unsigned short             max_threads_;           //< РњР°РєСЃРёРјР°Р»СЊРЅРѕРµ РєРѕР»РёС‡РµСЃС‚РІРѕ РїРѕС‚РѕРєРѕРІ, РєРѕС‚РѕСЂРѕРµ РјРѕР¶РЅРѕ Р±СѓРґРµС‚ РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ.
  std::vector<std::thread>   threads_;               //< Р Р°Р±РѕС‡РёРµ РїРѕС‚РѕРєРё.
  TypeExtCpu                 simd_;                  //< Р Р°СЃС€РёСЂРµРЅРёРµ РїСЂРѕС†РµСЃСЃРѕСЂР° РёРґРё DSP РєРѕС‚РѕСЂРѕРµ РґРѕР»Р¶РЅРѕ РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊСЃСЏ РЅР° РјРѕРјРµРЅС‚ РІС‹Р·РѕРІР°.
  std::vector<io::MCallInfo> calls_;                 //< РќРµ СЂР°Р·РґРµР»СЏРµРјР°СЏ РёРЅС„РѕСЂРјР°С†РёСЏ РІС‹Р·РѕРІР° РґР»СЏ РєР°Р¶РґРѕРіРѕ РїРѕС‚РѕРєР°.
  std::vector<std::size_t>   src_heights_;           //< Р’С‹СЃРѕС‚С‹ РІСЃРµС… РёСЃС‚РѕС‡РЅРёРєРѕРІ РІСЃРµС… РїРѕС‚РѕРєРѕРІ, С‚.Рє. РґР»СЏ РєР°Р¶РґРѕРіРѕ РїРѕС‚РѕРєР° РІРѕР·РјРѕР¶РЅРѕ СѓРЅРёРєР°Р»СЊРЅРѕРµ РґРµР»РµРЅРёРµ РїРѕ РІС‹СЃРѕС‚Рµ.
  functs_mcall_type          thread_functs_;         //< Р Р°Р±РѕС‡РёРµ С„СѓРЅРєС†РёРё РїРѕС‚РѕРєРѕРІ, С‚.Рµ. С„Р°РєС‚РёС‡РµСЃРєРё Р°Р»РіРѕСЂРёС‚РјС‹ РѕР±СЂР°Р±РѕС‚РѕРєРё РґР°РЅРЅС‹С….
  mutable sync_type          mtx_;                   //< РЎРёРЅСЂРѕРЅРёР·РёСЂСѓСЋС‰РёР№ РїСЂРёРјРёС‚РёРІ РґР»СЏ СѓРїРѕСЂСЏРґРѕС‡РёРІР°РЅРёСЏ РґРѕСЃС‚СѓРїР° Рє РѕР±СЉРµРєС‚Сѓ.
  ExpandedTimeStatistic      expand_time_algs_;      //< Р’СЂРµРјРµРЅР° Р·Р°С‚СЂР°С‡РµРЅРЅС‹Рµ РєР°Р¶РґС‹Рј Р°Р»РіРѕСЂРёС‚РјРѕРј.
};

}}}      // namespace libs::optim::mcalls
