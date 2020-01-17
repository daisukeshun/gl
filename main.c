#include <GL/glew.h>
#include <GL/freeglut.h>
#include "m_math.h"
#include "m_array.h"
#include "m_shader.h"
#include "m_mesh.h"

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
	glClearColor(.2, .2, .2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void reshape(GLint w, GLint h){

}

void globInit(int* argc, char ** argv, Window* win){

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(
			win->width,
		   	win->height);

	glutInitWindowPosition(
			(glutGet(GLUT_SCREEN_WIDTH)  - win->width)  * .5f,
		   	(glutGet(GLUT_SCREEN_HEIGHT) - win->height) * .5f);

	win->id = glutCreateWindow(win->title);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glewExperimental = GL_TRUE;
	GLenum initGlew = glewInit();
	if(initGlew != GLEW_OK){
		fprintf(stderr, "GLEW is not ok:%s", glewGetErrorString(initGlew));nl;
	}
}

char * shaderFolder = "./res/shaders/";
int main(int argc, char ** argv){

	ShaderUtil sUtil	= createShaderUtil();
	MathUtil mUtil		= createMathUtil();
	MeshUtil mshUtil	= createMeshUtil();
	Location loc;

	Window MainWindow;
	MainWindow.width = 800;
	MainWindow.height = 600;
	MainWindow.title = "FCEngine";


	globInit(&argc, argv, &MainWindow);

	array adata = Array(9);
	adata.element[0] = -1;
	adata.element[1] = -1;
	adata.element[2] = -1;

	adata.element[3] = 1;
	adata.element[4] = -1;
	adata.element[5] = -1;

	adata.element[6] = 0;
	adata.element[7] = 1;
	adata.element[8] = -1;

	Mesh tst;
	tst.DATA_SIZE = adata.size;
	tst.NUM_VERTICES = adata.len;
	tst.DATA_OFFSET = 0;
	tst.V_COMPONENTS = 3;
	tst.DATA_TYPE = GL_FLOAT;
	tst.STRIDE = 3 * sizeof(*adata.element);
	tst.NORMALIZE = GL_FALSE;

	GLfloat * projection = mUtil.perspective(45, MainWindow.width / MainWindow.height, .1f, 100.f);
	GLfloat * rotation = mUtil.rotation(0, 0, radians(180));
	GLfloat * translation = mUtil.translation(0.5, 0, -20);
	GLfloat * VP = mUtil.mat4mul(projection, translation);
	GLfloat * MVP = mUtil.mat4mul(VP, rotation);

	free(projection);
	free(translation);
	free(VP);
	free(rotation);

	glGenVertexArrays(1, &tst.vao);
	glBindVertexArray(tst.vao);

	glGenBuffers(1, &tst.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tst.vbo);
	glBufferData(GL_ARRAY_BUFFER, tst.DATA_SIZE, adata.element, GL_STATIC_DRAW);

	ArrayUtil_delete(adata);

	glBindVertexArray(0);
	mshUtil.draw(tst);

	char *vs, *fs;
	vs = strplus(shaderFolder, "basic.vs");
	fs = strplus(shaderFolder, "basic.fs");
	GLuint prog = sUtil.program(vs, fs);

	free(vs);
	free(fs);

	sUtil.use(prog);

	loc.position = glGetAttribLocation(prog, "position");
	loc.mvp = glGetUniformLocationARB(prog, "MVP");

	glEnableVertexAttribArray(loc.position);
	glUniformMatrix4fv(loc.mvp, 1, GL_TRUE, MVP);

	free(MVP);

	glutMainLoop();
	sUtil.del(prog);

	glutLeaveMainLoop();
	glutDestroyWindow(MainWindow.id);

	free(MainWindow.title);
	return 0;
}

	/*
	 * 1. Описывает, какой аргумент ШЕЙДЕРА мы хотим настроить. layout (location = 0) => 0
	 * 2. Описывает размер аргумента в ШЕЙДЕРЕ. in vec3 => 3, in vec2 => 2
	 * 3. Тип описываемых данных.
	 * 4. Нормализировать ли данные.
	 * 5. Шаг между передаваемыми ДАННЫМИ (количество компонент в вершине/цвете * sizeof(указатель на массив))
	 * 6. Смещение данных вначале буфера. (Требуется приведение типов для явного GLvoid*)
	 */


