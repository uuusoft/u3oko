#pragma once
/**
file        includes.hpp
\brief      Файл, определяет набор интерфейсов и типов для ядра.
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       10.12.2016.
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Внешний интерфейс включения модуля.
*/
#include "event.hpp"
#include "timed-event.hpp"

#include "props/terminals/end-point-prop.hpp"

#include "props/mix_mul/out-channel-info.hpp"
#include "props/mix_mul/mix-mul-prop.hpp"

#include "props/application/application-prop.hpp"
#include "props/hardware/info-cpu-event.hpp"

#include "props/base_id/buff2module-info.hpp"
#include "props/base_id/base-id-prop.hpp"

#include "props/videos/gens/diff/params-video-diff-prop.hpp"
#include "props/videos/gens/diff/info-buff-video-diff-prop.hpp"
#include "props/videos/gens/diff/video-diff-prop.hpp"

#include "props/videos/noises/time/video-time-noise-remover-prop.hpp"
#include "props/videos/noises/time/ext/median-time-filter-prop.hpp"
#include "props/videos/noises/time/ext/COldTimeNoiseRemoverProp.hpp"

#include "props/videos/noises/freq/info-buff-freq-noise-remover.hpp"
#include "props/videos/noises/freq/freq-video-noise-remover-prop.hpp"

#include "props/videos/noises/space/video-space-noise-remover-prop.hpp"
//#include "props/videos/noises/space/ext/COldSpaceNoiseRemoverProp.hpp"
#include "props/videos/noises/space/ext/median-space-filter-prop.hpp"

#include "props/videos/generic/convolution/buff-video-convolution-prop.hpp"
#include "props/videos/generic/convolution/video-convolution-prop.hpp"

#include "props/videos/generic/motion_est/events-buff-info.hpp"
#include "props/videos/generic/motion_est/video-est-motion-prop.hpp"

#include "props/videos/generic/vec2image/buff-event-info-vec2image1.hpp"
#include "props/videos/generic/vec2image/vec2image-prop.hpp"

#include "props/videos/generic/scaler/buff-event-info-video-scaler.hpp"
#include "props/videos/generic/scaler/video-scaler-prop.hpp"

#include "props/videos/generic/sharper/CVideoSharperProp.hpp"
#include "props/videos/generic/detect/video-detect-prop.hpp"

#include "props/videos/generic/convert/type-src2dst.hpp"
#include "props/videos/generic/convert/type-convert-accuracy.hpp"
#include "props/videos/generic/convert/video-convert-prop.hpp"

#include "props/videos/generic/correct/video-correct-prop.hpp"
#include "props/videos/generic/gradient/gradient-prop.hpp"
#include "props/videos/generic/histogram/video-histogram-prop.hpp"
#include "props/videos/generic/text/CVideoTextProp.hpp"
#include "props/videos/generic/matrix/CVideoMatrixProp.hpp"

#include "props/videos/generic/driver/type-catch-rgn.hpp"
#include "props/videos/generic/driver/video-driver-prop.hpp"
#include "props/videos/generic/driver/links-video-driver-prop.hpp"
#include "props/videos/generic/driver/video-driver-capture-prop.hpp"

#include "props/videos/generic/codec/consts/vals.hpp"
#include "props/videos/generic/codec/override-codec-data-type.hpp"
#include "props/videos/generic/codec/type-codec-mode.hpp"
#include "props/videos/generic/codec/video-codec-flat-prop.hpp"
#include "props/videos/generic/codec/video-codec-prop.hpp"

#include "props/videos/generic/morph/morph-operation-type.hpp"
#include "props/videos/generic/morph/morph-operation-params.hpp"
#include "props/videos/generic/morph/morph-buff-info.hpp"
#include "props/videos/generic/morph/video-morphology-prop.hpp"

#include "props/modules/log/consts/vals.hpp"
#include "props/modules/log/vals-log-module.hpp"
#include "props/modules/log/property-log-module-event.hpp"

#include "props/modules/storage/using-path-type.hpp"
#include "props/modules/storage/checker-storage-type.hpp"
#include "props/modules/storage/path-info.hpp"
#include "props/modules/storage/property-storage-module-event.hpp"

#include "props/modules/events/consts/vals.hpp"
#include "props/modules/events/vals-events-module.hpp"
#include "props/modules/events/property-events-module-event.hpp"

#include "runtime/runtime-event.hpp"
#include "runtime/error/base-error-event.hpp"

#include "runtime/mem/buff-event.hpp"
#include "runtime/mem/buffs-event.hpp"
#include "runtime/mem/zip-data-event.hpp"

#include "runtime/video/frame-done.hpp"
#include "runtime/video/detect-violation.hpp"
#include "runtime/video/face-detect.hpp"

#include "runtime/interf/base-interf-event.hpp"
#include "runtime/interf/icorrect-image.hpp"
#include "runtime/interf/icodec-image.hpp"
#include "runtime/interf/ibase-id.hpp"
#include "runtime/interf/icapture-image.hpp"
#include "runtime/interf/interf-correct-image-event.hpp"
#include "runtime/interf/interf-codec-image-event.hpp"
#include "runtime/interf/interf-base-id-event.hpp"
#include "runtime/interf/interf-capture-image-event.hpp"

#include "runtime/state/change-state-event.hpp"
#include "runtime/state/expand-time-statistic-event.hpp"

#include "register_events_in_archives.hpp"
