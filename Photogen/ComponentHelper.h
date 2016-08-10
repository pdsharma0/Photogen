#pragma once

// Helper functions for Components 
// Basically instead of creating a base class
// with common functions, a set of helper 
// functions are sufficient 

#include "Entity.h"
#include <map>
#include <iostream>

typedef std::map<Entity, unsigned> EntityComponentMap;
typedef std::function<void(unsigned, unsigned)> EntityMoveCallback;

// currIndex : Index where the current Entity will be stored
// size : Max permissible size of Component data
// e : Entity to be added
// map : Mapping between an entity and its index into Component's data array
inline bool AddEntityToComponent(unsigned& currIndex, unsigned& size, Entity& e, EntityComponentMap& map) {
	// Check size
	if (currIndex >= size - 1) {
		std::cout << "Size exceeded! Couldn't add Entity : " << e.id << std::endl;
		return false;
	}

	// index at which the entity will be added to Component
	map[e] = currIndex++;

	return true;
}

// currIndex : Current size of map
// e : Entity to be removed
// map : Entity -> index
// moveCallback : Moves data from a src index to a dst index
inline void RemoveEntityFromComponent(unsigned& currIndex, Entity& e, EntityComponentMap& map, EntityMoveCallback moveCallback) {

	std::cout << "RemoveEntity : " << e.id << std::endl;

	if (currIndex == 0) {
		std::cout << "No entities present!\n";
		return;
	}

	// Get the index of current entity to be removed
	auto it = map.find(e);
	if (it == map.end()) {
		std::cout << "Entity not found!\n";
		return;
	}

	// Get the index of erased entity
	int dstIndex = it->second;

	// Remove the entity mapping
	map.erase(e);

	moveCallback(currIndex - 1, dstIndex);

	// Decrease _currIndex
	currIndex--;
}

inline int LookupEntityInComponent(Entity& e, EntityComponentMap& map) {
	// Find entity index
	if (map.find(e) != map.end()) {
		return map[e];
	}
	return -1;
}
