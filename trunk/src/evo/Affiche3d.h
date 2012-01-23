#ifndef __AFFICHE3D_H_
#define __AFFICHE3D_H_

#include "Parametres.h"
#include "InitGLmodes.h"
#include "Camera.h"
#include "GA.h"

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

class Affiche3D : public InitGLmodes, public Camera
{
public: 
       char buffer[50];    
       
public:
       Affiche3D(int GFXOPENARG, int ScrW, int ScrH);
       virtual ~Affiche3D();

public: 
       void Render();   
       void AfficheBox();   
};

#endif
