//my bool type
typedef char bool;
#define True 1;
#define False 0;

#include <stdlib.h>

//print vector to terminal
//useful for debug
#define logVec2(vector) printf("%f %f\n",\
						vector[0], \
						vector[1], 

#define logVec3(vector) printf("%f %f %f\n",\
						vector[0], \
						vector[1], \
						vector[2]) 

#define logVec4(vector) printf("%f %f %f %f\n",\
						vector[0], \
						vector[1], \
						vector[2], \
						vector[3]) 
//___________________________ vectors types _______________________________________
//floats
typedef float * vec4f;
typedef float * vec3f;
typedef float * vec2f;

//ints
typedef int * vec4i;
typedef int * vec3i;
typedef int * vec2i;
//___________________________ matrices types _______________________________________
//floats
typedef float ** mat4f;
typedef float ** mat3f;
typedef float ** mat2f;

//ints
typedef int ** mat4i;
typedef int ** mat3i;
typedef int ** mat2i;
//___________________________ triangles types _______________________________________
//floats
typedef vec4f * Triangle4f;
typedef vec2f * Triangle2f;

//ints
typedef vec4i * Triangle4i;
typedef vec2i * Triangle2i;

/*	
float levVec3(vec3f vector){
	return sqrtf(
			vector[0]*vector[0] +
			vector[1]*vector[1] +
			vector[2]*vector[2]);
}
*/
