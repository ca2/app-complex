#pragma once



namespace complex_drawing
{


   class CLASS_DECL_APP_COMPLEX_DRAWING application :
      virtual public ::simple_drawing::application,
      virtual public ::core::application
   {
   public:

      
      application();
      virtual ~application();


      ::type get_pane_view_type() const override;


      ::e_status init_instance() override;


   };


} // namespace complex_drawing



