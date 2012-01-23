#include "GA.h"  

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// GArender()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::GArender(ADN *iadn)
{
 if(renderallgenome == 0)
 {
  if(CENTRAGE==1)
   BaryCentrage(iadn);
  
  RenderGenes(iadn);
  RenderLinks(iadn);
  RenderAdn1d(iadn); 
 }
 else
 {
  if(CENTRAGE==1)
   BaryCentrage(iadn);
  
  RenderGenes(iadn);
  RenderLinks(iadn);
  RenderAllGenome();  
 }
 
}
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// BaryCentrage()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::BaryCentrage(ADN *iadn)
{
int i;
Vect3d dr, barycentre;

 barycentre = addv(iadn->TheAdn[iadn->GenesPos1dSorted[0]]->pos, iadn->TheAdn[iadn->GenesPos1dSorted[1]]->pos);
 barycentre = divvs(barycentre, 2.0);        

//-----------------------------------------------------------------------------
// Compute genes pos barycenter
//----------------------------------------------------------------------------- 
                 
 for(i=2; i<NBGENES-1; i++)  
 {   
  barycentre = addv(barycentre, iadn->TheAdn[iadn->GenesPos1dSorted[i]]->pos); 
  barycentre = divvs(barycentre, 2.0);
 } 
 
//-----------------------------------------------------------------------------
// Center all
//----------------------------------------------------------------------------- 

 barycentre = mulvs(barycentre, -1.0);

 for(i=0; i<NBGENES; i++)  
 {   
  iadn->TheAdn[iadn->GenesPos1dSorted[i]]->pos = addv(iadn->TheAdn[iadn->GenesPos1dSorted[i]]->pos, barycentre); 
 }  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// RenderAllGenome()
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::RenderAllGenome()
{
int i;
float rela;

 glMatrixMode(GL_PROJECTION);					
 glPushMatrix();									
 glLoadIdentity();									
 glOrtho(-1,1,-1,1,-1,1);							
 glMatrixMode(GL_MODELVIEW);							
 glPushMatrix();									
 glLoadIdentity();								

 glDisable(GL_LIGHTING);
 glEnable(GL_BLEND);	
 glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 		
 glDisable(GL_DEPTH_TEST);
 
 rela=0.09;
 
 for(i=0; i<NBGENOME; i++)       
 {     
  RenderGenome( AdnPop[i], -0.91+(float)i*rela*2 , -0.95+(float)i*rela*2  );  
  RenderGenome( AdnPopCopy[i], -0.91+rela+(float)i*rela*2 , -0.95+rela+(float)i*rela*2  ); 
 }
    
 glLineWidth(1.0);
      
 // Restore Modes
 glDisable(GL_BLEND);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_LIGHTING);
  
 glMatrixMode(GL_PROJECTION);						
 glPopMatrix();									
 glMatrixMode(GL_MODELVIEW);						
 glPopMatrix();	
}

