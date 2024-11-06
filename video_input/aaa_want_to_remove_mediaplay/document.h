#pragma once


namespace mediaplay
{


   class data;
   class impact;


   class CLASS_DECL_APP_CORE_AUDIO document :
      virtual public ::user::document
   {
   public:


      ::pointer<data>      m_pmediaplaydata;
      impact *         m_pmediaplayview;
      bool           m_bWriting;


      document();
      virtual ~document();


      virtual huge_integer increment_reference_count()
      {

         return ::object::increment_reference_count();

      }

      virtual huge_integer decrement_reference_count()
      {

         return ::object::decrement_reference_count();

      }

      data *         get_media_data();
      impact *         get_media_impact();

      bool on_open_document(const ::payload & payloadFile) override;
      virtual void delete_contents(); // delete doc items etc

      virtual ::pointer<::mediaplay::data>create_new_mediaplay_data();


   };


} // namespace mediaplay



