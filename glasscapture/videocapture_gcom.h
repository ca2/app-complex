#pragma once


namespace videocapture
{


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE gcom :
      virtual public impact_base,
      virtual public ::backview::user::impact
   {
   public:


      ::image_pointer        m_pimageBk;
      bool                    m_bBkLoaded;


      gcom(::object * pobject);
      virtual ~gcom();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_routing(::channel * pchannel);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnDestroy);

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }

   };


} // namespace videocapture





















