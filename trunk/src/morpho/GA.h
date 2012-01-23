#ifndef __GA_H_
#define __GA_H_

#include "ADN.h"

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

class GA : public MathsVector
{
public: 
        FILE    *testout;
        FILE    *inputfile;
        
        ADN     *AdnPop[NBGENOME]; 
        float   fitnesstb[NBGENOME];
        int     fitnessind[NBGENOME];
                
        ADN     *AdnPopCopy[NBGENOME]; 
        float   fitnesstbcopy[NBGENOME];
        int     fitnessindcopy[NBGENOME];                
        
        int     cycle;
        int     morphostep;
        bool    renderallgenome;
        
public: 
        GA();
        GA(char *initfile);
        virtual ~GA();
                
public:  
        void  GAmain();
        void  GAInitAdnPop(char *initfilename);        
        void  GAInitAdnPopCopy();
        void  GAcopy(ADN *iadn, ADN *jadn);         
        void  GAcore();
        void  GAtranspose(ADN *iadn);
        void  BaryCentrage(ADN *iadn);        
        float CalculFitness(ADN *iadn);
               
        void  Morphogenese(ADN *iadn);               
        void  Interaction(ADN *iadn, GENES *igene, int num);  
        void  LinkCloseCrGenes(ADN *iadn, GENES *igene, int num);
        void  CrgEffectiveLink(ADN *iadn);
         
        void  MovePrevious(ADN *iadn, GENES *igene);
        void  MoveNext(ADN *iadn, GENES *igene);        
        float CalculArcDist(float Dist1d);     

        void  GArender(ADN *iadn);         
        void  RenderGenes(ADN *iadn);
        void  RenderLinks(ADN *iadn);   
        void  RenderAdn1d(ADN *iadn);   
        void  RenderAllGenome();   
        void  RenderGenome(ADN *iadn, float ystart, float ystop);                           
};


#endif
