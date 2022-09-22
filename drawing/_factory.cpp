// Created by camilo on 2022-05-30 08:29 PM <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "application.h"


__FACTORY_EXPORT void app_complex_drawing_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_complex_drawing::application, ::acme::application >();

}
