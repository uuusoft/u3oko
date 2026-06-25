#pragma once
/**
file        includes.hpp
\author     Erashov Anton erashov2026@proton.me
\date       10.12.2016
\project    u3_ievents_lib
\brief      Файл, определяет набор интерфейсов и типов для ядра
*/
#include "enum-selector-impls.hpp"
#include "enum-ops-status.hpp"

#include "event.hpp"
#include "timed-event.hpp"
#include "ops-status-event.hpp"

#include "props/terminals/end-point-prop.hpp"

#include "props/mix_mul/out-channel-info.hpp"
#include "props/mix_mul/mix-mul-prop.hpp"

#include "props/application/application-prop.hpp"

#include "props/hardware/info-cpu-event.hpp"

#include "props/base_id/buf2module-info.hpp"
#include "props/base_id/base-id-prop.hpp"

#include "props/videos/gens/diff/params-video-diff-prop.hpp"
#include "props/videos/gens/diff/info-buf-video-diff-prop.hpp"
#include "props/videos/gens/diff/video-diff-prop.hpp"

#include "props/videos/noises/time/buf-video-time-noise-remover-prop.hpp"
#include "props/videos/noises/time/video-time-noise-remover-prop.hpp"
#include "props/videos/noises/time/ext/median-time-filter-prop.hpp"

#include "props/videos/noises/freq/info-buf-freq-noise-remover.hpp"
#include "props/videos/noises/freq/freq-video-noise-remover-prop.hpp"

#include "props/videos/noises/space/buf-video-space-noise-remover-prop.hpp"
#include "props/videos/noises/space/video-space-noise-remover-prop.hpp"
#include "props/videos/noises/space/ext/median-space-filter-prop.hpp"

#include "props/videos/generic/convolution/enum-convs.hpp"
#include "props/videos/generic/convolution/buf-video-convolution-prop.hpp"
#include "props/videos/generic/convolution/video-convolution-prop.hpp"

#include "props/videos/generic/motion_est/events-buf-info-motion-est.hpp"
#include "props/videos/generic/motion_est/video-est-motion-prop.hpp"

#include "props/videos/generic/vec2image/buf-event-info-vec2image1.hpp"
#include "props/videos/generic/vec2image/vec2image-prop.hpp"

#include "props/videos/generic/scaler/type-scaler.hpp"
#include "props/videos/generic/scaler/buf-event-info-video-scaler.hpp"
#include "props/videos/generic/scaler/video-scaler-prop.hpp"

// #include "props/videos/generic/sharper/CVideoSharperProp.hpp"

#include "props/videos/generic/morph/enum-morph-ops.hpp"
#include "props/videos/generic/morph/morph-operation-params.hpp"
#include "props/videos/generic/morph/morph-buf-info.hpp"
#include "props/videos/generic/morph/video-morphology-prop.hpp"

#include "props/videos/generic/detect/video-detect-prop.hpp"

#include "props/videos/generic/convert/enum-src2dsteqs.hpp"
#include "props/videos/generic/convert/enum-accuracys.hpp"
#include "props/videos/generic/convert/video-convert-prop.hpp"

#include "props/videos/generic/correct/video-correct-prop.hpp"

#include "props/videos/generic/gradient/type-gradient.hpp"
#include "props/videos/generic/gradient/channel-gradient.hpp"
#include "props/videos/generic/gradient/gradient-prop.hpp"

#include "props/videos/generic/histogram/video-histogram-prop.hpp"

#include "props/videos/generic/text/CVideoTextProp.hpp"

#include "props/videos/generic/matrix/CVideoMatrixProp.hpp"

#include "props/videos/generic/driver/type-catch-rgn.hpp"
#include "props/videos/generic/driver/camera-focus-type.hpp"
#include "props/videos/generic/driver/video-driver-prop.hpp"
#include "props/videos/generic/driver/links-video-driver-prop.hpp"
#include "props/videos/generic/driver/video-driver-capture-prop.hpp"

#include "props/videos/generic/codec/consts/video-codec-prop-const-vals.hpp"
#include "props/videos/generic/codec/override-codec-data-type.hpp"
#include "props/videos/generic/codec/type-codec-mode.hpp"
#include "props/videos/generic/codec/video-codec-flat-prop.hpp"
#include "props/videos/generic/codec/video-codec-prop.hpp"

#include "props/modules/log/consts/ievents-modules-log-vals.hpp"
#include "props/modules/log/log-levels-enum.hpp"
#include "props/modules/log/log-vals-enum.hpp"
#include "props/modules/log/property-log-module-event.hpp"

#include "props/modules/storage/path-usings-enum.hpp"
#include "props/modules/storage/checkers-enum.hpp"
#include "props/modules/storage/path-info.hpp"
#include "props/modules/storage/property-storage-module-event.hpp"

#include "props/modules/events/consts/property-events-module-const-vals.hpp"
#include "props/modules/events/events-vals-enum.hpp"
#include "props/modules/events/property-events-module-event.hpp"

#include "runtime/runtime-event.hpp"
#include "runtime/error/base-error-event.hpp"

#include "runtime/mem/buf-event.hpp"
#include "runtime/mem/bufs-event.hpp"
#include "runtime/mem/zip-data-event.hpp"

#include "runtime/video/frame-done.hpp"
#include "runtime/video/state-detect-violation.hpp"
#include "runtime/video/detect-violation.hpp"
#include "runtime/video/face-detect.hpp"
#include "runtime/video/system-specific-driver-prop.hpp"

#include "runtime/interf/interfaces/ievents-runtime-interf-interfaces-syn.hpp"
#include "runtime/interf/interfaces/ibase-runtime-interf.hpp"
#include "runtime/interf/interfaces/icorrect-image.hpp"
#include "runtime/interf/interfaces/icodec-image.hpp"
#include "runtime/interf/interfaces/ibase-id.hpp"
#include "runtime/interf/interfaces/icapture-image.hpp"

#include "runtime/interf/base-interf-event.hpp"
#include "runtime/interf/interf-correct-image-event.hpp"
#include "runtime/interf/interf-codec-image-event.hpp"
#include "runtime/interf/interf-base-id-event.hpp"
#include "runtime/interf/interf-capture-image-event.hpp"

#include "runtime/state/change-state-event.hpp"
#include "runtime/state/expand-times-event.hpp"

#include "runtime/control/sync-objs-time.hpp"
#include "runtime/control/sync-objs-action.hpp"
#include "runtime/control/sync-objs-group.hpp"
#include "runtime/control/sync-objs.hpp"

#include "ievents-register_events_in_archives.hpp"
