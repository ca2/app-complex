#pragma once


namespace notify_drawing
{


   class CLASS_DECL_APP_SIMPLE_NOTIFY_DRAWING impact :
      virtual public ::simple_drawing::impact
   {
   public:


      impact();
      virtual ~impact();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual void install_message_routing(::channel * psender);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace notify_drawing


