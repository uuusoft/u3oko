#pragma once
/**
\file       impl.hpp
\date       01.01.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief      Програмная реализация коррекции изображения.
*/

namespace dlls { namespace uplifters { namespace vcorrect { namespace soft {
/**
\brief  Модуль для коррекции базовых свойств изображения (насыщенность/тон/яркость.etc).
*/
class Impl : public ICorrectImage
{
  public:
  Impl ();

  virtual ~Impl ();


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ICorrectImage);

  //  ICorrectImage overrides
  virtual void change_state_int (bool _enable) override;
  virtual void update_property_int (const VideoCorrectProp::raw_ptr _info) override;
  virtual bool process_int (IVideoBuff::raw_ptr _h16_buff, IVideoBuff::raw_ptr _s16_buff, IVideoBuff::raw_ptr _l16_buff) override;

  void graduent_correct (IVideoBuff& _buff, const std::array<short, 256>& _vals2vals);

  void bright_correct (IVideoBuff& y16_buff);

  void sat2byte_correct (IVideoBuff& y16_buff);

  VideoCorrectProp::craw_ptr props_;               //< Свойства коррекции изображения, загруженные из xml.
  ::libs::optim::io::hioptim const_add_;           //< Указатель на алгоритм добавление константы к массиву.
  ::libs::optim::io::hioptim sat2byte_;            //< Указатель на алгоритм сжатие диапазона short->byte
  ::libs::optim::io::hioptim grad_funct_;          //< Указатель на алогритм градационного преобразования.
  std::array<short, 256>     contrast_hsl_;        //< Предрасчитанные коэффициенты изменения контраста.
  std::array<short, 256>     saturation_hsl_;      //< Предрасчитанные коэффициенты изменения насыщенности.
  CallerImpl::ptr            pthreads_;            //< Пул потоков для обработки данных.
};

}}}}      // namespace dlls::uplifters::vcorrect::soft
