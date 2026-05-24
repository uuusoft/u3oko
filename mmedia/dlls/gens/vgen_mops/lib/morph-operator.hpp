#pragma once
/**
\file       morph-operator.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       16.07.2018
\project    u3_vgen_mops_lib
*/

namespace dlls::gens::vgen_mops::lib::helpers
{
/// Вспомогательный объект для вычисления МО
class MorphOperator final
{
  public:
  MorphOperator ();
  ~MorphOperator ();

  MorphOperator (const MorphOperator& src)            = delete;
  MorphOperator& operator= (const MorphOperator& src) = delete;

  void init ();
  void set_transform_info (syn::TransformInfo*);

  void applay_operation2buf (
    const syn::NodeID&                id_node,
    const syn::MorphOperationParams&  op,
    ::libs::bufs::Bufs*               pbuf,
    ::utils::dbufs::video::IVideoBuf* pdst);

  private:
  /// Функция реализации операции эрозии над буфером
  /// \param[in]  op параметры операции
  /// \param[in]  pbuf  буфер источник
  /// \param[out] pdst   буфер назначения
  void erosion_buf (
    const syn::NodeID&                id_node,
    const syn::MorphOperationParams&  op,
    ::libs::bufs::Bufs*               pbuf,
    ::utils::dbufs::video::IVideoBuf* pdst);
  /// Функция подготовки параметров для МО erosion
  /// \param[in]    size_spot  размер пятна операции
  /// \param[out ]  cinfo      параметры функции
  /// \param[out ]  tfunct     возвращаемая функция
  void fill_koeffs_for_erosion_operation (
    const std::int16_t                 size_spot,
    ::libs::optim::io::MCallInfo&      cinfo,
    ::libs::optim::mcalls::InfoMFunct& tfunct);
  /// Функция реализации операции дилатации над буфером
  /// \param[in]  op параметры операции
  /// \param[in]  pbuf  буфер источник
  /// \param[out] pdst   буфер назначения
  void dilation_buf (
    const syn::NodeID&                id_node,
    const syn::MorphOperationParams&  op,
    ::libs::bufs::Bufs*               pbuf,
    ::utils::dbufs::video::IVideoBuf* pdst);
  /// Функция подготовки параметров для МО dilation
  /// \param[in]    size_spot  размер пятна операции
  /// \param[out ]  cinfo    параметры функции
  /// \param[out ]  tfunct   возвращаемая функция
  void fill_koeffs_for_dilation_operation (
    const std::int16_t                 size_spot,
    ::libs::optim::io::MCallInfo&      cinfo,
    ::libs::optim::mcalls::InfoMFunct& tfunct);

  syn::IMCaller::ptr         pthreads_;         //< Указатель на пул потоков для вычисления МО
  ::libs::optim::io::hioptim conv_mod_3x3_;     //< Функция свертки 3х3
  ::libs::optim::io::hioptim conv_mod_5x5_;     //< Функция свертки 5х5
  ::libs::optim::io::hioptim conv_mod_7x7_;     //< Функция свертки 7х7
  ::libs::optim::io::hioptim conv_mod_9x9_;     //< Функция свертки 9х9
  ::libs::optim::io::hioptim conv_mod_11x11_;   //< Функция свертки 11х11
  syn::TransformInfo*        transinfo_;        //< Указатель на текущий параметр при вызове функции transform
};
}   // namespace dlls::gens::vgen_mops::lib::helpers
