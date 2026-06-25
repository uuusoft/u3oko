/**
\file       v4l2-vgen-resource-holder.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../v4l2-vgen-includes_int.hpp"
#include "v4l2-vgen-resource-holder.hpp"

// old shit
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
namespace dlls::sources::v4l2_vgen::helpers
{
camera_status_t
ACameraManager_deleteCameraIdList_helper (ACameraIdList* val)
{
  ACameraManager_deleteCameraIdList (val);
  return ACAMERA_OK;
}


camera_status_t
ACameraManager_delete_helper (ACameraManager* val)
{
  ACameraManager_delete (val);
  return ACAMERA_OK;
}


camera_status_t
ACameraCaptureSession_close_helper (ACameraCaptureSession* val)
{
  ACameraCaptureSession_close (val);
  return ACAMERA_OK;
}


camera_status_t
ACaptureSessionOutputContainer_free_helper (ACaptureSessionOutputContainer* val)
{
  ACaptureSessionOutputContainer_free (val);
  return ACAMERA_OK;
}


camera_status_t
ACaptureRequest_free_helper (ACaptureRequest* val)
{
  ACaptureRequest_free (val);
  return ACAMERA_OK;
}


camera_status_t
ACameraOutputTarget_free_helper (ACameraOutputTarget* val)
{
  ACameraOutputTarget_free (val);
  return ACAMERA_OK;
}


camera_status_t
ACaptureSessionOutput_free_helper (ACaptureSessionOutput* val)
{
  ACaptureSessionOutput_free (val);
  return ACAMERA_OK;
}


camera_status_t
AImageReader_delete_helper (AImageReader* val)
{
  AImageReader_delete (val);
  return ACAMERA_OK;
}


camera_status_t
ACameraMetadata_free_helper (ACameraMetadata* val)
{
  ACameraMetadata_free (val);
  return ACAMERA_OK;
}


camera_status_t
AImage_delete_helper (AImage* val)
{
  AImage_delete (val);
  return ACAMERA_OK;
}
}   // namespace dlls::sources::v4l2_vgen::helpers
#endif
