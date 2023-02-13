#include "framework.h"



namespace mediaplaylist
{


   main_impact::main_impact()
   {

   }


   main_impact::~main_impact()
   {

   }


   void main_impact::install_message_routing(::channel * pchannel)
   {
      ::user::split_impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &main_impact::on_message_create);
   }

#ifdef _DEBUG
   void main_impact::assert_ok() const
   {
      ::user::split_impact::assert_ok();
   }

   void main_impact::dump(dump_context & dumpcontext) const
   {
      ::user::split_impact::dump(dumpcontext);
   }
#endif //_DEBUG


   void main_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(ptopic);

   }


   ::mediaplaylist::document * main_impact::get_document()
   {

      return dynamic_cast < ::mediaplaylist::document * > (::user::impact::get_document());

   }


   void main_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();


   }


   void main_impact::on_create_split_impact()
   {

      SetSplitOrientation(e_orientation_horizontal);

      SetPaneCount(2);

      set_position(0, 25);

      m_panea[0]->m_bFixedSize = true;

      initialize_split_layout();

      create_impact < mediaplaylist::edit_impact >(get_document(), get_pane_holder(0), "edit_impact");

      create_impact < mediaplaylist::body_impact >(get_document(), get_pane_holder(1), "body_impact");

   }


   body_impact::body_impact()
   {

   }


   body_impact::~body_impact()
   {

   }


   void body_impact::install_message_routing(::channel * pchannel)
   {
      ::user::split_impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &body_impact::on_message_create);
   }

#ifdef _DEBUG
   void body_impact::assert_ok() const
   {
      ::user::split_impact::assert_ok();
   }

   void body_impact::dump(dump_context & dumpcontext) const
   {
      ::user::split_impact::dump(dumpcontext);
   }
#endif //_DEBUG


   void body_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(ptopic);

   }


   ::mediaplaylist::document * body_impact::get_document()
   {

      return dynamic_cast < ::mediaplaylist::document * > (::user::impact::get_document());

   }


   void body_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();


   }


   void body_impact::on_create_split_impact()
   {

      SetSplitOrientation(e_orientation_vertical);

      SetPaneCount(2);

      set_position_rate(0, 0.33);

      m_splitbara[0]->m_dwMaxPosition = 284;

      initialize_split_layout();

      create_impact < mediaplaylist::playlist_list_impact >(get_document(), get_pane_holder(0), "playlist_list_main_impact");

      create_impact < mediaplaylist::right_impact >(get_document(), get_pane_holder(1), "list_main_impact");

   }


   right_impact::right_impact()
   {

   }


   right_impact::~right_impact()
   {

   }


   void right_impact::install_message_routing(::channel * pchannel)
   {
      ::user::split_impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &right_impact::on_message_create);
   }

#ifdef _DEBUG
   void right_impact::assert_ok() const
   {
      ::user::split_impact::assert_ok();
   }

   void right_impact::dump(dump_context & dumpcontext) const
   {
      ::user::split_impact::dump(dumpcontext);
   }
#endif //_DEBUG


   void right_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(ptopic);

   }


   ::mediaplaylist::document * right_impact::get_document()
   {

      return dynamic_cast < ::mediaplaylist::document * > (::user::impact::get_document());

   }


   void right_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();


   }


   void right_impact::on_create_split_impact()
   {

      SetSplitOrientation(e_orientation_horizontal);

      SetPaneCount(2);

      set_position(0, 90);

      m_panea[0]->m_bFixedSize = true;

      m_splitbara[0]->m_dwMaxPosition = 284;

      initialize_split_layout();

      create_impact < mediaplaylist::impact >(get_document(), get_pane_holder(0), "playlist_list_right_impact");

      create_impact < mediaplaylist::list_impact >(get_document(), get_pane_holder(1), "list_right_impact");

   }



} // namespace mediaplaylist










