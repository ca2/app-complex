#include "framework.h"

#include "aura/update.h"
#include "acme/constant/id.h"


namespace mediaplay
{


   data::data()
   {

      m_bWrite = false;

      m_emode = mode_none;

      m_bPlay = false;

   }

   data::~data()
   {
   }


   void data::initialize_data(::data::data_container_base * pdocument)
   {

      auto estatus = ::data::data::initialize_data(pdocument);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   bool data::on_new_document()
   {

      return true;

   }


   ::thread * data::HelperGetMidiPlayerCallbackThread()
   {

      return nullptr;

   }


   data::e_mode data::get_mode()
   {

      return m_emode;

   }


   data::enum_type data::get_type()
   {

      return m_etype;

   }


   bool data::on_open_asciimedia_document(::payload & varFileAudio, ::payload payloadFile)
   {

      ::file::path pathFile = payloadFile.get_file_path();

      string str = pcontext->m_papexcontext->file()->as_string(payloadFile);

      string_array stra;

      stra.add_lines(str);

      string strSong;

      strSong = stra[1];

      if (strSong.case_insensitive_begins_eat("./") || strSong.case_insensitive_begins_eat(".\\"))
      {

         ::file::path path;

         path = pathFile;

         strSong = path.folder() / strSong;

      }

      varFileAudio = strSong;

      string_array stra2;

      stra2.explode(":", stra[2]);

      if (stra2.get_count() > 0)
      {

         if (stra2[0] == "2")
         {

            m_strAscFormat = "2";

            if (stra2.get_count() >= 2)
            {

               m_iAscLineCount = atoi(stra2[1]);

            }
            else
            {

               m_iAscLineCount = 13;

            }

         }
         else
         {

            m_strAscFormat = "1";

         }

      }

      string strAsc;

      if (stra2.case_insensitive_contains("base64") && stra2.case_insensitive_contains("gz"))
      {

         auto pfileSource = create_memory_file();

         pbase64->decode(pfileSource->get_primitive_memory(), stra[3]);

         auto pfileTarget = create_memory_file();

         compress_context compress(this);

         compress.ungz(pfileTarget, pfileSource);

         strAsc = pfileTarget->to_string();

      }
      else if (stra2.case_insensitive_contains("base64"))
      {

         auto pfileSource = create_memory_file();

         pbase64->decode(pfileSource->get_primitive_memory(), stra[3]);

         strAsc = pfileSource->to_string();

      }
      else
      {

         strAsc = stra[3];

         strAsc.replace("\\n", "\n");

      }

      m_strAsc = strAsc;

      if (m_strAscFormat == "1")
      {

         avoid_parsing_exception avoidParsingException;

         auto pFind = m_strAsc.find('\"');

         if (::is_set(pFind))
         {

            const char * psz = &m_strAsc.c_str()[iFind];

            string strFrame;

            try
            {

               while ((strFrame = ::str::consume_c_quoted_value(psz)).has_char())
               {

                  strFrame.replace("\t", "\n");

                  m_straFrame.add(strFrame);

                  ::str::consume_spaces(psz);

               }

            }
            catch (...)
            {

            }

         }

      }
      else if (m_strAscFormat == "2")
      {

         string_array straLines;

         straLines.add_lines(m_strAsc);

         string strFrame;

         string strLine;

         int iDelay;

         for (index i = 0; i < straLines.get_size();)
         {

            strFrame.empty();

            strLine = straLines[i];

            iDelay = atoi(strLine);

            m_iaDelay.add(iDelay);

            i++;

            for (index j = 0; j < m_iAscLineCount - 1 && i < straLines.get_size(); j++)
            {

               strFrame += straLines[i];

               strFrame += "\n";

               i++;

            }

            m_straFrame.add(strFrame);

         }

      }

      return true;

   }


   bool data::on_open_document(const ::payload & varFileParam)
   {

      ::payload payloadFile(varFileParam);

      synchronous_lock synchronouslock(this->synchronization());

      enum_type enum_type = calc_file_type(payloadFile);

      if (enum_type == type_unknown)
      {

         return false;

      }

      if(enum_type == type_zip)
      {

         return on_open_zip_file(payloadFile);

      }

      if(payloadFile.get_file_path().case_insensitive_ends(".asciimedia"))
      {

         ::payload varFileAudio;

         if (!on_open_asciimedia_document(varFileAudio, payloadFile))
         {

            return false;

         }

         payloadFile = varFileAudio;

      }

      m_etype = enum_type;

      e_mode emode = calc_mode(enum_type);

      m_emode = emode;

      if(get_mode() == mode_wave)
      {

         auto pupdate = new_update();

         m_payloadFile = payloadFile;

         m_path = m_payloadFile.get_file_path();

         ptopic->m_atom = id_get_topic_wave_player;

         apply(ptopic);

         ::pointer<::wave::player>pwaveplayer = pupdate->m_pobjectTopic;

         if(pwaveplayer != nullptr)
         {

            on_initialize_wave_player(pwaveplayer);

            ::wave::player_command_pointer command(e_create);

            if(m_etype == data::type_rtp)
            {

               command->OpenRtpFile(pcontext->m_papexcontext->get_reader(payloadFile));

            }
            else
            {

               bool bSeekable = !(string_begins(m_path,"http://") || string_begins(m_path,"https://")
                                  || string_begins(m_path,"uifs://") || string_begins(m_path,"fs://")
                                  //|| payloadFile.cast < ::sockets::http_buffer >() != nullptr
                                  //|| payloadFile.propset()["file"].cast < ::sockets::http_buffer >() != nullptr
                                  || payloadFile.propset()["file"].cast < ::file::file >() != nullptr); // may be seekable through memory buffer but should also know the length before-hand

               command->OpenFile(pcontext->m_papexcontext->get_reader(payloadFile), bSeekable);

            }

            pwaveplayer->post_command(command);

         }

         on_after_open_wave_document();

         return true;

      }
      else if(get_mode() == mode_midi)
      {

         synchronouslock.unlock();

         return on_open_midi_document(payloadFile);

      }
      else
      {

         return false;

      }

   }


   bool data::on_open_midi_document(::payload payloadFile)
   {

      UNREFERENCED_PARAMETER(payloadFile);

      return false;

   }


   void data::delete_contents()
   {

      m_strAsc.empty();

      m_straFrame.erase_all();

      m_iaDelay.erase_all();

      m_strAscFormat.empty();

   }


   bool data::open_file(const ::string & bstrFilePath,bool bMakeVisible)
   {

      string str;

      str = bstrFilePath;

      ::pointer<::create>pcreate(this);

      pcreate->m_payloadFile = str;

      pcreate->m_bMakeVisible = bMakeVisible;

      psession->userex()->do_request(pcreate);

      return ::user::__document(pcreate);

   }


   data::enum_type data::calc_file_type(::payload payloadFile)
   {

      // quite simple by the time.

      ::file::path path = payloadFile.get_file_path();

      path.trim("\"'");

      string strServer;

      strServer = purl->get_server(path);

      if (::str::find_wwci("youtube.com", strServer) >= 0
            || ::str::find_wwci("youtu.be", strServer) >= 0)
      {

         return type_wav;

      }
      else if(path.case_insensitive_begins("rtp://") || path.case_insensitive_begins("rtprx://"))
      {

         return type_rtp;

      }
      else if(path.case_insensitive_ends(".cda"))
      {

         return type_cda;

      }
      else if (path.case_insensitive_begins("spotify_track:"))
      {

         return type_spotify_track;

      }
      else if (path.case_insensitive_begins("spotify:track:"))
      {

         return type_spotify_track;

      }
      else if(path.case_insensitive_ends(".mp3"))
      {

         return type_mpeg;

      }
      else if(path.case_insensitive_ends(".vqf"))
      {

         return type_twinvq;

      }
      else if(path.case_insensitive_ends(".wma"))
      {

         return type_wm;

      }
      else if (path.case_insensitive_ends(".m4a"))
      {

         return type_wm;

      }
      else if(path.case_insensitive_ends(".wav"))
      {

         return type_wav;

      }
      else if(path.case_insensitive_ends(".zip"))
      {

         return type_zip;

      }
      else if (path.case_insensitive_contains(".zip:"))
      {

         return type_zip;

      }
      else if (path.case_insensitive_ends(".mid"))
      {

         return type_midi;

      }
      else if (path.case_insensitive_ends(".kar"))
      {

         return type_midi;

      }
      else if (path.case_insensitive_ends(".mk1"))
      {

         return type_midi;

      }
      else if (path.case_insensitive_ends(".st3"))
      {

         return type_midi;

      }
      else if(path.case_insensitive_ends(".asciimedia"))
      {

         string str = pcontext->m_papexcontext->file()->as_string(path);

         string_array stra;

         stra.add_lines(str);

         if (stra.has_elements(2))
         {

            return calc_file_type(stra[1]);

         }

      }

      return type_unknown;

   }


   data::e_mode data::calc_mode(enum_type enum_type)
   {

      switch(enum_type)
      {
      case type_aiff:
      case type_cda:
      case type_mpeg:
      case type_twinvq:
      case type_wm:
      case type_wav:
      case type_rtp:
      case type_spotify_track:
         return mode_wave;
      case type_unknown:
      case type_midi:
         return mode_midi;
      default:
         break;
      }

      return mode_none;

   }


   ::file::path data::get_file_path()
   {

      return m_path;

   }


   ::user::document * data::get_document()
   {

      return dynamic_cast < ::user::document * > (m_pdocument.get());

   }


   string data::get_animated_title()
   {

      string_array stra;

      if(get_document()->get_title().has_char())
      {

         stra.add(get_document()->get_title());

      }

      return stra.implode(" - ");

   }


   bool data::is_writing()
   {

      return m_bWrite;

   }


   bool data::on_open_zip_file(const ::string & lpszPathName)
   {

      string wstrPathName(lpszPathName);
      string wstrZipPath;
      string wstrTitle;

      auto pFind = wstrPathName.find(".zip:");
      if(iFind > 0)
      {
         wstrZipPath = wstrPathName.left()(iFind + 4);
         wstrTitle = wstrPathName.substr(iFind + 5);
         wstrTitle.replace("\\","/");
      }
      else
      {
         wstrZipPath = wstrPathName;
      }

      string strPathName;

      strPathName = pcontext->m_papexcontext->dir()->time() / "mplite";

      if(!pcontext->m_papexcontext->dir()->is(strPathName))
      {

         if(pcontext->m_papexcontext->file()->exists(strPathName))
         {

            try
            {

               pcontext->m_papexcontext->file()->del(strPathName);

            }
            catch(...)
            {

               return false;

            }

         }

         if (!pcontext->m_papexcontext->dir()->create(strPathName))
         {

            return false;

         }

      }

      string strFileName;

      strFileName = pcontext->m_papexcontext->file()->time(strPathName,1);

      compress_context compress(this);

      if (!compress.unzip(strFileName, lpszPathName))
      {

         return false;

      }

      return on_open_document(strFileName);

   }



   bool data::on_after_open_wave_document()
   {

      return false;

   }


   bool data::on_initialize_wave_player(::wave::player * pplayer)
   {

      UNREFERENCED_PARAMETER(pplayer);

      return false;

   }

   /*bool data::open_document_no_reserve(const ::string & pszFilePath)
   {

   UNREFERENCED_PARAMETER(pszFilePath);

   return false;

   }*/


} // namespace mediaplay



