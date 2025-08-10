#pragma once


namespace multimedia_playlist
{


   namespace veriwell
   {

      
      class xml_playlist;


      class CLASS_DECL_APP_CORE_AUDIO playlist :
         virtual public ::multimedia_playlist::playlist
      {
      public:


         xml_playlist      *        m_pxmlplaylist;


         playlist();
         virtual ~playlist();


         virtual void initialize_multimedia_playlist_veriwell_playlist(session * psession);


         virtual string get_name() override;

         virtual string_array_base get_stra() override;

         virtual void on_update() override;

         virtual void on_update_tracks() override;

         virtual bool update() override;

         //virtual bool update_tracks();

         //virtual void on_tracks_erased(const int * tracks, int num_tracks);

         virtual bool save() override;

         virtual bool load(string strFile) override;

         virtual string add_song(::payload payloadFile, bool bAddDuplicate) override;
         virtual bool erase_song(::collection::index iSong, bool bUpdateSongs = true) override;
         virtual void ensure_playlist() override;

         virtual ::collection::count get_count() override;


         virtual bool is_recursive() override;
         virtual bool is_loop() override;
         virtual bool is_shuffle() override;

         virtual void set_flag(const ::scoped_string & scopedstr, bool bFlag);
         virtual bool get_flag(const ::scoped_string & scopedstr, bool bDefault);
         virtual void set_int(const ::scoped_string & scopedstr, long long iValue) override;
         virtual long long get_int(const ::scoped_string & scopedstr, long long iDefault) override;
         virtual void set_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrValue) override;
         virtual string get_string(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrValue) override;

         veriwell::session * session();


      };

   } // namespace namespace veriwell

} // namespace multimedia_playlist





