#pragma once


namespace multimedia_playlist
{


   namespace veriwell
   {


      class CLASS_DECL_APP_CORE_AUDIO web_api :
         virtual public ::multimedia_playlist::web_api
      {
      public:


         string            m_strAccessToken;
         string            m_strTokenType;
         int               m_iExpires;
         string            m_strRefreshToken;
         ::earth::time  m_timeAuth;

         
         web_api();
         virtual ~web_api();


         virtual bool auth(bool bForce = false);

         virtual bool call(string & str, string strUrl, property_set & set);
         virtual ::payload get(string strUrl);
         virtual ::payload call(string strUrl, property_set & set);


      };


   } // namespace namespace veriwell


} // namespace spotify



