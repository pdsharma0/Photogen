#pragma once


#include "Entity.h"
#include "EntityManager.h"
#include "GlobalDefines.h"
#include "Datatypes.h"
#include <vector>
#include <map>

/* Maintains a renderable mesh for entities	*/
class MeshComponentManager {

public:

	/* Ctor */
	MeshComponentManager(EntityManager& em);

	/* Dtor */
	~MeshComponentManager();

	/* Add a entity-name pair; Returns false if no space left */
	bool AddEntity(Entity e, Mesh& mesh);

	/* Removes an entity */
	void RemoveEntity(Entity e);

	/* Returns nullptr if entity doesn't exist */
	Mesh* GetEntityMesh(Entity e);

private:

	/* Given an entity, find its index in the manager */
	int Lookup(Entity e);

	void AllocateData(unsigned int size);

	void FreeData();

	/* Moves Entity data from src index to dst index */
	void MoveData(unsigned src, unsigned dst);

	struct InstanceData {

		InstanceData() : n(0), entity(nullptr), mesh(nullptr) {}

		unsigned int n;
		Entity* entity;
		Mesh* mesh;
	}_data;

	/* Map to store relationship between entity ID and component's packed index
	So that we don't have to find the entity every time we lookup it's component */
	std::map<Entity, unsigned> _map;

	unsigned int _currIndex;
};
#pragma once
