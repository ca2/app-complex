#include "framework.h"



namespace mediaplaylist
{


   item::item(tree * ptree)
   {
      
      m_ptree = ptree;

   }


   string item::data_item_get_text(object * pparticle)
   {
      __UNREFERENCED_PARAMETER(pparticle);
      return m_strName;
   }

   index item::data_item_get_image(object * pparticle)
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
