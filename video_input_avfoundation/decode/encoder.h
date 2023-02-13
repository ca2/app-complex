#pragma once


namespace audio
{

   class CLASS_DECL_APP_CORE_AUDIO encoder :
      virtual public ::object
   {
   public:


      encoder();
      virtual ~encoder();

      virtual void      EncoderSetSamplesPerSec(u32 user) = 0;
      virtual void      EncoderSetChannelCount(u32 user) = 0;
      virtual void      EncoderSetBitsPerSample(u32 user) = 0;
      virtual bool      EncoderSetFile(::pointer<::file::file>pfile) = 0;
      virtual bool      EncoderInitialize() = 0;
      //virtual bool      EncoderGetAttribute(EAttribute attribute, char * lpcszUTF8, i32 iSize);

      // return number of bytes written
      virtual void      EncoderWriteBuffer(void * lpvoidBuffer, u32 uiBufferSize) = 0;

      virtual bool      EncoderFinalize() = 0;
   };


} // namespace audio



