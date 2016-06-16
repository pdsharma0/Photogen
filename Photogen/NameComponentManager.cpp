#include "NameComponentManager.h"
#include "ComponentHelper.h"

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

	int index = _currIndex;
	if (AddEntityToComponent(_currIndex, _data.n, e, _map)) {
		_data.entity[index] = e;
		_data.name[index] = sn;
		return true;
	}

	return false;
}

void NameComponentManager::MoveData(unsigned src, unsigned dst) {
	Entity srcEntity = _data.entity[src];
	_data.entity[dst] = srcEntity;
	_data.name[dst] = _data.name[src];
	// update moved entity's mapping index
	_map[srcEntity] = dst;
}

void NameComponentManager::RemoveEntity(Entity e) {
	RemoveEntityFromComponent(_currIndex, e, _map, std::bind(&NameComponentManager::MoveData, this, std::placeholders::_1, std::placeholders::_2));
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
	return LookupEntityInComponent(e, _map);
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