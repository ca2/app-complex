// Created on 2021-07-07 by camilo 14:11 BRT <3ThomasBorregaardSorensen!!
#pragma once


namespace video_input
{


   class CLASS_DECL_VIDEO_INPUT render :
      virtual public ::object
   {
   public:

      ::image::image_pointer        m_pimage;


      manual_reset_happening* m_pevRenderEnd;



      render();
      ~render() override;


      virtual void initialize_video_input_render(device * pdevice);

      virtual void prepare_image();


      // void assert_ok() const override;
      //void dump(dump_context& dumpcontext) const override;

#ifdef _DEBUG

      long long increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      long long decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }


#endif

      void handle(::topic * ptopic, ::handler_context * pcontext) override;

      virtual bool start_capture();

      virtual void on_layout(::draw2d::graphics_pointer& pgraphics);

      //virtual void defer_update_bilbo();

      //virtual void OnCaptureEvent(wparam wparam, lparam lparam);

      virtual void on_create();
      void destroy() override;

      //virtual string get_videocapture();

      //virtual string get_processed_videocapture();


      //virtual void defer_check_on_draw_layout();
      //virtual void on_draw_image_layer(::draw2d::graphics_pointer& pgraphics);

      // IUnknown
      //STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
      //STDMETHODIMP_(ULONG) AddRef();
      //STDMETHODIMP_(ULONG) Release();
      //virtual HRESULT STDMETHODCALLTYPE OnSample(
      ///* [annotation][in] */
      //_In_opt_  IMFSample *pSample) override;
   };


} // namespace video_input




