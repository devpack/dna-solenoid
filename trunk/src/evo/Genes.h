#ifndef __GENES_H_
#define __GENES_H_

#include "Parametres.h"
#include "InitGLmodes.h"
#include "MathsVector.h" 

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

class GENES : public MathsVector
{
public:
        unsigned short type;
        unsigned short tf;
        
        unsigned short acti;
        unsigned short ini;
        unsigned short promo;
        unsigned short orf;
 
        int      indgenome;
                                                                               
        Vect3d   pos;
        Vect3d   vel;                   
        Vect3d   acc;
        float    mass;

        GLfloat ambient[4], specular[4], diffuse[4]; 
        
        GENES    *tfactivatedgenes[NBGENESPERRESEAUX-1];    // activated gene by tf
        GENES    *previous, *next;
        
#if defined(DYNAMIC_VERSION)
        GENES    *crgeneslinked[NBGENESPERRESEAUX-1];    // linked genes
#endif
                                            
public: 
        GENES(int type, unsigned short tf);
        
        void     initcolortable();
};


#endif
