// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"
#include "callback.h"
#include "device.h"
#include "format_reader.h"
#include "media_format.h"
#include "video_input.h"
#include "render.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/keep.h"
#include "aura/graphics/image/image.h"
#include "acme/operating_system/windows_common/com/hresult_exception.h"
#include <Mferror.h>
#pragma comment(lib, "mfplat")
#pragma comment(lib, "mf")
#pragma comment(lib, "mfuuid")
#pragma comment(lib, "Shlwapi")

#define HRESULT_ERROR_MSCRAP_HARDWARE_LOCK 0xC00D3704

//#define CHECK_HR(x) if (FAILED(x)) { goto done; }

namespace video_input_media_foundation
{


   callback::callback(device * pdevice) : m_cRef(1), m_iMemory(0), m_bClose(false)
   {

      m_pdevice = pdevice;
      m_bLoop = false;
      m_bStopCapturing = true;

   }


   callback::~callback(void)
   {

      if (m_pmediasession)
      {

         m_pmediasession->Shutdown();

      }

   }


   void callback::_initialize_callback(GUID VideoFormat)
   {

      comptr < IMFMediaType > pmediatype;

      comptr < IMFPresentationDescriptor > ppresentationdescriptor;
      comptr < IMFStreamDescriptor > pstreamdescriptor;
      comptr < IMFMediaTypeHandler > pmediatypehandler;
      comptr < IMFMediaType > pCurrentType;

      HRESULT hr = S_OK;

      ::pointer<::video_input::media_format>pmediaformat;

      if (m_pmediasession)
      {

         m_pmediasession->Shutdown();

      }

      hr = m_pdevice->m_pmediasource->CreatePresentationDescriptor(&ppresentationdescriptor);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      BOOL fSelected;

      hr = ppresentationdescriptor->GetStreamDescriptorByIndex(0, &fSelected, &pstreamdescriptor);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      hr = pstreamdescriptor->GetMediaTypeHandler(&pmediatypehandler);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      DWORD cTypes = 0;

      hr = pmediatypehandler->GetMediaTypeCount(&cTypes);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      if (cTypes > 0)
      {

         hr = pmediatypehandler->GetCurrentMediaType(&pCurrentType);

         if (FAILED(hr))
         {

            auto estatus = ::windows::hresult_status(hr);

            throw ::exception(estatus);

         }

         auto pformatreader = m_pdevice->øcreate_new < format_reader >();

         pmediaformat = pformatreader->Read(pCurrentType);

      }

      unsigned int sizeRawImage = 0;

      if (VideoFormat == MFVideoFormat_RGB24)
      {

         sizeRawImage = pmediaformat->m_uFrameSize * 3;

      }
      else if (VideoFormat == MFVideoFormat_RGB32)
      {

         sizeRawImage = pmediaformat->m_uFrameSize * 4;

      }
      else if (VideoFormat == MFVideoFormat_ARGB32)
      {

         sizeRawImage = pmediaformat->m_uFrameSize * 4;

      }

      m_memorya[0].set_size(sizeRawImage);

      m_memorya[1].set_size(sizeRawImage);

      m_pmemoryOut = &m_memorya[1];

      // Configure the media type that the Sample Grabber will receive.
      // Setting the major and subtype is usually enough for the topology loader
      // to resolve the topology.

      hr = MFCreateMediaType(&pmediatype);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      hr = pmediatype->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      hr = pmediatype->SetGUID(MF_MT_SUBTYPE, VideoFormat);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      // Create the sample grabber sink.
      hr = MFCreateSampleGrabberSinkActivate(pmediatype, this, &m_pdevice->m_pactivate);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      // To run as fast as possible, set this attribute (requires Windows 7):
      hr = m_pdevice->m_pactivate->SetUINT32(MF_SAMPLEGRABBERSINK_IGNORE_CLOCK, true);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      // Create the Media Session.

      hr = MFCreateMediaSession(NULL, &m_pmediasession);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      // Create the topology.

      _create_topology();

   }

   void callback::_start_capturing()
   {

      prop_variant var;

      HRESULT hr = m_pmediasession->Start(&GUID_NULL, &var);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      m_bStopCapturing = false;

   }


   void callback::_stop_capturing()
   {

      m_bStopCapturing = true;

   }


