#include "framework.h"



namespace mediaplaylist
{


   ::update::update()
   {

   }

   ::update::~::update()
   {

   }

   int ::update::GetHint()
   {
      return m_iHint;
   }

   void ::update::SetHint(int iHint)
   {
      m_iHint = iHint;
   }

   void ::update::AddAttachableImpact(::pointer<::user::impact>impact)
   {
      m_impactpaAttachable.add(pimpact);
   }

   void ::update::GetAttachableImpacts(array < ::pointer<::user::impact> ::pointer<::user::impact>> viewpa)
   {
      viewpa = m_impactpaAttachable;
   }

   bool ::update::is_type_of(EHint ehint)
   {
      return m_iHint == ehint;
   }


} // namespace mediaplaylist




