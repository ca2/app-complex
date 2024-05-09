#pragma once


namespace mediaplaylist
{


   class tree;


   class CLASS_DECL_APP_CORE_AUDIO item :
      virtual public ::data::item
   {
   public:
      
      
      tree *            m_ptree;
      string            m_strName;
      i32           m_iIdentation;


      item(tree * ptree);


      string data_item_get_text(object * pparticle);
      ::collection::index data_item_get_image(object * pparticle);



   };


} // namespace mediaplaylist