   void callback::_capture_loop()
   {

      KEEP(m_bLoop, true, false);

      m_pdevice->m_edevicestate = ::video_input::e_device_state_capturing;

      comptr < IMFMediaEvent > pEvent;

      HRESULT hr = S_OK;

      hr = m_pmediasession->SetTopology(0, m_ptopology);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      _start_capturing();

      while (::task_get_run())
      {

         HRESULT hrStatus = S_OK;

         if (!m_pmediasession)
         {

            break;

         }

         hr = m_pmediasession->GetEvent(MF_EVENT_FLAG_NO_WAIT, &pEvent);

         if (hr == MF_E_NO_EVENTS_AVAILABLE)
         {

            if (!::task_get_run())
            {

               break;

            }

            preempt(1_s);

            continue;

         }

         if (FAILED(hr))
         {

            auto estatus = ::windows::hresult_status(hr);

            throw ::exception(estatus);

         }

         hr = pEvent->GetStatus(&hrStatus);

         if (hrStatus == HRESULT_ERROR_MSCRAP_HARDWARE_LOCK)
         {

            m_pdevice->m_edevicestate = ::video_input::e_device_state_already_in_use_by_other_client;

         }

         MediaEventType eventtype;

         hr = pEvent->GetType(&eventtype);

         if (FAILED(hr))
         {

            hr = S_OK;

            return;

         }

         switch (eventtype)
         {
         case MESessionStarted:
         {

            if (m_pdevice->m_edevicestate != ::video_input::e_device_state_already_in_use_by_other_client)
            {

               m_pdevice->m_edevicestate = ::video_input::e_device_state_capturing;

            }

         }
         break;
         case MESessionEnded:
         {

            m_pdevice->informationf("IMAGEGRABBER VIDEODEVICE %s: MESessionEnded", m_pdevice->m_strName.c_str());

            m_pmediasession->Stop();

         }
         break;

         case MESessionStopped:
         {

            m_pdevice->informationf("IMAGEGRABBER VIDEODEVICE %s: MESessionStopped", m_pdevice->m_strName.c_str());

         }
         break;

         case MEVideoCaptureDeviceRemoved:
         {

            m_pdevice->informationf("IMAGEGRABBER VIDEODEVICE %s: MEVideoCaptureDeviceRemoved", m_pdevice->m_strName.c_str());

            m_pdevice->m_edevicestate = ::video_input::e_device_state_device_removed;

         }
         break;
         case MESessionTopologyStatus:
         {

            MF_TOPOSTATUS status = MF_TOPOSTATUS_INVALID;

            HRESULT hr = pEvent->GetUINT32(MF_EVENT_TOPOLOGY_STATUS, (UINT32 *)&status);

            if (SUCCEEDED(hr))
            {

               m_pdevice->informationf("IMAGEGRABBER VIDEODEVICE %s: MESessionTopologyStatus %d", m_pdevice->m_strName.c_str(), status);

               if (status == MF_TOPOSTATUS_READY)
               {



               }
               else if (status == MF_TOPOSTATUS_ENDED)
               {


               }

            }

            break;

         }
         default:
            break;
         }

         if (m_pdevice->m_edevicestate == ::video_input::e_device_state_device_removed)
         {

            m_pdevice->m_pvideoinput->itema().erase(m_pdevice);

            break;

         }

      }

   }


   void callback::_create_topology()
   {

      comptr<IMFPresentationDescriptor > ppresentationdescriptor;
      comptr<IMFStreamDescriptor > pstreamdescriptor;
      comptr<IMFMediaTypeHandler > pmediatypehandler;
      comptr<IMFTopologyNode > pNode1;
      comptr<IMFTopologyNode > pNode2;

      HRESULT hr = S_OK;
      DWORD cStreams = 0;

      hr = MFCreateTopology(&m_ptopology);

      if (FAILED(hr))
      {

         auto estatus = ::windows::hresult_status(hr);

         throw ::exception(estatus);

      }

      hr = m_pdevice->m_pmediasource->CreatePresentationDescriptor(&ppresentationdescriptor);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = ppresentationdescriptor->GetStreamDescriptorCount(&cStreams);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      for (DWORD i = 0; i < cStreams; i++)
      {

         // In this example, we look for audio streams and connect them to the sink.

         BOOL fSelected = false;

         GUID majorType;

         hr = ppresentationdescriptor->GetStreamDescriptorByIndex(i, &fSelected, &pstreamdescriptor);

         if (FAILED(hr))
         {

            throw ::hresult_exception(hr);

         }

         hr = pstreamdescriptor->GetMediaTypeHandler(&pmediatypehandler);

         if (FAILED(hr))
         {

            throw ::hresult_exception(hr);

         }

         hr = pmediatypehandler->GetMajorType(&majorType);

         if (FAILED(hr))
         {

            throw ::hresult_exception(hr);

         }

         if (majorType == MFMediaType_Video && fSelected)
         {

            _add_source_node(ppresentationdescriptor, pstreamdescriptor, pNode1);

            _add_output_node(0, pNode2);

            hr = pNode1->ConnectOutput(0, pNode2, 0);

            if (FAILED(hr))
            {

               throw ::hresult_exception(hr);

            }

            break;

         }
         else
         {

            hr = ppresentationdescriptor->DeselectStream(i);

            if (FAILED(hr))
            {

               throw ::hresult_exception(hr);

            }

         }

      }

   }


