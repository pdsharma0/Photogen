#include "EntityManager.h"
#include "NameComponentManager.h"
#include <iostream>
#include <vector>

int main() {

	std::vector<Entity> entities;

	EntityManager eManager;
    NameComponentManager ncManager;

    Entity e1 = eManager.create();
	Entity e2 = eManager.create();
	Entity e3 = eManager.create();
	Entity e4 = eManager.create();

    ncManager.AddEntity(e1, "first");
	ncManager.AddEntity(e2, "second");
	ncManager.AddEntity(e3, "third");
	ncManager.AddEntity(e4, "fourth");

	// TESTS for NameComponentManager
	std::cout << ncManager.GetEntityName(e1) << std::endl;
	std::cout << ncManager.GetEntityName(e2) << std::endl;
	std::cout << ncManager.GetEntityName(e3) << std::endl;
	std::cout << ncManager.GetEntityName(e4) << std::endl;

	ncManager.PrintEntityNames();

	ncManager.RemoveEntity(e1);
	ncManager.PrintEntityNames();

	ncManager.RemoveEntity(e4);
	ncManager.PrintEntityNames();

	ncManager.RemoveEntity(e3);
	ncManager.PrintEntityNames();

	ncManager.RemoveEntity(e2);
	ncManager.PrintEntityNames();

	ncManager.RemoveEntity(e1);
	ncManager.PrintEntityNames();
	
	
	/*for (int i = 0; i < 100; i++) {
		Entity e = eManager.create();
		entities.push_back(e);
	}

	std::cout << "Original Entities : ";
	eManager.PrintAliveEntities();

	for (int i = 0; i < 50; i++) {
		eManager.destroy(entities[i]);
	}

	std::cout << "\nEntities left after destroying half of them : ";
	eManager.PrintAliveEntities();

	for (int i = 0; i < 20; i++) {
		Entity e = eManager.create();
	}

	std::cout << "\nEntities left after adding a few : ";
	eManager.PrintAliveEntities();*/
}