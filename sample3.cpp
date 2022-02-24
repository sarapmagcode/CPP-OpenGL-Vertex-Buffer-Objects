#define GLEW_STATIC

#include<GL/glew.h>
#include<GL/glut.h>
#include <GL/freeglut_ext.h>
#include<iostream>

using namespace std;

void display();
void triangle();
void GLAPIENTRY
MessageCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam );

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Setup Test");
	glutDisplayFunc(display);
	GLenum err = glewInit();
	if (err == GLEW_OK) {
		glutMainLoop();
	} else {
		cout << "Error in initializing GLEW extension library...";
	}
	return 0;
}

void triangle() {
	GLfloat trianglevertices[] = {
		0.0f, .75f, 0.0f,
		-0.75f, 0.0f, 0.0f,
		0.75f, 0.0f, 0.0f,
		
		-0.75f, -0.75f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.75f, -0.75f, 0.0f
	};
	
	GLubyte indices[] = {
		0,1,2,
		3,4,5
	};

	//2. Generate a Vertex Object ID for your array of vertices and normal arrays and bind it
	GLuint VBOid; 
	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*18, trianglevertices, GL_STATIC_DRAW);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	GLuint VBOindex; 
	glGenBuffers(1, &VBOindex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*6, indices, GL_STATIC_DRAW);
	
	//3. Activate and specify pointer to vertex array
	glEnableClientState(GL_NORMAL_ARRAY); 
	
	//4. Draw the primitive object
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glNormalPointer(GL_UNSIGNED_BYTE,0, 0);
	
	//5.
	//glDrawArrays(GL_TRIANGLES,0,6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
	// bind with 0, so, switch back to normal pointer operation
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBOid);
	glDeleteBuffers(1, &VBOindex);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(.16f, .72f, .08f, 1.0f);
	
	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	
	triangle();
	glFlush();
}

// reference: https://www.khronos.org/opengl/wiki/Debug_Output
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}
