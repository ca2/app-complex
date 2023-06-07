#include "framework.h"
#include "form.h"
#include "acme/constant/message.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/platform/context.h"
#include "base/user/user/user.h"


namespace app_complex_form
{


   form::form()
   {



   }


   form::~form()
   {

   }


#ifdef _DEBUG


   int64_t form::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t form::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void form::install_message_routing(::channel * psender)
   {

      ::user::form_impact::install_message_routing(psender);

      MESSAGE_LINK(MESSAGE_CREATE, psender, this, &form::on_message_create);
      MESSAGE_LINK(e_message_context_menu, psender, this, &form::on_message_context_menu);

   }


   void form::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      pgraphics->fill_rectangle(rectangleClient, argb(127, 245, 250, 255));

   }


   void form::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

   }


   void form::on_message_context_menu(::message::message * pmessage)
   {

      auto pcontextmenu = pmessage->m_union.m_pcontextmenu;

      auto point = pcontextmenu->GetPoint();

      auto puser = user()->m_pbaseuser;

      auto strXml = context()->file()->as_string("matter://form/form.menu");

      puser->track_popup_xml_menu(this, strXml, 0, point);

   }


   void form::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_impact::on_layout(pgraphics);

   }


} // namespace app_complex_form



