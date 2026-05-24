/**
\file       open-h264-impl.cpp
\date       06.07.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/
#include "codec/api/wels/codec_api.h"

#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "helpers/convert-funcs.hpp"
#include "helpers/dump-funcs.hpp"
#include "open-h264-impl.hpp"

namespace dlls::codecs::vcodec_x264::impls::openh264
{
OpenH264Impl::OpenH264Impl () :
  coder_ (nullptr),
  decoder_ (nullptr)
{
}


OpenH264Impl::~OpenH264Impl ()
{
  destroy_coder_int ();
  destroy_decoder_int ();
}


void
OpenH264Impl::create_coder_int (
  const syn::VideoCodecProp& cinfo,
  const syn::AllocBufInfo&   coder_frame_info)
{
  const auto birate = ::libs::ievents::props::videos::generic::codec::to_bitrate_x264 (
    cinfo.plane_,
    coder_frame_info.geom_dims_[::utils::dbufs::video::Dims::width],
    coder_frame_info.geom_dims_[::utils::dbufs::video::Dims::height]);

  U3_LOG_DATA_DEV ("create encoder" + VTOLOG (birate) + VTOLOG (coder_frame_info.geom_dims_[::utils::dbufs::video::Dims::width]) + VTOLOG (coder_frame_info.geom_dims_[::utils::dbufs::video::Dims::height]));
  U3_CHECK (!coder_, "!coder_ not empty");
  U3_CHECK (0 == WelsCreateSVCEncoder (&coder_), "WelsCreateSVCEncoder");
  U3_CHECK (coder_, "coder_ empty");

#if 0
  SEncParamBase params;
  memset (&params, 0, sizeof (params));
  params.iUsageType     = CAMERA_VIDEO_REAL_TIME;
  params.fMaxFrameRate  = 30;
  params.iPicWidth      = coder_frame_info_.width_;
  params.iPicHeight     = coder_frame_info_.height_;
  params.iTargetBitrate = birate;
  //params.iRCMode        = RC_BITRATE_MODE;
  params.iRCMode = RC_BUFFERBASED_MODE;

  U3_CHECK (0 == coder_->Initialize (&params), "coder_->Initialize");
#endif

#if 1
  SEncParamExt ext_params;

  memset (&ext_params, 0, sizeof (ext_params));

  ext_params.iUsageType     = CAMERA_VIDEO_REAL_TIME;
  ext_params.fMaxFrameRate  = 30;
  ext_params.iPicWidth      = coder_frame_info.geom_dims_[::utils::dbufs::video::Dims::width];
  ext_params.iPicHeight     = coder_frame_info.geom_dims_[::utils::dbufs::video::Dims::height];
  ext_params.iTargetBitrate = birate;
  ext_params.iRCMode        = RC_BITRATE_MODE;
  // ext_params.iRCMode      = RC_BUFFERBASED_MODE;

  // ext_params.iTemporalLayerNum = 0; //temporal layer number, max temporal layer = 4
  //  int                 iSpatialLayerNum;    ///< spatial layer number,1<= iSpatialLayerNum <= MAX_SPATIAL_LAYER_NUM, MAX_SPATIAL_LAYER_NUM = 4
  //  SSpatialLayerConfig sSpatialLayers[MAX_SPATIAL_LAYER_NUM];
  // ext_params.iComplexityMode = LOW_COMPLEXITY;
  ext_params.iComplexityMode = MEDIUM_COMPLEXITY;
  // ext_params.iComplexityMode = HIGH_COMPLEXITY;
  // ext_params.uiIntraPeriod   = 0;
  // ext_params.iNumRefFrame = 0;
  // ext_params.eSpsPpsIdStrategy = CONSTANT_ID; //different stategy in adjust ID in SPS/PPS: 0- constant ID, 1-additional ID, 6-mapping and additional
  // ext_params.bPrefixNalAddingCtrl = false;//false:not use Prefix NAL; true: use Prefix NAL
  ext_params.bEnableSSEI            = false;   // false:not use SSEI; true: use SSEI -- TODO: planning to remove the interface of SSEI
  ext_params.bSimulcastAVC          = false;   //(when encoding more than 1 spatial layer) false: use SVC syntax for higher layers; true: use Simulcast AVC
  ext_params.iPaddingFlag           = 0;
  ext_params.iEntropyCodingModeFlag = 0;   // 0:CAVLC  1:CABAC.
  ext_params.bEnableFrameSkip       = 0;   // False: don't skip frame even if VBV buf overflow.True: allow skipping frames to keep the bitrate within limits
  ext_params.iMaxBitrate            = 0;   // the maximum bitrate, in unit of bps, set it to UNSPECIFIED_BIT_RATE if not needed
  // ext_params.iMaxQp                 = ;    // the maximum QP encoder supports
  // ext_params.iMinQp                 = ;    // the minmum QP encoder supports
  // ext_params.uiMaxNalSize           = ;    // the maximum NAL size.  This value should be not 0 for dynamic slice mode


  /*

int          iMaxQp;             ///<
int          iMinQp;             ///<
uint32_t ;       ///<

//LTR settings
bool         bEnableLongTermReference;   ///< 1: on, 0: off
int          iLTRRefNum;                 ///< the number of LTR(long term reference),TODO: not supported to set it arbitrary yet
uint32_t iLtrMarkPeriod;             ///< the LTR marked period that is used in feedback
/ multi-thread settings
std::uint16_t
  iMultipleThreadIdc;     ///< 1 # 0: auto(dynamic imp internal encoder); 1: multiple threads imp disabled; lager than 1: count number of threads;
bool bUseLoadBalancing;   ///< only used when uiSliceMode=1 or 3, will change slicing of a picture during the run-time of multi-thread encoding, so the result of each run may be different

// Deblocking loop filter
int iLoopFilterDisableIdc;      ///< 0: on, 1: off, 2: on except for slice boundaries
int iLoopFilterAlphaC0Offset;   ///< AlphaOffset: valid range [-6, 6], default 0
int iLoopFilterBetaOffset;      ///< BetaOffset: valid range [-6, 6], default 0
//pre-processing feature
bool bEnableDenoise;               ///< denoise control
bool bEnableBackgroundDetection;   ///< background detection control //VAA_BACKGROUND_DETECTION //BGD cmd
bool bEnableAdaptiveQuant;         ///< adaptive quantization control
bool bEnableFrameCroppingFlag;     ///< enable frame cropping flag: TRUE always in application
bool bEnableSceneChangeDetect;

bool bIsLosslessLink;   ///<  LTR advanced setting
*/

  U3_CHECK (0 == coder_->InitializeExt (&ext_params), "coder_->InitializeEx");
