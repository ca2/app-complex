#include "framework.h"



namespace multimedia
{


   namespace audio_mixer_user_base
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
         MESSAGE_LINK(::user::e_message_create, pchannel, this, &slider::on_message_create);
         MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &slider::on_message_left_button_down);
         MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &slider::on_message_left_button_up);
         MESSAGE_LINK(::user::e_message_mouse_move, pchannel, this, &slider::on_message_mouse_move);
         //MESSAGE_LINK(::user::e_message_timer, pchannel, this, &slider::on_timer);
         //MESSAGE_LINK(::user::e_message_size, pchannel, this, &slider::on_message_size);
      }



      /////////////////////////////////////////////////////////////////////////////
      // slider message handlers

      int slider::GetLineSize() const
      {
         return m_iLineSize;
      }

      void slider::SetLineSize(int iLineSize)
      {
         m_iLineSize = iLineSize;
      }

      int slider::GetPageSize() const
      {
         return m_iPageSize;
      }

      void slider::SetPageSize(int iPageSize)
      {
         m_iPageSize = iPageSize;
      }

      int slider::GetRangeMax() const
      {
         return m_iRangeMax;
      }

      int slider::GetRangeMin() const
      {
         return m_iRangeMin;
      }

      void slider::GetRange(int &iMin, int &iMax) const
      {
         iMin = m_iRangeMin;
         iMax = m_iRangeMax;
      }

      void slider::SetRangeMin(int iMin, bool bRedraw)
      {
         m_iRangeMin = iMin;
         if(bRedraw)
         {
            set_need_redraw();
         }
      }

      void slider::SetRangeMax(int iMax, bool bRedraw)
      {
         m_iRangeMax = iMax;
         if(bRedraw)
         {
            set_need_redraw();
         }

      }

      void slider::SetRange(int iMin, int iMax, bool bRedraw)
      {
         m_iRangeMin = iMin;
         m_iRangeMax = iMax;
         if(bRedraw)
         {
            set_need_redraw();
         }
      }

      void slider::SetRange(int iMin, int iMax)
      {
         m_iRangeMin = iMin;
         m_iRangeMax = iMax;
      }

      int slider::GetPos() const
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

      void slider::SetPos(int iPos)
      {
         m_iPos = iPos;

         if(::logic::condition(m_bPresenceOnHover, m_bHover))
         {
            set_need_redraw();
         }
      }



      void slider::update_drawing_objects()
      {

         //      ::aura::savings & savings = session()->savings();

         auto pgraphics = create_memory_graphics();

         ::double_rectangle rectangleX;

         this->rectangle(rectangleX);

         //      int cx = rectangleX.width();
         //      int cy = rectangleX.height();

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

         set_timer(1317, 100, nullptr);

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
         ::int_point point = pmouse->m_point;
         screen_to_client()(point);
         if(m_bTracking)
         {
            ::pointer<::user::interaction>pParentWnd = get_parent();

            SetTrackingPos(point);

            if(m_eorientation == e_orientation_horizontal)
            {
               pParentWnd->send_message(
               ::user::e_message_scroll_x,
               MAKEWPARAM(SB_THUMBTRACK, m_iTrackingPos),
               (LPARAM) (::user::interaction * )(this));
               set_need_redraw();
            }
            else if(m_eorientation == e_orientation_vertical)
            {
               pParentWnd->send_message(
               ::user::e_message_scroll_y,
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

            ::double_rectangle rectangleThumb;
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

            ::double_rectangle rectangleX;
            this->rectangle(rectangleX);
            if(!rectangleX.contains(point))
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
         ::int_point point = pmouse->m_point;
         screen_to_client()(point);
         ::double_rectangle rectangleTrack;
         GetThumbRect(rectangleTrack);
         ::double_rectangle rectanglePageA;
         ::double_rectangle rectangleX;
         this->rectangle(rectangleX);
         GetPageARect(rectangleX, rectangleTrack, rectanglePageA);
         ::double_rectangle rectanglePageB;
         GetPageBRect(rectangleX, rectangleTrack, rectanglePageB);
         if(rectangleTrack.contains(point))
         {
            SetCapture();
            m_iTrackingPos = m_iPos;
            m_bTracking = true;
            ::int_point pointTrackOffset;
            pointTrackOffset = point;
            pointTrackOffset -= rectangleTrack.top_left();
            m_sizeTrackOffset = pointTrackOffset;
         }
         //    else if(m_pregionA.PtInRegion(point))
         //    {
         //        SetCapture();
         //        ScrollLineA();
         //        set_timer(100, 300, nullptr);
         //    }
         //    else if(m_pregionB.PtInRegion(point))
         //    {
         //        SetCapture();
         //        ScrollLineB();
         //        set_timer(200, 300, nullptr);
         //    }
         else if(rectanglePageA.contains(point))
         {
            if(!rectangleTrack.contains(point))
            {
               SetCapture();
               ScrollPageA();
               set_timer(300, 300, nullptr);
            }
         }
         else if(rectanglePageB.contains(point))
         {
            if(!rectangleTrack.contains(point))
            {
               SetCapture();
               ScrollPageB();
               set_timer(400, 300, nullptr);
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
         ::int_point point = pmouse->m_point;
         screen_to_client()(point);
         kill_timer(100);
         kill_timer(110);
         kill_timer(200);
         kill_timer(210);
         kill_timer(300);
         kill_timer(310);
         kill_timer(400);
         kill_timer(410);

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
               ::user::e_message_scroll_x,
               MAKEWPARAM(SB_THUMBPOSITION, m_iPos),
               (LPARAM) dynamic_cast < ::user::interaction * >(this));
               set_need_redraw();
            }
            else if(m_eorientation == e_orientation_vertical)
            {
               pParentWnd->send_message(
               ::user::e_message_scroll_y,
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

      bool slider::GetPageARect(::int_rectangle * lpRectClient,::int_rectangle * lpRectTrack, ::int_rectangle * lpRect)
      {
         if(m_eorientation == e_orientation_horizontal)
         {
            lpRect->left() = lpRectClient->left() + GetSystemMetrics(SM_CXHSCROLL);
            lpRect->top() = lpRectTrack->top();
            lpRect->right() = lpRectTrack->left();
            lpRect->bottom() = lpRectTrack->bottom();
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            lpRect->left() = lpRectTrack->left();
            lpRect->top() = lpRectClient->top() + GetSystemMetrics(SM_CYVSCROLL);
            lpRect->right() = lpRectTrack->right();
            lpRect->bottom() = lpRectTrack->top();
         }
         return true;
      }

      bool slider::GetPageBRect(::int_rectangle * lpRectClient,::int_rectangle * lpRectTrack, ::int_rectangle * lpRect)
      {
         if(m_eorientation == e_orientation_horizontal)
         {
            lpRect->left() = lpRectTrack->right();
            lpRect->top() = lpRectTrack->top();
            lpRect->right() = lpRectClient->right() - GetSystemMetrics(SM_CXHSCROLL);
            lpRect->bottom() = lpRectTrack->bottom();
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            lpRect->left() = lpRectTrack->left();
            lpRect->top() = lpRectTrack->bottom();
            lpRect->right() = lpRectTrack->right();
            lpRect->bottom() = lpRectClient->bottom() - GetSystemMetrics(SM_CYVSCROLL);
         }
         return true;
      }


      void slider::on_timer(::timer * ptimer)
      {
         ::audio_mixer_user::level_control::on_timer(ptimer);
         ::int_point point;
         ::double_rectangle rectangle;
         ::double_rectangle rectangleTrack;
         ::double_rectangle rectangleX;
         switch(ptimer->m_uTimer)
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
            kill_timer(ptimer->m_uTimer);
            set_timer(110, 10, nullptr);
         case 110:
            ScrollLineA();
            if(m_iPos == m_iRangeMin)
            {
               kill_timer(110);
            }
            break;
         case 200:
            kill_timer(ptimer->m_uTimer);
            set_timer(210, 10, nullptr);
         case 210:
            ScrollLineB();
            if(m_iPos == m_iRangeMax - m_iPageSize)
            {
               kill_timer(210);
            }
            break;
         case 300:
            kill_timer(ptimer->m_uTimer);
            set_timer(310, 10, nullptr);
         case 310:
            GetCursorPos(&point);
            screen_to_client(&point);
            this->rectangle(rectangleX);
            GetThumbRect(rectangleTrack);
            GetPageARect(rectangleX, rectangleTrack, rectangle);
            if(!rectangle.contains(point))
            {
               kill_timer(310);
               break;
            }
            if(m_iPos == m_iRangeMin)
            {
               kill_timer(ptimer->m_uTimer);
               break;
            }
            ScrollPageA();
            break;
         case 400:
            kill_timer(ptimer->m_uTimer);
            set_timer(410, 10, nullptr);
         case 410:
            GetCursorPos(&point);
            screen_to_client(&point);
            this->rectangle(rectangleX);
            GetThumbRect(rectangleTrack);
            GetPageBRect(rectangleX, rectangleTrack, rectangle);
            if(!rectangle.contains(point))
            {
               kill_timer(410);
               break;
            }
            if(m_iPos == m_iRangeMax - m_iPageSize)
            {
               kill_timer(410);
               break;
            }
            ScrollPageB();
            break;
         default:
            kill_timer(ptimer->m_uTimer);
            break;
         }
         // trans   ::user::interaction::OnTimer(ptimer->m_uTimer);
      }

      bool slider::GetThumbRect(::int_rectangle * lpRect)
      {
         ::double_rectangle rectangleX;
         this->rectangle(rectangleX);
         double dInc;
         double dPos;
         if(m_eorientation == e_orientation_horizontal)
         {
            dInc = ((double) rectangleX.width() - (m_iMargin * 2)) / (m_iRangeMax - m_iRangeMin);
            dPos = m_iMargin;
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            dInc = ((double) rectangleX.height() - (m_iMargin * 2)) / (m_iRangeMax - m_iRangeMin);
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
         ::double_rectangle rectangleThumb;
         if(m_eorientation == e_orientation_horizontal)
         {
            lpRect->left() = ((int) dPos) - 4;
            lpRect->right() = lpRect->left() + 10;
            lpRect->top() = rectangleX.top();
            lpRect->bottom() = rectangleX.bottom() + 1;;
         }
         else if(m_eorientation == e_orientation_vertical)
         {
            lpRect->left() = rectangleX.left();
            lpRect->right() = rectangleX.right() + 1 ;
            lpRect->top() = ((int) dPos) - 4;
            lpRect->bottom() = lpRect->top() + 10;
            //        int iHeight = rectangleX.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy() - 1;
            //      if(m_iRangeMax - m_iRangeMin - m_iPageSize == 0)
            //        lpRect->top() = 0;
            //  else
            //    lpRect->top() = GetSystemMetrics(SM_CYVSCROLL) + 1 + (iPos - m_iRangeMin) * iHeight / (m_iRangeMax - m_iRangeMin - m_iPageSize);
            //        lpRect->bottom() = lpRect->top() + sizeTrack.cy();
            //      lpRect->left() = rectangleX.left() + 1;
            //    lpRect->right() = lpRect->left() + sizeTrack.cx();
         }
         return true;
      }




      int slider::SetTrackingPos(::int_point point)
      {
         double nPos;
         ::size sizeTrack;

         //    GetThumbSize(sizeTrack);
         ::double_rectangle rectangleX;
         this->rectangle(rectangleX);
         sizeTrack.cx() = 10;
         sizeTrack.cy() = rectangleX.height();
         if(m_eorientation == e_orientation_horizontal)
         {
            int iWidth = rectangleX.width() - m_iMargin * 2;
            nPos = point.x() - m_sizeTrackOffset.x();
            nPos -= m_iMargin - 4;
            nPos *= m_iRangeMax - m_iRangeMin;
            nPos /= iWidth;
            nPos += m_iRangeMin;

         }
         else if(m_eorientation == e_orientation_vertical)
         {
            int iHeight = rectangleX.height() -  m_iMargin * 2;
            nPos = point.y() - m_sizeTrackOffset.y();
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
            m_iTrackingPos = (int) nPos;
         }
         else
         {
            m_iPos = (int) nPos;
         }
         return true;
      }


      int slider::ScrollLineA()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         int nPos = m_iPos;
         nPos-=3;
         if(nPos < m_iRangeMin)
            nPos = m_iRangeMin;
         m_iPos = nPos;
         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_x,
            MAKEWPARAM(SB_LINELEFT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_y,
            MAKEWPARAM(SB_LINEUP, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         set_need_redraw();
         return true;
      }

      int slider::ScrollLineB()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         int nPos = m_iPos;
         nPos+=3;
         if(nPos > m_iRangeMax - m_iPageSize)
            nPos = m_iRangeMax - m_iPageSize;
         m_iPos = nPos;

         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_x,
            MAKEWPARAM(SB_LINERIGHT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_y,
            MAKEWPARAM(SB_LINEDOWN, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         return true;
      }
      int slider::ScrollPageA()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         int nPos = m_iPos;
         nPos-=m_iPageSize ;
         if(nPos < m_iRangeMin)
            nPos = m_iRangeMin;
         m_iPos = nPos;
         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_x,
            MAKEWPARAM(SB_LINELEFT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_y,
            MAKEWPARAM(SB_LINEUP, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         set_need_redraw();
         return true;

      }

      int slider::ScrollPageB()
      {
         ::pointer<::user::interaction>pParentWnd = get_parent();
         int nPos = m_iPos;
         nPos+=m_iPageSize ;
         if(nPos > m_iRangeMax - m_iPageSize)
            nPos = m_iRangeMax - m_iPageSize;
         m_iPos = nPos;

         if(m_eorientation == e_orientation_horizontal)
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_x,
            MAKEWPARAM(SB_LINERIGHT, m_iPos),
            (LPARAM) dynamic_cast < ::user::interaction * >(this));
         }
         else
         {
            pParentWnd->send_message(
            ::user::e_message_scroll_y,
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
         //      int iMin = GetRangeMin();
         //      int iMax = GetRangeMax();
         SetPos((int) (((m_iRangeMax - m_iRangeMin) * dRate) + m_iRangeMin));

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



         ::aura::savings & savings = session()->savings();

         ::double_rectangle rectangleX;
         this->rectangle(rectangleX);

         ::double_rectangle rectangleClip = rectangleX;

         ::double_rectangle rectangleDraw;
         rectangleDraw.intersect(rectangleClip, rectangleX);

         informationf("slider:OnPaint\n");
         informationf("rectangle.left()  : %d, ", rectangleDraw.left());
         informationf("rectangle.top()   : %d, ", rectangleDraw.top());
         informationf("rectangle.right() : %d, ", rectangleDraw.right());
         informationf("rectangle.bottom(): %d\n", rectangleDraw.bottom());

//         ::double_rectangle rectangleSrcClipBox = rectangleDraw;

         if(savings.is_trying_to_save(::e_resource_processing))
         {
            pgraphics->fill_rectangle(rectangleDraw, argb(255, 255,255,255));
         }
         else
         {
            pgraphics->fill_rectangle(rectangleDraw, argb(127, 255,255,255));
         }

//         ::double_rectangle rectangleD = rectangleX;


         ::double_rectangle rectangleThumb;
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
         ::int_point point;
         psession->get_cursor_position(&point);
         screen_to_client(&point);

         ::double_rectangle rectangleX;
         this->rectangle(rectangleX);
         return rectangleX.contains(point) != 0;

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


   } // namespace audio_mixer_user_base


} // namespace multimedia



