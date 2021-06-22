#include <stdio.h>
#include <cmath>
#include <GL/glut.h>

bool flag = false;
static float fRotAngle = -60.0f; 
GLdouble znear = 4.0;
int i = 0; 
int j = 0;
int k = 0;
int b = 0;
int maxBrKuglica = 12;


void kuglica(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix(); 
	glTranslatef( x,y,z ); 
	glRotatef( fRotAngle, 1.0f, 0.0f, 1.0f ); 
	glutWireSphere(0.5,8,8); 
	glPopMatrix(); 
}

GLfloat xleft = -5.5;
GLfloat alpha = 0;
int masa = 6;

void Redraw(){
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	glFrustum( -2.0f, 2.0f, -2.0f, 2.0f, znear, 40.0f );
	glMatrixMode(GL_MODELVIEW); 
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ); 
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, -10.0f );
	glRotatef( fRotAngle/6, 1.0f, 0.0f, 1.0f );
	glutWireSphere(10,12,12);
	glPopMatrix();
	for(int i=0; i<maxBrKuglica; i++) kuglica(xleft+i,sin(0.035*(alpha+i*30.0)),0);
	fRotAngle+= 0.5f; if(fRotAngle>masa*360.0) fRotAngle = 0;
	glutSwapBuffers(); 
}
void Redraw2(){
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	glFrustum( -2.0f, 2.0f, -2.0f, 2.0f, znear, 40.0f );
	glMatrixMode(GL_MODELVIEW);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt( 0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, -10.0f );
	glRotatef( fRotAngle/6, 1.0f, 0.0f, 1.0f );
	glutWireSphere(10,12,12);
	glPopMatrix();
	for(int i=0; i<maxBrKuglica; i++) kuglica(sin(0.035*(alpha+i*30.0)),xleft+i,0);
	fRotAngle+= 0.5f; if(fRotAngle>masa*360.0) fRotAngle = 0;
	glutSwapBuffers(); 
}


void Timer( int iValue ){
	glutPostRedisplay(); 
	glutTimerFunc( 1, Timer, iValue ); 
}

void Keyboard( unsigned char uKey, int x, int y ){
	switch ( uKey ){
		case 0x1B: exit( 0 );break; 
		case 'q' : znear+=0.1;break;
		case 'a' : znear-=0.1;break;
		case 'w' : alpha+=3.0f;break;
		case 's' : alpha-=3.0f;break;
		case '1' : 
			if (maxBrKuglica > 0){
				maxBrKuglica--; 
			}
			break;
		case '2' : 
			if (maxBrKuglica < 12){
				maxBrKuglica++; 
			}
			break;
	}
	if (uKey == 'b')
	{
		b++;
		if (b == 1)
		{
			glutTimerFunc( 1, Timer, 50 );
		}
		if (b > 1)
		{
			b=0;
		}
	}
	if (uKey == 'n')
	{
		k++;
		if (k == 1)
		{
			glutDisplayFunc( Redraw2 );
		}
		if (k > 1)
		{
			k = 0;
			glutDisplayFunc( Redraw );
		}
	}
	if (uKey == 'c')
	{
		i++;
		if (i == 1)
		{
			glClearColor(0.0, 1.0, 1.0, 0.0);
			Redraw();
		}
		if (i == 2)
		{
			i = 2;
			glClearColor(1.0, 0.5, 0.0, 0.0);
			Redraw();
		}
		if (i > 2)
		{
			i = 0;
			glClearColor(0.0, 0.0, 0.0, 0.0);
			Redraw();
		}
	}
	if (uKey == 'v')
	{
		j++;
		if (j == 1)
		{
			glColor3f(0.0,0.0,1.0); 
			Redraw();
		}
		if (j == 2)
		{
			j = 2;
			glColor3f(1.0,0.0,0.0);
			Redraw();
		}
		if (j > 2)
		{
			j = 0;
			glColor3f(1.0,1.0,1.0);
			Redraw();
		}
	}
}

void KonzolniTekst(){
	printf("\nPROJEKAT KUGLICE\n");
	printf("\nB - pokreni sve kuglice\n");
	printf("\nQ - uvecavaj sve kuglice\n");
	printf("\nA - smanjuj sve kuglice\n");
	printf("\nW - kretanje kuglica naizmenico s leva na desno\n");
	printf("\nS - kretanje kuglica naizvmenicno s desna na levo\n");
	printf("\nN - promeni koordinatnu osu kuglicama\n");
	printf("\nC - promeni pozadinsku boju\n");
	printf("\nV - promeni boju kuglicama\n");
	printf("\n1 - smanji broj kuglica\n");
	printf("\n2 - povecaj broj kuglica\n");
	printf("\nESC - zatvori program\n");
}

int main( int argc, char **argv ){
	KonzolniTekst();
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE ); 
	glutInitWindowPosition( 0, 0 ); 
	glutInitWindowSize( 600, 600 ); 
	glutInit( &argc, argv ); 
	glutCreateWindow( "Kuglice" ); 
	glutKeyboardFunc( Keyboard );
	glutDisplayFunc( Redraw ); 
	glutMainLoop(); 
	return 0;
}


