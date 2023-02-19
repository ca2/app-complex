#pragma once


#include "core/_.h"
//#include "core/user/userex/_userex.h"


#if defined(_app_simple_box_project)
#define CLASS_DECL_APP_SIMPLE_BOX  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SIMPLE_BOX  CLASS_DECL_IMPORT
#endif


namespace user
{

   class button;

   typedef ::user::show < ::user::button > button_impact;

} // namespace user


namespace simple_message_box
{

   class application;

} // namespace simple_message_box


#include "application.h"



