#pragma once
/**
\file       vcodec-gen-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcodec_gen
*/

namespace dlls::codecs::vcodec_gen
{
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  public:
  //  ext types
  using icodec_type  = std::array< syn::VideoCodecProp, 4 >;
  using icodecs_type = std::vector< icodec_type >;

  InfoFilter ();
  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  void init ();

  syn::VideoCodecProp::raw_ptr        rprops_         = nullptr;   //< Настроенный указатель на свойства (для удобства)
  codec_gen::CodecGeneric::raw_ptr    dll_codec_      = nullptr;   //< Указатель на кодек, полученный из библиотеки
  std::uint64_t                       counter_frames_ = 0;         //< Счетчик кадров
  CodecImplInfo                       file_info_;                  //< Информация из файла с кодеком
  syn::ICodecImage::weak_ptr          active_codec_impl_;          //< Выбранная на данный момент реализация кодека Может например прийти вместе с сообщением syn::InterfCodecImageEvent
  ::libs::helpers::fps::FpsController fps_;                        //< Поле для контроля fps

  protected:
  //  BaseInfoFilter overrides
  virtual void sync_int (bool force) override;
};
}   // namespace dlls::codecs::vcodec_gen
