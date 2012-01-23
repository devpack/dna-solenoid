#include "Genes.h"  

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Constructor & Destructor
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

GENES::GENES(int type, unsigned short tf)
{
int i;

#if defined(DYNAMIC_VERSION)
 for(i=0; i<NBGENESPERRESEAUX-1; i++)
  crgeneslinked[i] = NULL;
#endif
  
 previous   = next = NULL;
 this->tf   = tf;   
 this->type = type;

 for(i=0; i<NBGENESPERRESEAUX-1; i++)
  tfactivatedgenes[i] = NULL;
  
 initcolortable();
  
 pos = clrv(); vel = clrv(); acc = clrv();
  
 if( tf==0 )
  mass = GENEMASS;
 else
  mass = TFMASSE;
}



///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GENES::initcolortable()
{

 switch(type)
 {
   case 0:
   { 
    ambient[0]  = 0.0; ambient[1]  = 1.0; ambient[2]  = 0.0; ambient[3]  = 1.0;
    diffuse[0]  = 0.0; diffuse[1]  = 1.0; diffuse[2]  = 0.0; diffuse[3]  = 1.0;
    specular[0] = 0.0; specular[1] = 1.0; specular[2] = 0.0; specular[3] = 1.0;
   }
   break;
   
   case 1:
   { 
    ambient[0]  = 1.0; ambient[1]  = 0.0; ambient[2]  = 0.0; ambient[3]  = 1.0;
    diffuse[0]  = 1.0; diffuse[1]  = 0.0; diffuse[2]  = 0.0; diffuse[3]  = 1.0;
    specular[0] = 1.0; specular[1] = 0.0; specular[2] = 0.0; specular[3] = 1.0;
   }
   break; 
   
    case 2:
   { 
    ambient[0]  = 1.0; ambient[1]  = 0.0; ambient[2]  = 1.0; ambient[3]  = 1.0;
    diffuse[0]  = 1.0; diffuse[1]  = 0.0; diffuse[2]  = 1.0; diffuse[3]  = 1.0;
    specular[0] = 1.0; specular[1] = 0.0; specular[2] = 1.0; specular[3] = 1.0;
   }
   break; 

    case 3:
   { 
    ambient[0]  = 0.0; ambient[1]  = 0.0; ambient[2]  = 1.0; ambient[3]  = 1.0;
    diffuse[0]  = 0.0; diffuse[1]  = 0.0; diffuse[2]  = 1.0; diffuse[3]  = 1.0;
    specular[0] = 0.0; specular[1] = 0.0; specular[2] = 1.0; specular[3] = 1.0;
   }
   break; 
   
    case 4:
   { 
    ambient[0]  = 0.0; ambient[1]  = 1.0; ambient[2]  = 1.0; ambient[3]  = 1.0;
    diffuse[0]  = 0.0; diffuse[1]  = 1.0; diffuse[2]  = 1.0; diffuse[3]  = 1.0;
    specular[0] = 0.0; specular[1] = 1.0; specular[2] = 1.0; specular[3] = 1.0; 
   }
   break;  
   
    case 5:
   { 
    ambient[0]  = 0.9; ambient[1]  = 0.7; ambient[2]  = 0.4; ambient[3]  = 1.0;
    diffuse[0]  = 0.9; diffuse[1]  = 0.7; diffuse[2]  = 0.4; diffuse[3]  = 1.0;
    specular[0] = 0.9; specular[1] = 0.7; specular[2] = 0.4; specular[3] = 1.0; 
   }
   break;    
 }

}
