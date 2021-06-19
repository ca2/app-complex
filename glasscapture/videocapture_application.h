#pragma once


namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE application :
      virtual public ::aura::application
   //,virtual public ::html::application
   {
   public:


      enum enum_type
      {

         type_normal,
         type_mili,

      };

      enum_type                                 m_etype;
      string                                 m_strHelloMultiverse;
      string                                 m_strHelloMultiverseDefault;
      string                                 m_strAlternateHelloMultiverse;
      string                                 m_strAlternateHelloMultiverseDefault;

      bool                                   m_bMultiverseChat;

      bool                                   m_bMFStartup;

      ::user::document *                     m_pdocMenu;
//      ::calculator::plain_edit_view *        m_prollfps;
      ::user::plain_edit_view *              m_prollfps;
      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseView;
      ::user::single_document_template *     m_ptemplateHelloMultiverseSwitcher;
      ::user::single_document_template *     m_ptemplateHelloMultiverseFontSel;

      //::user::split_view *                             m_ptopviewLast;
      //view *                                 m_pviewLast;

      //::user::split_view *                             m_ptopviewMain;
      //view *                                 m_pviewMain;
      //::user::button_view *                          m_ptoggleviewMain;
      //::user::plain_edit_view *              m_peditMain;

      //::user::split_view *                             m_ptopviewSwitcher;
      //view *                                 m_pviewSwitcher;
      //::user::button_view *                          m_ptoggleviewSwitcher;
      //::user::plain_edit_view *              m_peditSwitcher;

      //::user::split_view *                             m_ptopviewFont;
      //::user::font_list_view *               m_pfontlistview;
      //::user::button_view *                          m_ptoggleviewFontSel;
      //::user::plain_edit_view *              m_peditFontSel;

      ::mutex                                  m_mutexAiFont;
      i32                                m_iErrorAiFont;
      bool                                   m_bLoadAiFont;
      void *                                 m_faceAi; // FT_Face m_faceAi;

      application(::object * pobject);
      virtual ~application();


      virtual ::e_status init_instance() override;
      virtual i32  exit_application() override;

      virtual void on_request(::create * pcreate);

      static ::u32 thread_proc_load_ai_font(void * pparam);
      virtual void load_ai_font();

      //virtual void on_create_split_view(::user::split_view * psplit) override;

      //virtual void on_control_event(::user::control_event * pevent) override;

      //virtual void on_control_event(::user::control_event * pevent) override;

      //virtual void on_create_impact(::user::impact_data * pimpactdata) override;

      //virtual void on_change_cur_sel(::user::tab * ptab) override;

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);

   };


} // namespace videocapture



