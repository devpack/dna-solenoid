/*---------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------*/
/*--------------               DNA MORPHOGENESIS             ----------------*/
/*---------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------*/

#include <allegro.h>
#include <alleggl.h>
#include "Affiche3d.h"
//#include <GL/glu.h>
//#include <GL/glext.h>	
//#include <GL/glaux.h>	

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Timer
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

volatile int Time=0;
void TimerFunc()
{
 Time++;
}
END_OF_FUNCTION(TimerFunc);

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// FPS
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

volatile int TimeFps=0;
void FpsTimer()
{
 TimeFps++;
}
END_OF_FUNCTION(FpsTimer);

float TimeStart=0; 
float TimeEnd=0; 
float TimeLasted=200; 
int   NbFrame=0;

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Main
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

int main(int argc,char* argv[]) 
{     
 if (argc>1)
  InitPlayfield::GFXOPENARG=!strcmp(argv[1],"fullscreen");
  
 Affiche3D *DISPLAY=new Affiche3D(InitPlayfield::GFXOPENARG, InitPlayfield::ScrW, InitPlayfield::ScrH);
 GA        *GENOME =new GA();
 
//-----------------------------------------------------------------------------
// TIMER
//----------------------------------------------------------------------------- 
 
 // Timer part
 LOCK_VARIABLE(Time);
 LOCK_FUNCTION(TimerFunc); 
 install_int_ex(TimerFunc, BPS_TO_TIMER(60));
 
 LOCK_VARIABLE(TimeFps);
 LOCK_FUNCTION(FpsTimer);
 install_int_ex(FpsTimer, BPS_TO_TIMER(1000));  
 
//-----------------------------------------------------------------------------
// THE Loop
//----------------------------------------------------------------------------- 
  
 while(! key[KEY_ESC] && !mouse_b&1)
 {
 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
//-----------------------------------------------------------------------------
// SYNC
//----------------------------------------------------------------------------- 
 
 while(Time > 0)
 {
  DISPLAY->UpdateCameraPos(); 

  Time--;   
 }

//-----------------------------------------------------------------------------
// FPS
//----------------------------------------------------------------------------- 

  if (NbFrame++>=10)									
  {
   NbFrame    = 0;		
   TimeEnd    = TimeFps;  	
   TimeLasted = TimeEnd - TimeStart;
   TimeStart  = TimeEnd;		
   sprintf(DISPLAY->buffer, "FPS:%i", int(float(10000.0)/TimeLasted));		
  }
  else
   sprintf(DISPLAY->buffer, "FPS:%i", int(float(10000.0)/TimeLasted));
  
  DISPLAY->myglprint(0.82, 1.0, 0.0, makecol(255,255,255), DISPLAY->buffer); 
 
  //sprintf(DISPLAY->buffer, "x:%i", int(DISPLAY->xcamera));
  //DISPLAY->myglprint(0.55, 1.0, 0.0, makecol(255,255,255), DISPLAY->buffer); 
  //sprintf(DISPLAY->buffer, "y:%i", int(DISPLAY->ycamera));
  //DISPLAY->myglprint(0.7, 1.0, 0.0, makecol(255,255,255), DISPLAY->buffer); 
  //sprintf(DISPLAY->buffer, "z:%i", int(DISPLAY->zcamera));
  //DISPLAY->myglprint(0.85, 1.0, 0.0, makecol(255,255,255), DISPLAY->buffer);   

  sprintf(DISPLAY->buffer, "AdnSize:%i", ADNSIZE);
  DISPLAY->myglprint(-1.0, 1.0, 0.0, makecol(255,255,255), DISPLAY->buffer);
  
  sprintf(DISPLAY->buffer, "LoopSize:%i",  (int)LOOPSIZE);
  DISPLAY->myglprint(-1.0, 0.96, 0.0, makecol(255,255,255), DISPLAY->buffer);   

  sprintf(DISPLAY->buffer, "Fitness:%5.2f", GENOME->AdnPop[GENOME->fitnessind[0]]->fitness);
  DISPLAY->myglprint(-1.0, 0.92, 0.0, makecol(255,255,255), DISPLAY->buffer);
     
  sprintf(DISPLAY->buffer, "MorphoStep:%i", GENOME->morphostep);
  DISPLAY->myglprint(-1.0, 0.88, 0.0, makecol(255,255,255), DISPLAY->buffer); 
  
  sprintf(DISPLAY->buffer, "Cycles:%i", GENOME->cycle);
  DISPLAY->myglprint(-1.0, 0.84, 0.0, makecol(255,255,255), DISPLAY->buffer);                     
                                       
  sprintf(DISPLAY->buffer, "genome", int(DISPLAY->xcamera));  
  DISPLAY->myglprint(-0.05, -0.965, 0.0, makecol(255,255,255), DISPLAY->buffer);
   
  //sprintf(DISPLAY->buffer, ":%f", GENOME->CalculArcDist(300.0));
  //DISPLAY->myglprint(-0.9, 0.8, 0.0, makecol(255,255,255), DISPLAY->buffer);       
                   
//-----------------------------------------------------------------------------
// BLIT IT
//----------------------------------------------------------------------------- 

 DISPLAY->CameraTransformations(); 
 if(ROTATE==1)
  DISPLAY->CameraRotate();  
 
 DISPLAY->Render();   
 GENOME ->GAmain();                                                                                   
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
 glFlush();

 allegro_gl_flip(); 

}

//-----------------------------------------------------------------------------
// EXIT
//-----------------------------------------------------------------------------

 delete GENOME;
 delete DISPLAY;
 
  return 0;
}
END_OF_MAIN();


