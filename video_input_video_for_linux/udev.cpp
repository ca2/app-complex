/*
Copyright (C) 2014 by Leonhard Oelke <leonhard@in-verted.de>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "framework.h"
#include "video_input.h"
#include "device.h"
#include <pthread.h>
#include <libudev.h>
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/acme.h"
#include "apex/platform/system.h"

//#include <util/threading.h>
//#include <util/darray.h>
//#include <obs.h>

//#include "v4l2-udev.h"

/** udev action enum */
enum udev_action {
   UDEV_ACTION_ADDED,
   UDEV_ACTION_REMOVED,
   UDEV_ACTION_UNKNOWN
};

//static const char *udev_signals[] = {"void device_added(string device)",
//                                     "void device_removed(string device)",
//                                     NULL};

/* global data */
static uint_fast32_t udev_refs = 0;
static pthread_mutex_t udev_mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_t udev_thread;
//static os_event_t *udev_event;

//static signal_handler_t *udev_signalhandler = NULL;

///**
// * udev gives us the device action as string, so we convert it here ...
// *
// * @param action the udev action as string
// * @return the udev action as enum value
// */
static enum udev_action udev_action_to_enum(const char *action)
{
   if (!action)
      return UDEV_ACTION_UNKNOWN;

   if (!strncmp("add", action, 3))
      return UDEV_ACTION_ADDED;
   if (!strncmp("remove", action, 6))
      return UDEV_ACTION_REMOVED;

   return UDEV_ACTION_UNKNOWN;
}

CLASS_DECL_ACME ::acme::system * acmesystem();
/**
 * Call all registered callbacks with the event
 *
 * @param dev udev device that had an event occuring
 */
static inline void udev_signal_event(struct udev_device *dev)
{
   const char *node;
   enum udev_action action;
   //struct calldata data;

   pthread_mutex_lock(&udev_mutex);

   node = udev_device_get_devnode(dev);
   auto pszAction = udev_device_get_action(dev);
   action = udev_action_to_enum(pszAction);

   //calldata_init(&data);

   //calldata_set_string(&data, "device", node);

   try
   {

      switch (action)
      {
         case UDEV_ACTION_ADDED:
         {

            ::topic topic(id_video_input_device_added);

            auto psystem = ::acme::acme::g_pacme->m_pplatform->acmesystem();

            psystem->m_papexsystem->route(&topic, nullptr);

         }
            break;
         case UDEV_ACTION_REMOVED:
         {

            ::topic topic(id_video_input_device_removed);

            auto psystem = ::acme::acme::g_pacme->m_pplatform->acmesystem();

            psystem->m_papexsystem->route(&topic, nullptr);

         }
            break;
         default:
            break;
      }

   }
   catch(...)
   {


   }



//   calldata_free(&data);

   pthread_mutex_unlock(&udev_mutex);
}

///**
// * Event listener thread
// */
//static void *udev_event_thread(void *vptr)
//{
//   UNUSED_PARAMETER(vptr);
//
//
//   return NULL;
//}

namespace video_input_video_for_linux
{


//
//
//#if HAVE_UDEV
//   /**
// * Device added callback
// *
// * If everything went fine we can start capturing again when the device is
// * reconnected
// */
//static void device_added(void *vptr, calldata_t *calldata)
//{
//	V4L2_DATA(vptr);
//
//	obs_source_update_properties(m_pdevice->m_iSource);
//
//	const char *dev;
//	calldata_get_string(calldata, "device", &dev);
//
//	if (strcmp(data->device_id, dev))
//		return;
//
//	blog(LOG_INFO, "Device %s reconnected", dev);
//
//	v4l2_init(data);
//}
///**
// * Device removed callback
// *
// * We stop recording here so we don't block the device node
// */
//static void device_removed(void *vptr, calldata_t *calldata)
//{
//	V4L2_DATA(vptr);
//
//	obs_source_update_properties(m_pdevice->m_iSource);
//
//	const char *dev;
//	calldata_get_string(calldata, "device", &dev);
//
//	if (strcmp(data->device_id, dev))
//		return;
//
//	blog(LOG_INFO, "Device %s disconnected", dev);
//
//	v4l2_terminate(data);
//}
//
//#endif


   void video_input::v4l2_init_udev(void)
   {

      acmesystem()->m_papexsystem->add_handler(this);

      fork([]()
           {


              int fd;
              fd_set fds;
              struct timeval tv;
              struct udev *udev;
              struct udev_monitor *mon;
              struct udev_device *dev;

              /* set up udev monitoring */
              udev = udev_new();
              mon = udev_monitor_new_from_netlink(udev, "udev");
              udev_monitor_filter_add_match_subsystem_devtype(mon, "video4linux",
                                                              NULL);
              if (udev_monitor_enable_receiving(mon) < 0)
              {

                 //return NULL;

                 return;

              }

              /* set up fds */
              fd = udev_monitor_get_fd(mon);

              while (::task_get_run()) {
                 FD_ZERO(&fds);
                 FD_SET(fd, &fds);
                 tv.tv_sec = 1;
                 tv.tv_usec = 0;

                 if (select(fd + 1, &fds, NULL, NULL, &tv) <= 0)
                    continue;

                 dev = udev_monitor_receive_device(mon);
                 if (!dev)
                    continue;

                 udev_signal_event(dev);

                 udev_device_unref(dev);
              }

              udev_monitor_unref(mon);
              udev_unref(udev);


           });





//
//      pthread_mutex_lock(&udev_mutex);
//
//      /* set up udev */
//      if (udev_refs == 0)
//      {
//         if (os_event_init(&udev_event, OS_EVENT_TYPE_MANUAL) != 0)
//            goto fail;
//         if (pthread_create(&udev_thread, NULL, udev_event_thread,
//                            NULL) != 0)
//            goto fail;
//
//         udev_signalhandler = signal_handler_create();
//         if (!udev_signalhandler)
//            goto fail;
//         signal_handler_add_array(udev_signalhandler, udev_signals);
//      }
//      udev_refs++;
//
//      signal_handler_t *sh = v4l2_get_udev_signalhandler();
//
//      signal_handler_connect(sh, "device_added", &s_device_added, data);
//      signal_handler_connect(sh, "device_removed", &s_device_removed, data);
//
//
//   fail:
//      pthread_mutex_unlock(&udev_mutex);
   }

   void video_input::v4l2_unref_udev(void)
   {
      pthread_mutex_lock(&udev_mutex);

//      /* unref udev monitor */
//      if (udev_refs && --udev_refs == 0)
//      {
//         os_event_signal(udev_event);
//         pthread_join(udev_thread, NULL);
//         os_event_destroy(udev_event);
//
//         if (udev_signalhandler)
//            signal_handler_destroy(udev_signalhandler);
//         udev_signalhandler = NULL;
//      }

      pthread_mutex_unlock(&udev_mutex);
   }


}

//signal_handler_t *v4l2_get_udev_signalhandler(void)
//{
//   return udev_signalhandler;
//}


