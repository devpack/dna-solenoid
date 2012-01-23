#include "GA.h"

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Constructor & Destructor
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

GA::GA()
{
int i;

 xrand(0.0, 1000.0);                                        // fix 1er rand bug

 for(i=0; i<NBGENOME; i++)
 {   
  AdnPop[i] = new ADN(1);
  AdnPopCopy[i] = new ADN(1);
 } 
 //AdnPop[0] = new ADN(1); 

 GAInitAdnPopCopy();
   
 for(i=0; i<NBGENOME; i++)
 {  
  fitnessind[i] = i;
  fitnessindcopy[i] = i;  
 }
 
 renderallgenome=0;
 cycle=0;  
 morphostep=0;
 testout=fopen("testoutput.txt","w"); 
}

GA::GA(char *initfilename)
{
int i;

 xrand(0.0, 1000.0);                                        // fix 1er rand bug

 GAInitAdnPop(initfilename);  // init AdnPop from file

 for(i=0; i<NBGENOME; i++)
  AdnPopCopy[i] = new ADN(0);

 GAInitAdnPopCopy();          // Copy + transpose AdnPop -> AdnPopCopy
   
 for(i=0; i<NBGENOME; i++)
 {  
  fitnessind[i] = i;
  fitnessindcopy[i] = i;  
 }
 
 renderallgenome=0;
 cycle=0;  
 morphostep=0;
 testout=fopen("testoutput.txt","w"); 
}

