#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE gcom :
      virtual public impact_base,
      virtual public ::backview::user_interaction
   {
   public:


      ::image_pointer        m_pimageBk;
      bool                    m_bBkLoaded;


      gcom();
      virtual ~gcom();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      ::e_status initialize(::object * pobject) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }

   };


} // namespace video_capture





















