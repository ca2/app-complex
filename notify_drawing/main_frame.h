#pragma once


namespace notify_drawing
{


   class CLASS_DECL_APP_SIMPLE_NOTIFY_DRAWING main_frame :
      virtual public simple_drawing::main_frame
   {
   public:



      main_frame();
      virtual ~main_frame();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;



   };


} // namespace notify_drawing












