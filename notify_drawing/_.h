#pragma once


#include "app-simple/drawing/_.h"


#ifdef _APP_SIMPLE_NOTIFY_DRAWING_LIBRARY
#define CLASS_DECL_APP_SIMPLE_NOTIFY_DRAWING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SIMPLE_NOTIFY_DRAWING  CLASS_DECL_IMPORT
#endif



namespace notify_drawing
{

   class application;
   class impact;

} // namespace flag


#include "application.h"



