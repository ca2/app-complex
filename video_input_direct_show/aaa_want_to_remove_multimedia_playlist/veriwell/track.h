#pragma once


namespace multimedia_playlist
{


   namespace veriwell
   {


      class CLASS_DECL_APP_CORE_AUDIO track:
         virtual public ::multimedia_playlist::track
      {
      public:

         ::file::path               m_path;
         //sp_track *              m_tr;


         //playlist *              m_pl;
         //int                     m_iIndex;
         //string                  m_strName;
         ////::duration m_durationLastUpdate;
         //bool                    m_bNew;
         //string_array_base                 m_straArtist;
         //string                  m_strArtist;
         string                  m_strAlbumArt;


         track();
         virtual ~track();


         virtual void initialize_multimedia_playlist_veriwell_track(session * psession);


         virtual string   get_name() override;
         virtual string   get_artist() override;
         virtual string   get_id() override;
         virtual string   get_album() override;

         virtual void on_update() override;
         virtual bool update() override;

         virtual bool load(::payload payloadFile) override;

         virtual string get_path() override;

      };

   } // namespace namespace veriwell

} // namespace multimedia_playlist


