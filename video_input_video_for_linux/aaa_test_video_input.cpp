// https://www.codeproject.com/Tips/559437/Capturing-Video-from-Web-camera_parameters-on-Windows-and-by
#include "framework.h"

// TestvideoInput.cpp: �������u�t�u�|���u�� �������{�� �r�����t�p �t�|�� �{���~�����|���~���s�� �����y�|���w�u�~�y��.
//

//#include "framework.h"
#include <windows.h>
//#include "video_input_video_for_linux.h"
//#include "highgui.h"

#pragma comment(lib, "lib\\opencv\\Release\\opencv_highgui242.lib")
#pragma comment(lib, "lib\\opencv\\Release\\opencv_core242.lib")

#pragma comment(lib, "video_input_video_for_linux.lib")

void StopEvent(int deviceID, void * userData)
{
   video_input_video_for_linux * VI = &video_input_video_for_linux::get_instance();

   VI->close_device(deviceID);
}

int _tmain(int argc, TCHAR * argv[])
{
   video_input_video_for_linux * VI = &video_input_video_for_linux::get_instance();

   int i = VI->list_devices();

   if (i > 0)
   {
      if (VI->setup_device(i - 1, 640, 480, 60))
      {
         VI->set_emergency_stop_event(i - 1, NULL, StopEvent);

         if (VI->is_frame_new(i - 1))
         {
            int countLeftFrames = 0;

            cvNamedWindow("VideoTest", CV_WINDOW_AUTOSIZE);
            CvSize size = cvSize(VI->get_width(i - 1), VI->get_height(i - 1));

            IplImage * frame;

            frame = cvCreateImage(size, 8, 3);

            while (1)
            {
               if (VI->is_frame_new(i - 1))
               {
                  VI->get_pixels(i - 1, (unsigned char *)frame->imageData);

                  cvShowImage("VideoTest", frame);

                  countLeftFrames = 0;
               }
               else
                  countLeftFrames++;

               char c = cvWaitKey(33);

               if (c == 27)
                  break;

               if (c == 49)
               {
                  camera_parameters CP = VI->get_parameters(i - 1);
                  CP.Brightness.m_lCurrentValue = 128;
                  CP.Brightness.m_lFlag = 1;
                  VI->set_parameters(i - 1, CP);
               }

               if (!VI->is_device_setup(i - 1))
               {
                  break;
               }

               if (countLeftFrames > 60)
                  break;
            }

            VI->close_device(i - 1);

            cvDestroyWindow("VideoTest");
         }
      }
   }

   if (VI->setup_device(i - 1, 1920, 1080, 60))
   {
      if (VI->is_frame_new(i - 1))
      {
         int countLeftFrames = 0;

         cvNamedWindow("VideoTest1", CV_WINDOW_AUTOSIZE);
         CvSize size = cvSize(VI->get_width(i - 1), VI->get_height(i - 1));

         IplImage * frame;

         frame = cvCreateImage(size, 8, 3);

         while (1)
         {
            if (VI->is_frame_new(i - 1))
            {
               VI->get_pixels(i - 1, (unsigned char *)frame->imageData, false);
               cvShowImage("VideoTest1", frame);
               countLeftFrames = 0;
            }
            else
               countLeftFrames++;

            char c = cvWaitKey(33);

            if (c == 27)
               break;

            if (!VI->is_device_setup(i - 1))
            {
               break;
            }

            if (countLeftFrames > 60)
               break;
         }

         VI->close_device(i - 1);

         cvDestroyWindow("VideoTest1");
      }

   }
   return 0;
}
