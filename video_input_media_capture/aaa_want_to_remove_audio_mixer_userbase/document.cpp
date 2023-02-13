#include "framework.h"



namespace multimedia
{


   namespace audio_mixer_userbase
   {


      document::document()
      {
      }

      document::~document()
      {
      }

      bool document::on_new_document()
      {

         if(!::user::document::on_new_document())
            return false;

         return true;
      }



#ifdef _DEBUG
      void document::assert_ok() const
      {
         ::user::document::assert_ok();
      }

      void document::dump(dump_context & dumpcontext) const
      {
         ::user::document::dump(dumpcontext);
      }
#endif //_DEBUG



   } // namespace audio_mixer_userbase


} // namespace multimedia





