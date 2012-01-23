#include "InitPlayfield.h"

const int   InitPlayfield::ScrW = 1024;
const int   InitPlayfield::ScrH = 768;
int         InitPlayfield::GFXOPENARG = 0;    // 1 = FULLSCREEN | 0 = WINDOWED
   
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Constructor & Destructor
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

InitPlayfield::InitPlayfield(int GFXOPENARG, int ScrW, int ScrH)
{
 //allegro_init();
   install_allegro(SYSTEM_AUTODETECT, 0, atexit);  // avoid errno undefined

  /*
 install_allegro_gl();
 
 allegro_gl_set(AGL_DOUBLEBUFFER, true);
 allegro_gl_set(AGL_SUGGEST, AGL_DOUBLEBUFFER);  
          
		  	allegro_gl_clear_settings();

 allegro_gl_set(AGL_Z_DEPTH, 24);
 allegro_gl_set(AGL_COLOR_DEPTH,32);
 allegro_gl_set(AGL_RENDERMETHOD, 1);
 allegro_gl_set(AGL_FULLSCREEN, GFXOPENARG); 
 allegro_gl_set(AGL_SUGGEST, AGL_FULLSCREEN | AGL_Z_DEPTH | AGL_COLOR_DEPTH | AGL_DOUBLEBUFFER | 
                             AGL_RENDERMETHOD);

 set_gfx_mode(GFX_OPENGL, ScrW, ScrH, 0, 0);
 
 install_keyboard();    
 install_mouse();
 install_timer(); 
 */
 
	install_allegro_gl();
	install_keyboard();
	install_mouse();
	
	allegro_gl_clear_settings();
	allegro_gl_set(AGL_COLOR_DEPTH, 32);
	allegro_gl_set(AGL_Z_DEPTH, 24);
	allegro_gl_set(AGL_WINDOWED, TRUE);
	allegro_gl_set(AGL_DOUBLEBUFFER, 1);
	allegro_gl_set(AGL_RENDERMETHOD, 1);
	allegro_gl_set(AGL_SUGGEST, AGL_COLOR_DEPTH | AGL_DOUBLEBUFFER
	             | AGL_RENDERMETHOD | AGL_Z_DEPTH | AGL_WINDOWED);
	
	if (set_gfx_mode(GFX_OPENGL, ScrW, ScrH, 0, 0)) {	
		allegro_message("Error setting OpenGL graphics mode:\n%s\n"
		                "Allegro GL error : %s\n",
		                allegro_error, allegro_gl_error);
	}
 

 	  install_timer();

 srand(time(NULL)); 
 
 dothepalette();
}

InitPlayfield::~InitPlayfield()
{
 poll_mouse();
 poll_keyboard();
 allegro_exit();
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void  InitPlayfield::dothepalette()
{
int c;
 
 palette[0].r = 0;   palette[0].g = 0;   palette[0].b = 0;
 palette[1].r = 255; palette[1].g = 255; palette[1].b = 255;
 
 palette[2].r = 0;   palette[2].g = 255;   palette[2].b = 0;
 palette[3].r = 255;   palette[3].g = 0;   palette[3].b = 0;
 palette[4].r = 255;   palette[4].g = 0;   palette[4].b = 255;
 palette[5].r = 0;   palette[5].g = 0;   palette[5].b = 255;
 palette[6].r = 0;   palette[6].g = 255;   palette[6].b = 255; 
 
 set_palette(palette);
}



