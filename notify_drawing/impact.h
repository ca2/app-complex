#pragma once


namespace notify_drawing
{


   class CLASS_DECL_APP_SIMPLE_NOTIFY_DRAWING impact :
      virtual public ::simple_drawing::impact
   {
   public:


      impact();
      virtual ~impact();

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual void install_message_routing(::channel * psender);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace notify_drawing


