#include "GA.h"


#if defined(DYNAMIC_VERSION) // <---------------------- FOR ! DYNAMIC VERSION !

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Morphogenese()  ! DYNAMIC VERSION !
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::Morphogenese(ADN *iadn)
{
int    i, dnagenepos;
Vect3d dvel, dpos;
GENES  *igene;

 permute(iadn->rndtb, NBGENES);    // for all genes in rnd order
 
//-----------------------------------------------------------------------------
// Compute who is link whith who (: close enough crgenes)
//-----------------------------------------------------------------------------  

 for(i= 0; i < NBGENES; i++) // Link gene's pointers
 { 
  dnagenepos = iadn->GenesPos1d[iadn->rndtb[i]];
  igene      = iadn->TheAdn[dnagenepos];
  
  LinkCloseCrGenes(iadn, igene, dnagenepos);
 }
   
 CrgEffectiveLink(iadn);          // Move them toghether  
  
//-----------------------------------------------------------------------------
// Leap Frog + CheckDistance + Interaction | for all gene (rnd order)
//----------------------------------------------------------------------------- 

 for(i= 0; i < NBGENES; i++)
 {
  dnagenepos = iadn->GenesPos1d[iadn->rndtb[i]];
  igene      = iadn->TheAdn[dnagenepos];
  
//-----------------------------------------------------------------------------
// Leap Frog part 1 => new gene's position
//----------------------------------------------------------------------------- 

  dvel       = mulvs(igene->acc, 0.5 * DT);
  igene->vel = addv (igene->vel, dvel);
  dpos       = mulvs(igene->vel, DT);
  igene->pos = addv (igene->pos, dpos);
  
//-----------------------------------------------------------------------------
// Check distance rules
//----------------------------------------------------------------------------- 
  
  MovePrevious(iadn, igene);
  MoveNext(iadn, igene);
    
//-----------------------------------------------------------------------------
// Compute interaction of gene i with others crgenes (same familly)
//----------------------------------------------------------------------------- 
  
  Interaction(iadn, igene, dnagenepos);
    
//-----------------------------------------------------------------------------
// Leap Frog part 2
//----------------------------------------------------------------------------- 

  dvel       = mulvs(igene->acc, 0.5 * DT);
  igene->vel = addv (igene->vel, dvel);
  igene->acc = clrv();
  
  
 } // for all gene
    
}


///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Interaction(GENES *igene, int num)  ! DYNAMIC VERSION !
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

// Calcul les interactions du gene i avec les autres genes de sa famille
void GA::Interaction(ADN *iadn, GENES *igene, int num)
{
int j;
int indstartfamille;
Vect3d dr;
Vect3d acci;
float  dr2, drabs, phii;

 indstartfamille = (igene->type ) * NBGENESPERRESEAUX; // 1er indice de la famille ds GenesPos1d

  // for all crgenes in one familly
  for(j = indstartfamille; j < (indstartfamille + NBGENESPERRESEAUX) ; j++) 
  {
   if(num!=iadn->GenesPos1d[j]) // no self interaction
   { 
    dr    = subv(iadn->TheAdn[iadn->GenesPos1d[j]]->pos, igene->pos);
    dr2   = dotvp(dr, dr);

    if( dr2 > INTERACTLIMIT*INTERACTLIMIT)
    {
     drabs = sqrt(dr2);
     phii  = (iadn->TheAdn[iadn->GenesPos1d[j]]->mass)/(drabs*dr2);  
     //phii = (phii > 0.0000001) ? 0.0000001 : phii;     // Calm
     
     acci  = mulvs(dr, phii);  
     igene->acc = addv (igene->acc, acci );
    }
         
   } // if not self interact
  } // for for 
 
}


