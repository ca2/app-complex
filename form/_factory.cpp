// Created by camilo on 2022-05-30 08:29 PM <3ThomasBorregaardS�rensen!!
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_app_complex_form.h"
#endif


__FACTORY_EXPORT void app_complex_form_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_complex_form::application, ::app >();

}
