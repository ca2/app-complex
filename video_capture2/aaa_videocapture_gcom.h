#pragma once


namespace video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE gcom :
      virtual public impact_base,
      virtual public ::backimpact::user_interaction
   {
   public:


      ::image::image_pointer        m_pimageBk;
      bool                    m_bBkLoaded;


      gcom();
      virtual ~gcom();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      ::e_status initialize(::particle * pparticle) override;

      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void handle(::topic * ptopic, ::handler_context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual long long increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual long long decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }

   };


} // namespace video_capture





















