#include <GL/glew.h>
#include "../utils/u_read.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct seShaderProgramCreateInfo
{
	const GLchar * vertexShaderFilePath;
	const GLchar * fragmentShaderFilePath;
	GLuint _id;
} seShaderProgramCreateInfo;

char seShaderProgramCreate(seShaderProgramCreateInfo * program);
GLuint seLoadShader(GLenum shaderType, const char * path);
char seShaderLinkingCheck(GLuint id);
char seUniformMatrix(seShaderProgramCreateInfo * program, const GLchar * uniform, glm::mat4 matrix);
char seUseProgram(seShaderProgramCreateInfo * program);
char seUniformVector(seShaderProgramCreateInfo * program, const GLchar * uniform, glm::vec4 color);
char seShaderProgramDelete(seShaderProgramCreateInfo * program);
