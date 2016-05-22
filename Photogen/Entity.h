#pragma once

struct Entity {
	unsigned int id;

	// Overload equality check operator
	inline bool operator==(const Entity& e) const {
		return (id == e.id);
	}

    bool operator<(const Entity& e) const {
        return id < e.id;
    }
};
