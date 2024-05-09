#include "framework.h"

#include "base/update.h" 


#define DEBUG_REPEAT_OPEN 1
//#define DEBUG_REPEAT_OPEN 1

namespace mediaplay
{


   document::document()
   {

      m_pmediaplayview = nullptr;

      m_bWriting  = false;

   }


   document::~document()
   {

   }


   data * document::get_media_data()
   {

      return m_pmediaplaydata;

   }


   impact * document::get_media_impact()
   {

      return m_pmediaplayview;

   }


   ::pointer<::mediaplay::data>document::create_new_mediaplay_data()
   {

      return __allocate< ::mediaplay::data >();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         delete_contents();

      }

      ::pointer<::mediaplay::data>pdata;

      int iTest = DEBUG_REPEAT_OPEN;
auto tickStart = ::duration::now();

      for (::collection::index i = 0; i < iTest; i++)
      {

         if (pdata != nullptr)
         {

            try
            {

               pdata.release();

            }
            catch (...)
            {

            }

         }

         pdata = create_new_mediaplay_data();

         pdata->m_pdocument = this;

         if (!pdata->on_open_document(payloadFile))
         {

            return false;

         }

      }

      string str;

      if (iTest > 1)
      {
auto tickEnd = ::duration::now();

         double d = __double(tickEnd - tickStart) / (double)(iTest);

         str.formatf("%0.3f ms", d);

         message_box(str + string(" : Open ") + as_string(iTest) + " times");

      }

      m_pmediaplaydata = pdata;

      m_path = payloadFile.get_file_path();

      auto ptopic = new_action(id_after_open_document);

      update_all_impacts(ptopic);

      return true;

   }


   void document::delete_contents()
   {

      auto ptopic = new_action(id_delete_contents);

      update_all_impacts(ptopic);

      if (m_datamap.get_count() > 0)
      {

         try
         {

            m_pmediaplaydata->delete_contents();

         }
         catch(...)
         {

         }

         try
         {

            m_pmediaplaydata.release();

         }
         catch(...)
         {

         }

         try
         {

            m_datamap.erase_all();

         }
         catch (...)
         {

         }

      }

   }


} // namespace mediaplay



