#pragma once


namespace wave
{



   class in_listener_set :
      public comparable_array < in_listener *, in_listener *>
   {
   public:


      in_listener_set();
      virtual ~in_listener_set();


      virtual void in_data_proc(in * pwavein, u32 dwSampleTime, int iBuffer);



   };


} // namespace wave



