#pragma once


namespace videocapture
{


   enum EPaneImpact
   {
      impact_none,
      impact_menu,
      PaneImpactGcom,
      MAIN_IMPACT,
      PaneImpactHelloMultiverseSwitcher,
      PaneImpactFontSel
   };


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE ::update :
      public object
   {
   public:


      enum enum_type
      {

         TypeNone,
         TypeGetImpact,
         TypeSetImpact,
         TypeOnShowKaraoke,
         TypeOnShowImpact,

      };

      EPaneImpact m_eview;
      enum_type m_etype;


      ::update();
      virtual ~::update();


      void set_type(enum_type enum_type);

      bool is_type_of(enum_type enum_type);


   };


} // namespace videocapture















