#pragma once

#include <vector>
#include <string>
#include "Entity.h"
#include "Datatypes.h"
#include <iostream>
#include <map>

#define MAX_NAME_COMPONENTS 1000

// ======================== //
//	 Manages entity names	//
// ======================== //
class NameComponentManager {

public:

	NameComponentManager(EntityManager& em) {
		_data.n = MAX_NAME_COMPONENTS;
		_currIndex = 0;

		// Initialize memory here
		_data.entity = new Entity[_data.n];
		_data.name = new CompactString[_data.n];

		// Register RemoveEntity as a callback with EntityManager
		// RemoveEntity being a class member function is actually
		// void RemoveEntity(NameComponentManager* this, Entity e)
		// Hence to std::bind we pass the address of this function, this pointer and a placeholder argument for Entity
		em.AddDestroyCallback(std::bind(&NameComponentManager::RemoveEntity, this, std::placeholders::_1));
	}

	// Keep a fixed sized allocation for now
	// It can grow in size once MemAllocater is done
	NameComponentManager(unsigned int size) {
		_data.n = size;
		_currIndex = 0;

		// Initialize memory here
		_data.entity = new Entity[_data.n];
		_data.name = new CompactString[_data.n];
	}
    
	// ------------------------------
	// Adds an entity and its name 
	// Returns true if Entity was successfully added
	// Else returns false
	// ------------------------------
    bool AddEntity(Entity e, CompactString sn) {

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

	// ---------------------------
	// Remove the supplied entity
	// ---------------------------
    void RemoveEntity(Entity e) {

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

	// -------------------------------------------------------------
	// Get name of a given entity
	// Returns null string if entity doesn't exist in the manager
	// -------------------------------------------------------------
    char* GetEntityName(Entity e) {
        
        int entityIdx = Lookup(e);
        if (entityIdx == -1) {
            std::cout << "Entity {" << e.id << "} not found!\n";
            return '\0';
        }
        else {
            return _data.name[entityIdx].str;
        }
    }

	// ----------------------------------------
	// Print names of all entities registered
	// ----------------------------------------
	void PrintEntityNames() {
		std::cout << "[NameComponentManager] {Index = {EntityID : EntityName}}  : \n";
		for (auto it = _map.begin(); it != _map.end(); it++) {
			std::cout << it->second << " = " << it->first.id << " : " << _data.name[it->second].str << std::endl;
		}
	}

private:

	// ------------------------------------------------
	// Given an entity, find its index in the manager
	// ------------------------------------------------
    int Lookup(Entity e) {
        // Find entity index
        if (_map.find(e) != _map.end()) {
            return _map[e];
        }
        return -1;
    }

	// ------------------------------------------------------------------
	// PerfOp : Using std::vector isn't the best way to manage memory
	// 2 separate vectors will cause fragmented allocation
	// Create a MemAllocater which suballocates from a larger pool 
	// ------------------------------------------------------------------
    struct InstanceData {

		InstanceData() : n(0), entity(nullptr), name(nullptr) {}

		unsigned int n;
        Entity* entity;
		CompactString* name;
    };
    InstanceData _data;

    // Map to store relationship between entity ID and component's packed index
    // So that we don't have to find the entity every time we lookup it's component
    std::map<Entity, unsigned> _map;

	unsigned int _currIndex;
};
