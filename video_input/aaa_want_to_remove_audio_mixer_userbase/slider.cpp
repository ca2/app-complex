#include "framework.h"



namespace multimedia
{


   namespace audio_mixer_userbase
   {


      slider::slider() :
         m_ppenThumbA(e_create),
         m_ppenThumbB(e_create),
         m_ppenHoverA(e_create),
         m_ppenHoverB(e_create),
         m_pbrush(e_create)
      {

         m_bPresenceOnHover = false;

         ::draw2d::graphics_pointer g(e_create);

         g->CreateCompatibleDC(nullptr);

         m_ppenThumbA->create_solid(1, argb(200, 255, 63, 63));
         m_ppenThumbB->create_solid(1, argb(200, 255, 192, 192));
         m_ppenHoverA->create_solid(1, argb(200, 255, 255, 63));
         m_ppenHoverB->create_solid(1, argb(200, 255, 255, 192));
         m_iPos = 0;
         m_eorientation = e_orientation_horizontal;
         m_iRangeMin = 0;
         m_iRangeMax = 100;
         m_iMargin = 5;
         m_bTracking = false;
         m_bThumbHover = false;
         m_iPageSize = 1;
         m_iLineSize = 1;

         m_pbrush->create_null();

      }

      slider::~slider()
      {
      }

      void slider::install_message_routing(::channel * pchannel)
      {
         ::user::interaction::install_message_routing(pchannel);
         MESSAGE_LINK(e_message_create, pchannel, this, &slider::on_message_create);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &slider::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &slider::on_message_left_button_up);
         MESSAGE_LINK(e_message_mouse_move, pchannel, this, &slider::on_message_mouse_move);
         //MESSAGE_LINK(e_message_timer, pchannel, this, &slider::_001OnTimer);
         //MESSAGE_LINK(e_message_size, pchannel, this, &slider::on_message_size);
      }



      /////////////////////////////////////////////////////////////////////////////
      // slider message handlers

      i32 slider::GetLineSize() const
      {
         return m_iLineSize;
      }

      void slider::SetLineSize(i32 iLineSize)
      {
         m_iLineSize = iLineSize;
      }

      i32 slider::GetPageSize() const
      {
         return m_iPageSize;
      }

      void slider::SetPageSize(i32 iPageSize)
      {
         m_iPageSize = iPageSize;
      }

      i32 slider::GetRangeMax() const
      {
         return m_iRangeMax;
      }

      i32 slider::GetRangeMin() const
      {
         return m_iRangeMin;
      }

      void slider::GetRange(i32 &iMin, i32 &iMax) const
      {
         iMin = m_iRangeMin;
         iMax = m_iRangeMax;
      }

      void slider::SetRangeMin(i32 iMin, bool bRedraw)
      {
         m_iRangeMin = iMin;
         if(bRedraw)
         {
            set_need_redraw();
         }
      }

      void slider::SetRangeMax(i32 iMax, bool bRedraw)
      {
         m_iRangeMax = iMax;
         if(bRedraw)
         {
            set_need_redraw();
         }

      }

      void slider::SetRange(i32 iMin, i32 iMax, bool bRedraw)
      {
         m_iRangeMin = iMin;
         m_iRangeMax = iMax;
         if(bRedraw)
         {
            set_need_redraw();
         }
      }

      void slider::SetRange(i32 iMin, i32 iMax)
      {
         m_iRangeMin = iMin;
         m_iRangeMax = iMax;
      }

      i32 slider::GetPos() const
      {
         if(m_bTracking)
         {
            return  m_iTrackingPos;
         }
         else
         {
            return m_iPos;
         }

      }

      void slider::SetPos(i32 iPos)
      {
         m_iPos = iPos;

         if(::logic::condition(m_bPresenceOnHover, m_bHover))
         {
            set_need_redraw();
         }
      }



