#pragma once

#include <vector>
#include <string>
#include "Entity.h"
#include "Datatypes.h"
#include <iostream>
#include <map>
#include "EntityManager.h"
#include "GlobalDefines.h"

/* Manages entity names	*/
class NameComponentManager {

public:

	NameComponentManager(EntityManager& em);

	~NameComponentManager();
    
	/* Add a entity-name pair; Returns false if no space left */
	bool AddEntity(Entity e, CompactString sn);

	/* Removes an entity */
	void RemoveEntity(Entity e);

	/* Returns null if entity doesn't exist */
	char* GetEntityName(Entity e);

	/* Print names of all entities registered */
	void PrintEntityNames();

private:

	/* Given an entity, find its index in the manager */
	int Lookup(Entity e);

	void AllocateData(unsigned int size);

	void FreeData();

	/* Moves Entity data from src index to dst index */
	void MoveData(unsigned src, unsigned dst);

    struct InstanceData {

		InstanceData() : n(0), entity(nullptr), name(nullptr) {}

		unsigned int n;
        Entity* entity;
		CompactString* name;
    }_data;

    /* Map to store relationship between entity ID and component's packed index
       So that we don't have to find the entity every time we lookup it's component */
    std::map<Entity, unsigned> _map;

	unsigned int _currIndex;
};