GA::~GA()
{ 
int i;

 fclose(testout);
  
 for(i=0; i<NBGENOME; i++)
 {
  delete AdnPop[i];   
  delete AdnPopCopy[i]; 
 } 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// GAInitAdnPop()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::GAInitAdnPop(char *initfilename)
{
int i;

 if ( (inputfile = fopen(initfilename, "r+"))==NULL )
  { fprintf(stderr, "inputfile Error \n" ); exit(1); }
  
  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// GAInitAdnPopCopy()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::GAInitAdnPopCopy()
{
int i, k, j;
 
 for(i=0; i<NBGENOME; i++)
  GAcopy(AdnPop[i], AdnPopCopy[i]);

 for(i=0; i<NBGENOME; i++)
  GAtranspose(AdnPopCopy[i]);

 for(i=0; i<NBGENOME; i++)    
 {           
  AdnPopCopy[i]->InitGenesPos3d();   
                
#if defined(DYNAMIC_VERSION)
   for(k=0; k<NBGENES; k++)   
    for(j=0; j<NBGENESPERRESEAUX-1; j++)
     AdnPopCopy[i]->TheAdn[AdnPopCopy[i]->GenesPos1dSorted[k]]->crgeneslinked[j] = NULL;
#endif
 }    
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// GAmain()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

 /*
 for(k=0; k<NBGENES; k++)
 {
    cl = (int)(k/NBGENESPERRESEAUX);
    
  if(AdnPop[0]->GenesPos1dTf[k] == 1)
  {
   for(j=0; j<NBGENESPERRESEAUX-1; j++)
    fprintf(testout,"%i \n",AdnPop[0]->TheAdn[AdnPop[0]->GenesPos1d[k]]->tfactivatedgenes[j]); 
   
    fprintf(testout,"\n");   
   for(j=cl*NBGENESPERRESEAUX; j<cl*NBGENESPERRESEAUX+NBGENESPERRESEAUX; j++)
    fprintf(testout,"%i \n",AdnPop[0]->GenesPos1dTf[j]);   

    fprintf(testout,"\n");   
   for(j=cl*NBGENESPERRESEAUX; j<cl*NBGENESPERRESEAUX+NBGENESPERRESEAUX; j++)
    fprintf(testout,"%i \n",AdnPop[0]->TheAdn[AdnPop[0]->GenesPos1d[j]]); 
    
    fprintf(testout,"\n");                 
  }
  
 }
 
exit(1);
 */
 
void GA::GAmain()
{
int i, k, j, cl;
    
 if (key[KEY_F1]) renderallgenome=1;
 if (key[KEY_F2]) renderallgenome=0;

 // Stop motion
 if (!key[KEY_LCONTROL])
 {      
 
  if( morphostep < MORPHOTIME )
  {
   for(i=0; i<NBGENOME; i++)   
   {
    Morphogenese(AdnPop[i]);
    Morphogenese(AdnPopCopy[i]);
   } 
  }
  else
  { 
   GAcore();
  
   cycle++;
   morphostep=0;
  }
  
  morphostep++; 
 }
    
    
 GArender(AdnPop[0]); // render the best morpho anim
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Gacore()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::GAcore()
{
int i, j, k; 
  
//-----------------------------------------------------------------------------
// Calcul Fitness + Sort individu
//----------------------------------------------------------------------------- 
 
 for(i=0; i<NBGENOME; i++)
 {  
  CalculFitness(AdnPop[i]);
  CalculFitness(AdnPopCopy[i]);  
 }
     
 //for(i=0; i<NBGENOME; i++)
 //{
 // fitnesstb[i] = AdnPop[i]->fitness; 
 // fitnesstbcopy[i] = AdnPopCopy[i]->fitness;   
 //}
    
 //sort_ind(fitnesstb, fitnessind, NBGENOME);       // sort ordre croissant

//-----------------------------------------------------------------------------
// GA : Do NBGENOME mutated best
//----------------------------------------------------------------------------- 
 
 for(i=0; i<NBGENOME; i++)
 {
  if( AdnPop[i]->fitness > AdnPopCopy[i]->fitness )
  {
   GAcopy( AdnPopCopy[i], AdnPop[i] );
   fprintf(testout,"%f \n",AdnPopCopy[0]->fitness);   
  } 
  else
  fprintf(testout,"%f \n",AdnPop[0]->fitness);   
 }
 
 for(i=0; i<NBGENOME; i++)
  delete AdnPopCopy[i];
 
 for(i=0; i<NBGENOME; i++)
  AdnPopCopy[i] = new ADN(0);
  
 for(i=0; i<NBGENOME; i++)
  GAcopy(AdnPop[i], AdnPopCopy[i]);

 for(i=0; i<NBGENOME; i++)
  GAtranspose(AdnPopCopy[i]);
     
//-----------------------------------------------------------------------------
// Rebuild 3D Pos + clear linked genes
//-----------------------------------------------------------------------------    
  
 for(i=0; i<NBGENOME; i++)    
 {           
  AdnPop[i]->InitGenesPos3d();   
                
#if defined(DYNAMIC_VERSION)
   for(k=0; k<NBGENES; k++)   
    for(j=0; j<NBGENESPERRESEAUX-1; j++)
     AdnPop[i]->TheAdn[AdnPop[i]->GenesPos1dSorted[k]]->crgeneslinked[j] = NULL;
#endif     
 } 

 for(i=0; i<NBGENOME; i++)    
 {           
  AdnPopCopy[i]->InitGenesPos3d();                 

#if defined(DYNAMIC_VERSION)
   for(k=0; k<NBGENES; k++)   
    for(j=0; j<NBGENESPERRESEAUX-1; j++)
     AdnPopCopy[i]->TheAdn[AdnPopCopy[i]->GenesPos1dSorted[k]]->crgeneslinked[j] = NULL;
#endif      
 } 
 
//-----------------------------------------------------------------------------
// Write infos
//----------------------------------------------------------------------------- 

// for(i=0; i<NBGENOME; i++)  
//  fprintf(testout,"%f \n",AdnPop[i]->fitness); 
    
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// GAcopy()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::GAcopy(ADN *iadn, ADN *jadn)
{
int k;

  jadn->FreeGenesPlace();                     // Free former Genes object
   
  for(k=0; k<NBGENES; k++)
  { 
   jadn->GenesPos1d[k]     = iadn->GenesPos1d[k];     // Copy genes pos table
   jadn->GenesPos1dType[k] = iadn->GenesPos1dType[k]; // Copy genes type table
   jadn->GenesPos1dTf[k]   = iadn->GenesPos1dTf[k];   // Copy genes tf table      
  }
   
  jadn->PutGenesOnAdn();                      // Create new Genes object + GenesPos1dSorted
  jadn->InitTfActivatedGenes();
  jadn->InitGenesDoubleLinkedChained();
  
  //jadn->InitGenesPos3d()();                 // No need car did by GAcore
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// GAtranspose()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::GAtranspose(ADN *iadn)
{
int i, k, cpt, out, oldpos, newpos;


 // a gene place
 do
 {
  oldpos = rand()%(ADNSIZE-1); 
 } while ( iadn->TheAdn[oldpos]== NULL );
 
 // an empty place with neighbours respect
 i=0; 
 do
 {
  cpt=0;
  out=0;
  newpos = rand()%(ADNSIZE-1); 
  
   for(k=0; k<=GENESIZE; k++)
   {
    if( newpos-k >= 0) 
    {
     if( iadn->TheAdn[newpos-k] == NULL )
      cpt++;
    }
    else
     out++;
       
    if( newpos+k < ADNSIZE)
    { 
     if( iadn->TheAdn[newpos+k] == NULL )    
      cpt++;
    }
    else
     out++;
           
   } 
 
  if( cpt == (GENESIZE+1)*2 - out )
   i=1;  
    
 } while ( i==0 );
 
 
 // new ptr
 iadn->TheAdn[newpos] = iadn->TheAdn[oldpos];
 iadn->TheAdn[oldpos]  = NULL;  

 // Rebuild Tables
 i=0;
 while( iadn->GenesPos1d[i] != oldpos)
 { i++; } 
 iadn->GenesPos1d[i] = newpos;
 
 i=0;
 while( iadn->GenesPos1dSorted[i] != oldpos)
 { i++; }
 iadn->GenesPos1dSorted[i] = newpos;               

 // Rebuild GenesPos1dSorted + DoubleLinkedChained
 sort(iadn->GenesPos1dSorted, NBGENES); 
 iadn->InitGenesDoubleLinkedChained();  // double linked chaine (!must be sorted)
 
}
 
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// CalculFitness()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

float GA::CalculFitness(ADN *iadn)
{
int i,j;
Vect3d dr;
float  dr2, drabs;
  
 iadn->fitness = 0.0; 
           
 for(i=0; i<NBGENES; i++)
 {
  if( iadn->TheAdn[iadn->GenesPos1d[i]]->tf == 1)
  {
   for(j=0; j<NBGENESPERRESEAUX-1; j++)
   { 
    dr    = subv( iadn->TheAdn[iadn->GenesPos1d[i]]->tfactivatedgenes[j]->pos,
                  iadn->TheAdn[iadn->GenesPos1d[i]]->pos );
                  
    dr2   = dotvp(dr, dr);
    drabs = sqrt(dr2);  
    iadn->fitness += drabs;
    //iadn->fitness += dr2;                   
   }
   
  } // if tf
 } // test all for tf              
 
 iadn->fitness /= (float)(NBGENESPERRESEAUX-1); 
 return(iadn->fitness);
}


/*
float GA::CalculFitness(ADN *iadn)
{
int i,j;
Vect3d dr;
float  dr2, drabs;
  
 iadn->fitness = 0.0; 
           
 for(i=0; i<NBRESEAUX; i++)  
  for(j=1; j<NBGENESPERRESEAUX; j++)
  {   
   dr     = subv( iadn->TheAdn[iadn->GenesPos1d[i*NBGENESPERRESEAUX]]->pos, 
                  iadn->TheAdn[iadn->GenesPos1d[(i*NBGENESPERRESEAUX)+j]]->pos);
   dr2    = dotvp(dr, dr);
   drabs  = sqrt(dr2);
   iadn->fitness += drabs;
   //iadn->fitness += dr2;   
  } 

 iadn->fitness /= (float)(NBGENESPERRESEAUX-1);    
 
 return(iadn->fitness);
}
*/