      void slider::update_drawing_objects()
      {

         //      ::aura::savings & savings = psession->savings();

         auto pgraphics = create_memory_graphics();

         ::rectangle rectangleClient;

         client_rectangle(rectangleClient);

         //      i32 cx = rectangleClient.width();
         //      i32 cy = rectangleClient.height();

         /*if(iEconoMode == Savings::SaveNoSave)
         {
         if(m_dcBuffer.m_hDC == nullptr)
         {
         m_dcBuffer.CreateCompatibleDC(pgraphics);
         m_bitmapBufferOriginal.attach(m_dcBuffer.get_current_bitmap()->GetSafeHandle());
         }
         else
         {
         m_dcBuffer.set(m_bitmapBufferOriginal);
         }

         if(m_bitmapBuffer.m_hObject == nullptr)
         {
         m_bitmapBuffer.CreateCompatibleBitmap(pgraphics, cx + 100, cy + 100);
         }
         else
         {
         BITMAP bm;
         if(!m_bitmapBuffer.GetBitmap(&bm))
         {
         ATTENTION;
         m_bitmapBuffer.delete_object();
         m_bitmapBuffer.CreateCompatibleBitmap(pgraphics, cx + 100, cy + 100);
         }
         if(cx > bm.bmWidth ||
         cy > bm.bmHeight)
         {
         m_bitmapBuffer.delete_object();
         m_bitmapBuffer.CreateCompatibleBitmap(pgraphics, cx + 100, cy + 100);
         }
         }
         m_dcBuffer.set(m_bitmapBuffer);
         }
         else
         {
         if(m_dcBuffer.m_hDC != nullptr)
         {
         m_dcBuffer.set(m_bitmapBufferOriginal.detach());
         m_dcBuffer.DeleteDC();
         }
         if(m_bitmapBuffer.m_hObject != nullptr)
         {
         m_bitmapBuffer.delete_object();
         }
         }*/

         //HeapCompact(GetProcessHeap(), 0);
         //::draw2d::graphics_pointer::DeleteTempMap();
      }

      void slider::on_message_create(::message::message * pmessage)
      {
         ::pointer<::message::create>pcreate(pmessage);
         if(pcreate->previous())
            return;

         update_drawing_objects();

         SetTimer(1317, 100, nullptr);

      }

      /*CXfplayerImpact * slider::GetParentLyricWindow()
      {
      ::pointer<::user::interaction>pParentWnd = get_parent();
      if(pParentWnd != nullptr &&
      base_class <CXfplayerImpact >::bases(pParentWnd))
      return (CXfplayerImpact *) pParentWnd;
      return nullptr;


      }*/

      void slider::on_message_mouse_move(::message::message * pmessage)
      {
         auto pmouse = pmessage->m_union.m_pmouse;
         ::point_i32 point = pmouse->m_point;
         screen_to_client()(point);
         if(m_bTracking)
         {
            ::pointer<::user::interaction>pParentWnd = get_parent();

            SetTrackingPos(point);

            if(m_eorientation == e_orientation_horizontal)
            {
               pParentWnd->send_message(
               e_message_hscroll,
               MAKEWPARAM(SB_THUMBTRACK, m_iTrackingPos),
               (LPARAM) (::user::interaction * )(this));
               set_need_redraw();
            }
            else if(m_eorientation == e_orientation_vertical)
            {
               pParentWnd->send_message(
               e_message_vscroll,
               MAKEWPARAM(SB_THUMBTRACK, m_iTrackingPos),
               (LPARAM) (::user::interaction * )(this));
               set_need_redraw();
            }
            else
            {
               ASSERT(false);
            }
         }
         else
         {
            ::pointer<::user::interaction>pWndCapture = psession->GetCapture();
            if(pWndCapture == nullptr || pWndCapture->get_handle() != get_handle())
            {
               SetCapture();
            }

            ::rectangle rectangleThumb;
            GetThumbRect(rectangleThumb);

            if(rectangleThumb.contains(point))
            {
               if(!m_bThumbHover)
               {
                  m_bThumbHover = true;
                  set_need_redraw();
               }
            }
            else
            {
               if(m_bThumbHover)
               {
                  m_bThumbHover = false;
                  set_need_redraw();
               }
            }

            ::rectangle rectangleClient;
            client_rectangle(rectangleClient);
            if(!rectangleClient.contains(point))
            {
               psession->ReleaseCapture();
            }

         }
         pmouse->m_bRet = true;
         pmouse->m_lresult = 1;

         // trans   ::user::interaction::OnMouseMove(pmouse->m_nFlags, point);
      }

