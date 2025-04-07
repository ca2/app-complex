// Created on 2021-07-07 by camilo 14:11 BRT <3ThomasBorregaardSorensen!!
#pragma once


//#include <mfcaptureengine.h>
#include "app-complex/video_input/render.h"


namespace video_input_video_for_linux
{


   class CLASS_DECL_VIDEO_INPUT_MEDIA_FOUNDATION render :
      virtual public ::video_input::render
   {
   public:


      ::pointer<device>         m_pdevice;



      render();
      ~render() override;


      void initialize_video_input_render(::video_input::device * pdevice) override;

      // void assert_ok() const override;
      //void dump(dump_context& dumpcontext) const;

#ifdef _DEBUG

      long long increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }

      long long decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }

#endif


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      void on_create()override;
      void destroy() override;

   };


} // namespace video_capture



