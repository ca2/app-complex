#include "framework.h"



namespace multimedia_playlist
{


   web_api::web_api()
   {

      m_iExpires = 0;

   }


   web_api::~web_api()
   {


   }


   bool web_api::auth(int iForceAuthLevel)
   {

      return false;

   }

   bool web_api::call(string & str,string strUrl,property_set & set, bool bNetworkPayload, int iForceAuthLevel)
   {

      return false;
   
   }

   ::payload web_api::call(string strUrl,property_set & set)
   {

      string strResponse;

      if(!call(strResponse,strUrl,set))
      {

         return false;

      }

      ::payload network_payload;

      try
      {

         const char * pszResponse = strResponse;

         network_payload.parse_network_payload(pszResponse);

      }
      catch(...)
      {

         return false;

      }

      return network_payload;

   }


   ::payload web_api::get(string strUrl)
   {

      ::property_set set;

      return call(strUrl,set);

   }


} // namespace spotify
















