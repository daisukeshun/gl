#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct seCameraCreateInfo
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	GLfloat mouseSpeed;
	GLfloat speed;
	GLfloat motionSpeed;
	GLfloat mousePositionX;
	GLfloat mousePositionY;
	GLfloat verticalAngle;
	GLfloat horizontalAngle;

	GLchar cursor;

	glm::mat4 projection;
	glm::mat4 view;

} seCameraCreateInfo;

void seCameraUpdate(seCameraCreateInfo * camera);
void seCameraSeeTo(seCameraCreateInfo * camera, GLfloat x, GLfloat y, GLfloat z);
void seCameraMoveTo(seCameraCreateInfo * camera, GLfloat x, GLfloat y, GLfloat z);
