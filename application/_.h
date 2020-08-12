#pragma once


#include "core/_.h"



#ifdef _APP_SIMPLE_APPLICATION_LIBRARY
#define CLASS_DECL_APP_SIMPLE_APPLICATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SIMPLE_APPLICATION  CLASS_DECL_IMPORT
#endif


namespace simple_application
{

   class application;
   class pane_view;
   class document;
   class view;

} // namespace flag


#include "application.h"



