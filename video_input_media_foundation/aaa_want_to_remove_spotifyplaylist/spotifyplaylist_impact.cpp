#include "framework.h"



namespace mediaplaylist
{


   impact::impact(::particle * pparticle) :
      ::object(pparticle),
      user::place_holder_container(pparticle),
      user::split_layout(pparticle),
      user::split_impact(pparticle)
   {
      m_dataid = "impact";
   }

   impact::~impact()
   {
   }

   void impact::install_message_routing(::channel * pchannel)
   {
      ::user::split_impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
   }

#ifdef _DEBUG
   void impact::assert_ok() const
   {
      ::user::split_impact::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::split_impact::dump(dumpcontext);
   }
#endif //_DEBUG

   void impact::handle(::topic * ptopic, ::context * pcontext)
   {
      __UNREFERENCED_PARAMETER(pimpact);
      __UNREFERENCED_PARAMETER(eupdate);
      __UNREFERENCED_PARAMETER(pHint);
   }

   ::pointer<::mediaplaylist::document>impact::get_document()
   {
      return  (::user::impact::get_document());
   }

   void impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();


   }


   void impact::on_create_split_impact()
   {

      SetSplitOrientation(e_orientation_vertical);

      SetPaneCount(2);

      set_position_rate(0,0.33);

      m_splitbara[0]->m_dwMaxPosition = 284;

      initialize_split_layout();

      create_impact < mediaplaylist::playlist_list_impact >(get_document(),::rectangle(),get_pane_holder(0),"playlist_list_impact");

      create_impact < mediaplaylist::list_impact >(get_document(),::rectangle(),get_pane_holder(1),"list_impact");

   }



} // namespace mediaplaylist








