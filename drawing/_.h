#pragma once


#include "app-simple/drawing/_.h"


#ifdef _APP_COMPLEX_DRAWING_LIBRARY
#define CLASS_DECL_APP_COMPLEX_DRAWING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_COMPLEX_DRAWING  CLASS_DECL_IMPORT
#endif


namespace complex_drawing
{

   
   class application;
   class pane_view;


} // namespace flag





#include "application.h"



