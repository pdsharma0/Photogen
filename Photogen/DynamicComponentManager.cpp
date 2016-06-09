#include "DynamicComponentManager.h"

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

	// Check size
	if (_currIndex >= _data.n - 1) {
		std::cout << "Couldn't add Entity : " << e.id << std::endl;
		return false;
	}

	// index at which the entity will be added to Component
	int index = _currIndex++;
	//_map.insert(std::make_pair(e, index));
	_map[e] = index;

	_data.entity[index] = e;
	_data.updateFunctor[index] = uf;

	return true;
}

void DynamicComponentManager::RemoveEntity(Entity e) {

	std::cout << "RemoveEntity : " << e.id << std::endl;

	if (_currIndex == 0) {
		std::cout << "No entities present!\n";
		return;
	}

	// Get the index of current entity to be removed
	int index = -1;
	auto it = _map.find(e);
	if (it == _map.end())
		return;

	index = it->second;

	// Remove the entity mapping
	_map.erase(e);

	// Move the last entity to current index
	if (_currIndex > 1) {
		Entity lastEntity = _data.entity[_currIndex - 1];
		_data.entity[index] = lastEntity;
		_data.updateFunctor[index] = _data.updateFunctor[_currIndex - 1];

		// update moved entity's mapping index
		_map[lastEntity] = index;
	}

	// Decrease _currIndex
	_currIndex--;
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