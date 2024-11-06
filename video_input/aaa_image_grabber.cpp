// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"

#include "_video_input.h"

#pragma comment(lib, "mfplat")
#pragma comment(lib, "mf")
#pragma comment(lib, "mfuuid")
#pragma comment(lib, "Shlwapi")


//#define CHECK_HR(x) if (FAILED(x)) { goto done; }

namespace video_input
{


   image_grabber::image_grabber(unsigned int deviceID) : m_cRef(1), m_uDevice(deviceID), m_iMemory(0), m_bClose(false)
   {

      HRESULT hr = MFStartup(MF_VERSION);

      if (FAILED(hr))
      {
         debug_print_out * pdebugprintout = &debug_print_out::get_instance();

         pdebugprintout->print_out(L"MEDIA FOUNDATION: It cannot be created!!!\n");
      }

   }


   image_grabber::~image_grabber(void)
   {

      if (m_pmediasession)
      {

         m_pmediasession->Shutdown();

      }

      debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: Destroing instance of the image_grabber class \n", m_uDevice);

   }

   HRESULT image_grabber::initImageGrabber(IMFMediaSource * pSource, GUID VideoFormat)
   {
      
      comptr < IMFActivate > pSinkActivate;
      comptr < IMFMediaType > pmediatype;

      comptr < IMFPresentationDescriptor > ppresentationdescriptor;
      comptr < IMFStreamDescriptor > pstreamdescriptor;
      comptr < IMFMediaTypeHandler > pmediatypehandler;
      comptr < IMFMediaType > pCurrentType;

      HRESULT hr = S_OK;
      media MT;

      // Clean up.
      if (m_pmediasession)
      {
         m_pmediasession->Shutdown();
      }

      //SafeReleaseAllCount(&m_pmediasession);
      //SafeReleaseAllCount(&m_ptopology);

      m_pmediasource = pSource;




      hr = pSource->CreatePresentationDescriptor(&ppresentationdescriptor);
      if (FAILED(hr))
      {
         return hr;
      }

      BOOL fSelected;
      hr = ppresentationdescriptor->GetStreamDescriptorByIndex(0, &fSelected, &pstreamdescriptor);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pstreamdescriptor->GetMediaTypeHandler(&pmediatypehandler);
      if (FAILED(hr))
      {
         return hr;
      }

      DWORD cTypes = 0;
      hr = pmediatypehandler->GetMediaTypeCount(&cTypes);
      if (FAILED(hr))
      {
         return hr;
      }

      if (cTypes > 0)
      {
         hr = pmediatypehandler->GetCurrentMediaType(&pCurrentType);

         if (FAILED(hr))
         {
            return hr;
         }

         MT = format_reader::Read(pCurrentType);
      }

   //err:
//      SafeReleaseAllCount(&ppresentationdescriptor);
  //    ::acme::del(pstreamdescriptor);
    //  ::acme::del(pmediatypehandler);
      //::acme::del(pCurrentType);

      unsigned int sizeRawImage = 0;

      if (VideoFormat == MFVideoFormat_RGB24)
      {
         sizeRawImage = MT.m_uFrameSize * 3;
      }
      else if (VideoFormat == MFVideoFormat_RGB32)
      {
         sizeRawImage = MT.m_uFrameSize * 4;
      }
      else if (VideoFormat == MFVideoFormat_ARGB32)
      {
         sizeRawImage = MT.m_uFrameSize * 4;
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

         return hr;

      }

      hr = pmediatype->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);

      if (FAILED(hr))
      {

         return hr;

      }

      hr = pmediatype->SetGUID(MF_MT_SUBTYPE, VideoFormat);

      if (FAILED(hr))
      {

         return hr;

      }


      // Create the sample grabber sink.
      hr = MFCreateSampleGrabberSinkActivate(pmediatype, this, &pSinkActivate);


      if (FAILED(hr))
      {

         return hr;

      }



      // To run as fast as possible, set this attribute (requires Windows 7):
      hr = pSinkActivate->SetUINT32(MF_SAMPLEGRABBERSINK_IGNORE_CLOCK, true);


      if (FAILED(hr))
      {

         return hr;

      }



      // Create the Media Session.

      hr = MFCreateMediaSession(NULL, &m_pmediasession);


      if (FAILED(hr))
      {

         return hr;

      }



      // Create the topology.
      hr = CreateTopology(pSource, pSinkActivate, &m_ptopology);
         

      if (FAILED(hr))
      {

         return hr;

      }




