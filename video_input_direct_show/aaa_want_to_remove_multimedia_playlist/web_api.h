#pragma once


namespace multimedia_playlist
{


   class CLASS_DECL_APP_CORE_AUDIO web_api:
      virtual public ::object
   {
   public:


      string            m_strAccessToken;
      string            m_strTokenType;
      int               m_iExpires;
      string            m_strRefreshToken;
      ::earth::time  m_timeAuth;


      web_api();
      virtual ~web_api();


      virtual bool auth(int iForceAuthLevel = 0);

      virtual bool call(string & str, string strUrl,property_set & set, bool bNetworkPayload = true, int iForceAuthLevel = 0);
      virtual ::payload get(string strUrl);
      virtual ::payload call(string strUrl,property_set & set);


   };


} // namespace spotify







