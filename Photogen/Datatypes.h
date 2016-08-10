#pragma once

#include <cstring>
#include <iostream>

#define COMPACT_STRING_SIZE 64

// ------------------
// A 64Byte string
// ------------------
struct CompactString {

	CompactString() {
		std::memset(str, '\0', sizeof(str));
	}

	CompactString(char* src) {
		std::memcpy(str, src, sizeof(str));
	}

	// Overload equality operator
	inline void operator=(const CompactString& src) const {
		memcpy((void*)str, src.str, sizeof(str));
	}

	char str[COMPACT_STRING_SIZE];
};

// -------------------
// Topology of a Mesh
// -------------------
enum MeshTopology {
	POINTS,
	LINES,
	TRIANGLES,
	TRIANGLE_STRIP,
};

// ---------------------------
// A vertex holds 3D position
// ---------------------------
struct Vertex {
	float _x, _y, _z;

	Vertex(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z) {}
	Vertex(float x) : _x(x), _y(x), _z(x) {}
};

#define MESH_N_VERTICES 1024

// --------------------------------------------
// Mesh is a container for a list of vertices
// --------------------------------------------
class Mesh {
protected:
	Vertex* _vertices;
	MeshTopology _topology;
	unsigned _maxVertices;
	unsigned _nVertices;

public:
	Mesh() : _topology(TRIANGLES), _maxVertices(0), _nVertices(0), _vertices(nullptr) {}

	virtual ~Mesh() {
		delete[] _vertices;
	}

	MeshTopology GetTopology() const {
		return _topology;
	}

	void SetTopology(MeshTopology t) {
		_topology = t;
	}

	unsigned GetSize() const {
		return _maxVertices;
	}

	unsigned GetNumVertices() const {
		return _nVertices;
	}

	// Returns true if we're able to succesfully allocate 
	// required number of vertices for this mesh
	// Else returns false
	bool AllocateVertexArray(unsigned maxVertices) {
		if (maxVertices) {
			_maxVertices = maxVertices;
			_vertices = new Vertex[maxVertices]; // Replace this with a custom suballocater returning 4Kb chunks (depends on typical mesh size though)
			if (_vertices) {
				return true;
			}
			else {
				std::cout << "Couldn't allocate a vertex-array of size " << _maxVertices << std::endl;
			}
		}
		return false;
	}

	void AddVertex(Vertex& vertex) {
		if (_nVertices < _maxVertices - 1)
			_vertices[_nVertices++] = vertex;
		else
			std::cout << "Can't add any more vertices, mesh reached its max vertex capacity : " << _maxVertices << std::endl;
	}

	void ResetData() {
		_nVertices = 0;
	}
};

// -----------------------------------
// Represents a single triangle
// -----------------------------------
class TriangleMesh : Mesh {
public:
	TriangleMesh(Vertex& v0, Vertex& v1, Vertex& v2) : Mesh() {
		AllocateVertexArray(3);
		SetTopology(TRIANGLES);
		_vertices[0] = v0;
		_vertices[1] = v1;
		_vertices[2] = v2;
	}

};


