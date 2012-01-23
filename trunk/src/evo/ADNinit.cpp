#include "ADN.h"


///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// InitGenesDoubleLinkedChained()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::InitGenesDoubleLinkedChained()
{
int i;

 // attention init to NULL for recursion
 for(i=0; i<NBGENES; i++)
 {
  TheAdn[GenesPos1dSorted[i]] -> next = NULL;
  TheAdn[GenesPos1dSorted[i]] -> previous = NULL;  
 }
  
 // next link
 for(i=0; i<NBGENES-1; i++)
  TheAdn[GenesPos1dSorted[i]] -> next = TheAdn[GenesPos1dSorted[i+1]];
  
 // previous link
 for(i=1; i<NBGENES; i++)
  TheAdn[GenesPos1dSorted[i]] -> previous = TheAdn[GenesPos1dSorted[i-1]];  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// InitGenesPos3d()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::InitGenesPos3d()
{
int i;
float theta, phi, R, MaxDist;

 for(i=0; i<NBGENES; i++)
 {
  TheAdn[GenesPos1dSorted[i]]->pos = clrv();
  TheAdn[GenesPos1dSorted[i]]->vel = clrv();
  TheAdn[GenesPos1dSorted[i]]->acc = clrv();
 }
 
 TheAdn[GenesPos1dSorted[0]]->pos = setvs(0.0, 0.0, 0.0); 

 for(i=1; i<NBGENES; i++)
 {
  MaxDist  = (float)GenesPos1dSorted[i] - (float)GenesPos1dSorted[i-1] ;
  R        = xrand(1.0, MaxDist);
  
  theta    = xrand(-PI, PI);            // New pos coord spherique
  phi      = xrand(-PI/2.0, PI/2.0);  
  
  TheAdn[GenesPos1dSorted[i]]->pos = setvs(R*cos(theta)*cos(phi), R*sin(theta)*cos(phi), R*sin(phi)); 
  TheAdn[GenesPos1dSorted[i]]->pos = addv(TheAdn[GenesPos1dSorted[i]]->pos, TheAdn[GenesPos1dSorted[i-1]]->pos);  
  
  InitMovePrevious(TheAdn[GenesPos1dSorted[i]]);
 }
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// InitGenesPosRnd()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::InitGenesPosRnd()
{
int j, k, rnd, cpt;
int zz[ADNSIZE];

 for(j=0; j<ADNSIZE; j++) 
  zz[j]=0;
 
 cpt=0;
 
 do
 {
  rnd = rand()%ADNSIZE; 
 
  if( zz[rnd]!= -1 ) 
  {
   GenesPos1d[cpt] = rnd; 
 
   for(k=0; k<=GENESIZE; k++)
   {
    if(GenesPos1d[cpt]-k >= 0)      zz[GenesPos1d[cpt]-k] = -1;
    if(GenesPos1d[cpt]+k < ADNSIZE) zz[GenesPos1d[cpt]+k] = -1;  
   }
   
  cpt++; 
  }
   
 } while( cpt < NBGENES );
 
 
 /* 
 for(j=0; j<ADNSIZE; j++) 
  zz[j]=j;
  
 permute(zz, ADNSIZE);
 
 for(j=0; j<NBGENES; j++) 
  GenesPos1d[j] = zz[j]; 
 */
 
  
    
/*
int j;

//-----------------------------------------------------------------------------
// Random table : GenesPos1d : 0 < ADNSIZE
//----------------------------------------------------------------------------- 

 GenesPos1d[0] = rand()%ADNSIZE;
    
 for(j=1; j<NBGENES; j++)
 {
   do {
       GenesPos1d[j] = rand()%ADNSIZE;
      } while (GenesPos1d[j] == GenesPos1d[j-1]) ;
 }
*/ 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// InitTypeandTf()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::InitTypeandTf()
{
int i, type;
unsigned short tf;
int rnd=0; 

//-----------------------------------------------------------------------------
// Creation of Genes object at random pos (from random table) on dna
// ------000000~~~~~~:::::: (4 reseaux de 6 genes (en paquet de meme type))
//----------------------------------------------------------------------------- 

 for(i=0; i<NBGENES; i++)
 {
   if( (i%NBGENESPERRESEAUX) == 0 )
    rnd = rand()%NBGENESPERRESEAUX;
    
  type = (int)(i/NBGENESPERRESEAUX); // paquet de NBGENESPERRESEAUX genes
  tf = ( i == (type*NBGENESPERRESEAUX+rnd) ) ? 1 : 0;
  
  GenesPos1dType[i] = type;
  GenesPos1dTf[i]   = tf; 
 }
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// PutGenesOnAdn()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::PutGenesOnAdn()
{
int i, type, k;
unsigned short tf;
int rnd; 
   
 // Free init genes place
 for(i=0; i<ADNSIZE; i++)
  TheAdn[i] = NULL;
    
 // Create and Init Genes from type and tf table
 for(i=0; i<NBGENES; i++)
 {
  TheAdn[GenesPos1d[i]] = new GENES(GenesPos1dType[i],GenesPos1dTf[i]); // build a gene of type l et tf  
 }
 
//-----------------------------------------------------------------------------
// Sort GenesPos1d table to know the real genes's order
//----------------------------------------------------------------------------- 
 
 for(i=0; i<NBGENES; i++)
  GenesPos1dSorted[i] = GenesPos1d[i];
 
 sort(GenesPos1dSorted, NBGENES);
 
 // Mark each gene with it's relative postion on dna, first, second etc ...
 for(i=0; i<NBGENES; i++)
  TheAdn[GenesPos1dSorted[i]]->indgenome = i;  
    
 // Info   
 //for(i=0; i<NBGENES; i++)  
 // fprintf(testout,"%i \n",GenesPos1d[i]);  
 
 //for(i=0; i<NBGENES; i++)  
 // fprintf(testout,"%i \n",GenesPos1dSorted[i]);   
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// InitTfActivatedGenes()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::InitTfActivatedGenes()
{
int j, k, cluster;
 
 for(k=0; k<NBGENES; k++)
 {
  if(GenesPos1dTf[k] == 1)
  {
   cluster = ( (int)(k/NBGENESPERRESEAUX) ) * NBGENESPERRESEAUX;
 
   for(j=0; j<NBGENESPERRESEAUX-1; j++)
   { 
    if(TheAdn[GenesPos1d[cluster]]->tf==0)
    {
     TheAdn[GenesPos1d[k]]->tfactivatedgenes[j] = TheAdn[GenesPos1d[cluster]];
     cluster++;
    }
    else
    {
     j--;
     cluster++;
    } 
   }
   
  } // if Tf
  
 } // for NBGENES
  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// PeriodiqueInitGenesOnAdn()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void ADN::InitGenesPosPeriodic()
{ 
int i, j;
int interval;
int first;

 interval = ADNSIZE / NBGENESPERRESEAUX;
 
 for(i=0; i<NBRESEAUX; i++) 
  for(j=0; j<NBGENESPERRESEAUX; j++) 
  {
   GenesPos1d[i*NBGENESPERRESEAUX] = 0 + i*(interval/NBRESEAUX);
   first = GenesPos1d[i*NBGENESPERRESEAUX];
   
   GenesPos1d[j+i*NBGENESPERRESEAUX] = j*interval + first;    
  }
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// InitMovePrevious(GENES *igene)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////
// Move ALL previous according to min dist and move ONE previous for max dist

void ADN::InitMovePrevious(GENES *igene)
{
GENES  *previousgene;
Vect3d dr, drapproche, dreloigne;
float  dr2, drabs, dr1d, drtrop, minarcdist;

 if(igene->previous != NULL)  // if non first gene
 { 
  previousgene = igene->previous;     
  
  while(previousgene != NULL) // For all previous neighbours 
  { 
   // Calcul dist 3D et dist 1D de igene et de SES previous voisin 
   dr             = subv( previousgene->pos, igene->pos);
   dr2            = dotvp(dr, dr);
   drabs          = sqrt(dr2);
    
   dr1d = ABS( (float)(GenesPos1dSorted[igene->indgenome] -
                       GenesPos1dSorted[previousgene->indgenome]) );
           
    // Distance MIN 
    if( dr1d < LOOPSIZE) // inside a boucle
    {
     minarcdist = InitCalculArcDist(dr1d);
    
     if ( drabs < minarcdist ) // too close
     {
      drtrop = minarcdist - drabs ; 
      drabs = (drabs==0) ? 0.000001 : drabs;      
      dreloigne = mulvs ( divvs(dr,drabs) , drtrop) ;
      previousgene->pos = addv(previousgene->pos, dreloigne);    
     }
    }
     
    previousgene = previousgene->previous;                // previousgene gene en 1D
 
   } // (while) for all previous neighbours   
   
   // ------------------------------
   // Max dist, only for 1 neighbour
   // ------------------------------
   previousgene = igene->previous;  

   dr             = subv( previousgene->pos, igene->pos);
   dr2            = dotvp(dr, dr);
   drabs          = sqrt(dr2);
    
   dr1d = ABS( (float)(GenesPos1dSorted[igene->indgenome] -
                       GenesPos1dSorted[previousgene->indgenome]) );
          
    if( drabs > dr1d ) // too far
    {
     drtrop = drabs - dr1d;  
     drtrop = (drtrop < 1) ? 1.0 : drtrop;          
     drapproche = mulvs ( divvs(dr,-drabs) , drtrop) ;
     previousgene->pos = addv(previousgene->pos, drapproche);
    }  
                    
  } // if non first gene

}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// InitCalculArcDist(float Dist1d)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

// Compute arc distance in function of the linéar distance
float ADN::InitCalculArcDist(float Dist1d)
{
float angleaucentre;
float rayon = LOOPSIZE / _2PI;

 angleaucentre = (_2PI * Dist1d) / LOOPSIZE;
 angleaucentre = (angleaucentre > PI) ? _2PI - angleaucentre : angleaucentre;
 angleaucentre /= 2.0;
 
 return ( (float) ABS( 2.0*rayon*sin(angleaucentre) ));
}

