#include <GL/glew.h>
#include <GL/freeglut.h>
#include "m_math.h"
#include "m_array.h"
#include "m_shader.h"
#include "m_scene.h"

GLfloat * projection;
GLfloat * rotation;
GLfloat * translation;
GLfloat * VP;
GLfloat * MVP;

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

Scene Main;
MathUtil math_util;
MeshUtil mesh_util;
SceneUtil scene_util;
ArrayUtil array_util;
ShaderUtil shader_util;
Location location;
int angle = 0;
char * shaderFolder = "./sources/shaders/";

typedef struct Window{
	GLfloat width, height;
	int id;
	char * title;
} Window;

void display(void){
	char *vs, *fs;
	vs = strplus(shaderFolder, "basic.vs");
	fs = strplus(shaderFolder, "basic.fs");
	GLuint prog = shader_util.program(vs, fs); 
	free(vs);
   	free(fs);

	translation = math_util.translation(
			Main.object[0].position[0],
			Main.object[0].position[1],
			Main.object[0].position[2]
			);
	rotation = math_util.rotation((angle * DEG_TO_RAD), radians(0), radians(0));
	VP = math_util.mat4mul(projection, translation);
	MVP = math_util.mat4mul(VP, rotation);

	shader_util.use(prog);

	location.position = glGetAttribLocation(prog, "position");
	location.mvp = glGetUniformLocationARB(prog, "MVP");

	glEnableVertexAttribArray(location.position);
	glUniformMatrix4fv(location.mvp, 1, GL_TRUE, MVP);

	glClearColor(.2, .2, .2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	unsigned int i;
	for(i = 0; i < Main.objectsCount; i++){
		glBindVertexArray(Main.vao[i]);
		glDrawElements(GL_TRIANGLES, Main.NUM_VERTICES[i], GL_UNSIGNED_INT, NULL);
	}

	shader_util.del(prog);
	glBindVertexArray(0);
	glFlush();
}

char key[256] = { 0 };

void tick(int value){
	angle = (angle == 360) ? 0 : angle+1;
	glutTimerFunc(16, tick, 0);
	glutPostRedisplay();
}

void reshape(GLint w, GLint h){
	math_util		= createMathUtil();
	projection = math_util.perspective(45, w/h, .1f, 100.f);
}

void keyProc(unsigned char code, int w, int h){
	printf("%c", code);nl;
	key[code] = 1;
	if(key['a'] || key['A']){
		translation = math_util.translation(radians(1), 0, 0);
	}
	/*pInt(code);nl;*/
}

void specKeyProc(int key, int w, int h){
	pInt(key);nl;
}

void specKeyUpProc(int key, int w, int h){
	pInt(key);nl;
}

void mousePress(int button, int state, int x, int y){
	pInt( state );nl;
}

void mouseMove(int x, int y){
	printf("%d %d\n", x, y);
}

void globInit(int* argc, char ** argv, Window* win){
	math_util	= createMathUtil();
	mesh_util	= createMeshUtil();
	shader_util = createShaderUtil();
	array_util	= createArrayUtil();
	scene_util	= createSceneUtil();

	projection	= math_util.mat4();
	rotation	= math_util.mat4();
	translation = math_util.mat4();
	VP			= math_util.mat4();
	MVP			= math_util.mat4();

	Main = scene_util.scene(30);
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
	Window MainWindow;
	MainWindow.width = 700;
	MainWindow.height = 700;
	MainWindow.title = "FCEngine";

	globInit(&argc, argv, &MainWindow);

	Mesh cube0 = {.path = "cube.obj", .id = -1};
	cube0.position = math_util.vec3();
	cube0.position[2] = -5;

	mesh_util.load(&cube0.V_DATA, &cube0.F_DATA, cube0.path);

	scene_util.add(
			&shader_util,
			&Main,
			&cube0,
			GL_DYNAMIC_DRAW);

	glutMainLoop();

	glutLeaveMainLoop();
	glutDestroyWindow(MainWindow.id);
	unsigned int i;
	for(i = 0; i < Main.objectsCount; i++){
		glDeleteVertexArrays(1, &Main.vao[i]);
	}

	free(MainWindow.title);
	scene_util.del(&Main);
	free(projection);
	free(translation);
	free(VP);
	free(rotation);
	free(MVP);
	return 0;
}

