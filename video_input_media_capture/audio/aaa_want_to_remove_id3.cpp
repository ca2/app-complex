#include "framework.h"

#define ID3LIB_LINKOPTION 3
#include "id3.h"


CLASS_DECL_AURA strsize unichar_len(const unichar * psz);


int id3_cp(ID3_TextEnc enc)
{

   if (enc == ID3TE_ISO8859_1)
   {

      return 28591;

   }
   else if (enc == ID3TE_UTF16)
   {

      return 1200;

   }
   else if (enc == ID3TE_UTF16BE)
   {

      return 1201;

   }
   else if (enc == ID3TE_UTF8)
   {

      return 65001;

   }
   else
   {

      return -1;

   }



}

string id3_field_text(ID3_Field * pfield)
{

   int iEnc = id3_cp(pfield->GetEncoding());

   if (iEnc == -1)
   {

      if (pfield->GetRawText() != nullptr)
      {

         return pfield->GetRawText();

      }

      return (const wchar_t *)pfield->GetRawUnicodeText();

   }
   else if (iEnc == 28591)
   {

      return multibyte_to_unicode(iEnc, pfield->GetRawText());

   }
   else if (iEnc == 1200)
   {

      string str;

      memory mem;

      int iCharCount = (int) unichar_len((const unichar *)pfield->GetRawUnicodeText());

      int iLenBytes = (iCharCount + 1) * 2;

      mem.set_size(iLenBytes);

      ::memory_copy(mem.get_data(), pfield->GetRawUnicodeText(), iLenBytes);

      unichar * pwsz = (unichar * )mem.get_data();

      while (*pwsz != L'\0')
      {

         ::u8 * psz = (::u8 *)pwsz;

         ::u8 ch0 = psz[0];

         psz[0] = psz[1];

         psz[1] = ch0;

         pwsz++;

      }

      pwsz = (unichar * )mem.get_data();

      str = pwsz;

      return str;

   }
   else
   {

      return multibyte_to_unicode(iEnc, (const ::string &)pfield->GetRawUnicodeText());

   }


}


string id3_frame_text(ID3_Frame * pframe)
{

   string str = id3_field_text(pframe->GetField(ID3FN_TEXTENC));

   if (str.has_char())
   {

      return str;

   }

   str = id3_field_text(pframe->GetField(ID3FN_TEXT));

   return str;

}



CLASS_DECL_APP_CORE_MULTIMEDIA property_set id3_set(file_pointer pfile)
{

   property_set set;

   return set;

/*
   array < flags_t > flaga;

   flaga.add(ID3TT_ID3V2);
   flaga.add(ID3TT_ID3V1);
   flaga.add(ID3TT_MUSICMATCH);
   flaga.add(ID3TT_LYRICS3);
   flaga.add(ID3TT_LYRICS3V2);

   for (auto & flag : flaga)
   {

      std::istream is(pfile.m_p);

      ID3_IStreamReader rd(*is.m_pfile);

      ID3_Tag                             id3tag;

      //id3tag.Clear();

      id3tag.Link(rd, (flags_t)flag, false); // parse only in the begginning of file

      ID3_Frame * pframe;

      if (set["name"].is_empty())
      {

         if ((pframe = id3tag.Find(ID3FID_TITLE)))
         {

            set["name"] = id3_frame_text(pframe);

         }

      }

      if (set["album"].is_empty())
      {

         if ((pframe = id3tag.Find(ID3FID_ALBUM)))
         {

            set["album"] = id3_frame_text(pframe);

         }

      }

      if (set["artist"].is_empty())
      {

         if ((pframe = id3tag.Find(ID3FID_LEADARTIST)))
         {

            set["artista"].stra().add(id3_frame_text(pframe));

            set["artist"] = set["artista"].stra().implode(", ");

         }

      }

      if (set["year"].is_empty())
      {

         if ((pframe = id3tag.Find(ID3FID_YEAR)))
         {

            set["year"] = id3_frame_text(pframe);

         }

      }

      if (set["composer"].is_empty())
      {

         if ((pframe = id3tag.Find(ID3FID_COMPOSER)))
         {

            set["composer"] = id3_frame_text(pframe);

         }

      }

      if (!set["name"].is_empty()
            && !set["album"].is_empty()
            && !set["artist"].is_empty()
            && !set["year"].is_empty()
            && !set["composer"].is_empty())
      {

         break;

      }

   }

   return set;*/

}
