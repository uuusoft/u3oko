#pragma once
/**
\file       v4l2-vgen-resource-holder.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.02.2026
\project    u3_v4l2_vgen
*/

// old shit
#ifdef U3_FAKE_DISABLE
namespace dlls::sources::v4l2_vgen::helpers
{
template< typename ResourceTType, camera_status_t (*free_funct) (ResourceTType*) >
class ResourceHolder final
{
  public:
  explicit ResourceHolder (ResourceTType* val = nullptr) :
    resource_ (val)
  {
  }


  ~ResourceHolder ()
  {
    release ();
  }

  ResourceHolder (const ResourceHolder&)            = delete;
  ResourceHolder& operator= (const ResourceHolder&) = delete;


  void
  release () noexcept
  {
    if (nullptr == resource_)
    {
      return;
    }

    try
    {
      camera_status_t res = ACAMERA_OK;
      U3_CHECK_AVGEN (free_funct (resource_));
    }
    catch (const std::exception& e)
    {
      U3_LOG_DATA_EXCEPT (/*std::string (typeid (ResourceTType).name ()) +*/ e.what ());
    }
    catch (...)
    {
      U3_LOG_DATA_EXCEPT (/*typeid (ResourceTType).name ()*/ "...");
    }

    resource_ = nullptr;
  }


  ResourceTType*&
  update ()
  {
    release ();
    return resource_;
  }


  void
  set (ResourceTType* val)
  {
    release ();
    resource_ = val;
  }


  operator bool () const
  {
    return resource_ ? true : false;
  }


  ResourceTType*
  operator->()
  {
    U3_CHECK (resource_, "operator->");
    return resource_;
  }


  ResourceTType*
  operator* ()
  {
    U3_CHECK (resource_, "operator*");
    return resource_;
  }


  private:
  ResourceTType* resource_;
};


camera_status_t ACameraManager_deleteCameraIdList_helper (ACameraIdList* val);
camera_status_t ACameraManager_delete_helper (ACameraManager* val);
camera_status_t ACameraCaptureSession_close_helper (ACameraCaptureSession* val);
camera_status_t ACaptureSessionOutputContainer_free_helper (ACaptureSessionOutputContainer* val);
camera_status_t ACaptureRequest_free_helper (ACaptureRequest* val);
camera_status_t ACameraOutputTarget_free_helper (ACameraOutputTarget* val);
camera_status_t ACaptureSessionOutput_free_helper (ACaptureSessionOutput* val);
camera_status_t AImageReader_delete_helper (AImageReader* val);
camera_status_t ACameraMetadata_free_helper (ACameraMetadata* val);
camera_status_t AImage_delete_helper (AImage* val);

using acamera_id_list_type                   = ResourceHolder< ACameraIdList, ACameraManager_deleteCameraIdList_helper >;
using acamera_manager_type                   = ResourceHolder< ACameraManager, ACameraManager_delete_helper >;
using acamera_device_type                    = ResourceHolder< ACameraDevice, ACameraDevice_close >;
using acamera_capture_session_type           = ResourceHolder< ACameraCaptureSession, ACameraCaptureSession_close_helper >;
using acapture_session_output_container_type = ResourceHolder< ACaptureSessionOutputContainer, ACaptureSessionOutputContainer_free_helper >;
using acapture_session_output_type           = ResourceHolder< ACaptureSessionOutput, ACaptureSessionOutput_free_helper >;
using acapture_request_type                  = ResourceHolder< ACaptureRequest, ACaptureRequest_free_helper >;
using acamera_output_target_type             = ResourceHolder< ACameraOutputTarget, ACameraOutputTarget_free_helper >;
using aimage_reader_type                     = ResourceHolder< AImageReader, AImageReader_delete_helper >;
using acamera_metadata_type                  = ResourceHolder< ACameraMetadata, ACameraMetadata_free_helper >;
using aimage_type                            = ResourceHolder< AImage, AImage_delete_helper >;
}   // namespace dlls::sources::v4l2_vgen::helpers
#endif