#endif

  // std::int32_t idr_interval = 0;
  //  coder_->SetOption (ENCODER_OPTION_IDR_INTERVAL, &idr_interval);

  SProfileInfo sProfileInfo;
  sProfileInfo.iLayer = 0;
  // sProfileInfo.uiProfileIdc = PRO_BASELINE;
  sProfileInfo.uiProfileIdc = PRO_MAIN;
  U3_CHECK_NT (0 == coder_->SetOption (ENCODER_OPTION_PROFILE, &sProfileInfo), "SetOption (ENCODER_OPTION_PROFILE");
  // ENCODER_OPTION_IDR_INTERVAL

  // SLevelInfo sLevelInfo;
  // sLevelInfo.iLayer     = 0;
  // sLevelInfo.uiLevelIdc = LEVEL_UNKNOWN;
  //  coder_->SetOption (ENCODER_OPTION_LEVEL, &sLevelInfo);

  // 0:quality mode;1:bit-rate mode;2:bitrate limited mode
  // std::int32_t rc_mode = 2;
  // coder_->SetOption (ENCODER_OPTION_RC_MODE, &rc_mode);

  //
  //
  //
  //
  //
  //
  // ENCODER_OPTION_LEVEL
  // int videoFormat = videoFormatI420;
  // encoder_->SetOption (ENCODER_OPTION_DATAFORMAT, &videoFormat);
  // SetOption (ENCODER_OPTION_TRACE_LEVEL, &g_LevelSetting);
}


void
OpenH264Impl::destroy_coder_int ()
{
  if (!coder_)
  {
    return;
  }

  coder_->Uninitialize ();
  WelsDestroySVCEncoder (coder_);
  coder_ = nullptr;
}


