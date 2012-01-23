#ifndef __ADN_H_
#define __ADN_H_

#include "Parametres.h"
#include "InitGLmodes.h"
#include "Genes.h"

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ADN
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

class ADN : public MathsVector
{
public:  
        //FILE    *testout;
        GENES   *TheAdn[ADNSIZE]; 
                    
        int     rndtb[NBGENES];
        int     GenesPos1d[NBGENES];
        int     GenesPos1dSorted[NBGENES];     
        int     GenesPos1dType[NBGENES];
        int     GenesPos1dTf[NBGENES];
                
        float   fitness;
        bool    periodic;
                 
public:        
        GLfloat ambient0[4], specular0[4], diffuse0[4];      
        GLfloat ambient1[4], specular1[4], diffuse1[4]; 
        GLfloat ambient2[4], specular2[4], diffuse2[4];
        GLfloat ambient3[4], specular3[4], diffuse3[4];
        GLfloat ambient4[4], specular4[4], diffuse4[4];                                      

        GLuint  TexID;
        BITMAP* Texture_bmp;
                                                                                                            
public: 
        ADN(bool periodic);
        virtual ~ADN();
       
public:    
        void  InitMovePrevious(GENES *igene);
        float InitCalculArcDist(float Dist1d);
        
        void  InitGenesDoubleLinkedChained();
        void  InitTypeandTf();
        void  InitTfActivatedGenes();
        void  PutGenesOnAdn(); 
        void  InitGenesPosRnd();          
        void  InitGenesPos3d();
        void  InitGenesPosPeriodic();
        void  FreeGenesPlace();
};


#endif
