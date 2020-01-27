#include <GL/glew.h>
#include <GL/freeglut.h>
#include "m_math.h"
#include "m_array.h"
#include "m_shader.h"
#include "m_mesh.h"

GLfloat * projection;
GLfloat * rotation;
GLfloat * translation;
GLfloat * VP;
GLfloat * MVP;

scene Main;
int angle = 0;
char * shaderFolder = "./sources/shaders/";

typedef struct Location{
	GLint position,
		   color,
		   projection,
		   translation,
		   rotation,
		   scale,
		   vp,
		   mvp;
} Location;

typedef struct Window{
	GLfloat width, height;
	int id;
	char * title;
} Window;

void display(void){
	ShaderUtil sUtil	= createShaderUtil();
	MathUtil mUtil		= createMathUtil();
	Location loc;

	char *vs, *fs;
	vs = strplus(shaderFolder, "basic.vs");
	fs = strplus(shaderFolder, "basic.fs");
	GLuint prog = sUtil.program(vs, fs); 
	free(vs);
   	free(fs);

	translation = mUtil.translation(0, 0, -5);
	rotation = mUtil.rotation((angle * DEG_TO_RAD), radians(0), radians(0));
	VP = mUtil.mat4mul(projection, translation);
	MVP = mUtil.mat4mul(VP, rotation);

	sUtil.use(prog);

	loc.position = glGetAttribLocation(prog, "position");
	loc.mvp = glGetUniformLocationARB(prog, "MVP");

	glEnableVertexAttribArray(loc.position);
	glUniformMatrix4fv(loc.mvp, 1, GL_TRUE, MVP);

	glClearColor(.2, .2, .2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(Main.vao);
	glDrawElements(GL_TRIANGLES, Main.NUM_VERTICES, GL_UNSIGNED_INT, NULL);

	sUtil.del(prog);
	glBindVertexArray(0);
	glFlush();
}

void tick(int value){
	angle = (angle == 360) ? 0 : angle+1;
	glutTimerFunc(16, tick, 0);
	glutPostRedisplay();
}

void reshape(GLint w, GLint h){
	MathUtil mUtil		= createMathUtil();
	projection = mUtil.perspective(45, w/h, .1f, 100.f);
}

void keyProc(unsigned char code, int w, int h){
	pInt(code);nl;
}

void specKeyProc(int key, int w, int h){
	pInt(key);nl;
}

void specKeyUpProc(int key, int w, int h){
	pInt(key);nl;
}

void mousePress(int button, int state, int x, int y){
	pInt( button );nl;
}

void mouseMove(int x, int y){
	printf("%d %d\n", x, y);
}

void globInit(int* argc, char ** argv, Window* win){

	/*Glut init*/
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);

	/*Glut window creation*/
	glutInitWindowSize(
			win->width,
		   	win->height);
	glutInitWindowPosition(
			(glutGet(GLUT_SCREEN_WIDTH)  - win->width)  * .5f,
		   	(glutGet(GLUT_SCREEN_HEIGHT) - win->height) * .5f);
	win->id = glutCreateWindow(win->title);

	/*register callbacks*/
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutTimerFunc(16, tick, 0);
	glutReshapeFunc(reshape);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyProc);
	glutSpecialFunc(specKeyProc);
	glutSpecialUpFunc(specKeyUpProc);
	glutMouseFunc(mousePress);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);

	/*gl init*/
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*glew init*/
	glewExperimental = GL_TRUE;
	GLenum initGlew = glewInit();
	if(initGlew != GLEW_OK){
		fprintf(stderr, "GLEW is not ok:%s", glewGetErrorString(initGlew));nl;
	}

}

int main(int argc, char ** argv){
	array * buffer = calloc(4, sizeof(array));

	MathUtil mUtil		= createMathUtil();
	MeshUtil mshUtil	= createMeshUtil();
	ArrayUtil aUtil		= createArrayUtil();

	Window MainWindow;
	MainWindow.width = 700;
	MainWindow.height = 700;
	MainWindow.title = "FCEngine";
	char * path = "cube.obj";

	globInit(&argc, argv, &MainWindow);

	mshUtil.load(&buffer[0], &buffer[1], path);

	Main.NUM_VERTICES = buffer[1].len;
	pushArrays(
			&Main.vao, 
			&Main.vbo, 
			&Main.ibo, 
			&buffer[0], 
			&buffer[1], 
			GL_DYNAMIC_DRAW);
	
	aUtil.del(&buffer[0]);
	aUtil.del(&buffer[1]);

	projection	= mUtil.mat4();
	rotation	= mUtil.mat4();
	translation = mUtil.mat4();
	VP			= mUtil.mat4();
	MVP			= mUtil.mat4();

	glutMainLoop();

	glutLeaveMainLoop();
	glutDestroyWindow(MainWindow.id);
	glDeleteVertexArrays(1, &Main.vao);

	free(MainWindow.title);
	free(buffer);

	free(projection);
	free(translation);
	free(VP);
	free(rotation);
	free(MVP);
	return 0;
}

