#pragma once


#include "core/_.h"



#if defined(_app_simple_application_project)
#define CLASS_DECL_APP_SIMPLE_APPLICATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SIMPLE_APPLICATION  CLASS_DECL_IMPORT
#endif


namespace simple_application
{

   class application;
   class pane_impact;
   class document;
   class impact;

} // namespace flag


#include "application.h"



