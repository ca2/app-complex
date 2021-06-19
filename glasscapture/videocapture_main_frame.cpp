#include "framework.h"


namespace videocapture
{


   main_frame::main_frame(::object * pobject) :
      object(pobject),
      simple_frame_window(pobject)
   {


      window_enable_full_screen();

      m_bWindowFrame = !papplication->has_property("client_only");



      if (papplication->has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucency = ::user::e_translucency_none;

      }
      else
      {

         m_bExplicitTranslucency = false;

      }



   }


   main_frame::~main_frame()
   {

   }

   void main_frame::install_message_routing(::channel * pchannel)
   {

      simple_frame_window::install_message_routing(pchannel);

      MESSAGE_LINK(WM_APP + 975, pchannel, this, &main_frame::_001OnCaptureEvent);

   }

   void main_frame::_001OnCaptureEvent(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      if (m_pview != nullptr)
      {

         m_pview->OnCaptureEvent(pusermessage->m_wparam, pusermessage->m_lparam);

      }

   }


   void main_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   ::experience::frame * main_frame::experience_get_frame()
   {

      //__pointer(::user::experience::main_frame::main_frame) pschema = papplication->experience()->experience_get_frame("experience_lite", "001");

      auto pframe = papplication->experience()->experience_get_frame(nullptr, "013");

      pframe->set_style("LightBlue");

      HWND hwnd = get_handle();

      //       // pschema->m_typeControlBoxButton = __type(MetaButton);

      return pframe;

   }

   bool main_frame::has_pending_graphical_update()
   {

      return true;

   }


   ::user::enum_translucency main_frame::get_translucency(::user::style * pstyle) const
   {

      if (m_bExplicitTranslucency)
      {

         etranslucency = m_etranslucency;

         return true;

      }

      if (m_puserstyle != nullptr)
      {

         if (m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
            return true;

      }
      etranslucency = ::user::e_translucency_present;

      //      etranslucency = ::user::e_translucency_none;

      return true;

   }


} // namespace videocapture







