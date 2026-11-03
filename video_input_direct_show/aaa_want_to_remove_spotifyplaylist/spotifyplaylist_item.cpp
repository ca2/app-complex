#include "framework.h"



namespace mediaplaylist
{


   item::item(tree * ptree)
   {
      
      m_ptree = ptree;

   }


   string item::get_item_text(object * pparticle)
   {
      __UNREFERENCED_PARAMETER(pparticle);
      return m_strName;
   }

   ::collection::index item::get_item_image(object * pparticle)
   {

      //if(m_ptree->is_selected(this))
      //{

      //   return -1;

      //}
      //else
      //{

      //   return -1;

      //}

      return -1;

   }



} // namespace mediaplaylist
