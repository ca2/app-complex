#pragma once


#include "aura/_.h"
#include "aura/user/user/user.h"
#include "aura/user/simple/simple.h"
#include "core/user/userex/userex.h"


#ifdef _APP_SIMPLE_HELLOWORLD_LIBRARY
    #define CLASS_DECL_APP_SIMPLE_HELLOWORLD  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_APP_SIMPLE_HELLOWORLD  CLASS_DECL_IMPORT
#endif


#define HI_LOGIN 1
#define HI_SHUTDOWN_JUST_AFTER_FIRST_MAIN_TASK 0


namespace helloworld
{

   class application;

} // namespace flag


#define APP_TYPE ::helloworld::application


#include "helloworld_document.h"
#include "helloworld_view.h"
#include "helloworld_frame.h"


#include "helloworld_application.h"

