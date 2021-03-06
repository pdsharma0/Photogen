#include "EntityManager.h"
#include "NameComponentManager.h"
#include <iostream>
#include <vector>

int main() {

	std::vector<Entity> entities;

	EntityManager eManager;
    NameComponentManager ncManager(eManager);

    Entity e1 = eManager.Create();
	Entity e2 = eManager.Create();
	Entity e3 = eManager.Create();
	Entity e4 = eManager.Create();

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

	//ncManager.RemoveEntity(e1);
	eManager.Destroy(e1);
	ncManager.PrintEntityNames();

	eManager.Destroy(e4);
	ncManager.PrintEntityNames();

	eManager.Destroy(e3);
	ncManager.PrintEntityNames();

	eManager.Destroy(e2);
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