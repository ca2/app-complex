﻿#include "framework.h"


namespace simple_drawing
{


   ::update::update()
   {
      m_eview = impact_none;
      m_etype = TypeNone;

   }


   ::update::~::update()
   {

   }


   bool ::update::is_type_of(e_type e_type)
   {

      return m_etype == e_type;

   }


   void ::update::set_type(e_type e_type)
   {

      m_etype = e_type;

   }


} // namespace simple_drawing



