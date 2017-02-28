#pragma once

#include "Datatypes.h"
#include "Entity.h"
#include "MeshComponentManager.h"
#include <map>

// This class is responsible for rendering all the entities 
// added to it. It looks for the corresponding mesh from the
// MeshComponentManager and based on the type of the mesh (point, line, triangle, triangle_strip)
// creates vertex and index buffers for them
// Each Mesh ( has a vertex array) also points to a Material which contains the
// shade properties (material data)

// OPTION-1 : 
// Using a (clustered) Forward+ rendering pipeline (http://www.3dgep.com/forward-plus/)
// which allows more flexibility (than deferred) to have per object material types and shading models
// It also handles opaque and transparent objects natively, and MSAA.
// Typically 5000-6000 dynamic lights can be rendered using this technique in 1080p on modern GPUs
// http://www.gamedev.net/topic/677570-when-would-you-want-to-use-forward-or-differed-rendering/

class Shader {
protected:
	std::string _highLevel;
};


// A Renderpass 
// List of meshes to render
// Contains code for the graphics pipeline i.e. vertex, tessellation, geometry, pixel, compute shader
// RenderSystem is responsible for creating GPU memory objects for each of the mesh to render
// vertex buffers, index buffers, uniforms, shaders, framebuffers, textures, general purpose r/w buffers etc.
// We bind entities to a renderpass, which has all the information to submit a drawcall for a particular mesh
// and material
// Also, a renderpass has state information such as 
// a. Number of framebuffers required
// b. Depth/Stencil test
// c. What resources are required for an entity's mesh and material combo. (Whenever we add a mesh to a renderpass
//    it will contain flags to indicate how many vertex-buffers are required for example, or whether we need that
//	  normal map from mesh. This information is part of a renderpass as it knows about the shader inputs.
//    This allows RenderSystem's resource manager to only allocate resources of a particular entity if required
//	  by a renderpass.
//
// The RenderSystem has a list of renderpasses. Whenever we add an entity to a renderer, based on some flags
// we add it to a bunch of renderpasses. For example, some entites would be bound to some particular post-process
// renderpass but some to a different post-process. Transparent objects would need a separate transparent pass.
// The RenderSystem first allocate resources for all Renderpasses i.e. all meshes and material objects for all 
// bound entities. Also the program objects, uniforms for shaders, framebuffers etc.
// The RenderSystem then just calls the render-function of each renderpass. With memory buffers already in place, 
// it's just a matter of sequencing computations to GPU now through these renderpasses.
class RenderPass {
protected:
	Entity* _entities;			// List of entities to render (Based on their mesh and material)
	Shader* _vertexshader;		// Pool of all vertex-shaders required in this pass
	Shader* _fragmentShader;	// Pool of all fragment-shaders required in this pass

	std::map<unsigned, unsigned> _vertexShaderMap;	// Index from entity to its vertex-shader index
	std::map<unsigned, unsigned> _fragShaderMap;	// Index from entity to its pixel-shader index

	int 
}


struct IndexBuffer 
{
	unsigned int id;
};

struct VertexBuffer {
	unsigned int id;
}

#define MAX_RENDERABLE_ENTITIES 1024

/* Contains a list of entities to render 
 * Refers to each entitiy's mesh from the meshcomponentmanager
 * Adds it into its own renderableEntities list 
 * Respnsible for creating framebuffer (includies widowing system code)
 * Renders each entity in a forward way first, creating/deleting resources
 */
class RenderSystem {
protected:
	Entity*			_renderEntity;			// A subset of entities needs rendering



	//Mesh*			_renderMesh;			// Renderable Entities can share meshes
	//IndexBuffer*	_iBuffer;				// Meshes can share index buffers and vertex buffers
	//VertexBuffer*	_vPosBuffer;			// Position vertex-buffer 
	//VertexBuffer*	_normalBuffer;
	//Material*		_material;				// Entities share materials just like meshes



	//std::map<unsigned, unsigned> _entityMeshMap; // Mapping from an entitity's index in _renderEntity array to _renderMesh
	//std::map<unsigned, unsigned> _entityMaterialMap;

	//std::map<unsigned, unsigned> _meshIBMap;
	//std::map<unsigned, unsigned> _meshPosVBMap;
	//std::map<unsigned, unsigned> _meshNormalVBMap;


public:

	RenderSystem();

	~RenderSystem();

	// Add an entity on if it has a valid mesh in the mesh component manager
	// Then copy the mesh properties to its own list of meshes for faster access
	// Also, copy the material properties into the material list
	// Have a flag for each entity indicating all the resources needed to render it
	// have been allocated, only then it can be rendered. i.e, the mesh it referes to
	// and the material it needs, have their resources allcated such as vertex buffer,
	// index buffer, shaders, shader uniforms, textures, render-targets etc.
	// Some of these are global resources such as framebuffers which are internally
	// manageed by the RenderSystem itself.
	// 
	void AddEntity(Entity e);

};