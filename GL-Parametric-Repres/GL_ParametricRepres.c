//************************************************************************
//
//				This program is show how to use Newton difference
//				method to calculate an example.
//											   ----made by SeokHo
//
//************************************************************************
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

#define N 5
#define IT 400

void RenderScene(void);
void SetupRC(void);
void ChangeSize(int, int);


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Points Example");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}


void RenderScene(void)
{
	GLdouble basey[N], d[N][N], basex[N], t[N], x[IT]={0,}, y[IT]={0,}, a[N], b[N];
	GLint i, j, n;
	GLdouble item[N], X, Y;

	//init
	basex[0] = 0.0; 
	basex[1] = 1.0;
	basex[2] = 1.0;
	basex[3] = 0.0;
	basex[4] = 0.0;

	basey[0] = 0.0;
	basey[1] = 0.0;
	basey[2] = 1.0;
	basey[3] = 1.0;
	basey[4] = 0.0;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
		for(n=0;n<N;n++)
		{
			glVertex2f(basex[n], basey[n]);
		}
	// Done drawing points
	glEnd();
	
	for(n=0;n<N;n++)	//...Here mean's we know t0, we get t for n=1,...N-1
	{
		if(n==0)
		{
			t[n] = 0.0;
		}
		else
		{
			t[n] = sqrt(pow((basex[n] - basex[n-1]), 2) + pow((basey[n] - basey[n-1]), 2)) + t[n-1];
		}
	}
//...calculate coe a  ***********************************************
	for(i=0;i<N;i++)
	{
		d[i][0] = basex[i];				//...dependent variable is x
	}
	for(j=1;j<N;j++)
	{
		for(i=0;i<N-j;i++)
		{
			d[i][j] = (d[i+1][j-1] - d[i][j-1]) / (t[i+j] - t[i]);		//...independent variable is t
		}
	}
	for(i=0;i<N;i++)
	{
		a[i] = d[0][i];
	}
	for(n=0;n<IT;n++)
	{
		X = (double)n/100;//!!!!!!!!!!!!!!!!!!!!...here is important about the value
		Y = 0.0;
		for(i=0;i<N;i++)
		{
			item[i] = 1.0;
		}
		for(i=1;i<N;i++)
		{
			for(j=0;j<i;j++)
			{
				item[i] *= (X - t[j]);
			}
			
			item[i] = item[i] * a[i];		
			Y += item[i];
		}
		Y += a[0];
		x[n] = Y;
	}
//...calculate coe b  ***********************************************
	for(i=0;i<N;i++)
	{
		d[i][0] = basey[i];				//...dependent variable is y
	}
	for(j=1;j<N;j++)
	{
		for(i=0;i<N-j;i++)
		{
			d[i][j] = (d[i+1][j-1] - d[i][j-1]) / (t[i+j] - t[i]);		//...independent variable is t
		}
	}
	for(i=0;i<N;i++)
	{
		b[i] = d[0][i];
	}

	// Call only once for all remaining points
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
		for(n=0;n<IT;n++)
		{
			X = (double)n/100;//!!!!!!!!!!!!!!!!!!!!...here is important about the value
			Y = 0.0;
			for(i=0;i<N;i++)
			{
				item[i] = 1.0;
			}
			for(i=1;i<N;i++)
			{
				for(j=0;j<i;j++)
				{
					item[i] *= (X - t[j]);
				}
				
				item[i] = item[i] * b[i];		
				Y += item[i];
			}
			Y += b[0];
			y[n] = Y;
			glVertex2f(x[n], y[n]);
		}
	// Done drawing points
	glEnd();
	// Flush drawing commands
	glFlush();
}

void SetupRC()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;
		
	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)w / (GLfloat)h;
 //   if (w <= h) 
//		glOrtho (-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, 1.0, -1.0);
  //  else 
//		glOrtho (-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, 1.0, -1.0);

	if (w <= h) 
		glOrtho (-1.0, 1.5, -1.0 / aspectRatio, 1.5 / aspectRatio, 1.0, -1.0);
    else 
		glOrtho (-1.0 * aspectRatio, 1.5 * aspectRatio, -1.0, 1.5, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
