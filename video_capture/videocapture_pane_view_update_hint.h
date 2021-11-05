#pragma once


namespace videocapture
{


   enum EPaneView
   {
      impact_none,
      impact_menu,
      PaneViewGcom,
      MAIN_IMPACT,
      PaneViewHelloMultiverseSwitcher,
      PaneViewFontSel
   };


   class CLASS_DECL_APP_CORE_VIDEOCAPTURE ::update :
      public object
   {
   public:


      enum enum_type
      {

         TypeNone,
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,

      };

      EPaneView m_eview;
      enum_type m_etype;


      ::update();
      virtual ~::update();


      void set_type(enum_type enum_type);

      bool is_type_of(enum_type enum_type);


   };


} // namespace videocapture















