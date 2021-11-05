#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE document :
      public ::user::document
   {
   public:


      document();
	   virtual ~document();

      
	   void assert_valid() const override;
	   void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


   };


} // namespace video_capture