///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// CrgEffectiveLink()  ! DYNAMIC VERSION !
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::CrgEffectiveLink(ADN *iadn)
{
int i, k;
float  theta, phi, R;
Vect3d dr, drapproche;
float  dr2, drabs, drtrop;
GENES  *igene, *linkedgene;

 for(i= 0; i < NBGENES; i++)
  for(k= 0; k < NBGENESPERRESEAUX-1; k++)
  {
   igene      = iadn->TheAdn[iadn->GenesPos1d[i]];                     // current gene
   linkedgene = iadn->TheAdn[iadn->GenesPos1d[i]]->crgeneslinked[k];   // linked gene
   
   if( linkedgene != NULL ) // if linked, i.e. if linked gene exist
   {
   
   // linked = same pos
   igene->pos = addv(igene->pos, linkedgene->pos);
   igene->pos = divvs(igene->pos, 2.0);
   linkedgene->pos = igene->pos;      
   
    /*  
    dr    = subv( linkedgene->pos, igene->pos);  
    dr2   = dotvp(dr, dr);
    drabs = sqrt(dr2);
    
     if( drabs > LINKLIMIT )
     {
      drtrop = drabs - LINKLIMIT;         
      drapproche = mulvs ( divvs(dr,+drabs) , drtrop ) ;
      igene->pos = addv(igene->pos, drapproche); 
     }
    */
    
   } // if linked
   
  } // for for
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// LinkCloseCrGenes(GENES *igene, int num)  ! DYNAMIC VERSION !
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::LinkCloseCrGenes(ADN *iadn, GENES *igene, int num)
{
int    j, i, k;
Vect3d dr;
float  drabs;
int    indstartfamille;
bool   linked;
GENES *linkedgene;

 indstartfamille = (igene->type ) * NBGENESPERRESEAUX; // 1er indice de la famille ds GenesPos1d

  // for all crgenes in one familly
  for(j = indstartfamille; j < (indstartfamille + NBGENESPERRESEAUX) ; j++) 
  {
   if(num!=iadn->GenesPos1d[j]) // no self linking
   {
    linkedgene = iadn->TheAdn[iadn->GenesPos1d[j]];
    
    dr    = subv(linkedgene->pos, igene->pos);
    drabs = sqrt( dotvp(dr, dr) );
    
    // Already linked ? 
    linked=FALSE;
     for(k=0; k < NBGENESPERRESEAUX-1 ; k++) 
      if( igene -> crgeneslinked[k] == linkedgene )
       linked=TRUE;
    
     // Do the link ?
     if( drabs<LINKLIMIT && linked==FALSE) // close enought to be linked
     {
      i=0;
       while( igene->crgeneslinked[i]!=NULL) // first free place
       { i++; }
      igene->crgeneslinked[i] = linkedgene;
     }
    
   } // if no self linking
   
  } // for all crgenes in familly
  
}

#else // <--------------------------------------------- FOR ! DYNAMIC VERSION !

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Morphogenese()  ! NON DYNAMIC VERSION !
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::Morphogenese(ADN *iadn)
{
int    i, dnagenepos;
Vect3d dvel, dpos;
GENES  *igene;

 permute(iadn->rndtb, NBGENES);    // for all genes in rnd order
 
 for(i= 0; i < NBGENES; i++)
 {
  dnagenepos = iadn->GenesPos1d[iadn->rndtb[i]];
  igene      = iadn->TheAdn[dnagenepos];
      
//-----------------------------------------------------------------------------
// Compute interaction of gene i with others crgenes (same familly)
//----------------------------------------------------------------------------- 
  
  Interaction(iadn, igene, dnagenepos);

//-----------------------------------------------------------------------------
// Check distance rules
//----------------------------------------------------------------------------- 

  MovePrevious(iadn, igene);
  MoveNext(iadn, igene);


 } // for all gene
  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Interaction(GENES *igene, int num) ! NON DYNAMIC VERSION !
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

// Calcul les interactions du gene i avec les autres genes de sa famille
void GA::Interaction(ADN *iadn, GENES *igene, int num)
{
int j;
int indstartfamille;
Vect3d dr, dpos;
float  dr2, drabs, attract_coef;

 indstartfamille = (igene->type ) * NBGENESPERRESEAUX; // 1er indice de la famille ds GenesPos1d

  for(j = indstartfamille; j < (indstartfamille + NBGENESPERRESEAUX) ; j++) 
  {
   if(num!=iadn->GenesPos1d[j]) // no self interaction
   { 
    dr    = subv(iadn->TheAdn[iadn->GenesPos1d[j]]->pos, igene->pos);
    dr2   = dotvp(dr, dr);
    drabs = sqrt(dr2);
    
    if(drabs>20.0)
    {
     attract_coef = (iadn->TheAdn[iadn->GenesPos1d[j]]->mass)/(drabs*dr2);  
     attract_coef = (attract_coef > 1) ? 1 : attract_coef;
     
     //attract_coef *= 1.0;
     dpos  = mulvs(dr, attract_coef);  

     igene->pos = addv (igene->pos, dpos );
    }
      
   } // if not self interact
  } // for for 
  
}


#endif // <-------------------------------------------- FOR ! DYNAMIC VERSION !


///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// MovePrevious(GENES *igene)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////
// Move ALL previous according to min dist and move ONE previous for max dist

void GA::MovePrevious(ADN *iadn, GENES *igene)
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
    
   dr1d = ABS( (float)(iadn->GenesPos1dSorted[igene->indgenome] -
                       iadn->GenesPos1dSorted[previousgene->indgenome]) );
           
    // Distance MIN 
    if( dr1d < LOOPSIZE) // inside a boucle
    {
     minarcdist = CalculArcDist(dr1d);
    
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
    
   dr1d = ABS( (float)(iadn->GenesPos1dSorted[igene->indgenome] -
                       iadn->GenesPos1dSorted[previousgene->indgenome]) );
          
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
// MoveNext(GENES *igene)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////
// Move ALL next according to min dist and move ONE next for max dist

void GA::MoveNext(ADN *iadn, GENES *igene)
{
GENES  *nextgene;
Vect3d dr, drapproche, dreloigne;
float  dr2, drabs, dr1d, drtrop, minarcdist; 
 
 if(igene->next != NULL)  // if non last gene
 { 
  nextgene = igene->next;     
  
  while(nextgene != NULL) // For all nexts neighbours 
  {
   // Calcul dist 3D et dist 1D de igene et de SES next voisin 
   dr             = subv( nextgene->pos, igene->pos);
   dr2            = dotvp(dr, dr);
   drabs          = sqrt(dr2);
    
   dr1d = ABS( (float)(iadn->GenesPos1dSorted[igene->indgenome] -
                       iadn->GenesPos1dSorted[nextgene->indgenome]) );
             
    // Distance MIN 
    if( dr1d < LOOPSIZE) // inside a boucle
    {
     minarcdist = CalculArcDist(dr1d);
    
     if ( drabs < minarcdist ) // too close
     {
      drtrop = minarcdist - drabs ; 
      drabs = (drabs==0) ? 0.000001 : drabs;      
      dreloigne = mulvs ( divvs(dr,drabs) , drtrop) ;
      nextgene->pos = addv(nextgene->pos, dreloigne);    
     }
    }
           
   nextgene = nextgene->next;                               // next gene en 1D
 
   } // (while) for all next neighbours  
   
   // ------------------------------
   // Max dist, only for 1 neighbour
   // ------------------------------
   nextgene = igene->next; 
   
   dr             = subv( nextgene->pos, igene->pos);
   dr2            = dotvp(dr, dr);
   drabs          = sqrt(dr2);
    
   dr1d = ABS( (float)(iadn->GenesPos1dSorted[igene->indgenome] -
                       iadn->GenesPos1dSorted[nextgene->indgenome]) );
               
    if( drabs > dr1d ) // too far
    {
     drtrop = drabs - dr1d;     
     drtrop = (drtrop < 1) ? 1.0 : drtrop;          
     drapproche = mulvs ( divvs(dr,-drabs) , drtrop) ;
     nextgene->pos = addv(nextgene->pos, drapproche);
    }    
      
  } // if non last gene
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// CalculArcDist(float Dist1d)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

// Compute arc distance in function of the linéar distance
float GA::CalculArcDist(float Dist1d)
{
float angleaucentre;
float rayon = LOOPSIZE / _2PI;

 angleaucentre = (_2PI * Dist1d) / LOOPSIZE;
 angleaucentre = (angleaucentre > PI) ? _2PI - angleaucentre : angleaucentre;
 angleaucentre /= 2.0;
 
 return ( (float) ABS( 2.0*rayon*sin(angleaucentre) ));
}
