#include "MeshComponentManager.h"
#include "ComponentHelper.h"

MeshComponentManager::MeshComponentManager(EntityManager& em) {

	AllocateData(MAX_NAME_COMPONENTS);
	_currIndex = 0;

	// Register RemoveEntity as a callback with EntityManager
	// RemoveEntity being a class member function is actually
	// void RemoveEntity(MeshComponentManager* this, Entity e)
	// Hence to std::bind we pass the address of this function, this pointer and a placeholder argument for Entity
	em.AddDestroyCallback(std::bind(&MeshComponentManager::RemoveEntity, this, std::placeholders::_1));
}

MeshComponentManager::~MeshComponentManager() {
	FreeData();
}

bool MeshComponentManager::AddEntity(Entity e, Mesh& m) {

	int index = _currIndex;
	if (AddEntityToComponent(_currIndex, _data.n, e, _map)) {
		_data.entity[index] = e;
		_data.mesh[index] = m; // Shallow copy is fine here 
		return true;
	}

	return false;
}

void MeshComponentManager::MoveData(unsigned src, unsigned dst) {
	Entity srcEntity = _data.entity[src];
	_data.entity[dst] = srcEntity;
	_data.mesh[dst] = _data.mesh[src];
	// update moved entity's mapping index
	_map[srcEntity] = dst;
}

void MeshComponentManager::RemoveEntity(Entity e) {
	RemoveEntityFromComponent(_currIndex, e, _map, std::bind(&MeshComponentManager::MoveData, this, std::placeholders::_1, std::placeholders::_2));
}

Mesh* MeshComponentManager::GetEntityMesh(Entity e) {

	int entityIdx = Lookup(e);
	if (entityIdx == -1) {
		std::cout << "Entity {" << e.id << "} not found!\n";
		return nullptr;
	}
	else {
		return &_data.mesh[entityIdx];
	}
}

// ------------------------------------------------
// Given an entity, find its index in the manager
// ------------------------------------------------
int MeshComponentManager::Lookup(Entity e) {
	return LookupEntityInComponent(e, _map);
}

// This pre-allocation is dumb. Think of something better!
void MeshComponentManager::AllocateData(unsigned int size) {
	_data.n = size;
	_data.entity = new Entity[size];
	_data.mesh = new Mesh[size];
}

void MeshComponentManager::FreeData() {
	delete[] _data.entity;
	delete[] _data.mesh;
}