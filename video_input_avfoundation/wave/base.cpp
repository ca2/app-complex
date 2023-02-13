#include "framework.h"



namespace wave
{



   base::base( )
   {

   }


   base::~base()
   {

   }


   void base::init_thread()
   {

      if (!::thread::init_thread())
      {

         return false;

      }

      set_thread_priority(::e_priority_highest);

      return true;

   }


   void base::allocate_buffer_data(::wave::buffer::item * pbuffer, memsize uiBufferSize, memsize uiAlign)
   {

      pbuffer->m_mem.set_size(uiBufferSize+uiAlign);

      auto iOffset = ((uptr)pbuffer->m_mem.get_data()) % uiAlign;

      if(iOffset == 0)
      {

         pbuffer->m_pData = pbuffer->m_mem.get_data();

      }
      else
      {

         pbuffer->m_pData = pbuffer->m_mem.get_data() + uiAlign - iOffset;

      }

   }


   void base::free_buffer_data(            ::wave::buffer::item * pbuffer)
   {

   }


} // namespace wave


