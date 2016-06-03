#include "NameComponentManager.h"

NameComponentManager::NameComponentManager(EntityManager& em) {

	AllocateData(MAX_NAME_COMPONENTS);
	_currIndex = 0;

	// Register RemoveEntity as a callback with EntityManager
	// RemoveEntity being a class member function is actually
	// void RemoveEntity(NameComponentManager* this, Entity e)
	// Hence to std::bind we pass the address of this function, this pointer and a placeholder argument for Entity
	em.AddDestroyCallback(std::bind(&NameComponentManager::RemoveEntity, this, std::placeholders::_1));
}

NameComponentManager::~NameComponentManager() {
	FreeData();
}

bool NameComponentManager::AddEntity(Entity e, CompactString sn) {

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
	_data.name[index] = sn;

	return true;
}

void NameComponentManager::RemoveEntity(Entity e) {

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
		_data.name[index] = _data.name[_currIndex - 1];

		// update moved entity's mapping index
		_map[lastEntity] = index;
	}

	// Decrease _currIndex
	_currIndex--;
}

char* NameComponentManager::GetEntityName(Entity e) {

	int entityIdx = Lookup(e);
	if (entityIdx == -1) {
		std::cout << "Entity {" << e.id << "} not found!\n";
		return '\0';
	}
	else {
		return _data.name[entityIdx].str;
	}
}

void NameComponentManager::PrintEntityNames() {
	std::cout << "[NameComponentManager] {Index = {EntityID : EntityName}}  : \n";
	for (auto it = _map.begin(); it != _map.end(); it++) {
		std::cout << it->second << " = " << it->first.id << " : " << _data.name[it->second].str << std::endl;
	}
}

// ------------------------------------------------
// Given an entity, find its index in the manager
// ------------------------------------------------
int NameComponentManager::Lookup(Entity e) {
	// Find entity index
	if (_map.find(e) != _map.end()) {
		return _map[e];
	}
	return -1;
}

void NameComponentManager::AllocateData(unsigned int size) {
	_data.n = size;
	_data.entity = new Entity[size];
	_data.name = new CompactString[size];
}

void NameComponentManager::FreeData() {
	delete[] _data.entity;
	delete[] _data.name;
}