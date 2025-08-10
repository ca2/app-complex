#pragma once


namespace mediaplaylist
{


   class document;


} // namespace mediaplaylist


namespace mediaplay
{

   
   class document;


   class CLASS_DECL_APP_CORE_AUDIO data :
      virtual public ::data::data
   {
   public:


      enum e_mode
      {

         mode_none,
         mode_midi,
         mode_wave,

      };

      enum enum_type
      {

         type_unknown,
         type_aiff,
         type_cda,
         type_spotify_track,
         type_mpeg,
         type_twinvq,
         type_wm,
         type_wav,
         type_zip,
         type_rtp,
         type_midi,

      };

      ::memory_file              m_memfile;
      ::payload                        m_payloadFile;
      e_mode                     m_emode;
      enum_type                     m_etype;
      ::file::path               m_path;
      bool                       m_bWrite;
      bool                       m_bPlay;

      string                     m_strAsc;
      string                     m_strAscFormat;
      int                        m_iAscLineCount;
      string_array_base                    m_straFrame;
      ::int_array                  m_iaDelay;


      data();
      virtual ~data();

      
      virtual void initialize_data(::data::data_container_base * pdocument) override;


      virtual ::thread * HelperGetMidiPlayerCallbackThread();

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile);
      virtual void delete_contents();

      virtual bool on_open_zip_file(const ::string & lpszPathName);

      virtual bool is_writing();

      virtual string get_animated_title();

      virtual ::user::document * get_document();
      virtual ::file::path get_file_path();

      virtual e_mode calc_mode(enum_type enum_type);
      virtual enum_type get_type();
      virtual enum_type calc_file_type(::payload payloadFile);
      virtual e_mode get_mode();
      virtual bool open_file(const ::string & bstrFilePath, bool bMakeVisible);

      //virtual void on_http_request_response(::message::message * pmessage);


      virtual bool on_open_asciimedia_document(::payload & varFileAudio, ::payload payloadFile);
      virtual bool on_open_midi_document(::payload payloadFile);
      virtual bool on_after_open_wave_document();

      virtual bool on_initialize_wave_player(::wave::player * pplayer);


   };


} // namespace mediaplay

