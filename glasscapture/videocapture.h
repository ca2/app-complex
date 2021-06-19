#pragma once


#include "aura/_.h"
#include "aura/filesystem/filemanager/filemanager.h"
#include "aura/user/user/user.h"
#include "aura/user/html/html/html.h"
#include "app-core/gcom/gcom/gcom.h"


#ifdef _APP_CORE_VIDEOCAPTURE_LIBRARY
   #define CLASS_DECL_APP_CORE_VIDEOCAPTURE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APP_CORE_VIDEOCAPTURE  CLASS_DECL_IMPORT
#endif

//bool mf_startup();



namespace user
{

   typedef ::user::show < ::user::button > button_view;

} // namespace user


namespace videocapture
{

   class application;
   class top_view;
   class main_view;
   class document;
   class view;
   class font_view;

} // namespace flag


#undef APP_TYPE
#define APP_TYPE ::videocapture::application


int video_capture_enum_encoders(string_array & straName, string_array & straPath);

#include "user_font_list.h"

#include "videocapture_render.h"

#include "videocapture_document.h"
#include "videocapture_font_view.h"
#include "videocapture_edit_view.h"
#include "videocapture_toggle_view.h"
#include "videocapture_top_view.h"
#include "videocapture_view_base.h"
#include "videocapture_gcom.h"
#include "videocapture_view.h"
//#include "videocapture_lite_view.h"
//#include "videocapture_full_view.h"
#include "videocapture_main_view.h"
#include "videocapture_switcher_view.h"
#include "videocapture_frame.h"
#include "videocapture_main_frame.h"

#include "videocapture_pane_view.h"

#include "videocapture_application.h"

