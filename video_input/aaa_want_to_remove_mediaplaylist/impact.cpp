#include "framework.h"



namespace mediaplaylist
{


   impact::impact() :
      m_pfont(e_create)
   {

      m_pfont->create_point_font("Arial Black", 36, 800);

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
   }

#ifdef _DEBUG
   void impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //_DEBUG


   void impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      __UNREFERENCED_PARAMETER(ptopic);

   }


   ::mediaplaylist::document * impact::get_document()
   {

      return dynamic_cast < ::mediaplaylist::document * > (::user::impact::get_document());

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();


   }

   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);

      pgraphics->fill_rectangle(rectangleX, _001GetColor(::user::color_impact_background));

      pgraphics->selectFont(m_pfont);

      pgraphics->set_text_color(argb(255, 0, 0, 0));

      if(get_document() != nullptr && get_document()->impact_playlist() != nullptr)
      {

         pgraphics->text_out(5, 5, get_document()->impact_playlist()->get_title());

      }

   }

} // namespace mediaplaylist








