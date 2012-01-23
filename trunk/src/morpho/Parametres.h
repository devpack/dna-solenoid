#ifndef __PARAMETRES_H_
#define __PARAMETRES_H_

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// GLOBAL CONSTANT
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

#define DYNAMIC_VERSION

/*------------------------------ AFFICHE3D CLASS ----------------------------*/

const bool  AFFICHEBOX    = 1;

const float XWORLD        = 350.;
const float YWORLD        = 350.; 
const float ZWORLD        = 350.;

/*--------------------------------- XXX CLASS -------------------------------*/

const int   NBGENOME      = 1;        // Genetic part

const int   ADNSIZE       = 12000;                       // Genome size
const int   NBRESEAUX     = 5;                           // Nb transcription factor
const int   NBGENESPERRESEAUX = 6;                       // Nb crgene for one tf 
const int   NBGENES       = NBRESEAUX*NBGENESPERRESEAUX; // Nb genes total
const int   GENESIZE      = 32;                          // promo, acti, ini, orf

const int   XADNTEX1D     = (int)(ADNSIZE/40);
const int   YADNTEX1D     = 32; 

const float LOOPSIZE      = 1000.0;   // The minimun loop size for the dna (dna curvability)

const float INTERACTLIMIT = 90.0;     // dist 3D < INTERACTLIMIT => no acc
const float LINKLIMIT     = 70.0;     // dist 3D < LINKLIMIT => genes linked
const float DT            = 8.0;     // Step time integration

const float GENEMASS      = 1.0;     // Gene attraction strengh
const float TFMASSE       = 2.0;     // TF attraction strengh

const float ZOOM          = 0.2;      // Display

const bool  CENTRAGE      = 1;
const bool  ROTATE        = 1;

const int   MORPHOTIME    = 150000;

#endif
