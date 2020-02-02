#ifndef M_SCENE_H
#define M_SCENE_H
#include "m_mesh.h"
#include "m_shader.h"
typedef struct Scene{
	unsigned long objectsCount;
	unsigned long *NUM_VERTICES;
	unsigned long iterator;
	Mesh * object;
	GLuint *vao;
	GLuint *vbo;
	GLuint *ibo;
} Scene;

typedef struct SceneUtil{
	Scene (*scene)(unsigned long objectsCount);
	void (*add)(ShaderUtil *shader_util, Scene * scene, Mesh * object, GLenum drawType);
	void (*del)(Scene * scene);
} SceneUtil;

Scene SceneUtil_Scene(unsigned long objectsCount){
	Scene ret;
	ret.iterator		= 0;
	ret.objectsCount	= objectsCount;
	ret.object			= m_array(objectsCount, Mesh);
	ret.ibo				= m_array(objectsCount, GLuint);
	ret.vbo				= m_array(objectsCount, GLuint);
	ret.vao				= m_array(objectsCount, GLuint);
	ret.NUM_VERTICES	= m_array(objectsCount, unsigned long);
	return ret;
};

void SceneUtil_Add(ShaderUtil * shader_util, Scene * scene, Mesh * object, GLenum drawType){
	unsigned long current = scene->iterator;
	object->id = current;
	scene->NUM_VERTICES[current] = object->F_DATA.len;
	scene->object[current] = *object;
	shader_util->push(
			&scene->vao[current],
			&scene->vbo[current],
			&scene->ibo[current],
			&object->V_DATA,
			&object->F_DATA,
			drawType);
	scene->iterator++;
}

void SceneUtil_Del(Scene * scene){
	free(scene->vao);
	free(scene->vbo);
	free(scene->ibo);
	free(scene->NUM_VERTICES);
	scene->objectsCount = 0;
}

SceneUtil createSceneUtil(){
	SceneUtil ret;
	ret.add = SceneUtil_Add;
	ret.del = SceneUtil_Del;
	ret.scene = SceneUtil_Scene;
	return ret;
}


#endif
