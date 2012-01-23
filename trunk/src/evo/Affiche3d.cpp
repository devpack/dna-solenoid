#include "Affiche3d.h"  
  	
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

Affiche3D::Affiche3D(int GFXOPENARG, int ScrW, int ScrH)
          :InitGLmodes(GFXOPENARG, ScrW, ScrH)
{

}

Affiche3D::~Affiche3D()
{

}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void Affiche3D::Render()
{ 
 if( AFFICHEBOX == 1)
  AfficheBox(); 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void Affiche3D::AfficheBox()
{
 glDisable(GL_LIGHTING);
 glEnable(GL_BLEND);	

 //glBlendFunc( GL_ONE, GL_ONE ); 
 //glBlendFunc( GL_SRC_ALPHA, GL_ONE ); 
 //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );   
 glColor4f(0.2, 0.2, 0.25, 1.0);
 
 // Front
 glBegin(GL_LINE_LOOP);
  glVertex3f(-XWORLD/2,  YWORLD/2, ZWORLD/2);
  glVertex3f( XWORLD/2,  YWORLD/2, ZWORLD/2.0);
  glVertex3f( XWORLD/2, -YWORLD/2, ZWORLD/2.0);
  glVertex3f(-XWORLD/2, -YWORLD/2, ZWORLD/2.0);  
 glEnd();
 
 // Back
 glBegin(GL_LINE_LOOP);
  glVertex3f(-XWORLD/2,  YWORLD/2, -ZWORLD/2.0);
  glVertex3f( XWORLD/2,  YWORLD/2, -ZWORLD/2.0);
  glVertex3f( XWORLD/2, -YWORLD/2, -ZWORLD/2.0);
  glVertex3f(-XWORLD/2, -YWORLD/2, -ZWORLD/2.0);  
 glEnd(); 
 
 // Side
 glBegin(GL_LINES);
 
  glVertex3f(-XWORLD/2,  YWORLD/2, ZWORLD/2.0);
  glVertex3f(-XWORLD/2,  YWORLD/2, -ZWORLD/2.0);
    glVertex3f(XWORLD/2, YWORLD/2, ZWORLD/2.0);
  glVertex3f(XWORLD/2, YWORLD/2, -ZWORLD/2.0); 
  
  glVertex3f(XWORLD/2, -YWORLD/2, ZWORLD/2.0);
  glVertex3f(XWORLD/2, -YWORLD/2, -ZWORLD/2.0);
  
  glVertex3f(-XWORLD/2, -YWORLD/2, ZWORLD/2.0);
  glVertex3f(-XWORLD/2, -YWORLD/2, -ZWORLD/2.0); 
   
 glEnd();  
 
 glEnable(GL_LIGHTING);
}









