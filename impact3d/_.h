#pragma once


#include "core/_.h"


#ifdef _APP_COMPLEX_IMPACT3D_LIBRARY
#define CLASS_DECL_APP_COMPLEX_IMPACT3D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_COMPLEX_IMPACT3D  CLASS_DECL_IMPORT
#endif


namespace app_complex_impact3d
{

   class application;
   class pane_impact;
   class document;
   class impact;
   class render;

} // namespace app_complex_impact3d


namespace opengl
{


   class opengl;
   class shader;
   class buffer;
   class program;
   


} // namespace opengl


#include "aura/gpu/gpu/_.h"

#include "gpu_opengl/_.h"


