#ifndef __INITGLMODE_H_
#define __INITGLMODE_H_

#include "InitPlayfield.h"
#include <GL/glaux.h>	
#include <GL/glu.h>

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

class InitGLmodes : public InitPlayfield
{
public:       
       // FOG
       GLfloat fog_color[4];
       
       // TEXTURE
	   AUX_RGBImageRec* TextureImage;
   	   GLuint	        TextureId;								
      
       GLuint  TexID;
       BITMAP* Texture_bmp;

       // MATERIAL
       GLfloat ambient	[4];
       GLfloat specular [4];
       GLfloat diffuse	[4];   
           
       // LIGHT    
       GLfloat light_pos[4];
       GLfloat light_dir[3];

       // Print
       FONT* TexturedFont;     
        
public:
       InitGLmodes(int GFXOPENARG, int ScrW, int ScrH);
       virtual ~InitGLmodes();
       
public:           
       void  initblend();   
       void  inithideface();
       void  initshade();
       void  initfog();
       void  initlight();
       void  initmaterial();
       void  inittexture();
       void  inithints();          

       void  myglprint(float x, float y, float z, int color, char *str);         
};



#endif