      void slider::on_message_left_button_down(::message::message * pmessage)
      {
         auto pmouse = pmessage->m_union.m_pmouse;
         ::point_i32 point = pmouse->m_point;
         screen_to_client()(point);
         ::rectangle rectangleTrack;
         GetThumbRect(rectangleTrack);
         ::rectangle rectanglePageA;
         ::rectangle rectangleClient;
         client_rectangle(rectangleClient);
         GetPageARect(rectangleClient, rectangleTrack, rectanglePageA);
         ::rectangle rectanglePageB;
         GetPageBRect(rectangleClient, rectangleTrack, rectanglePageB);
         if(rectangleTrack.contains(point))
         {
            SetCapture();
            m_iTrackingPos = m_iPos;
            m_bTracking = true;
            ::point_i32 pointTrackOffset;
            pointTrackOffset = point;
            pointTrackOffset -= rectangleTrack.top_left();
            m_sizeTrackOffset = pointTrackOffset;
         }
         //    else if(m_pregionA.PtInRegion(point))
         //    {
         //        SetCapture();
         //        ScrollLineA();
         //        SetTimer(100, 300, nullptr);
         //    }
         //    else if(m_pregionB.PtInRegion(point))
         //    {
         //        SetCapture();
         //        ScrollLineB();
         //        SetTimer(200, 300, nullptr);
         //    }
         else if(rectanglePageA.contains(point))
         {
            if(!rectangleTrack.contains(point))
            {
               SetCapture();
               ScrollPageA();
               SetTimer(300, 300, nullptr);
            }
         }
         else if(rectanglePageB.contains(point))
         {
            if(!rectangleTrack.contains(point))
            {
               SetCapture();
               ScrollPageB();
               SetTimer(400, 300, nullptr);
            }
         }

         pmouse->m_bRet = true;
         pmouse->m_lresult = 1;


         // trans   ::user::interaction::OnLButtonDown(pmouse->m_nFlags, point);
      }

      void slider::on_message_left_button_up(::message::message * pmessage)
      {
         auto pmouse = pmessage->m_union.m_pmouse;
         ::pointer<::user::interaction>pwindow = psession->GetCapture();
         ::point_i32 point = pmouse->m_point;
         screen_to_client()(point);
         KillTimer(100);
         KillTimer(110);
         KillTimer(200);
         KillTimer(210);
         KillTimer(300);
         KillTimer(310);
         KillTimer(400);
         KillTimer(410);

         if(pwindow != nullptr && pwindow->get_handle() == get_handle())
         {
            psession->ReleaseCapture();
            bool bWasTracking = m_bTracking;
            m_bTracking = false;
            ::pointer<::user::interaction>pParentWnd = get_parent();
            if(bWasTracking)
               SetTrackingPos(point);
            if(m_eorientation == e_orientation_horizontal)
            {
               pParentWnd->send_message(
               e_message_hscroll,
               MAKEWPARAM(SB_THUMBPOSITION, m_iPos),
               (LPARAM) dynamic_cast < ::user::interaction * >(this));
               set_need_redraw();
            }
            else if(m_eorientation == e_orientation_vertical)
            {
               pParentWnd->send_message(
               e_message_vscroll,
               MAKEWPARAM(SB_THUMBPOSITION, m_iPos),
               (LPARAM) dynamic_cast < ::user::interaction * >(this));
               set_need_redraw();
            }
            else
            {
               ASSERT(false);
            }
         }
         pmouse->m_bRet = true;
         pmouse->m_lresult = 1;
         // trans   ::user::interaction::OnLButtonUp(pmouse->m_nFlags, point);
      }