      return hr;
   }

   
   void image_grabber::stopGrabbing()
   {
      
      if (m_pmediasession)
      {

         m_pmediasession->Stop();

      }

      debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: Stopping of of grabbing of images\n", m_uDevice);

   }


   HRESULT image_grabber::startGrabbing(void)
   {
      debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      comptr< IMFMediaEvent > pEvent;

      //::CoInitialize(NULL);

      prop_variant var;
      PropVariantInit(&var);

      HRESULT hr = S_OK;
      hr = m_pmediasession->SetTopology(0, m_ptopology);

      if (FAILED(hr))
      {

         return hr;

      }

      hr = m_pmediasession->Start(&GUID_NULL, &var);

      if (FAILED(hr))
      {

         return hr;

      }

      pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: Start Grabbing of the images\n", m_uDevice);

      while (1)
      {

         HRESULT hrStatus = S_OK;

         MediaEventType met;

         if (!m_pmediasession)
         {

            break;

         }

         hr = m_pmediasession->GetEvent(0, &pEvent);

         if (FAILED(hr))
         {

            return hr;

         }

         hr = pEvent->GetStatus(&hrStatus);

         if (FAILED(hr))
         {
            hr = S_OK;

            return hr;
         }

         hr = pEvent->GetType(&met);

         if (FAILED(hr))
         {
            hr = S_OK;

            return hr;
         }

         if (met == MESessionEnded)
         {
            pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: MESessionEnded \n", m_uDevice);

            m_pmediasession->Stop();

            break;
         }

         if (met == MESessionStopped)
         {
            pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: MESessionStopped \n", m_uDevice);

            break;
         }


         if (met == MEVideoCaptureDeviceRemoved)
         {
            pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: MEVideoCaptureDeviceRemoved \n", m_uDevice);

            break;
         }

      }

      pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: Finish startGrabbing \n", m_uDevice);

      return hr;

   }


   HRESULT image_grabber::CreateTopology(IMFMediaSource * pSource, IMFActivate * pSinkActivate, IMFTopology ** ppTopo)
   {
      comptr<IMFTopology > pTopology;
      comptr<IMFPresentationDescriptor > ppresentationdescriptor;
      comptr<IMFStreamDescriptor > pstreamdescriptor;
      comptr<IMFMediaTypeHandler > pmediatypehandler;
      comptr<IMFTopologyNode > pNode1;
      comptr<IMFTopologyNode > pNode2;

      HRESULT hr = S_OK;
      DWORD cStreams = 0;

      hr = MFCreateTopology(&pTopology);

      if (FAILED(hr))
      {

         return hr;

      }


      hr = pSource->CreatePresentationDescriptor(&ppresentationdescriptor);

      if (FAILED(hr))
      {

         return hr;

      }


      hr = ppresentationdescriptor->GetStreamDescriptorCount(&cStreams);


      if (FAILED(hr))
      {

         return hr;

      }



      for (DWORD i = 0; i < cStreams; i++)
      {
         // In this example, we look for audio streams and connect them to the sink.

         BOOL fSelected = false;
         GUID majorType;

         hr = ppresentationdescriptor->GetStreamDescriptorByIndex(i, &fSelected, &pstreamdescriptor);
         if (FAILED(hr))
         {
            return hr;
         }

         hr = pstreamdescriptor->GetMediaTypeHandler(&pmediatypehandler);
         if (FAILED(hr))
         {
            return hr;
         }

         hr = pmediatypehandler->GetMajorType(&majorType);
         if (FAILED(hr))
         {
            return hr;
         }


         if (majorType == MFMediaType_Video && fSelected)
         {
            hr = AddSourceNode(pTopology, pSource, ppresentationdescriptor, pstreamdescriptor, &pNode1);
            if (FAILED(hr))
            {
               return hr;
            }

            hr = AddOutputNode(pTopology, pSinkActivate, 0, &pNode2);
            if (FAILED(hr))
            {
               return hr;
            }

            hr = pNode1->ConnectOutput(0, pNode2, 0);
            if (FAILED(hr))
            {
               return hr;
            }

            break;
         }
         else
         {
            hr = ppresentationdescriptor->DeselectStream(i);
            if (FAILED(hr))
            {
               return hr;
            }

         }
      }

      *ppTopo = pTopology;
      (*ppTopo)->AddRef();

      return hr;

   }

   HRESULT image_grabber::AddSourceNode(
      IMFTopology * pTopology,           // Topology.
      IMFMediaSource * pSource,          // Media source.
      IMFPresentationDescriptor * ppresentationdescriptor,   // Presentation descriptor.
      IMFStreamDescriptor * pstreamdescriptor,         // Stream descriptor.
      IMFTopologyNode ** ppNode)         // Receives the node pointer.
   {
      IMFTopologyNode * pNode = NULL;

      HRESULT hr = S_OK;
      hr = MFCreateTopologyNode(MF_TOPOLOGY_SOURCESTREAM_NODE, &pNode);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pNode->SetUnknown(MF_TOPONODE_SOURCE, pSource);
      if (FAILED(hr))
      {
         return hr;
      }
      hr = pNode->SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, ppresentationdescriptor);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pNode->SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, pstreamdescriptor);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pTopology->AddNode(pNode);
      if (FAILED(hr))
      {
         return hr;
      }


      // Return the pointer to the caller.
      *ppNode = pNode;
      (*ppNode)->AddRef();

      return hr;

   }


   HRESULT image_grabber::AddOutputNode(
      IMFTopology * pTopology,     // Topology.
      IMFActivate * pActivate,     // Media sink activation object.
      DWORD dwId,                 // Identifier of the stream sink.
      IMFTopologyNode ** ppNode)   // Receives the node pointer.
   {
      IMFTopologyNode * pNode = NULL;

      HRESULT hr = S_OK;
      hr = MFCreateTopologyNode(MF_TOPOLOGY_OUTPUT_NODE, &pNode);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pNode->SetObject(pActivate);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pNode->SetUINT32(MF_TOPONODE_STREAMID, dwId);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pNode->SetUINT32(MF_TOPONODE_NOSHUTDOWN_ON_REMOVE, false);
      if (FAILED(hr))
      {
         return hr;
      }

      hr = pTopology->AddNode(pNode);
      if (FAILED(hr))
      {
         return hr;
      }


      // Return the pointer to the caller.
      *ppNode = pNode;
      (*ppNode)->AddRef();

      return hr;

   }


   HRESULT image_grabber::CreateInstance(image_grabber ** ppIG, unsigned int deviceID)
   {

      *ppIG = aaa_primitive_new image_grabber(deviceID);

      if (ppIG == NULL)
      {

         return E_OUTOFMEMORY;

      }

      debug_print_out * pdebugprintout = &debug_print_out::get_instance();

      pdebugprintout->print_out(L"IMAGEGRABBER VIDEODEVICE %i: Creating instance of image_grabber\n", deviceID);

      return S_OK;

   }


   STDMETHODIMP image_grabber::QueryInterface(REFIID riid, void ** ppv)
   {
      // Creation tab of shifting interfaces from start of this class
      static const QITAB qit[] =
      {

          QITABENT(image_grabber, IMFSampleGrabberSinkCallback),
          QITABENT(image_grabber, IMFClockStateSink),
          { 0 }
      };
      return QISearch(this, qit, riid, ppv);
   }

   STDMETHODIMP_(ULONG) image_grabber::AddRef()
   {
      return InterlockedIncrement(&m_cRef);
   }

   STDMETHODIMP_(ULONG) image_grabber::Release()
   {
      ULONG cRef = InterlockedDecrement(&m_cRef);
      if (cRef == 0)
      {
         delete this;
      }
      return cRef;
   }

   STDMETHODIMP image_grabber::OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset)
   {
      return S_OK;
   }

   STDMETHODIMP image_grabber::OnClockStop(MFTIME hnsSystemTime)
   {
      return S_OK;
   }

   STDMETHODIMP image_grabber::OnClockPause(MFTIME hnsSystemTime)
   {
      return S_OK;
   }

   STDMETHODIMP image_grabber::OnClockRestart(MFTIME hnsSystemTime)
   {
      return S_OK;
   }

   STDMETHODIMP image_grabber::OnClockSetRate(MFTIME hnsSystemTime, float flRate)
   {
      return S_OK;
   }

   STDMETHODIMP image_grabber::OnSetPresentationClock(IMFPresentationClock * pClock)
   {
      return S_OK;
   }

   STDMETHODIMP image_grabber::OnProcessSample(REFGUID guidMajorMediaType, DWORD dwSampleFlags,
      LONGLONG llSampleTime, LONGLONG llSampleDuration, const BYTE * pSampleBuffer,
      DWORD dwSampleSize)
   {
      
      m_memorya[m_iMemory].copy_from(pSampleBuffer, dwSampleSize);

      m_memorya[m_iMemory].m_eobject += e_object_changed;

      m_pmemoryOut = &m_memorya[m_iMemory];

      if (m_iMemory == 0)
      {

         m_iMemory = 1;

      }
      else
      {

         m_iMemory = 0;

      }

      return S_OK;

   }


   STDMETHODIMP image_grabber::OnShutdown()
   {
      return S_OK;
   }

   
   ::memory * image_grabber::get_memory()
   {
      
      return m_pmemoryOut;

   }



} // namespace video_input



