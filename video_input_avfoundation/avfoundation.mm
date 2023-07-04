//
//  avfoundation.m
//  video_input_avfoundation
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 14/04/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AppKit/AppKit.h>
#include <dispatch/dispatch.h>

#include "avcapture_device_callback.h"

@interface Capture : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>
- (void) captureOutput: (AVCaptureOutput*) poutput
 didOutputSampleBuffer: (CMSampleBufferRef) buffer
        fromConnection: (AVCaptureConnection*) pconnection;
//- (void) captureOutput: (AVCaptureOutput*) output
//   didDropSampleBuffer: (CMSampleBufferRef) buffer
//        fromConnection: (AVCaptureConnection*) connection;
@end
@interface Capture ()
{
   
   AVCaptureSession *            m_psession;
   AVCaptureDevice *             m_pdevice;
   CVImageBufferRef              m_bufferHead;
   CFRunLoopRef                  m_runLoop;
   CIContext *                   m_context;
   CGSize                        m_size;
   bool                          m_bRun;
   avcapture_device_callback *   m_pcallback;
   int                           m_iCount;
   dispatch_queue_t              m_dispatchqueueOutput;
   AVCaptureDeviceInput *        m_pinput;
   AVCaptureVideoDataOutput *    m_poutput;
}

- (void) callCallback;
- (void) stop;
- (void) run;
-(AVCaptureVideoDataOutput *) createOutput;
@end

@implementation Capture

- (id) initWithDevice: (AVCaptureDevice *) pdevice WithCallback : (avcapture_device_callback * ) pcallback withSize : (CGSize) size
{

   self = [super init];
   m_runLoop = CFRunLoopGetCurrent();
   m_bufferHead = nil;
   m_iCount = 0;
   m_size = size;
   m_pcallback = pcallback;
   m_bRun = true;
   m_context = [ CIContext contextWithOptions: nil];

   m_pdevice = pdevice;
   
   NSLog(@"[device] %@", m_pdevice);

   NSError* error = nil;

   m_pinput = [ AVCaptureDeviceInput deviceInputWithDevice: m_pdevice  error: &error];
   
   NSLog(@"[input] %@", m_pinput);

   m_poutput = [ self createOutput ];
    
   return self;
   
}


- (void) run
{
   
   AVCaptureSession* psession = [ [ AVCaptureSession alloc ] init ];
   
   [ psession addInput: m_pinput ];
   
   [ psession addOutput: m_poutput ];
   
   m_psession = psession;

   [ m_psession startRunning ];
   
   CFRunLoopRun();
   
}

- (void) dealloc
{
   
   @synchronized (self)
   {
      
      CVBufferRelease(m_bufferHead);
      
   }

   NSLog(@"capture released");
   
}


- (AVCaptureVideoDataOutput *) createOutput
{
   
   m_dispatchqueueOutput = dispatch_queue_create("AVCaptureOutput", DISPATCH_QUEUE_SERIAL);
   
   AVCaptureVideoDataOutput * poutput = [ [ AVCaptureVideoDataOutput alloc ] init ];

   [ poutput setSampleBufferDelegate: self queue: m_dispatchqueueOutput];

   NSLog(@"[output] %@", poutput);
   
   return poutput;
   
}

- (void) callCallback
{
   
   @synchronized (self)
   {
      
      CIImage* ciImage = [ CIImage imageWithCVImageBuffer: m_bufferHead ];

      CGImageRef cgImage = [m_context createCGImage:ciImage fromRect:CGRectMake(0, 0, m_size.width, m_size.height)];

      auto width = CGImageGetWidth(cgImage);

      auto height = CGImageGetHeight(cgImage);

      auto scan = CGImageGetBytesPerRow(cgImage);

      CFDataRef rawData = CGDataProviderCopyData(CGImageGetDataProvider(cgImage));

      UInt8 * buf = (UInt8 *) CFDataGetBytePtr(rawData);

      m_pcallback->avcapture_device_on_frame(buf, (int) width,(int) height, (int)scan);

      CFRelease(rawData);

      CGImageRelease(cgImage);  // Don't forget this! (memory leak)
      
   }
   
}


- (void )stop
{
   
   m_bRun = false;
   
}

- (void) captureOutput: (AVCaptureOutput*) poutput
   didOutputSampleBuffer: (CMSampleBufferRef) buffer
        fromConnection: (AVCaptureConnection*) pconnection
{
   
#pragma unused (poutput)
#pragma unused (pconnection)
   
   CVImageBufferRef bufferNew = CMSampleBufferGetImageBuffer(buffer);
   
   CVImageBufferRef bufferOld = nullptr;
   
   CVBufferRetain(bufferNew);
   
   @synchronized (self)
   {
      
      bufferOld = m_bufferHead;
      
      m_bufferHead = bufferNew;
    
      m_iCount++;
      
   }
  
   if(bufferOld)
   {
   
      CVBufferRelease(bufferOld);
      
   }
   
   [ self callCallback ];
  
   if (!m_bRun)
   {

      [ m_psession stopRunning ];
      
   }
   
}

//- (void) captureOutput: (AVCaptureOutput*) output
//   didDropSampleBuffer: (CMSampleBufferRef) buffer
//        fromConnection: (AVCaptureConnection*) connection
//{
//#pragma unused (output)
//#pragma unused (buffer)
//#pragma unused (connection)
//}
@end


