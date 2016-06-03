#include "EntityManager.h"

// -----------------------------------------------------------
EntityManager::EntityManager() {
	_entity.id = -1;
}

// -----------------------------------------------------------
// Creates and returns a new Entity
Entity EntityManager::Create() {
	_entity.id++;
	_entities.push_back(_entity);
	return _entity;
}

// -----------------------------------------------------------
void EntityManager::Destroy(Entity e) {
	_entities.remove(e);

	// Remove entity from all the component managers
	for (auto dc : _destroyCallbacks)
		dc(e);
}

// -----------------------------------------------------------
bool EntityManager::IsAlive(Entity e) const {
	for (auto it = _entities.begin(); it != _entities.end(); it++) {
		if (*it == e) return true;
	}
	return false;
}

// -----------------------------------------------------------
void EntityManager::PrintAliveEntities() const {
	std::cout << "{ ";
	for (auto it = _entities.begin(); it != _entities.end(); it++) {
		std::cout << (*it).id << ", ";
	}
	std::cout << "}\n";
}

// -----------------------------------------------------------
void EntityManager::AddDestroyCallback(DestroyCallback dc) {
	_destroyCallbacks.push_back(dc);
}