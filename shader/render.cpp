#include "framework.h"
#include <math.h>


void image_gl_set(image* pimage);


namespace simple_shader
{


   render::render()
   {

      m_bUpdateShader = false;

      m_strShaderPrefix = "default";

   }


   render::~render()
   {

   }


   ::e_status render::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      initialize_application_consumer();

      m_pcontext = System.get_gpu()->create_context();

      if (!m_pcontext)
      {

         return ::error_failed;

      }

      estatus = m_pcontext->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   int64_t render::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t render::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   void render::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_rectangle.area() <= 0)
      {

         return;

      }

      if (m_pcontext)
      {

         m_pcontext->resize_offscreen_buffer(m_rectangle.size());

      }
      
   }


   void render::defer_load_fragment(const char* pszPathPrefix)
   {

      if (string(pszPathPrefix) == "default")
      {

         m_strProjection.Empty();

         m_strFragment.Empty();

         defer_update_shader();

         return;

      }

      ::file::listing listing(get_context());

      listing.ls_pattern("dropbox://shader/simple shader/", { "*.frag" });

      for (auto& path : listing)
      {

         if (path.name().begins_ci(pszPathPrefix))
         {

            m_strFragment = m_pcontext->load_fragment(path, m_eshadersource);

            m_bUpdateShader = true;

            break;

         }

      }

   }


   ::e_status render::update_shader()
   {

      m_bUpdateShader = true;

      return ::success;

   }


   void render::defer_update_shader()
   {

      if (m_bUpdateShader)
      {

         m_bUpdateShader = false;

         _update_shader();

      }

   }


   ::e_status render::_update_shader()
   {

      ::e_status estatus = ::success_none;

      if(m_strProjection.is_empty())
      {

         m_strProjection = m_pcontext->_001GetIntroProjection();

      }

      if(m_strFragment.is_empty())
      {

         m_strFragment = m_pcontext->_001GetIntroFragment();

      }

      color32_t crText = argb(255, 55, 210, 120);

      string strProjection = m_strProjection;

      string strFragment = m_strFragment;

      ::gpu::context_lock lock(m_pcontext);

      m_pcontext->make_current();

      if (!m_pprogram)
      {

         estatus = __construct(m_pprogram);

      }

      m_pcontext->translate_shader(strProjection);

      m_pcontext->translate_shader(strFragment);

      if (::succeeded(estatus))
      {

         estatus = m_pprogram->create_program(strProjection, strFragment);

      }

      ::color::color color(crText);

      string strDataId;

      strDataId = m_pview->m_id;

      m_pcontext->m_pprogram = m_pprogram;

      m_pcontext->draw();

      //unsigned int texture1;

      //glGenTextures(1, &texture1);

      ////            glActiveTexture(GL_TEXTURE0);

      //glBindTexture(GL_TEXTURE_2D, texture1);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      m_millisStart.Now();

      return ::success;

   }


   void render::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      
      ::gpu::context_lock lock(m_pcontext);

      if (m_strShaderPrefix.has_char())
      {

         defer_load_fragment(m_strShaderPrefix);

         m_strShaderPrefix.Empty();

      }

      defer_update_shader();

      if (m_pcontext &&
        ::is_set(m_pcontext->m_pprogram) &&
       m_pcontext->m_pbuffer && ::is_ok(m_pcontext->m_pbuffer->m_pimage))
      {
         
         {

            ::gpu::context_lock lock(m_pcontext);
            
            m_pcontext->make_current();

            m_pcontext->start();

            {

               float x = (float) psession->get_cursor_pos().x;

               float y = (float) psession->get_cursor_pos().y;

               m_pcontext->m_pprogram->m_pshader->setVec2("mouse", x, y);
               m_pcontext->m_pprogram->m_pshader->setVec2("iMouse", x, y);

            }

            {

               float cx = (float) m_pcontext->m_pbuffer->m_pimage->width();

               float cy = (float) m_pcontext->m_pbuffer->m_pimage->height();

               m_pcontext->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
               m_pcontext->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);

            }

            {

               double dElapsed = __double(m_millisStart.elapsed());

               double dTime = dElapsed / 1000.0;

               float time = (float) dTime;

               m_pcontext->m_pprogram->m_pshader->setFloat("time", time);
               m_pcontext->m_pprogram->m_pshader->setFloat("iTime", time);

            }

            m_pcontext->render();

            m_pcontext->prepare_for_gpu_read();

            m_pcontext->m_pbuffer->gpu_read();
            
         }
      
         
#if !defined(__APPLE__)
         ::draw2d::matrix matrixOriginal;
         pgraphics->get(matrixOriginal);
         ::draw2d::matrix matrix(matrixOriginal);
         matrix.scale(1.0, -1.0);
         matrix.translate(0, m_rectangle.height());
         pgraphics->set(matrix);
#endif

         pgraphics->draw(m_rectangle, m_pcontext->m_pbuffer->m_pimage);

#if !defined(__APPLE__)
         pgraphics->set(matrixOriginal);
#endif
      }

      //_001OnDraw1Through3(pgraphics);

   }


   ::e_status render::set_font(const string & strFont)
   {

      if (strFont.is_empty())
      {

         return error_invalid_argument;

      }

      string strDataId;

      strDataId = m_pview->m_id;

      if (!Application.data_set(strDataId + ".font_family", m_strFont1))
      {

         return error_failed;

      }

      m_strFont1 = strFont;

      return ::success;

   }


   string render::get_font()
   {

      string strFont;

      strFont = Application.get_hover_font();

      if (strFont.has_char())
      {

         return strFont;

      }

      if (m_strFont1.is_empty())
      {

         string strDataId;

         strDataId = m_pview->m_id;

         if (!Application.data_get(strDataId + ".font_family", m_strFont1)
            || m_strFont1.is_empty())
         {

            m_strFont1 = os_font_name(e_font_sans_ex);

         }

      }

      return m_strFont1;

   }


   string application::get_main_title() const
   {

      string strSimple(m_strSimple);

      if (strSimple.trimmed().has_char())
      {

         return m_strSimple;

      }
      else
      {

         return m_strMainTitle;

      }

   }


} // namespace simple_shader



