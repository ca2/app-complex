#include "framework.h"



namespace wave
{

   format::format() :
      m_waveformat{}
   {

   }


   format::format(const format& format) :
      m_waveformat(format.m_waveformat)
   {

   }


   format::~format()
   {

   }


   format& format::operator = (const format& format)
   {

      if (&format != this)
      {

         m_waveformat = format.m_waveformat;

      }

      return *this;

   }


} // namespace wave



