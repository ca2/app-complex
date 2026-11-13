#include "platform.h"
#include "impact.h"
#include "application.h"
#include "pane_impact.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "app-complex/video_input/render.h"
#include "app-complex/video_input/device.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"
#include "berg/user/user/user.h"
#include "acme/user/menu/menu.h"
#include "acme/parallelization/synchronous_lock.h"


namespace app_complex_video_capture
{


   impact::impact()
   {

      m_bDefaultClickHandling = true;
      m_enonclient.erase(::user::e_non_client_background);
      m_enonclient.erase(::user::e_non_client_focus_rect);

   }


   impact::~impact()
   {

   }


   //void impact::assert_ok() const
   //{

   //   user::box::assert_ok();

   //}


   //void impact::dump(dump_context & dumpcontext) const
   //{

   //   user::box::dump(dumpcontext);

   //}


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create,pchannel,this,&impact::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &impact::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_context_menu, pchannel, this, &impact::on_message_context_menu);
      add_command_handler("video_show_stats", {this, &impact::on_toggle_show_stats});
      add_command_prober("video_show_stats", {this, &impact::on_update_show_stats});

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      //get_top_level()->add_fps_interest(this);

      add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen_fps);
      
   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

      if (m_prender)
      {

         m_prender->on_destroy();

         m_prender.release();

      }

   }


   void impact::on_message_context_menu(::message::message * pmessage)
   {

      pmessage->m_bRet = true;
      if (m_ptrackpopupContextMenu)
         return;

      ::pointer<::message::context_menu> pcontextmenu(pmessage);
      auto pmenu = user()->menu_from_xml(this,
         "<menubar><item id=\"video_show_stats\">Show stats</item></menubar>");
      m_ptrackpopupContextMenu = allocateø::menu::track_popup(
         pmenu, this, this, pcontextmenu->GetPoint());
      m_ptrackpopupContextMenu->track([this]()
      {
         m_ptrackpopupContextMenu.release();
      });

   }


   void impact::on_toggle_show_stats(::message::message * pmessage)
   {

      {
         synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         m_bShowStats = !m_bShowStats;
      }
      pmessage->m_bRet = true;
      set_need_redraw();
      post_redraw();

   }


   void impact::on_update_show_stats(::message::message * pmessage)
   {

      ::pointer<::message::command> pcommand(pmessage);
      synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      pcommand->enable();
      pcommand->set_check(m_bShowStats, ::e_source_sync);
      pcommand->m_bRet = true;

   }


   bool impact::on_click(::item *, ::user::mouse *)
   {
      if (!m_bEnableNativeSizeToggle)
      {
         m_bNativeSize.store(false);
         return true;
      }
      m_bNativeSize.store(!m_bNativeSize.load());
      set_need_redraw();
      post_redraw();
      return true;
   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto rectangleX = this->rectangle();
      trace_view_geometry();

      auto pvideoinputdevice = get_app()->m_pvideoinputdevice;

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (!pvideoinputdevice)
      {

         pdraw2dgraphics->set_font(this);

         pdraw2dgraphics->set_solid_color(::color::white);

         pdraw2dgraphics->fill_inset_rectangle(rectangleX, argb(127, 0, 0, 0));

         pdraw2dgraphics->text_out(10, 10, "No video input device selected.");

         return;

      }

      if (pvideoinputdevice->m_edevicestate == ::video_input::e_device_state_already_in_use_by_other_client
         || pvideoinputdevice->m_edevicestate == ::video_input::e_device_state_capture_failed)
      {

         pdraw2dgraphics->set_font(this);

         pdraw2dgraphics->set_solid_color(::color::white);

         pdraw2dgraphics->fill_inset_rectangle(rectangleX, argb(255, 0, 0, 0));

         pdraw2dgraphics->text_out(10, 10, "Unable to open camera. It may be in exclusive use by another application (such as OBS).");
         pdraw2dgraphics->text_out(10, 40, "Release the camera in the other application, then deselect and select it again to retry.");

         return;

      }

      m_prender = pvideoinputdevice->get_render();

      synchronous_lock synchronouslock(m_prender->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_prender->prepare_image();

      if (!m_prender->m_pimage)
      {
         pdraw2dgraphics->fill_inset_rectangle(rectangleX, argb(255, 0, 0, 0));
         pdraw2dgraphics->set_font(this);
         pdraw2dgraphics->set_solid_color(::color::white);
         pdraw2dgraphics->text_out(10, 10, "Waiting for camera frames (0 received).");
         return;
      }

      auto pimage = m_prender->m_pimage;
      const auto lastFrame = m_prender->m_timeLastFrame;
      const double measuredFps = m_prender->m_dCaptureFps;
      const double requestedFps = m_prender->m_dRequestedFps;
      const auto framesReceived = m_prender->m_uFramesReceived;
      synchronouslock.unlock();

      ::image::image_source imagesource(pimage);

      // Fullscreen always fits the capture to the view. Keep the native-size
      // preference for windowed inspection without carrying it into fullscreen.
      const bool fullScreen = top_level()->layout().is_full_screen();
      const bool nativeSize = m_bEnableNativeSizeToggle && m_bNativeSize.load() && !fullScreen;
      auto target = rectangleX;
      if (nativeSize)
      {
         // One source pixel per destination pixel; excess is clipped by the view.
         target.right = target.left + pimage->width();
         target.bottom = target.top + pimage->height();
         pdraw2dgraphics->fill_inset_rectangle(rectangleX, argb(255, 0, 0, 0));
      }
      if (!nativeSize && pimage->width() > 0 && pimage->height() > 0)
      {
         const double scale = minimum((double) rectangleX.width() / pimage->width(),
            (double) rectangleX.height() / pimage->height());
         const int width = (int) (pimage->width() * scale);
         const int height = (int) (pimage->height() * scale);
         target.left = rectangleX.left + (rectangleX.width() - width) / 2;
         target.top = rectangleX.top + (rectangleX.height() - height) / 2;
         target.right = target.left + width;
         target.bottom = target.top + height;
      }
      if (!nativeSize)
      {
         // The opaque video overwrites its target. Clear only the letterbox bars
         // instead of filling the entire full-screen surface before every frame.
         const auto black = argb(255, 0, 0, 0);
         if (target.top > rectangleX.top)
            pdraw2dgraphics->fill_inset_rectangle(::i32_rectangle(rectangleX.left, rectangleX.top, rectangleX.right, target.top), black);
         if (target.bottom < rectangleX.bottom)
            pdraw2dgraphics->fill_inset_rectangle(::i32_rectangle(rectangleX.left, target.bottom, rectangleX.right, rectangleX.bottom), black);
         if (target.left > rectangleX.left)
            pdraw2dgraphics->fill_inset_rectangle(::i32_rectangle(rectangleX.left, target.top, target.left, target.bottom), black);
         if (target.right < rectangleX.right)
            pdraw2dgraphics->fill_inset_rectangle(::i32_rectangle(target.right, target.top, rectangleX.right, target.bottom), black);
      }
      ::string previewGeometry;
      previewGeometry.formatf("fullscreen=%d source=%dx%d view=%dx%d target=(%d,%d %dx%d) native=%d",
         (int)fullScreen, pimage->width(), pimage->height(), rectangleX.width(), rectangleX.height(),
         target.left, target.top, target.width(), target.height(), (int)nativeSize);
      if (previewGeometry != m_strPreviewGeometry)
      {
         informationf("Video scaling: %s", previewGeometry.c_str());
         m_strPreviewGeometry = previewGeometry;
      }
      ::image::image_drawing_options imagedrawingoptions(target);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      const auto previousResizedImages = pdraw2dgraphics->m_bUseImageMipMapsOrResizedImages;
      pdraw2dgraphics->m_bUseImageMipMapsOrResizedImages = false;
      // Camera frames are opaque; avoid reading and blending the destination.
      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      // Keep smooth scaling now that the application requests GPU drawing.
      const char * scalingMode = nativeSize ? "native" : "bilinear";
      const auto previousInterpolation = pdraw2dgraphics->m_einterpolationmode;
      pdraw2dgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_bilinear);
      const auto drawStarted = std::chrono::steady_clock::now();
      try
      {
         pdraw2dgraphics->draw(imagedrawing);
      }
      catch (const ::exception & e)
      {
         auto now = std::chrono::steady_clock::now();
         if (std::chrono::duration<double>(now - m_timePreviewError).count() >= 1.0)
         {
            informationf("Video preview: image draw failed: %s", e.get_message().c_str());
            m_timePreviewError = now;
         }
         pdraw2dgraphics->set_interpolation_mode(previousInterpolation);
         pdraw2dgraphics->m_bUseImageMipMapsOrResizedImages = previousResizedImages;
         pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
         return;
      }
      const auto drawFinished = std::chrono::steady_clock::now();


      pdraw2dgraphics->set_interpolation_mode(previousInterpolation);

      pdraw2dgraphics->m_bUseImageMipMapsOrResizedImages = previousResizedImages;
      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      bool showStats;
      {
         synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         showStats = m_bShowStats;
      }
      if (showStats != m_bStatsWereVisible)
      {
         // Start a fresh measurement when the overlay is enabled again.
         m_uPreviewFrames = 0;
         m_uPreviewPaints = 0;
         m_uLastPreviewFrame = framesReceived;
         m_dDrawTotalMilliseconds = 0.0;
         m_dPreviewFps = 0.0;
         m_dDrawMilliseconds = 0.0;
         m_timePreviewWindow = drawFinished;
         m_bStatsWereVisible = showStats;
      }

         if (showStats)
         {
            m_dDrawTotalMilliseconds += std::chrono::duration<double, std::milli>(drawFinished - drawStarted).count();
            ++m_uPreviewPaints;
            if (framesReceived != m_uLastPreviewFrame)
            {
               ++m_uPreviewFrames;
               m_uLastPreviewFrame = framesReceived;
            }
            const double previewElapsed = std::chrono::duration<double>(drawFinished - m_timePreviewWindow).count();
            if (previewElapsed >= 1.0)
            {
               m_dPreviewFps = m_uPreviewFrames / previewElapsed;
               m_dDrawMilliseconds = m_dDrawTotalMilliseconds / m_uPreviewPaints;
               informationf("Video preview: mode=%s viewport=%dx%d capture=%.1f FPS preview=%.1f FPS paints=%.1f/s image draw=%.2f ms",
                  scalingMode, rectangleX.width(), rectangleX.height(),
                  measuredFps, m_dPreviewFps, m_uPreviewPaints / previewElapsed, m_dDrawMilliseconds);
               informationf("Video geometry: mode=%s source=%dx%d view=%dx%d aspect=%.6f target=(%d,%d %dx%d) aspect=%.6f margins L=%d T=%d R=%d B=%d root_fullscreen=%d",
                  scalingMode, pimage->width(), pimage->height(),
                  rectangleX.width(), rectangleX.height(),
                  rectangleX.height() > 0 ? (double)rectangleX.width() / rectangleX.height() : 0.0,
                  target.left, target.top, target.width(), target.height(),
                  target.height() > 0 ? (double)target.width() / target.height() : 0.0,
                  target.left - rectangleX.left, target.top - rectangleX.top,
                  rectangleX.right - target.right, rectangleX.bottom - target.bottom,
                  (int)top_level()->layout().is_full_screen());
               m_uPreviewFrames = 0;
               m_uPreviewPaints = 0;
               m_dDrawTotalMilliseconds = 0.0;
               m_timePreviewWindow = drawFinished;
            }

            ::string strFrames;
            const auto secondsSinceFrame = std::chrono::duration<double>(
               std::chrono::steady_clock::now() - lastFrame).count();
            const double captureFps = secondsSinceFrame > 2.0 ? 0.0 : measuredFps;
            strFrames.formatf("Capture: %.1f FPS | Mode: %d x %d @ %.2f FPS | Frames: %llu",
               captureFps, pvideoinputdevice->m_size.cx, pvideoinputdevice->m_size.cy,
               requestedFps, (unsigned long long) framesReceived);
            pdraw2dgraphics->fill_inset_rectangle(::i32_rectangle(0, 0, rectangleX.width(), 35), argb(200, 0, 0, 0));
            pdraw2dgraphics->set_font(this);
            pdraw2dgraphics->set_solid_color(::color::white);
            ::string strPreview;
            strPreview.formatf("Preview: %.1f FPS | Draw: %.2f ms | %s | Click video to toggle native/stretch",
               m_dPreviewFps, m_dDrawMilliseconds, nativeSize ? "Native 1:1 (clipped)" : "Stretched (bilinear)");
            pdraw2dgraphics->fill_inset_rectangle(::i32_rectangle(0, 35, rectangleX.width(), 70), argb(200, 0, 0, 0));
            try
            {
               pdraw2dgraphics->text_out(10, 10, strFrames);
               pdraw2dgraphics->text_out(10, 42, strPreview);
            }
            catch (const ::exception & e)
            {
               const auto now = std::chrono::steady_clock::now();
               if (std::chrono::duration<double>(now - m_timePreviewError).count() >= 1.0)
               {
                  informationf("Video preview: statistics text failed: %s", e.get_message().c_str());
                  m_timePreviewError = now;
               }
            }

         }

   }


   void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->id() == id_initial_update)
      {

         ::pointer<::userex::pane_tab_impact>ppaneimpact = get_typed_parent < ::userex::pane_tab_impact >();
         //if(ppaneimpact.is_set())
         //{
         //   ppaneimpact->m_pflagview = this;
         //}

      }
      __UNREFERENCED_PARAMETER(ptopic);
   }


   ::user::document * impact::get_document()
   {

      return  (::user::impact::get_document());

   }


   void impact::trace_view_geometry()
   {
      ::string geometry;
      int level = 0;
      for (auto interaction = (::user::interaction *) this; interaction; interaction = interaction->get_parent(), ++level)
      {
         auto local = interaction->rectangle();
         auto screen = interaction->screen_rectangle();
         ::string line;
         line.formatf("level=%d local=(%d,%d %dx%d) screen=(%d,%d %dx%d) aspect=%.6f delta16:9=%lld fullscreen=%d; ",
            level, local.left, local.top, local.width(), local.height(),
            screen.left, screen.top, screen.width(), screen.height(),
            local.height() > 0 ? (double) local.width() / local.height() : 0.0,
            (long long) local.width() * 9 - (long long) local.height() * 16,
            (int) interaction->layout().is_full_screen());
         geometry += line;
      }
      if (geometry != m_strGeometryTrace)
      {
         informationf("Video geometry (view level=0, then parents): %s", geometry.c_str());
         m_strGeometryTrace = geometry;
      }
   }


   void impact::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      trace_view_geometry();

      if (m_prender)
      {

         m_prender->on_layout(pdraw2dgraphics);

      }

   }


   void impact::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {
      }

   }


   void impact::on_draw_image_layer(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

   }



} // namespace app_complex_video_capture














