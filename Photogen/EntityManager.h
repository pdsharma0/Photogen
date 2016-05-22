#pragma once

#include <list>
#include <iostream>
#include "Entity.h"

class EntityManager {
public:

	EntityManager() {
		_entity.id = -1;
	}

	// Creates and returns a new Entity
	Entity Create() {
		_entity.id++;
		_entities.push_back(_entity);
		return _entity;
	}

	void Destroy(Entity e) {
		_entities.remove(e);
	}

	bool IsAlive(Entity e) const {
		for (auto it = _entities.begin(); it != _entities.end(); it++) {
			if (*it == e) return true;
		}
        return false;
	}

	void PrintAliveEntities() const {
		std::cout << "{ ";
		for (auto it = _entities.begin(); it != _entities.end(); it++) {
			std::cout << (*it).id << ", ";
		}
		std::cout << "}\n";
	}

protected:

	// A link list of entities such that creation and deletion is not expensive
	std::list<Entity> _entities;

	// Keeps track of entity ids
	Entity _entity;

};