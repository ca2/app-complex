#include "framework.h"



namespace multimedia_playlist
{


   namespace veriwell
   {

      web_api::web_api()
      {

         m_iExpires = 0;


         m_strAccessToken = pcontext->m_papexcontext->file()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\access_token.txt");
         m_strTokenType = pcontext->m_papexcontext->file()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\token_type.txt");
         m_iExpires = atoi(pcontext->m_papexcontext->file()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\expire_in.txt"));
         m_strRefreshToken = pcontext->m_papexcontext->file()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\refresh_token.txt");
         m_timeAuth.m_time = ansi_to_i64(pcontext->m_papexcontext->file()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\time_auth.txt"));

      }


      web_api::~web_api()
      {


      }


      bool web_api::auth(bool bForce)
      {

         ::earth::time tNow = ::earth::time::now();

         if (!bForce && m_strAccessToken.has_char() && (tNow - m_timeAuth).GetTotalSeconds() < (60 * 5))
            return true;

         string strClientId = acmefile()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\spotify\\client_id.txt");

         string strState;

         string strUrl;

         for (int i = 0; i < 8; i++)
         {

            property_set set;

            set["raw_http"] = true;

            strUrl = "https://api.ca2software.com/account/spotify_register";

            strState = pcontext->m_papexcontext->http().get(strUrl, set);

            if (strState.has_char())
               break;

         }

         if (strState.is_empty())
         {

            return false;

         }

         string strRedirectUri = "https://ca2software.com/spotify_redirect";

         //string strScope = "user-read-private user-read-email";

         string strScope;

         strUrl = "https://accounts.spotify.com/authorize?client_id=" + strClientId + "&response_type=code&state=" + strState + "&redirect_uri="
            + purl->url_encode(strRedirectUri) + ::str::has_char(strScope, "&scope=") + "&show_dialog=false";

         psystem->hyperlink().open_link(strUrl, "", "spotify");

         string strResponse;

         int i = 0;

         while (i < 84)
         {

            {

               property_set set;

               set["raw_http"] = true;

               strUrl = "https://api.ca2software.com/account/spotify_response?state=" + strState;

               strResponse = pcontext->m_papexcontext->http().get(strUrl, set);

            }

            if (strResponse.has_char())
               break;

            sleep(2000_ms);
            i++;
         }

         if (!strResponse.begins_eat("code="))
         {

            return false;

         }

         string strCode = strResponse;

         {

            property_set set;

            set["raw_http"] = true;

            set["post"]["grant_type"] = "authorization_code";
            set["post"]["code"] = strCode;
            set["post"]["redirect_uri"] = strRedirectUri;

            string strClientSecret = acmefile()->as_string(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\spotify\\client_secret.txt");

            set["headers"]["Authorization"] = "Basic " + pbase64->encode(strClientId + ":" + strClientSecret);

            strUrl = "https://accounts.spotify.com/api/token";

            strResponse = pcontext->m_papexcontext->http().get(strUrl, set);

         }

         string strAccessToken;
         string strTokenType;
         string strRefreshToken;

         {

            property_set network_payload;

            const char * pszResponse = strResponse;

            network_payload.parse_network_payload(pszResponse);

            m_strAccessToken = network_payload["access_token"];
            m_strTokenType = network_payload["token_type"];
            m_iExpires = network_payload["expires_in"];
            m_strRefreshToken = network_payload["refresh_token"];

         }

         if (m_strAccessToken.is_empty())
         {

            return false;

         }

         if (m_strTokenType.is_empty())
         {

            return false;

         }

         if (m_iExpires <= 0)
         {

            return false;

         }

         if (m_strRefreshToken.is_empty())
         {

            return false;

         }

         m_timeAuth = ::earth::time::now();

         pcontext->m_papexcontext->file()->put_contents(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\access_token.txt", m_strAccessToken);
         pcontext->m_papexcontext->file()->put_contents(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\token_type.txt", m_strTokenType);
         pcontext->m_papexcontext->file()->put_contents(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\expire_in.txt", as_string(m_iExpires));
         pcontext->m_papexcontext->file()->put_contents(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\refresh_token.txt", m_strRefreshToken);
         pcontext->m_papexcontext->file()->put_contents(         auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\waven\\time_auth.txt", as_string((i64)m_timeAuth.m_time));

         return true;

      }

      bool web_api::call(string & str, string strUrl, property_set & set)
      {

         bool bForce = false;

      retry:

         auth(bForce);

         {

            set["raw_http"] = true;

            set["headers"].propset().erase_all();

            set["headers"]["Authorization"] = m_strTokenType + " " + m_strAccessToken;
            set["headers"]["Accept"] = "application/network_payload";
            set["headers"]["Accept-Encoding"] = "gzip";

            str = pcontext->m_papexcontext->http().get(strUrl, set);

         }

         if (str.has_char())
            return true;

         if (bForce)
            return false;

         bForce = true;

         goto retry;

      }

      ::payload web_api::call(string strUrl, property_set & set)
      {

         string strResponse;

         if (!call(strResponse, strUrl, set))
         {

            return false;

         }

         ::payload network_payload;

         try
         {

            const char * pszResponse = strResponse;

            network_payload.parse_network_payload(pszResponse);

         }
         catch (...)
         {

            return false;

         }

         return network_payload;

      }


      ::payload web_api::get(string strUrl)
      {

         ::property_set set;

         return call(strUrl, set);

      }


   }// namespace veriwell

} // namespace spotify
