void
OpenH264Impl::create_decoder_int ()
{
  U3_ASSERT (!decoder_);
  auto ret = WelsCreateDecoder (&decoder_);
  U3_ASSERT (0 == ret);
  U3_ASSERT (decoder_);
}


void
OpenH264Impl::destroy_decoder_int ()
{
  if (!decoder_)
  {
    return;
  }

  decoder_->Uninitialize ();
  WelsDestroyDecoder (decoder_);
  decoder_ = nullptr;
}


bool
OpenH264Impl::compress_frame_int (const syn::VideoCodecProp& cinfo, EncodeFrameState& state)
{
  U3_CHECK (coder_, "empty coder");
  ::libs::optim::io::ProxyBuf dst (state.dbuf_, "dst OpenH264Impl::compress_frame_int");
  std::uint8_t*               dbuf        = dst.ubuf ();
  syn::HeaderIFrame*          head        = U3_CAST_CODECS< syn::HeaderIFrame* > (dbuf);
  int                         from_header = 0;
  ::libs::optim::io::ProxyBuf lsrc (state.sbuf_, "src_buf x264Impl::compress_frame");
  std::uint32_t               result_size = sizeof (syn::HeaderIFrame);

  head->reset ();

  SFrameBSInfo frame_info;
  memset (&frame_info, 0, sizeof (frame_info));

  SSourcePicture source_pic;
  memset (&source_pic, 0, sizeof (source_pic));

  source_pic.iPicWidth    = lsrc.width_;
  source_pic.iPicHeight   = lsrc.height_;
  source_pic.iColorFormat = videoFormatI420;
  source_pic.iStride[0]   = lsrc.stride_;
  // source_pic.iStride[0] = source_pic.iPicWidth;
  source_pic.iStride[1] = lsrc.stride_ >> 1;
  source_pic.iStride[2] = lsrc.stride_ >> 1;
  // pic.pData[0] = buf.data ();
  source_pic.pData[0] = lsrc.ubuf ();
  // debug
  source_pic.pData[1] = lsrc.ubuf ();
  source_pic.pData[2] = lsrc.ubuf ();
  // source_pic.pData[1] = nullptr;
  // source_pic.pData[0] + lsrc.width_* lsrc.height_;
  // source_pic.pData[2] = nullptr;
  // source_pic.pData[1] + (lsrc.width_ * lsrc.height_ >> 2);

  // prepare input data
  const auto res = coder_->EncodeFrame (&source_pic, &frame_info);
  U3_LOG_DATA_DEV (VTOLOG (res) + VTOLOG (frame_info.iLayerNum) + VTOLOG (frame_info.eFrameType));
  U3_ASSERT (res == cmResultSuccess);
  if (frame_info.eFrameType == videoFrameTypeSkip)
  {
    return false;
  }

  syn::IVideoBuf::fragments_type fragments;
  std::uint32_t                  size_fragments = 0;

  for (int indx = 0; indx < frame_info.iLayerNum; ++indx)
  {
    const auto&   linfo         = frame_info.sLayerInfo[indx];
    auto          naps_buf      = linfo.pBsBuf;
    std::uint32_t size_fragment = 0;

#if 0
    // debug
    helpers::dump (linfo);
#endif

    for (int nindx = 0; nindx < linfo.iNalCount; ++nindx)
    {
      const auto size_nal = linfo.pNalLengthInByte[nindx];
      U3_LOG_DATA_DEV (VTOLOG (linfo.iNalCount) + VTOLOG (nindx) + VTOLOG (linfo.pNalLengthInByte[nindx]));
      ::libs::helpers::mem::u3copy (naps_buf, dbuf + result_size + size_fragments + size_fragment, size_nal);
      size_fragment += size_nal;
      naps_buf += size_nal;
    }

    fragments.push_back (size_fragment);
    size_fragments += size_fragment;
  }

  state.dbuf_->set_fragments (fragments);
  // pic_in.i_pts = U3_CAST_INT32 (counter_frames_);

  head->csize_ = size_fragments;
  head->coff_  = from_header;
  from_header += size_fragments;
  result_size += size_fragments;

  U3_ASSERT (result_size > 0);

  auto& base_header = head->base_part_;
  auto& base_size   = base_header.sinfo_;

  base_header.style_         = helpers::convert_frame_style (frame_info.eFrameType);
  base_header.size_compress_ = result_size;
  base_size.width_           = lsrc.width_;
  base_size.height_          = lsrc.height_;
  base_size.stride_          = lsrc.width_ * (state.nocolor_ ? 3 : 1);

  head->cinfo_          = cinfo.plane_;
  head->cinfo_.nocolor_ = state.nocolor_;

  // libs::helpers::utils::cuuid_to_buf (::libs::helpers::uids::codecs::x264, head->base_part_.guid_);
  head->base_part_.guid_ = ::libs::helpers::uids::minor::id_val::x264;
  U3_ASSERT (head->check ());
  U3_LOG_DATA_DEV (VTOLOG (result_size));
  state.dbuf_->set_mem_var (::utils::dbufs::MemVars::size_data, result_size);
  // statistic_.update ("x264", size_fragments);
  return true;
}


