#pragma once


#include "acme/platform/department.h"


namespace video_input
{


   class CLASS_DECL_VIDEO_INPUT department :
      virtual public ::platform::department
   {

   public:


      department();
      ~department() override;


      void initialize(::particle * pparticle) override;


   };


} // namespace department



