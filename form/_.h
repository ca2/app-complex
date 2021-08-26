#pragma once


#include "aura/_.h"
#include "core/user/simple/_simple.h"


#ifdef _APP_SIMPLE_FORM_LIBRARY
#define CLASS_DECL_APP_SIMPLE_FORM  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SIMPLE_FORM  CLASS_DECL_IMPORT
#endif


namespace user
{

   typedef ::user::show < ::user::button > button_view;

} // namespace user


namespace simple_form
{

   class application;
   class main_impact;
   class document;
   class impact;
   class tab_view;

} // namespace flag


#undef APP_TYPE
#define APP_TYPE ::simple_form::application


#include "simple_form.h"
#include "simple_form_001.h"
#include "simple_form_002.h"


#include "document.h"
#include "impact.h"
#include "main_impact.h"
#include "frame.h"
#include "main_frame.h"

#include "tab_view.h"


#include "application.h"



