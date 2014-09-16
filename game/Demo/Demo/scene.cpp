#include "scene.h"

Scene::Scene() {
	render = new Render();
}

Scene::~Scene() {
	render = NULL;
}

void Scene::update() {
	level->update();
}

void Scene::load() {
	level = new Level(render);
	level->load();
}

void Scene::onkeypress(int key) {
    level->onkeypress(key);
}

void Scene::onkeyup(int key) {
    level->onkeyup(key);
}