      bool slider::GetPageARect(RECTANGLE_I32 * lpRectClient,RECTANGLE_I32 * lpRectTrack, RECTANGLE_I32 * lpRect)
      {
         if(m_eorientation == e_orientation_horizontal)
         {
            lpRect->left = lpRectClient->left + GetSystemMetrics(SM_CXHSCROLL);
            lpRect->top = lpRectTrack->top;
            lpRect->right = lpRectTrack->left;
            lpRect->bottom = lpRectTrack->bottom;
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            lpRect->left = lpRectTrack->left;
            lpRect->top = lpRectClient->top + GetSystemMetrics(SM_CYVSCROLL);
            lpRect->right = lpRectTrack->right;
            lpRect->bottom = lpRectTrack->top;
         }
         return true;
      }

      bool slider::GetPageBRect(RECTANGLE_I32 * lpRectClient,RECTANGLE_I32 * lpRectTrack, RECTANGLE_I32 * lpRect)
      {
         if(m_eorientation == e_orientation_horizontal)
         {
            lpRect->left = lpRectTrack->right;
            lpRect->top = lpRectTrack->top;
            lpRect->right = lpRectClient->right - GetSystemMetrics(SM_CXHSCROLL);
            lpRect->bottom = lpRectTrack->bottom;
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            lpRect->left = lpRectTrack->left;
            lpRect->top = lpRectTrack->bottom;
            lpRect->right = lpRectTrack->right;
            lpRect->bottom = lpRectClient->bottom - GetSystemMetrics(SM_CYVSCROLL);
         }
         return true;
      }


      void slider::_001OnTimer(::timer * ptimer)
      {
         ::audio_mixer::user::level_control::_001OnTimer(ptimer);
         ::point_i32 point;
         ::rectangle rectangle;
         ::rectangle rectangleTrack;
         ::rectangle rectangleClient;
         switch(ptimer->m_uEvent)
         {
         case 1317:
         {
            if(m_bPresenceOnHover)
            {
               DoHoverSmartUpdate();
            }
         }
         break;
         case 100:
            KillTimer(ptimer->m_uEvent);
            SetTimer(110, 10, nullptr);
         case 110:
            ScrollLineA();
            if(m_iPos == m_iRangeMin)
            {
               KillTimer(110);
            }
            break;
         case 200:
            KillTimer(ptimer->m_uEvent);
            SetTimer(210, 10, nullptr);
         case 210:
            ScrollLineB();
            if(m_iPos == m_iRangeMax - m_iPageSize)
            {
               KillTimer(210);
            }
            break;
         case 300:
            KillTimer(ptimer->m_uEvent);
            SetTimer(310, 10, nullptr);
         case 310:
            GetCursorPos(&point);
            screen_to_client(&point);
            client_rectangle(rectangleClient);
            GetThumbRect(rectangleTrack);
            GetPageARect(rectangleClient, rectangleTrack, rectangle);
            if(!rectangle.contains(point))
            {
               KillTimer(310);
               break;
            }
            if(m_iPos == m_iRangeMin)
            {
               KillTimer(ptimer->m_uEvent);
               break;
            }
            ScrollPageA();
            break;
         case 400:
            KillTimer(ptimer->m_uEvent);
            SetTimer(410, 10, nullptr);
         case 410:
            GetCursorPos(&point);
            screen_to_client(&point);
            client_rectangle(rectangleClient);
            GetThumbRect(rectangleTrack);
            GetPageBRect(rectangleClient, rectangleTrack, rectangle);
            if(!rectangle.contains(point))
            {
               KillTimer(410);
               break;
            }
            if(m_iPos == m_iRangeMax - m_iPageSize)
            {
               KillTimer(410);
               break;
            }
            ScrollPageB();
            break;
         default:
            KillTimer(ptimer->m_uEvent);
            break;
         }
         // trans   ::user::interaction::OnTimer(ptimer->m_uEvent);
      }