   void callback::_add_source_node(
      IMFPresentationDescriptor * ppresentationdescriptor,   // Presentation descriptor.
      IMFStreamDescriptor * pstreamdescriptor,         // Stream descriptor.
      comptr < IMFTopologyNode > & pnode)         // Receives the node pointer.
   {

      HRESULT hr = S_OK;

      hr = MFCreateTopologyNode(MF_TOPOLOGY_SOURCESTREAM_NODE, &pnode);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = pnode->SetUnknown(MF_TOPONODE_SOURCE, m_pdevice->m_pmediasource);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = pnode->SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, ppresentationdescriptor);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = pnode->SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, pstreamdescriptor);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = m_ptopology->AddNode(pnode);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

   }


   void callback::_add_output_node(
      DWORD dwId,                 // Identifier of the stream sink.
      comptr < IMFTopologyNode > & pnode)   // Receives the node pointer.
   {

      HRESULT hr = S_OK;

      hr = MFCreateTopologyNode(MF_TOPOLOGY_OUTPUT_NODE, &pnode);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = pnode->SetObject(m_pdevice->m_pactivate);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = pnode->SetUINT32(MF_TOPONODE_STREAMID, dwId);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = pnode->SetUINT32(MF_TOPONODE_NOSHUTDOWN_ON_REMOVE, false);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

      hr = m_ptopology->AddNode(pnode);

      if (FAILED(hr))
      {

         throw ::hresult_exception(hr);

      }

   }




   STDMETHODIMP callback::QueryInterface(REFIID riid, void ** ppv)
   {
      // Creation tab of shifting interfaces from start of this class
      static const QITAB qit[] =
      {

          QITABENT(callback, IMFSampleGrabberSinkCallback),
          QITABENT(callback, IMFSampleGrabberSinkCallback2),
          QITABENT(callback, IMFClockStateSink),
          { 0 }
      };
      auto result = QISearch(this, qit, riid, ppv);

      return result;
   }


   STDMETHODIMP_(ULONG) callback::AddRef()
   {
      return InterlockedIncrement(&m_cRef);
   }

   STDMETHODIMP_(ULONG) callback::Release()
   {
      ULONG cRef = InterlockedDecrement(&m_cRef);
      if (cRef == 0)
      {
         delete this;
      }
      return cRef;
   }

   STDMETHODIMP callback::OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset)
   {
      return S_OK;
   }

   STDMETHODIMP callback::OnClockStop(MFTIME hnsSystemTime)
   {
      return S_OK;
   }

   STDMETHODIMP callback::OnClockPause(MFTIME hnsSystemTime)
   {
      return S_OK;
   }

   STDMETHODIMP callback::OnClockRestart(MFTIME hnsSystemTime)
   {
      return S_OK;
   }

   STDMETHODIMP callback::OnClockSetRate(MFTIME hnsSystemTime, float flRate)
   {
      return S_OK;
   }

   STDMETHODIMP callback::OnSetPresentationClock(IMFPresentationClock * pClock)
   {
      return S_OK;
   }

   STDMETHODIMP callback::OnProcessSampleEx(
      /* [in] */ REFGUID guidMajorMediaType,
      /* [in] */ DWORD dwSampleFlags,
      /* [in] */ LONGLONG llSampleTime,
      /* [in] */ LONGLONG llSampleDuration,
      /* [annotation][in] */
      _In_reads_bytes_(dwSampleSize)  const BYTE * pSampleBuffer,
      /* [in] */ DWORD dwSampleSize,
      /* [annotation][in] */
      _In_  IMFAttributes * pAttributes)
   {

      return OnProcessSample(guidMajorMediaType, dwSampleFlags,
         llSampleTime, llSampleDuration,
         pSampleBuffer,
         dwSampleSize);
   }

   STDMETHODIMP callback::OnProcessSample(
      REFGUID guidMajorMediaType, DWORD dwSampleFlags,
      LONGLONG llSampleTime, LONGLONG llSampleDuration, const BYTE * pSampleBuffer,
      DWORD dwSampleSize)
   {

      m_memorya[m_iMemory].copy_from(pSampleBuffer, dwSampleSize);

      m_memorya[m_iMemory].set_flag(e_flag_changed);

      m_pmemoryOut = &m_memorya[m_iMemory];

      if (m_iMemory == 0)
      {

         m_iMemory = 1;

      }
      else
      {

         m_iMemory = 0;

      }

      pixmap p;

      p.initialize(m_pdevice->m_size, (image32_t *)pSampleBuffer, m_pdevice->m_size.cx() * 4);

      if (!m_pdevice->get_render()->m_pimage)
      {

         m_pdevice->øconstruct(m_pdevice->get_render()->m_pimage);

         m_pdevice->get_render()->m_pimage->create(m_pdevice->m_size);

      }

      for (int iLine = 0; iLine < m_pdevice->m_size.cy(); iLine++)
      {

         auto pline = ((unsigned char *)pSampleBuffer) + m_pdevice->m_size.cx() * 4 * iLine;

         pline += 3;

         for (int x = 0; x < m_pdevice->m_size.cx(); x++)
         {

            *pline = 255;

            pline += 4;

         }

      }

      synchronous_lock synchronouslock(m_pdevice->get_render()->synchronization());

      m_pdevice->get_render()->m_pimage->copy(& p);
      return S_OK;

   }


   STDMETHODIMP callback::OnShutdown()
   {
      return S_OK;
   }


   ::memory * callback::get_memory()
   {

      return m_pmemoryOut;

   }



} // namespace video_input_media_foundation



