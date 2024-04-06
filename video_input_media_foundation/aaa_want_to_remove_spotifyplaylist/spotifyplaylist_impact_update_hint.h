#pragma once


namespace mediaplaylist
{


   class CLASS_DECL_APP_CORE_AUDIO ::update : public ::object
   {
   public:

      enum EHint // Hints
      {
         HintInitial,
         HintFull,
         HintCurrentSong,
         HintMode,
         HintGetAttachableImpact,
         HintPop,
      };

   protected:


      i32     m_iHint;
      array < ::pointer<::user::impact> ::pointer<::user::impact>>_impactpaAttachable;

   public:

      ::update();
      virtual ~::update();


      bool is_type_of(EHint ehint);
      void AddAttachableImpact(::pointer<::user::impact>pimpact);
      void SetHint(i32 iHint);
      i32 GetHint();
      void GetAttachableImpacts(array < ::pointer<::user::impact> ::pointer<::user::impact>> viewpa);





   };


} // namespace mediaplaylist










