#pragma once


namespace notify_drawing
{


   class CLASS_DECL_APP_SIMPLE_NOTIFY_DRAWING view :
      virtual public ::simple_drawing::view
   {
   public:


      view();
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual void install_message_routing(::channel * psender);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace notify_drawing