void GA::RenderGenome(ADN *iadn, float ystart, float ystop)
{
int i;

 glLineWidth(1.0);
 
 // Back
 glColor3f(0.1, 0.1, 0.1);
 glBegin(GL_QUADS);
  glVertex2f(-1.0, ystop);    
  glVertex2f(1.0, ystop);
  glVertex2f(1.0, ystart);                
  glVertex2f(-1.0,ystart);
 glEnd(); 
	 
 glColor3f(0.6, 0.6, 0.6);
 glBegin(GL_LINES);
  glVertex2f(-1.0, ystop);    
  glVertex2f(1.0, ystop);
  glVertex2f(1.0, ystart);                
  glVertex2f(-1.0,ystart);
 glEnd();  

   
 // Vertical Lines
 for(i=0; i<NBGENES; i++)
 { 
  if(iadn->TheAdn[iadn->GenesPos1d[i]]->tf == 0)
    glLineWidth(3.0);
  else
    glLineWidth(5.0);
    
   glBegin(GL_LINES);    
    glColor3f(iadn->TheAdn[iadn->GenesPos1d[i]]->ambient[0], iadn->TheAdn[iadn->GenesPos1d[i]]->ambient[1], iadn->TheAdn[iadn->GenesPos1d[i]]->ambient[2]);
    glVertex2f(((float)iadn->GenesPos1d[i]-((float)ADNSIZE/2.)) / ((float)ADNSIZE/2.), ystop);
    glVertex2f(((float)iadn->GenesPos1d[i]-((float)ADNSIZE/2.)) / ((float)ADNSIZE/2.), ystart);   
   glEnd();  
 }
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// RenderAdn1d(ADN *iadn)
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::RenderAdn1d(ADN *iadn)
{    
int i;

 glMatrixMode(GL_PROJECTION);					
 glPushMatrix();									
 glLoadIdentity();									
 glOrtho(-1,1,-1,1,-1,1);							
 glMatrixMode(GL_MODELVIEW);							
 glPushMatrix();									
 glLoadIdentity();								

 glDisable(GL_LIGHTING);
 glEnable(GL_BLEND);	
 glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 		
 glDisable(GL_DEPTH_TEST);

 // Back
 glColor3f(0.1, 0.1, 0.1);
 glBegin(GL_QUADS);
  glVertex2f(-1.0, -0.95);    
  glVertex2f(1.0, -0.95);
  glVertex2f(1.0, -0.91);                
  glVertex2f(-1.0,-0.91);
 glEnd(); 
	 
 glColor3f(0.6, 0.6, 0.6);
 glBegin(GL_LINES);
  glVertex2f(-1.0, -0.951);    
  glVertex2f(1.0, -0.951);
  glVertex2f(1.0, -0.91);                
  glVertex2f(-1.0,-0.91);
 glEnd();  

   
 // Vertical Lines
 for(i=0; i<NBGENES; i++)
 { 
  if(iadn->TheAdn[iadn->GenesPos1d[i]]->tf == 0)
    glLineWidth(4.0);
  else
    glLineWidth(7.0);
    
   glBegin(GL_LINES);    
    glColor3f(iadn->TheAdn[iadn->GenesPos1d[i]]->ambient[0], iadn->TheAdn[iadn->GenesPos1d[i]]->ambient[1], iadn->TheAdn[iadn->GenesPos1d[i]]->ambient[2]);
    glVertex2f(((float)iadn->GenesPos1d[i]-((float)ADNSIZE/2.)) / ((float)ADNSIZE/2.), -0.95);
    glVertex2f(((float)iadn->GenesPos1d[i]-((float)ADNSIZE/2.)) / ((float)ADNSIZE/2.), -0.91);   
   glEnd();  
 }

 glLineWidth(1.0);
      
 // Restore Modes
 glDisable(GL_BLEND);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_LIGHTING);
  
 glMatrixMode(GL_PROJECTION);						
 glPopMatrix();									
 glMatrixMode(GL_MODELVIEW);						
 glPopMatrix();										
  
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::RenderGenes(ADN *iadn)
{
int i;
GENES *igene;

 for(i=0; i<NBGENES; i++)
 {

 igene = iadn->TheAdn[iadn->GenesPos1dSorted[i]];
  
  glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT  , igene->ambient  );
  glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE  , igene->diffuse  );
  glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR , igene->specular );
  glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, 40.	     );  
  
  glTranslatef(igene->pos.x * ZOOM, igene->pos.y * ZOOM, igene->pos.z * ZOOM); 
  
  	GLUquadricObj *q = gluNewQuadric();

   if (igene->tf == 1) {
   	gluSphere(q, 6.0, 16, 16);
    //glutSolidSphere(6.0,16,16);
	}
   else
   {
   double wid = 5.0;
   double hgt = 5.0;
   double dep = 5.0;

     glBegin(GL_QUADS);
    // Top
    glNormal3d(0,1,0);
    glVertex3d(-wid/2,hgt/2,dep);
    glVertex3d(wid/2,hgt/2,dep);
    glVertex3d(wid/2,hgt/2,0);
    glVertex3d(-wid/2,hgt/2,0);
    // Back
    glNormal3d(0,0,1);
    glVertex3d(-wid/2,hgt/2,dep);
    glVertex3d(-wid/2,-hgt/2,dep);
    glVertex3d(wid/2,-hgt/2,dep);
    glVertex3d(wid/2,hgt/2,dep);
    // Front
    glNormal3d(0,0,-1);
    glVertex3d(-wid/2,hgt/2,0);
    glVertex3d(wid/2,hgt/2,0);
    glVertex3d(wid/2,-hgt/2,0);
    glVertex3d(-wid/2,-hgt/2,0);
    // Left
    glNormal3d(1,0,0);
    glVertex3d(wid/2,hgt/2,0);
    glVertex3d(wid/2,hgt/2,dep);
    glVertex3d(wid/2,-hgt/2,dep);
    glVertex3d(wid/2,-hgt/2,0);
    // Right
    glNormal3d(-1,0,0);
    glVertex3d(-wid/2,hgt/2,dep);
    glVertex3d(-wid/2,hgt/2,0);
    glVertex3d(-wid/2,-hgt/2,0);
    glVertex3d(-wid/2,-hgt/2,dep);
    // Bottom
    glNormal3d(0,-1,0);
    glVertex3d(-wid/2,-hgt/2,dep);
    glVertex3d(-wid/2,-hgt/2,0);
    glVertex3d(wid/2,-hgt/2,0);
    glVertex3d(wid/2,-hgt/2,dep);
  glEnd();
   }
   // glutSolidCube(5.0);
    
  glTranslatef(-igene->pos.x * ZOOM, -igene->pos.y * ZOOM, -igene->pos.z * ZOOM);  
	
 } // end for
 
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------- 
///////////////////////////////////////////////////////////////////////////////

void GA::RenderLinks(ADN *iadn)
{
int i;

 glDisable(GL_LIGHTING);
 glColor3f(0.9, 0.9, 0.0);
  
 glBegin(GL_LINE_STRIP);
 
 for(i=0; i<NBGENES; i++)
  glVertex3f(iadn->TheAdn[iadn->GenesPos1dSorted[i]]->pos.x * ZOOM,  iadn->TheAdn[iadn->GenesPos1dSorted[i]]->pos.y * ZOOM, iadn->TheAdn[iadn->GenesPos1dSorted[i]]->pos.z * ZOOM);
  
 glEnd();
 
 glEnable(GL_LIGHTING); 
 
}
