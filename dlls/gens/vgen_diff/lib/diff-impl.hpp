#pragma once
/**
\brief      Filter for corrected image
\file       diff-impl.hpp
\date       01.01.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vgen_diff_lib
\brief      empty brief
*/

namespace dlls { namespace gens { namespace vgen_diff { namespace lib {
/**
  \brief  empty brief
  */
class DiffImpl final
{
  public:
  DiffImpl ();

  ~DiffImpl ();

  void set_props (VideoDiffProp::craw_ptr _props);

  void init ();

  void itransform (Buffs& _pbuffs);

  void make_diff_buff (const IVideoBuff& _csrc1, IVideoBuff& _csrc2res);

  void bin_buff (const short _bound, const short _val, IVideoBuff* _pdst);


  private:
  //  int types
  using off2buffs_type = std::map<off_buff_type, IVideoBuff::ptr>;

  VideoDiffProp::craw_ptr    props_;               //< Свойства вычисления разности.
  off2buffs_type             indx2prev_buff_;      //< Поле поиска предыдущего буфера (если он существует) по его индексу.
  IVideoBuff::ptr            temp_buff_;           //< Временный буфер для хранения текущего кадра, если источник и назначение разницы совпадают.
  ::libs::optim::io::hioptim cmp_get_const_;       //< Функция сравнения D[i] > Const1 ? Const2 : 0.
  ::libs::optim::io::hioptim abs_diff_;            //< Функция вычисления абсолютной разности между двумя изображениями.
  CallerImpl::ptr            pthreads_;            //< Пул потоков для обработки данных.
};

}}}}      // namespace dlls::gens::vgen_diff::lib
