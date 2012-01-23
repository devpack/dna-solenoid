#ifndef __INITPLAYFIELD_H_
#define __INITPLAYFIELD_H_

#include <allegro.h>
#include <alleggl.h>
#include "stdio.h"
#include "math.h"

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

class InitPlayfield
{
public:
       static const int   ScrW;
       static const int   ScrH;
       static int         GFXOPENARG;
       PALETTE            palette;
       
public:
       InitPlayfield(int GFXOPENARG, int ScrW, int ScrH);
       virtual ~InitPlayfield();
       
       void dothepalette();       
};



#endif


