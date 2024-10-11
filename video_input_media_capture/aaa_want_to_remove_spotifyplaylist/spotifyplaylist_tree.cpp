#include "framework.h"



namespace mediaplaylist
{


   tree::tree(::particle * pparticle) :
      ::object(pparticle),
      ::data::data(pparticle),
      ::data::tree(pparticle)
   {


   }

   tree::~tree()
   {
   }


   void tree::OnDraw(::image::image *pimage)
   {
      __UNREFERENCED_PARAMETER(pgraphics);
   }


   void tree::install_message_routing(::channel * pchannel)
   {

   }


   void tree::_001OnOpenItem(::pointer<::data::tree_item>pitem, const ::action_context & context)
   {
      __UNREFERENCED_PARAMETER(pitem);
      /*::pointer<::mediaplaylist::tree_item>pitemdata = (::pointer<::mediaplaylist::tree_item>pitem->m_pitemdata;
      if(papp->mediaplaylist::application::m_pmaillist == nullptr)
      {
      create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeatomNewImpact = ::type < right_impact >();
      create_impact(::type < right_impact >(), get_document(), get_parent(), 101);
      }
      if(papp->mediaplaylist::application::m_pmaillist == nullptr)
      return;
      ::cubesp(::mediaplaylist::document) pdocument = dynamic_cast < ::cubesp(::mediaplaylist::document) > (get_document());
      if(pdocument != nullptr && pdocument->m_pholderMailList != nullptr)
      {
      if(pdocument->m_pholderMailList->m_uiptraHold.get_size() > 0)
      {
      pdocument->m_pholderMailList->m_uiptraHold[0]->show_window(SW_HIDE);
      }
      pdocument->m_pholderMailList->hold(papp->mediaplaylist::application::m_prightview);
      pdocument->m_pholderMailList->on_layout(pgraphics);
      }
      else if(papp->mediaplaylist::application::m_pmainimpact == nullptr)
      {
      papp->hold(papp->mediaplaylist::application::m_prightview);
      }
      else
      {
      papp->mediaplaylist::application::m_pmainimpact->get_pane_window(1)->show_window(SW_HIDE);
      papp->mediaplaylist::application::m_pmainimpact->SetPane(1, papp->mediaplaylist::application::m_prightview, false);
      papp->mediaplaylist::application::m_pmainimpact->on_layout(pgraphics);
      }

      pitemdata->m_paccount->m_pop3.start();

      get_document()->set_account(pitemdata->m_paccount);

      papp->mediaplaylist::application::m_pmaillist->open_folder(pitemdata->m_strFolder);*/
   }

   void tree::_001OnItemExpand(::data::tree_item * pdataitem, const ::action_context & context)
   {
      __UNREFERENCED_PARAMETER(pdataitem);
      /*::pointer<::mediaplaylist::tree_item>pitem = (::pointer<::mediaplaylist::tree_item>pdataitem;

      if(pitem->m_iIdentation == 0)
      {
      papp->mediaplaylist::application::m_pmainimpact->get_pane_window(1)->show_window(SW_HIDE);
      papp->mediaplaylist::application::m_pmainimpact->SetPane(1, papp->mediaplaylist::application::m_prightpaneimpact, false);
      papp->mediaplaylist::application::m_pmainimpact->on_layout(pgraphics);
      }*/

   }


   void tree::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(pimpact);
      __UNREFERENCED_PARAMETER(eupdate);
      __UNREFERENCED_PARAMETER(pHint);

//      ::data::lock lock(m_spdata);

      ::pointer<::mediaplaylist::document>pdocument = pSender->get_document();

      if (pdocument.is_set())
      {

         create_tree(&pdocument->m_xmldoc);

      }

   }



   void tree::update_list()
   {
   }


   void tree::create_tree(::pointer<::xml::node>pnode, ::pointer<::data::tree_item>itemParent)
   {

      get_base_item()->erase_tree_item_descendants();

      if (pitemParent == nullptr)
         pitemParent = get_base_item();

      ::collection::index iStart = 0;
      ::pointer<::xml::node>pnodeChild;

      while ((pnodeChild = pnode->get_child("playlist", iStart)) != nullptr)
      {
         ::pointer<::mediaplaylist::item>pitem = __new ::mediaplaylist::item(this);
         pnodeChild->get_attr("name", pitem->m_strName);
         ::pointer<::data::tree_item>pitemNew = insert_item(pitem, ::data::e_relative_last_child, pitemParent);
         create_tree(pnodeChild, pitemNew);
         iStart++;
      }

   }


} // namespace mediaplaylist
