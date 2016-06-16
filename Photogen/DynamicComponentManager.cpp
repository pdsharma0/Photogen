#include "DynamicComponentManager.h"
#include <cassert>


DynamicComponentManager::DynamicComponentManager(EntityManager& em) {

	AllocateData(MAX_DYNAMIC_COMPONENTS);
	_currIndex = 0;

	// Register RemoveEntity as a callback with EntityManager
	// RemoveEntity being a class member function is actually
	// void RemoveEntity(DynamicComponentManager* this, Entity e)
	// Hence to std::bind we pass the address of this function, this pointer and a placeholder argument for Entity
	em.AddDestroyCallback(std::bind(&DynamicComponentManager::RemoveEntity, this, std::placeholders::_1));
}

DynamicComponentManager::~DynamicComponentManager() {
	FreeData();
}

bool DynamicComponentManager::AddEntity(Entity e, UpdateFunctor uf) {

	int index = _currIndex;
	if (AddEntityToComponent(_currIndex, _data.n, e, _map)) {
		// TODO : Add a function to InstanceData struct 
		// AddData(InstanceStruct is)
		// The plan is to make a base ComponentManager class
		// which has a base InstanceData class and also
		// a base Instance class
		// This way we can move the common functionality up the base class
		_data.entity[index] = e;
		_data.updateFunctor[index] = uf;
		return true;
	}

	return false;
}

void DynamicComponentManager::MoveData(unsigned src, unsigned dst) {
	Entity srcEntity = _data.entity[src];
	_data.entity[dst] = srcEntity;
	_data.updateFunctor[dst] = _data.updateFunctor[src];
	// update moved entity's mapping index
	_map[srcEntity] = dst;
}

void DynamicComponentManager::RemoveEntity(Entity e) {
	RemoveEntityFromComponent(_currIndex, e, _map, std::bind(&DynamicComponentManager::MoveData, this, std::placeholders::_1, std::placeholders::_2));
}

void DynamicComponentManager::UpdateEntites() {
	std::cout << "[DynamicComponentManager] Calling update on all dynamic entites...\n";
	for (auto it = _map.begin(); it != _map.end(); it++) {
		_data.updateFunctor[it->second]();
	}
}

// ------------------------------------------------
// Given an entity, find its index in the manager
// ------------------------------------------------
int DynamicComponentManager::Lookup(Entity e) {
	// Find entity index
	if (_map.find(e) != _map.end()) {
		return _map[e];
	}
	return -1;
}

void DynamicComponentManager::AllocateData(unsigned int size) {
	_data.n = size;
	_data.entity = new Entity[size];
	_data.updateFunctor = new UpdateFunctor[size];
}

void DynamicComponentManager::FreeData() {
	delete[] _data.entity;
	delete[] _data.updateFunctor;
}