#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct seCameraCreateInfo
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

} seCameraCreateInfo;