bool
OpenH264Impl::decompress_frame_int (
  const syn::HeaderIFrame*           head,
  const ::libs::optim::io::ProxyBuf& src,
  const std::int32_t                 src_size,
  const syn::IVideoBuf::raw_ptr      idst,
  std::uint8_t**                     dst,
  std::uint32_t&                     dst_stride,
  std::uint32_t&                     dst_width,
  std::uint32_t&                     dst_height)
{
  // const auto& base_head = head->base_part_;
  //  const auto&         info_head    = base_head.sinfo_;
  const std::uint8_t* sdata        = src.ubuf () + head->base_part_.size_;
  const std::uint8_t* cdata        = sdata + head->coff_;
  std::uint32_t       src_size_res = head->csize_;
  /// std::int32_t                 codec_error  = 0;

  try
  {
#if 0
  * @page Overview
  *   * This page is for openh264 codec API usage.
  *   * For how to use the encoder,please refer to page UsageExampleForEncoder
  *   * For how to use the decoder,please refer to page UsageExampleForDecoder
  *   * For more detail about ISVEncoder,please refer to page ISVCEnoder
  *   * For more detail about ISVDecoder,please refer to page ISVCDecoder
  * @page DecoderUsageExample
  *
  * @brief
  *   * An example for using the decoder for Decoding only or Parsing only
  *
  * Step 1:decoder declaration
  * @code
  *
  *  //decoder declaration
  *  ISVCDecoder *pSvcDecoder;
  *  //input: encoded bitstream start position; should include start code prefix
  *  std::uint8_t *pBuf =...;
  *  //input: encoded bit stream length; should include the size of start code prefix
  *  int iSize =...;
  *  //output: [0~2] for Y,U,V buf for Decoding only
  *  std::uint8_t *pData[3] =...;
  *  //in-out: for Decoding only: declare and initialize the output buf info, this should never co-exist with Parsing only
  *  SBufferInfo sDstBufInfo;
  *  memset(&sDstBufInfo, 0, sizeof(SBufferInfo));
  *  //in-out: for Parsing only: declare and initialize the output bitstream buf info for parse only, this should never co-exist with Decoding only
  *  SParserBsInfo sDstParseInfo;
  *  memset(&sDstParseInfo, 0, sizeof(SParserBsInfo));
  *  sDstParseInfo.pDstBuff = new std::uint8_t[PARSE_SIZE]; //In Parsing only, allocate enough buf to save transcoded bitstream for a frame
  *
  * @endcode
  *
  * Step 2:decoder creation
  * @code
  *  WelsCreateDecoder(&pSvcDecoder);
  * @endcode
  *
  * Step 3:declare required parameter, used to differentiate Decoding only and Parsing only
  * @code
  *  SDecodingParam sDecParam = {0};
  *  sDecParam.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_AVC;
  *  //for Parsing only, the assignment is mandatory
  *  sDecParam.bParseOnly = true;
  * @endcode
  *
  * Step 4:initialize the parameter and decoder context, allocate memory
  * @code
  *  pSvcDecoder->Initialize(&sDecParam);
  * @endcode
  *
  * Step 5:do actual decoding process in slice level;
  *        this can be done in a loop until data ends
  * @code
  *  //for Decoding only
  *  iRet = pSvcDecoder->DecodeFrameNoDelay(pBuf, iSize, pData, &sDstBufInfo);
  *  //or
  *  iRet = pSvcDecoder->DecodeFrame2(pBuf, iSize, pData, &sDstBufInfo);
  *  //for Parsing only
  *  iRet = pSvcDecoder->DecodeParser(pBuf, iSize, &sDstParseInfo);
  *  //decode failed
  *  If (iRet != 0){
  *      //error handling (RequestIDR or something like that)
  *  }
  *  //for Decoding only, pData can be used for render.
  *  if (sDstBufInfo.iBufferStatus==1){
  *      //output handling (pData[0], pData[1], pData[2])
  *  }
  * //for Parsing only, sDstParseInfo can be used for, e.g., HW decoding
  *  if (sDstBufInfo.iNalNum > 0){
  *      //Hardware decoding sDstParseInfo;
  *  }
  *  //no-delay decoding can be realized by directly calling DecodeFrameNoDelay(), which is the recommended usage.
  *  //no-delay decoding can also be realized by directly calling DecodeFrame2() again with NULL input, as in the following. In this case, decoder would immediately reconstruct the input data. This can also be used similarly for Parsing only. Consequent decoding error and output indication should also be considered as above.
  *  iRet = pSvcDecoder->DecodeFrame2(NULL, 0, pData, &sDstBufInfo);
  *  //judge iRet, sDstBufInfo.iBufferStatus ...
  * @endcode
  *
  * Step 6:uninitialize the decoder and memory free
  * @code
  *  pSvcDecoder->Uninitialize();
  * @endcode
  *
  * Step 7:destroy the decoder
  * @code
  *  DestroyDecoder(pSvcDecoder);
  * @endcode
  *
#endif
    if (!decoder_)
    {
      create_decoder ();
      const bool     parse_only = false;
      SDecodingParam dec_param  = { nullptr, 0, 0, ERROR_CON_DISABLE, parse_only, { sizeof (SVideoProperty), VIDEO_BITSTREAM_SVC } };
      // dec_param.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_AVC;
      //  for Parsing only, the assignment is mandatory
      // dec_param.bParseOnly = false;
      const auto ires = decoder_->Initialize (&dec_param);
      U3_CHECK (0 == ires, "call decoder_->Initialize" + VTOLOG (ires));
      int log_level = WELS_LOG_DETAIL;
      decoder_->SetOption (DECODER_OPTION_TRACE_LEVEL, &log_level);
    }

    // in-out: for Decoding only: declare and initialize the output buf info, this should never co-exist with Parsing only
    // const auto stride = idst->get_dim_var (utils::dbufs::video::Dims::stride);
    // const auto height = idst->get_dim_var (utils::dbufs::video::Dims::height);
    // const auto    size_lum   = stride * height;
    // const auto    size_chrom = stride * height >> 1;
    std::uint8_t* pData[3] = { nullptr, nullptr, nullptr };   // idst->get_buf (), idst->get_buf () + size_lum, idst->get_buf () + size_lum + size_chrom
    SBufferInfo   dst_buf_info;

    memset (&dst_buf_info, 0, sizeof (SBufferInfo));
    // dst_buf_info.UsrData.sSystemBuffer.

#if 0
    SParserBsInfo parser_info = { 0 };
    auto          res         = decoder_->DecodeParser (cdata, src_size_res, &parser_info);
    if (0 != res)
    {
      U3_LOG_DATA_ERROR ("call DecodeParser " + VTOLOG (res));
      return false;
    }
#endif

    // for Decoding only
    U3_LOG_DATA_DEV ("decode size" + VTOLOG (src_size_res));
    DECODING_STATE decode_res = dsErrorFree;
    decode_res                = decoder_->DecodeFrameNoDelay (cdata, src_size_res, pData, &dst_buf_info);
    if (0 != decode_res)
    {
      U3_LOG_DATA_ERROR ("call DecodeFrameNoDelay " + VTOLOG (decode_res));
      return false;
    }

    // for Decoding only, pData can be used for render.
    if (0 == dst_buf_info.iBufferStatus)
    {
      U3_LOG_DATA_DEV (VTOLOG (dst_buf_info.iBufferStatus));
      return false;
    }

    U3_LOG_DATA_DEV ("decode ok");
    const auto px_format = ::libs::helpers::uids::minor::id_val::i420;
    // src_buf->get_format ();   //
    // const auto stride_res = info_head.width_ * ::libs::helpers::uids::helpers::get_count_bytes_from_format (px_format);
    // const auto size_res   = info_head.height_ * stride_res;
    // const auto size_res   = dst_buf_info.UsrData.sSystemBuffer.iHeight * dst_buf_info.UsrData.sSystemBuffer.iStride[0];
    auto alloc_info = syn::AllocBufInfo (
      dst_buf_info.UsrData.sSystemBuffer.iWidth,
      dst_buf_info.UsrData.sSystemBuffer.iHeight,
      0,
      ::libs::helpers::uids::minor::id_val::y16,
      utils::dbufs::video::DimChecks::enable);

    alloc_info.flags_[::utils::dbufs::BufFlags::convolution_support] = true;
    idst->buf_alloc (alloc_info);

    // debug
    //::utils::dbufs::video::helpers::fill (idst, 0);

    // idst->
    // idst->set_mem_var (::utils::dbufs::MemVars::size_buf, size_res);
    // idst->set_dim_var (utils::dbufs::video::Dims::width, dst_buf_info.UsrData.sSystemBuffer.iWidth);
    // idst->set_dim_var (utils::dbufs::video::Dims::height, dst_buf_info.UsrData.sSystemBuffer.iHeight);
    // idst->set_dim_var (utils::dbufs::video::Dims::stride, stride_res);
    // idst->set_dim_var (utils::dbufs::video::Dims::stride, dst_buf_info.UsrData.sSystemBuffer.iStride[0]);

    //???
    //::libs::optim::io::hioptim                                     fx8_x16_;            //< ��������� �� ���������� �� �������������� ������� ����� �� X8 � X16
    //::utils::dbufs::video::helpers::raw_copy (pData[0], size_res, idst, 0);

    /*
    src_buf->buf_alloc (
      syn::AllocBufInfo (
        lbuf->get_dim_var (::utils::dbufs::video::Dims::width),
        lbuf->get_dim_var (::utils::dbufs::video::Dims::height),
        lbuf->get_dim_var (::utils::dbufs::video::Dims::stride),
        ::libs::helpers::uids::minor::id_val::y8));
        */

    *dst       = pData[0];
    dst_stride = dst_buf_info.UsrData.sSystemBuffer.iStride[0];
    dst_width  = dst_buf_info.UsrData.sSystemBuffer.iWidth;
    dst_height = dst_buf_info.UsrData.sSystemBuffer.iHeight;

#if 0
    U3TEST
    ::libs::optim::io::MCallInfo cinfo;
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (pData[0], dst_buf_info.UsrData.sSystemBuffer.iStride[0], dst_buf_info.UsrData.sSystemBuffer.iWidth, dst_buf_info.UsrData.sSystemBuffer.iHeight, "lbuf x264Impl::code_int"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (idst, "src_buf x264Impl::code_int"));

    ::libs::optim::mcalls::InfoMFunct tfunct (&fx8_x16_);

    pthreads_->mthreads_call (*id_node_graph_, tfunct, cinfo, transinfo_->exptimes_);

    idst->set_mem_var (::utils::dbufs::MemVars::size_data, size_res);
    idst->set_flag (utils::dbufs::BufFlags::empty, false);
#endif
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
  return true;
}

static const IBaseH264Impl::frame_formats_type frame_formats_coder_mode   = { ::libs::helpers::uids::minor::id_val::i420 };
static const IBaseH264Impl::frame_formats_type frame_formats_decoder_mode = { ::libs::helpers::uids::minor::id_val::i420 };

const IBaseH264Impl::frame_formats_type&
OpenH264Impl::get_support_frame_format_int (const syn::CodecModes& codec_mode) const
{
  switch (codec_mode)
  {
  case syn::CodecModes::coder:
    return frame_formats_coder_mode;
  case syn::CodecModes::decoder:
    return frame_formats_decoder_mode;
  default:
    U3_THROW_EXCEPTION ("uknown codec mode" + VTOLOG (U3_CAST_UINT32_FORCE (codec_mode)));
  }
}
}   // namespace dlls::codecs::vcodec_x264::impls::openh264
