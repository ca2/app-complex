#pragma once


#include "app-simple/form/_.h"
#include "core/_.h"


#ifdef _APP_COMPLEX_FORM_LIBRARY
#define CLASS_DECL_APP_COMPLEX_FORM  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_COMPLEX_FORM  CLASS_DECL_IMPORT
#endif


namespace user
{

   typedef ::user::show < ::user::button > button_impact;

} // namespace user


namespace app_complex_form
{

   class application;
   class main_impact;
   class document;
   class impact;
   class tab_impact;

} // namespace flag