//int quit(NSError * error)
//{
//  NSLog(@"[error] %@", [error localizedDescription]);
//  return 1;
//}



int avfoundation_enumerate_webcams(CFTypeRef ** pptyperef)
{
   
   NSArray<AVCaptureDevice *> * pdevices = nullptr;
   if (@available(macOS 10.15, *)) {
      auto types = @[AVCaptureDeviceTypeExternalUnknown];
      AVCaptureDeviceDiscoverySession * psession =
      [ AVCaptureDeviceDiscoverySession
        discoverySessionWithDeviceTypes:types
        mediaType: AVMediaTypeVideo position: AVCaptureDevicePositionUnspecified ];
      pdevices = [psession devices];
   }
   else
   {

      pdevices = [AVCaptureDevice devices];

   }
    
   auto count = [ pdevices count ];
   if(count <= 0)
   {
      
      * pptyperef = nullptr;
      return 0;
      
   }
   
   auto ptyperef = new CFTypeRef[count];
   for(int i = 0; i < count; i++)
   {
      ptyperef[i] = (__bridge_retained CFTypeRef ) [pdevices objectAtIndex:i];
      
      
   }
   *pptyperef = ptyperef;
      return (int) count;
   
}

CFTypeRef avdevice_capture_create(CFTypeRef typerefAVCaptureDevice, int w, int h, avcapture_device_callback * pcallback)
{
   CGSize size;
   size.width = w;
   size.height = h;
   AVCaptureDevice* pdevice = (__bridge AVCaptureDevice *)typerefAVCaptureDevice;

  Capture* capture = [[Capture alloc] initWithDevice:pdevice WithCallback:pcallback withSize: size];
//   capture->m_pcallback = ;
  //NSArray* devices =
  //  [AVCaptureDevice devicesWithMediaType: AVMediaTypeVideo];
  //AVCaptureDevice* device = [devices objectAtIndex: 0];
    //[AVCaptureDevice defaultDeviceWithMediaType: AVMediaTypeVideo];
  
  //capture.session = session;
   
  return (__bridge_retained CFTypeRef)capture;
   
}

void avdevice_capture_run(CFTypeRef typerefCapture)
{

   auto pcapture = (__bridge Capture *)typerefCapture;

   NSLog(@"Started");

   [ pcapture run ];
   //while(::task_get_run())
   //{
//   CFRunLoopRun();
//   //}

   NSLog(@"Stopped");

}


void avcapture_stop(CFTypeRef typerefCapture)
{
   
   auto pcapture = (__bridge_transfer Capture *)typerefCapture;
   
   [pcapture stop];

}

const char * avcapture_device_unique_id(CFTypeRef typeref)
{
   
   auto pdevice = (__bridge AVCaptureDevice *) typeref;
   
   return strdup([[ pdevice uniqueID] UTF8String]);
   
}


const char * avcapture_device_localized_name(CFTypeRef typeref)
{
   
   auto pdevice = (__bridge AVCaptureDevice *) typeref;
   
   return strdup([[ pdevice localizedName] UTF8String]);
   
}


bool avcapture_device_set_best_format_001(CFTypeRef ptyperef, int * w, int * h)
{
   
   AVCaptureDevice * pdevice = (__bridge AVCaptureDevice * ) ptyperef;
   
   AVCaptureDeviceFormat * pformatBest = nullptr;
   
   AVFrameRateRange * prangeBest = nullptr;
   
   int wMax = 0;
   
   int hMax = 0;
   
   for(AVCaptureDeviceFormat *pformat in [ pdevice formats ])
   {
    
      
      CMFormatDescriptionRef formatDescription = [pformat formatDescription];

      if (!formatDescription)
      {
      
         return false;
         
      }
      
      CMVideoDimensions dimensions = CMVideoFormatDescriptionGetDimensions(formatDescription);
      
      if(dimensions.width > wMax && dimensions.height > hMax)
      {
         
         pformatBest = pformat;
         
         wMax = dimensions.width;
         
         hMax = dimensions.height;
         
      }


      
   }
   
   
         for( AVFrameRateRange * prange in [ pformatBest videoSupportedFrameRateRanges ] )
         {
   
            if(!prangeBest || [ prange maxFrameRate ] > [ prangeBest maxFrameRate ])
            {
   
               //pformatBest = pformat;
   
               prangeBest = prange;
   
            }
   
        }
     
   [pdevice lockForConfiguration:nil];
          
   // Set the device's active format.
   [pdevice setActiveFormat: pformatBest];
          
          // Set the device's min/max frame duration.
   auto duration = [ prangeBest minFrameDuration];
   [ pdevice setActiveVideoMinFrameDuration : duration];
   [ pdevice setActiveVideoMaxFrameDuration : duration ];
          
   [ pdevice unlockForConfiguration ];

   CMFormatDescriptionRef formatDescription = [pformatBest formatDescription];

   if (!formatDescription)
   {
   
      return false;
      
   }
   
   CMVideoDimensions dimensions = CMVideoFormatDescriptionGetDimensions(formatDescription);
   
   if ((dimensions.width == 0) || (dimensions.height == 0))
   {
      
      return false;
      
   }
   
   *w = dimensions.width;
   
   *h = dimensions.height;
   
   return true;
   
}