      bool slider::GetThumbRect(RECTANGLE_I32 * lpRect)
      {
         ::rectangle rectangleClient;
         client_rectangle(rectangleClient);
         double dInc;
         double dPos;
         if(m_eorientation == e_orientation_horizontal)
         {
            dInc = ((double) rectangleClient.width() - (m_iMargin * 2)) / (m_iRangeMax - m_iRangeMin);
            dPos = m_iMargin;
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            dInc = ((double) rectangleClient.height() - (m_iMargin * 2)) / (m_iRangeMax - m_iRangeMin);
            dPos = m_iMargin;
         }
         if(m_bTracking)
         {
            dPos += dInc * (m_iTrackingPos - m_iRangeMin);
         }
         else
         {
            dPos += dInc * (m_iPos - m_iRangeMin);
         }
         ::rectangle rectangleThumb;
         if(m_eorientation == e_orientation_horizontal)
         {
            lpRect->left = ((i32) dPos) - 4;
            lpRect->right = lpRect->left + 10;
            lpRect->top = rectangleClient.top;
            lpRect->bottom = rectangleClient.bottom + 1;;
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            lpRect->left = rectangleClient.left;
            lpRect->right = rectangleClient.right + 1 ;
            lpRect->top = ((i32) dPos) - 4;
            lpRect->bottom = lpRect->top + 10;
            //        i32 iHeight = rectangleClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy - 1;
            //      if(m_iRangeMax - m_iRangeMin - m_iPageSize == 0)
            //        lpRect->top = 0;
            //  else
            //    lpRect->top = GetSystemMetrics(SM_CYVSCROLL) + 1 + (iPos - m_iRangeMin) * iHeight / (m_iRangeMax - m_iRangeMin - m_iPageSize);
            //        lpRect->bottom = lpRect->top + sizeTrack.cy;
            //      lpRect->left = rectangleClient.left + 1;
            //    lpRect->right = lpRect->left + sizeTrack.cx;
         }
         return true;
      }




      i32 slider::SetTrackingPos(::point_i32 point)
      {
         double nPos;
         ::size sizeTrack;

         //    GetThumbSize(sizeTrack);
         ::rectangle rectangleClient;
         client_rectangle(rectangleClient);
         sizeTrack.cx = 10;
         sizeTrack.cy = rectangleClient.height();
         if(m_eorientation == e_orientation_horizontal)
         {
            i32 iWidth = rectangleClient.width() - m_iMargin * 2;
            nPos = point.x - m_sizeTrackOffset.x;
            nPos -= m_iMargin - 4;
            nPos *= m_iRangeMax - m_iRangeMin;
            nPos /= iWidth;
            nPos += m_iRangeMin;

         }
         else if(m_eorientation == e_orientation_vertical)
         {
            i32 iHeight = rectangleClient.height() -  m_iMargin * 2;
            nPos = point.y - m_sizeTrackOffset.y;
            nPos -= m_iMargin - 4;
            nPos *= (m_iRangeMax - m_iRangeMin);
            nPos /= iHeight;
            nPos += m_iRangeMin;
         }
         else
         {
            throw ::exception(::exception("not expected"));
            //  ASSERT(false);
         }
         if(nPos < m_iRangeMin)
            nPos = m_iRangeMin;
         else if(nPos > m_iRangeMax)
            nPos = m_iRangeMax;
         if(m_bTracking)
         {
            m_iTrackingPos = (i32) nPos;
         }
         else
         {
            m_iPos = (i32) nPos;
         }
         return true;
      }


