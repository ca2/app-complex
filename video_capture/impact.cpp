#include "framework.h"
#include "impact.h"
#include "application.h"
#include "pane_impact.h"
#include "acme/handler/topic.h"
#include "app-complex/video_input/render.h"
#include "app-complex/video_input/device.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"


namespace app_complex_video_capture
{


   impact::impact()
   {

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   impact::~impact()
   {

   }


   //void impact::assert_ok() const
   //{

   //   user::box::assert_ok();

   //}


   //void impact::dump(dump_context & dumpcontext) const
   //{

   //   user::box::dump(dumpcontext);

   //}


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create,pchannel,this,&impact::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &impact::on_message_destroy);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      //get_top_level()->add_fps_interest(this);

      add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen_fps);
      
   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

      if (m_prender)
      {

         m_prender->on_destroy();

         m_prender.release();

      }

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto rectangleX = this->rectangle();

      auto pvideoinputdevice = get_app()->m_pvideoinputdevice;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (!pvideoinputdevice)
      {

         pgraphics->set_font(this);

         pgraphics->set_text_color(::color::white);

         pgraphics->fill_inset_rectangle(rectangleX, argb(127, 0, 0, 0));

         pgraphics->text_out(10, 10, "No video input device selected.");

         return;

      }

      if (pvideoinputdevice->m_edevicestate == ::video_input::e_device_state_already_in_use_by_other_client)
      {

         pgraphics->set_font(this);

         pgraphics->set_text_color(::color::white);

         pgraphics->fill_inset_rectangle(rectangleX, argb(127, 0, 0, 0));

         pgraphics->text_out(10, 10, "Webcam is in use by other application.");

         return;

      }

      m_prender = pvideoinputdevice->get_render();

      synchronous_lock synchronouslock(m_prender->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_prender->prepare_image();

      ::image::image_source imagesource(m_prender->m_pimage);

      ::image::image_drawing_options imagedrawingoptions(rectangleX);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pgraphics->m_bUseImageMipMapsOrResizedImages = false;

      pgraphics->draw(imagedrawing);

   }


   void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->id() == id_initial_update)
      {

         ::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
         //if(ppaneimpact.is_set())
         //{
         //   ppaneimpact->m_pflagview = this;
         //}

      }
      __UNREFERENCED_PARAMETER(ptopic);
   }


   ::user::document * impact::get_document()
   {

      return  (::user::impact::get_document());

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_prender)
      {

         m_prender->on_layout(pgraphics);

      }

   }


   void impact::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {
      }

   }


   void impact::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {

   }



} // namespace app_complex_video_capture














