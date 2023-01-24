#include "framework.h"


namespace simple_app
{


   window::window()
   {


   }


   window::~window()
   {

   }


   void window::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &window::on_message_close);
      MESSAGE_LINK(e_message_display_change, pchannel, this, &window::on_message_display_change);

   }


   void window::assert_ok() const
   {

      ::user::interaction::assert_ok();

   }


   void window::dump(dump_context & dumpcontext) const
   {

      ::user::interaction::dump(dumpcontext);

   }


   void window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, ::e_element_background);

      pgraphics->fill_rectangle(rectangleClient, argb(127, 255, 255, 255));
      
      double dBase = (double) rectangleClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      pgraphics->fill_solid_rect_dim(x, y, dBase * 5.0, dBase * 5.0, argb(127, 40, 150, 235));

      pgraphics->fill_solid_rect_dim(x + dBase * 6.0, y, dBase * 5.0, dBase * 5.0, argb(127, 40, 150, 235));

      pgraphics->fill_solid_rect_dim(x, y + dBase * 6.0, dBase * 11.0, dBase * 5.0, argb(127, 255, 110, 150));

      rectangleClient.deflate(dBase);

      for (int i = 0; i < dBase; i++)
      {

         pgraphics->draw_inset_3d_rectangle(rectangleClient, argb(255, 127, 127, 127));

         rectangleClient.deflate(1, 1);

      }

   }


   void window::on_message_close(::message::message* pmessage)
   {

      papp->close(::aura::end_app);

   }


   void window::on_message_display_change(::message::message* pmessage)
   {

      ::rectangle_i32 rectangleWindow;

      _001InitialFramePosition(rectangleWindow, { 0.05, 0.05, 0.4, 0.4 });

      display(e_display_restored);

      place(rectangleWindow);

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }



} // namespace simple_app



