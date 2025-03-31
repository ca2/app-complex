#pragma once


namespace mediaplaylist
{


   class tree;


   class CLASS_DECL_APP_CORE_AUDIO item :
      virtual public ::item
   {
   public:
      
      
      tree *            m_ptree;
      string            m_strName;
      int           m_iIdentation;


      item(tree * ptree);


      string get_item_text(object * pparticle);
      ::collection::index get_item_image(object * pparticle);



   };


} // namespace mediaplaylist



