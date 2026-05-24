#pragma once
/**
\file       dump-funcs.hpp
\date       26.08.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/

namespace dlls::codecs::vcodec_x264::impls::openh264::helpers
{
// EAI-REFACT
inline std::string
to_string (const EVideoFrameType& val)
{
  switch (val)
  {
  case videoFrameTypeIDR:
    return "videoFrameTypeIDR";
  case videoFrameTypeI:
    return "videoFrameTypeI";
  case videoFrameTypeP:
    return "videoFrameTypeP";
  case videoFrameTypeSkip:
    return "videoFrameTypeSkip";
  case videoFrameTypeIPMixed:
    return "videoFrameTypeIPMixed";
  default:
    U3_XLOG_ERROR ("unknown val EVideoFrameType" + std::to_string (val));
    return "unknown EVideoFrameType";
  }
}


inline void
dump (const SLayerBSInfo& info)
{
  U3_MARK_UNUSED const auto summ = std::accumulate (info.pNalLengthInByte, info.pNalLengthInByte + info.iNalCount, 0);
}


#if 0
inline std::string
slice2string (int val)
{
  switch (val)
    {
    case X264_TYPE_AUTO:
      return "X264_TYPE_AUTO";
    case X264_TYPE_IDR:
      return "X264_TYPE_IDR";
    case X264_TYPE_I:
      return "X264_TYPE_I";
    case X264_TYPE_P:
      return "X264_TYPE_P";
    case X264_TYPE_BREF:
      return "X264_TYPE_BREF";
    case X264_TYPE_B:
      return "X264_TYPE_B";
    case X264_TYPE_KEYFRAME:
      return "X264_TYPE_KEYFRAME";
    }
  return "unknown slice, " + std::to_string(val);
}


inline std::string
csp2string (int val)
{
  std::string ret;

  if (val & X264_CSP_VFLIP)
    {
      ret += "vertically flipped ";
    }

  if (val & X264_CSP_HIGH_DEPTH)
    {
      ret += "16 bit per pixel ";
    }

  val &= X264_CSP_MASK;

  switch (val)
    {
    case X264_CSP_NONE:
      ret += "X264_CSP_NONE";
      break;
    case X264_CSP_I400:
      ret += "X264_CSP_I400";
      break;
    case X264_CSP_I420:
      ret += "X264_CSP_I420";
      break;
    case X264_CSP_YV12:
      ret += "X264_CSP_YV12";
      break;
    case X264_CSP_NV12:
      ret += "X264_CSP_NV12";
      break;
    case X264_CSP_NV21:
      ret += "X264_CSP_NV21";
      break;
    case X264_CSP_I422:
      ret += "X264_CSP_I422";
      break;
    case X264_CSP_YV16:
      ret += "X264_CSP_YV16";
      break;
    case X264_CSP_NV16:
      ret += "X264_CSP_NV16";
      break;
    case X264_CSP_YUYV:
      ret += "X264_CSP_YUYV";
      break;
    case X264_CSP_UYVY:
      ret += "X264_CSP_UYVY";
      break;
    case X264_CSP_V210:
      ret += "X264_CSP_V210";
      break;
    case X264_CSP_I444:
      ret += "X264_CSP_I444";
      break;
    case X264_CSP_YV24:
      ret += "X264_CSP_YV24";
      break;
    case X264_CSP_BGR:
      ret += "X264_CSP_BGR";
      break;
    case X264_CSP_BGRA:
      ret += "X264_CSP_BGRA";
      break;
    case X264_CSP_RGB:
      ret += "X264_CSP_RGB";
      break;
    case X264_CSP_MAX:
      ret += "X264_CSP_MAX";
      break;
    default:
      ret += "unknown csp val, " + std::to_string(val);
      break;
    }
  return ret;
}


inline void
dump (const x264_sei_t& sei, const std::string& prefix = "")
{
}


inline void
dump (const x264_hrd_t& hrd, const std::string& prefix = "")
{
}


inline void
dump (const x264_image_t& image, const std::string& prefix = "")
{
}


inline void
dump (const x264_param_t* param, const std::string& prefix = "")
{
  if (!param)
    {
      return;
    }  
  //
  return;
}

#  if 0
typedef struct x264_param_t
{
    /* NAL HRD
     * Uses Buffering and Picture Timing SEIs to signal HRD
     * The HRD in H.264 was not designed with VFR in mind.
     * It is therefore not recommendeded to use NAL HRD with VFR.
     * Furthermore, reconfiguring the VBV (via x264_encoder_reconfig)
     * will currently generate invalid HRD. */
    int         i_nal_hrd;

    struct
    {
        /* they will be reduced to be 0 < x <= 65535 and prime */
        int         i_sar_height;
        int         i_sar_width;

        int         i_overscan;    /* 0=undef, 1=no overscan, 2=overscan */

        /* see h264 annex E for the values of the following */
        int         i_vidformat;
        int         b_fullrange;
        int         i_colorprim;
        int         i_transfer;
        int         i_colmatrix;
        int         i_chroma_loc;    /* both top & bottom */
    } vui;

    /* Bitstream parameters */
    int         i_frame_reference;  /* Maximum number of reference frames */
    int         i_dpb_size;         /* Force a DPB size larger than that implied by B-frames and reference frames.
                                     * Useful in combination with interactive error resilience. */
    int         i_keyint_max;       /* Force an IDR keyframe at this interval */
    int         i_keyint_min;       /* Scenecuts closer together than this are coded as I, not IDR. */
    int         i_scenecut_threshold; /* how aggressively to insert extra I frames */
    int         b_intra_refresh;    /* Whether or not to use periodic intra refresh instead of IDR frames. */

    int         i_bframe;   /* how many b-frame between 2 references pictures */
    int         i_bframe_adaptive;
    int         i_bframe_bias;
    int         i_bframe_pyramid;   /* Keep some B-frames as references: 0=off, 1=strict hierarchical, 2=normal */
    int         b_open_gop;
    int         b_bluray_compat;
    int         i_avcintra_class;
    int         i_avcintra_flavor;

    int         b_deblocking_filter;
    int         i_deblocking_filter_alphac0;    /* [-6, 6] -6 light filter, 6 strong */
    int         i_deblocking_filter_beta;       /* [-6, 6]  idem */

    int         b_cabac;
    int         i_cabac_init_idc;

    int         b_interlaced;
    int         b_constrained_intra;

    int         i_cqm_preset;
    char        *psz_cqm_file;      /* filename (in UTF-8) of CQM file, JM format */
    std::uint8_t     cqm_4iy[16];        /* used only if i_cqm_preset == X264_CQM_CUSTOM */
    std::uint8_t     cqm_4py[16];
    std::uint8_t     cqm_4ic[16];
    std::uint8_t     cqm_4pc[16];
    std::uint8_t     cqm_8iy[64];
    std::uint8_t     cqm_8py[64];
    std::uint8_t     cqm_8ic[64];
    std::uint8_t     cqm_8pc[64];

    /* Log */
    void        (*pf_log)( void *, int i_level, const char *psz, va_list );
    void        *p_log_private;
    int         i_log_level;
    int         b_full_recon;   /* fully reconstruct frames, even when not necessary for encoding.  Implied by psz_dump_yuv */
    char        *psz_dump_yuv;  /* filename (in UTF-8) for reconstructed frames */

    /* Encoder analyser parameters */
    struct
    {
        std::uint32_t intra;     /* intra partitions */
        std::uint32_t inter;     /* inter partitions */

        int          b_transform_8x8;
        int          i_weighted_pred; /* weighting for P-frames */
        int          b_weighted_bipred; /* implicit weighting for B-frames */
        int          i_direct_mv_pred; /* spatial vs temporal mv prediction */
        int          i_chroma_qp_offset;

        int          i_me_method; /* motion estimation algorithm to use (X264_ME_*) */
        int          i_me_range; /* integer pixel motion estimation search range (from predicted mv) */
        int          i_mv_range; /* maximum length of a mv (in pixels). -1 = auto, based on level */
        int          i_mv_range_thread; /* minimum space between threads. -1 = auto, based on number of threads. */
        int          i_subpel_refine; /* subpixel motion estimation quality */
        int          b_chroma_me; /* chroma ME for subpel and mode decision in P-frames */
        int          b_mixed_references; /* allow each mb partition to have its own reference number */
        int          i_trellis;  /* trellis RD quantization */
        int          b_fast_pskip; /* early SKIP detection on P-frames */
        int          b_dct_decimate; /* transform coefficient thresholding on P-frames */
        int          i_noise_reduction; /* adaptive pseudo-deadzone */
        float        f_psy_rd; /* Psy RD strength */
        float        f_psy_trellis; /* Psy trellis strength */
        int          b_psy; /* Toggle all psy optimizations */

        int          b_mb_info;            /* Use input mb_info data in x264_picture_t */
        int          b_mb_info_update; /* Update the values in mb_info according to the results of encoding. */

        /* the deadzone size that will be used in luma quantization */
        int          i_luma_deadzone[2]; /* {inter, intra} */

        int          b_psnr;    /* compute and print PSNR stats */
        int          b_ssim;    /* compute and print SSIM stats */
    } analyse;

    /* Rate control parameters */
    struct
    {
        int         i_rc_method;    /* X264_RC_* */

        int         i_qp_constant;  /* 0=lossless */
        int         i_qp_min;       /* min allowed QP value */
        int         i_qp_max;       /* max allowed QP value */
        int         i_qp_step;      /* max QP step between frames */

        int         i_bitrate;
        float       f_rf_constant;  /* 1pass VBR, nominal QP */
        float       f_rf_constant_max;  /* In CRF mode, maximum CRF as caused by VBV */
        float       f_rate_tolerance;
        int         i_vbv_max_bitrate;
        int         i_vbv_buf_size;
        float       f_vbv_buf_init; /* <=1: fraction of buf_size. >1: kbit */
        float       f_ip_factor;
        float       f_pb_factor;

        /* VBV filler: force CBR VBV and use filler bytes to ensure hard-CBR.
         * Implied by NAL-HRD CBR. */
        int         b_filler;

        int         i_aq_mode;      /* psy adaptive QP. (X264_AQ_*) */
        float       f_aq_strength;
        int         b_mb_tree;      /* Macroblock-tree ratecontrol. */
        int         i_lookahead;

        /* 2pass */
        int         b_stat_write;   /* Enable stat writing in psz_stat_out */
        char        *psz_stat_out;  /* output filename (in UTF-8) of the 2pass stats file */
        int         b_stat_read;    /* Read stat from psz_stat_in and use it */
        char        *psz_stat_in;   /* input filename (in UTF-8) of the 2pass stats file */

        /* 2pass params (same as ffmpeg ones) */
        float       f_qcompress;    /* 0.0 => cbr, 1.0 => constant qp */
        float       f_qblur;        /* temporally blur quants */
        float       f_complexity_blur; /* temporally blur complexity */
        x264_zone_t *zones;         /* ratecontrol overrides */
        int         i_zones;        /* number of zone_t's */
        char        *psz_zones;     /* alternate method of specifying zones */
    } rc;

    /* Cropping Rectangle parameters: added to those implicitly defined by
       non-mod16 video resolutions. */
    struct
    {
        std::uint32_t i_left;
        std::uint32_t i_top;
        std::uint32_t i_right;
        std::uint32_t i_bottom;
    } crop_rect;

    /* frame packing arrangement flag */
    int i_frame_packing;

    /* alternative transfer SEI */
    int i_alternative_transfer;

    /* Muxing parameters */
    int b_aud;                  /* generate access unit delimiters */
    int b_repeat_headers;       /* put SPS/PPS before each keyframe */
    int b_annexb;               /* if set, place start codes (4 bytes) before NAL units,
                                 * otherwise place size (4 bytes) before NAL units. */
    int i_sps_id;               /* SPS and PPS id number */
    int b_vfr_input;            /* VFR input.  If 1, use timebase and timestamps for ratecontrol purposes.
                                 * If 0, use fps only. */
    int b_pulldown;             /* use explicity set timebase for CFR */
    std::uint32_t i_fps_num;
    std::uint32_t i_fps_den;
    std::uint32_t i_timebase_num;    /* Timebase numerator */
    std::uint32_t i_timebase_den;    /* Timebase denominator */

    int b_tff;

    /* Pulldown:
     * The correct pic_struct must be passed with each input frame.
     * The input timebase should be the timebase corresponding to the output framerate. This should be constant.
     * e.g. for 3:2 pulldown timebase should be 1001/30000
     * The PTS passed with each frame must be the PTS of the frame after pulldown is applied.
     * Frame doubling and tripling require b_vfr_input set to zero (see H.264 Table D-1)
     *
     * Pulldown changes are not clearly defined in H.264. Therefore, it is the calling app's responsibility to manage this.
     */

    int b_pic_struct;

    /* Fake Interlaced.
     *
     * Used only when b_interlaced=0. Setting this flag makes it possible to flag the stream as PAFF interlaced yet
     * encode all frames progessively. It is useful for encoding 25p and 30p Blu-Ray streams.
     */

    int b_fake_interlaced;

    /* Don't optimize header parameters based on video content, e.g. ensure that splitting an input video, compressing
     * each part, and stitching them back together will result in identical SPS/PPS. This is necessary for stitching
     * with container formats that don't allow multiple SPS/PPS. */
    int b_stitchable;

    int b_opencl;            /* use OpenCL when available */
    int i_opencl_device;     /* specify count of GPU devices to skip, for CLI users */
    void *opencl_device_id;  /* pass explicit cl_device_id as void*, for API users */
    char *psz_clbin_file;    /* filename (in UTF-8) of the compiled OpenCL kernel cache file */

    /* Slicing parameters */
    int i_slice_max_size;    /* Max size per slice in bytes; includes estimated NAL overhead. */
    int i_slice_max_mbs;     /* Max number of MBs per slice; overrides i_slice_count. */
    int i_slice_min_mbs;     /* Min number of MBs per slice */
    int i_slice_count;       /* Number of slices per frame: forces rectangular slices. */
    int i_slice_count_max;   /* Absolute cap on slices per frame; stops applying slice-max-size
                              * and slice-max-mbs if this is reached. */

    /* Optional callback for freeing this x264_param_t when it is done being used.
     * Only used when the x264_param_t sits in memory for an indefinite period of time,
     * i.e. when an x264_param_t is passed to x264_t in an x264_picture_t or in zones.
     * Not used when x264_encoder_reconfig is called directly. */
    void (*param_free)( void* );
} x264_param_t;

#  endif

inline void
dump (const x264_picture_t& pict)
{
  dump( pict.extra_sei, "  " ),
  dump( pict.hrd_timing, " " );
  dump (pict.img, "  ");
  dump (pict.param, "  ");
}
#endif
}   // namespace dlls::codecs::vcodec_x264::impls::openh264::helpers
