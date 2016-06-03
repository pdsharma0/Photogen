#pragma once

#include <list>
#include <iostream>
#include "Entity.h"
#include <functional>
#include <vector>

typedef std::function<void(Entity)> DestroyCallback;

/* Class handles entity creation and destruction */
class EntityManager {
public:

	EntityManager();

	/* Creates a new entity */
	Entity Create();

	/* Destroys an already created entity */
	void Destroy(Entity e);

	/* Returns true if an entity is alive */
	bool IsAlive(Entity e) const;

	/* Prins all alive entities */
	void PrintAliveEntities() const;	

	/* Add a callback function to its list of destroy callbacks
	   which will be called when Destroy is called */
	void AddDestroyCallback(DestroyCallback dc); // Add to l

protected:

	/* A link list of entities */
	std::list<Entity> _entities;

	/* Current/Most recent entity */
	Entity _entity;

	/* A vector of function objects of type void foo(Entity e)
       Component managers will register callbacks for destryoing 
	   entities when it's destroyed from EntityManager */
	std::vector<DestroyCallback> _destroyCallbacks;

};