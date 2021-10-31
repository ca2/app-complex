#pragma once



namespace complex_form
{


   class CLASS_DECL_APP_COMPLEX_FORM application :
      virtual public ::simple_form::application
   {
   public:


      application();
      ~application() override;

      string preferred_experience() override;
      ::e_status init_instance() override;
      void term_application() override;

      void on_request(::create * pcreate) override;


#ifdef _DEBUG
      int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


   };


} // namespace simple_form



