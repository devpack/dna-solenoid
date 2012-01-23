#include "ADN.h"  

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Constructor & Destructor
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

ADN::ADN(bool periodic)
{
int i;

 //testout=fopen("testoutput.txt","w");                       // test file

 this->periodic = periodic;
 
 for(i=0; i<NBGENES; i++)
  rndtb[i]=i; 

 Texture_bmp = create_bitmap(XADNTEX1D, YADNTEX1D);

 if( periodic == 1)
  InitGenesPosPeriodic(); 
 else
  InitGenesPosRnd();

 InitTypeandTf();                                // ! tjrs before putGenesOnAdn()
 
 PutGenesOnAdn();                                // init genes's position on dna et sort
 InitTfActivatedGenes();                         // init tfactivatedgenes (GENES *)
 InitGenesDoubleLinkedChained();                 // double linked chaine (!must be sorted)
 
 InitGenesPos3d();                               // init 3D gene position
}


ADN::~ADN()
{  
int i;

 destroy_bitmap(Texture_bmp);
 //fclose(testout);

 FreeGenesPlace();
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// FreeGenesPlace()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::FreeGenesPlace()
{
int i;

 for(i=0; i<NBGENES; i++)
  delete TheAdn[GenesPos1d[i]];
}