      i32 slider::ScrollLineA()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         i32 nPos = m_iPos;
         nPos-=3;
         if(nPos < m_iRangeMin)
            nPos = m_iRangeMin;
         m_iPos = nPos;
         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            e_message_hscroll,
            MAKEWPARAM(SB_LINELEFT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            e_message_vscroll,
            MAKEWPARAM(SB_LINEUP, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         set_need_redraw();
         return true;
      }

      i32 slider::ScrollLineB()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         i32 nPos = m_iPos;
         nPos+=3;
         if(nPos > m_iRangeMax - m_iPageSize)
            nPos = m_iRangeMax - m_iPageSize;
         m_iPos = nPos;

         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            e_message_hscroll,
            MAKEWPARAM(SB_LINERIGHT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            e_message_vscroll,
            MAKEWPARAM(SB_LINEDOWN, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         return true;
      }
      i32 slider::ScrollPageA()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         i32 nPos = m_iPos;
         nPos-=m_iPageSize ;
         if(nPos < m_iRangeMin)
            nPos = m_iRangeMin;
         m_iPos = nPos;
         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            e_message_hscroll,
            MAKEWPARAM(SB_LINELEFT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            e_message_vscroll,
            MAKEWPARAM(SB_LINEUP, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         set_need_redraw();
         return true;

      }

      i32 slider::ScrollPageB()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         i32 nPos = m_iPos;
         nPos+=m_iPageSize ;
         if(nPos > m_iRangeMax - m_iPageSize)
            nPos = m_iRangeMax - m_iPageSize;
         m_iPos = nPos;

         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            e_message_hscroll,
            MAKEWPARAM(SB_LINERIGHT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            e_message_vscroll,
            MAKEWPARAM(SB_LINEDOWN, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         return true;
      }

      void slider::SetRate(double dRate)
      {
         if(dRate > 1.0)
            dRate = 1.0;
         if(dRate < 0.0)
            dRate = 0.0;
         //      i32 iMin = GetRangeMin();
         //      i32 iMax = GetRangeMax();
         SetPos((i32) (((m_iRangeMax - m_iRangeMin) * dRate) + m_iRangeMin));

      }

      double slider::GetRate() const
      {
         return (((double) GetPos()) - m_iRangeMin) / (((double)m_iRangeMax) - m_iRangeMin);
      }

      void slider::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         update_drawing_objects();
      }



      void slider::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if(m_bPresenceOnHover && !m_bHover)
            return;



         ::aura::savings & savings = psession->savings();

         ::rectangle rectangleClient;
         client_rectangle(rectangleClient);

         ::rectangle rectangleClip = rectangleClient;

         ::rectangle rectangleDraw;
         rectangleDraw.intersect(rectangleClip, rectangleClient);

         TRACE("slider:OnPaint\n");
         FORMATTED_TRACE("rectangle.left  : %d, ", rectangleDraw.left);
         FORMATTED_TRACE("rectangle.top   : %d, ", rectangleDraw.top);
         FORMATTED_TRACE("rectangle.right : %d, ", rectangleDraw.right);
         FORMATTED_TRACE("rectangle.bottom: %d\n", rectangleDraw.bottom);

//         ::rectangle rectangleSrcClipBox = rectangleDraw;

         if(savings.is_trying_to_save(::e_resource_processing))
         {
            pgraphics->fill_rectangle(rectangleDraw, argb(255, 255,255,255));
         }
         else
         {
            pgraphics->fill_rectangle(rectangleDraw, argb(127, 255,255,255));
         }

//         ::rectangle rectangleD = rectangleClient;


         ::rectangle rectangleThumb;
         GetThumbRect(rectangleThumb);

         pgraphics->set(m_pbrush);

         if(m_bThumbHover || m_bTracking)
         {
            pgraphics->set(m_ppenThumbA);
         }
         else
         {
            pgraphics->set(m_ppenHoverA);
         }

         pgraphics->rectangle(rectangleThumb);
         rectangleThumb.deflate(2, 2, 2, 2);
         pgraphics->rectangle(rectangleThumb);


         if(m_bThumbHover || m_bTracking)
         {
            pgraphics->set(m_ppenThumbB);
         }
         else
         {
            pgraphics->set(m_ppenHoverB);
         }

         rectangleThumb.inflate(1, 1, 1, 1);
         pgraphics->rectangle(rectangleThumb);


      }

      void slider::SetOrientation(enum_orientation orientation)
      {
         m_eorientation = orientation;
      }

      void slider::DoHoverSmartUpdate()
      {
         bool bNewHover = IsHover();

         if(bNewHover != m_bHover)
         {
            m_bHover = bNewHover;
            set_need_redraw();
         }

      }

      bool slider::IsHover()
      {
         ::point_i32 point;
         psession->get_cursor_position(&point);
         screen_to_client(&point);

         ::rectangle rectangleClient;
         client_rectangle(rectangleClient);
         return rectangleClient.contains(point) != 0;

      }


      bool slider::create_window(::user::interaction * puiParent, const ::atom & atom)
      {

         ::user::system createstruct(WS_EX_TRANSPARENT, nullptr, nullptr, WS_CHILD | WS_VISIBLE);

         if(!create_window_ex(createstruct, puiParent, atom))
         {

            return false;

         }

         return true;

      }


   } // namespace audio_mixer_userbase


} // namespace multimedia



