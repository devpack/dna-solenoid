#include "InitGLmodes.h"

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Constructor & Destructor
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

InitGLmodes::InitGLmodes(int GFXOPENARG, int ScrW, int ScrH)
            :InitPlayfield(GFXOPENARG, ScrW, ScrH)
{
 //glEnable(GL_NORMALIZE);
 //glClearColor(23./255., 23./255., 60./255., 0.);
 glClearColor(0.0, 0.0, 0.0, 0.0);

 glLineWidth(1.0);
 
 
 // GL Modes
 initblend();
 inithideface();
 initshade();
 initfog();
 initlight();
 initmaterial();
 inittexture();
 inithints();
 
 // Print
 TexturedFont = allegro_gl_convert_allegro_font(font, AGL_FONT_TYPE_TEXTURED, 32.0); 
}

InitGLmodes::~InitGLmodes()
{
 //glDeleteTextures( 1, &TextureId );
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::initblend()
{
 //glEnable(GL_BLEND); 
 //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::inithideface()
{
 glEnable(GL_DEPTH_TEST); 
 
 glCullFace(GL_BACK);
 glEnable(GL_CULL_FACE);  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::initshade()
{
 //glShadeModel(GL_FLAT);
 glShadeModel(GL_SMOOTH); 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::initfog()
{
 //glEnable(GL_FOG);
 
 //fog_color[0]=0.7; fog_color[1]=0.7; fog_color[2]=0.7; fog_color[3]=1.; 
 //glFogfv(GL_FOG_COLOR, fog_color); 
    
 //glFogi(GL_FOG_MODE, GL_EXP2);
 //glFogi(GL_FOG_MODE, GL_LINEAR); 
 //glFogf(GL_FOG_DENSITY, 0.000000005);
 
 //glFogi(GL_FOG_MODE, GL_LINEAR);
 //glFogfv(GL_FOG_COLOR, fog_color);
 //glFogf(GL_FOG_DENSITY, 1);
 //glFogf(GL_FOG_START, 0);
 //glFogf(GL_FOG_END, 4000); 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::initlight()
{
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
                                                             // w=0 => lumiere dist infini
 light_pos[0] = 1000.0; light_pos[1] = 1000.0; light_pos[2] = 1000.0; light_pos[3] = 0.0;    
 glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
 
 //light_dir[0] = 0.0; light_dir[1] = -1.0; light_dir[2] = 0.0;  
 //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir );
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::initmaterial()
{ 
 ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0; ambient[3]=1.0;
 diffuse[0] = 1.0; diffuse [1] = 1.0; diffuse[2] = 1.0; diffuse[3]=1.0;
 specular[0] = 1.0; specular[1] = 1.0; specular[2] = 1.0; specular  [3]=1.0;
  
 glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT  , ambient  );
 glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE  , diffuse  );
 glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR , specular );
 glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, 20.	     ); 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::inittexture()
{
 
//char *TexName = { "mountaintex512.bmp" }; 
 
 // Load + Bind Texture
 //FILE* fTest = fopen( TexName, "r" );
 //if( !fTest ) { allegro_message("No Texture Found \n"); exit(1); }
 //fclose( fTest );
 
 //TextureImage = auxDIBImageLoad( TexName );
 
 //glGenTextures    ( 1, &TextureId );
 //glBindTexture    ( GL_TEXTURE_2D, TextureId );
 
 //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data );    
 //glTexParameterf  (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
 //glTexParameterf  (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
 
 //glTexEnvf        (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 //glTexParameterf  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 //glTexParameterf  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 	
 //glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data );
 //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
 //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

 // Free Mem
 //if( TextureImage )
 //{
 // if( TextureImage->data )
 //  free( TextureImage->data );
  
 // free( TextureImage );
 //}
 
 /*
 allegro_gl_set_texture_format(GL_RGB8);   
 Texture_bmp = load_bitmap("mountaintex512.bmp", 0);
 TexID = allegro_gl_make_texture(Texture_bmp);
 glBindTexture(GL_TEXTURE_2D, TexID);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 destroy_bitmap(Texture_bmp); 
 */ 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::inithints()   
{
 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
 //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void InitGLmodes::myglprint(float x, float y, float z, int color, char *str)  
{
 glPushAttrib ( GL_LIGHTING_BIT | GL_TEXTURE_BIT | GL_ENABLE_BIT | 
                GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT); 
 
 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 glDisable(GL_LIGHTING);     
 glEnable(GL_TEXTURE_2D);
 glEnable(GL_BLEND);
 glBlendFunc(GL_ONE, GL_ONE);
  
 glMatrixMode(GL_PROJECTION);			
 glPushMatrix();									
 glLoadIdentity();								
 glMatrixMode(GL_MODELVIEW);						
 glPushMatrix();								
 glLoadIdentity();								 
 glScalef(0.1, 0.1, 0.1);  
 
 allegro_gl_printf(TexturedFont, x*10.0, y*10.0, z*10.0, color, str);
  
 glMatrixMode(GL_PROJECTION);					
 glPopMatrix();									
 glMatrixMode(GL_MODELVIEW);					
 glPopMatrix();									
 
 glPopAttrib();   
}
