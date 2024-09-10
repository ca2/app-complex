#pragma once


namespace mediaplaylist
{


   class document;


   class CLASS_DECL_APP_CORE_AUDIO tree :
      virtual public ::data::tree
   {
   public:




      tree(::particle * pparticle);
      virtual ~tree();



      virtual void OnDraw(::image::image *pimage);

      void install_message_routing(::channel * pchannel) override;

      void _001OnOpenItem(::pointer<::data::tree_item>pdataitem, const ::action_context & action_context);

      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context);

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      void update_list();

      void create_tree(::pointer<::xml::node>pnode, ::pointer<::data::tree_item>itemParent = nullptr);

   };



} // namespace mediaplaylist
