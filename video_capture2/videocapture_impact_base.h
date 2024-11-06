#pragma once


namespace app_complex_video_capture
{


   class CLASS_DECL_APP_COMPLEX_VIDEO_CAPTURE impact_base :
      virtual public ::user::impact
   {
   public:


 

      impact_base();
      virtual ~impact_base();

      virtual huge_integer increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual huge_integer decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void install_message_routing(::channel * pchannel) override;

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

      virtual void defer_check_on_draw_layout();

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace app_complex_video_capture





















