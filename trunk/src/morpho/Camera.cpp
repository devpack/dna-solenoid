#include "Camera.h"

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Constructor & Destructor
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

Camera::Camera() : xcamera(0.0), ycamera(CAMERAHEIGHT), zcamera(CAMERADISTANCE), 
                   yrotcamera(0.0), xrotcamera(0.0), zrotcamera(0.0), 
                   speedwalk(0), speedrot(0),
                   Znear(ZNEAR), Zfar(ZFAR),
                   angledevue(ANGLEDEVUE),
                   arot(0.0)                   
{
 Init3dView();
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Init3dView()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void Camera::Init3dView()
{
 glViewport(0, 0, InitPlayfield::ScrW, InitPlayfield::ScrH);
 
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 perspectiveGL(angledevue, (GLdouble)InitPlayfield::ScrW/InitPlayfield::ScrH, Znear, Zfar);

 glMatrixMode (GL_MODELVIEW); 
 glLoadIdentity(); 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Walk(GLfloat speed)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void Camera::Walk(GLfloat speed)
{
 GLfloat yangle = (-yrotcamera - 90.0) * Deg2Rad;
 GLfloat xangle = (-xrotcamera - 90.0) * Deg2Rad;
  
 ycamera += -cos(xangle) * speed; 
 xcamera += cos(yangle) * -sin(xangle) * speed;
 zcamera += sin(yangle) * -sin(xangle) * speed; 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Yrotcamera(GLfloat speed)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////
    
void Camera::Yrotcamera(GLfloat speed) 
{ 
 yrotcamera += speed; 
}

void Camera::Xrotcamera(GLfloat speed) 
{ 
 xrotcamera += speed; 
}

void Camera::Zrotcamera(GLfloat speed) 
{ 
 zrotcamera += speed; 
}
 
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// CameraTransformations()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////
           
void Camera::CameraTransformations()
{
 glLoadIdentity();         
 glRotatef(-xrotcamera, 1.0, 0.0, 0.0);
 glRotatef(-zrotcamera, 0.0, 0.0, 1.0);
 glRotatef(-yrotcamera, 0.0, 1.0, 0.0);
 glTranslatef(-xcamera, -ycamera, -zcamera); 
}  

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// CameraRotate(float a)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////
           
void Camera::CameraRotate()
{
 glRotatef(-yrotcamera + arot, 0.0, 1.0, 0.0);  
 arot += 0.03;  
}  

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// abs(float s)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////
        

float abs(float s)
{
return s<0?-s:s;
}

int sign(float s)
{
    if (s==0.0) return 0;
    return s<0?-1:1;
}
        
void Camera::UpdateCameraPos()
{
 Yrotcamera( ((GLfloat)(InitPlayfield::ScrW/2 - mouse_x)/100.)*20. );
 Xrotcamera( ((GLfloat)(InitPlayfield::ScrH/2 - mouse_y)/100.)*20. );  
 position_mouse(InitPlayfield::ScrW/2, InitPlayfield::ScrH/2);

 ycamera += 1.0*mouse_z; 
 
 const static int realkeys[]={KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT};
 
 static int keystate[]={0,0,0,0};
 
 if(key[KEY_UP])
    speedwalk+=0.2*SPEEDWALK;
 else if (key[KEY_DOWN])
    speedwalk-=0.2*SPEEDWALK;
 else
    speedwalk/=1.4;
    

 if(key[KEY_LEFT])
    speedrot+=0.2*SPEEDWALK;
 else if (key[KEY_RIGHT])
    speedrot-=0.2*SPEEDROT;
 else
    speedrot/=1.4;

 if (abs(speedwalk)>10*SPEEDWALK)
  speedwalk=10*SPEEDWALK*sign(speedwalk);
 if (abs(speedrot)>10*SPEEDROT)
  speedrot=10*SPEEDROT*sign(speedrot);

 if (abs(speedwalk)>0.01)     
  Walk( speedwalk);
 if (abs(speedrot)>0.01)     
  Yrotcamera( speedrot);

 for(int i=0;i<sizeof(keystate)/sizeof(int);i++)
   {
   keystate[i]=key[realkeys[i]];
   }
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void Camera::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
 GLdouble fW, fH;
 
 fH = tan( fovY / 180 * PI ) * zNear / 2;
 fW = fH * aspect;
 glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}
 
 
 
