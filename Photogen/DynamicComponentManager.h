#pragma once

#include <vector>
#include <string>
#include "Entity.h"
#include "Datatypes.h"
#include <iostream>
#include <map>
#include "EntityManager.h"
#include "GlobalDefines.h"
#include "ComponentHelper.h"

// The idea is to have this manager store a list
// of function pointers (or objects) for all the 
// entities. The GameLoopManager system will
// traverse through all dynamic entities and 
// Call this manager's update function at highest 
// tickrate. This manager's update funtion will 
// inturn update the entites at their tickrate
typedef std::function<void()> UpdateFunctor;

/* Manages entity names	*/
class DynamicComponentManager {

public:

	DynamicComponentManager(EntityManager& em);

	~DynamicComponentManager();

	/* Add a entity-name pair; Returns false if no space left */
	bool AddEntity(Entity e, UpdateFunctor uf);

	/* Removes an entity */
	void RemoveEntity(Entity e);

	/* Update all entities registered */
	void UpdateEntites();

private:

	/* Given an entity, find its index in the manager */
	int Lookup(Entity e);

	void AllocateData(unsigned int size);

	void FreeData();

	void MoveData(unsigned src, unsigned dst);

	struct InstanceData {

		InstanceData() : n(0), entity(nullptr), updateFunctor(nullptr) {}

		unsigned int n;
		Entity* entity;
		UpdateFunctor* updateFunctor;
	}_data;

	/* Map to store relationship between entity ID and component's packed index
	So that we don't have to find the entity every time we lookup it's component */
	EntityComponentMap _map;

	unsigned int _currIndex;
};

