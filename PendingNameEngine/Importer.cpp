#include "Importer.h"
#include "Application.h"
#include "Globals.h"
#include "Mesh.h"


Importer::Importer()
{
}

Importer::~Importer()
{
}

bool Importer::Init()
{
	LOG("Init Importer");
	bool ret = true;

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

bool Importer::CleanUp()
{
	LOG("Cleaning Importer");
	bool ret = true;

	aiDetachAllLogStreams();

	return ret;
}

bool Importer::Import(const char* full_path)
{
	bool ret = true;

	const aiScene* scene = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			const aiMesh* mesh = scene->mMeshes[i];
			LoadMesh(mesh);
		}
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", full_path);

	return ret;
}

void Importer::LoadMesh(const aiMesh * mesh)
{
	Mesh* my_mesh = new Mesh();
	
	my_mesh->data.num_vertex = mesh->mNumVertices;
	my_mesh->data.vertex = new vec[my_mesh->data.num_vertex];
	memcpy(my_mesh->data.vertex, mesh->mVertices, sizeof(vec)*my_mesh->data.num_vertex);
	LOG("New Mesh with %d vertices", my_mesh->data.num_vertex);

	glGenBuffers(1, (GLuint*) &(my_mesh->data.id_vertex));

	glBindBuffer(GL_ARRAY_BUFFER, my_mesh->data.id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec)*my_mesh->data.id_vertex, my_mesh->data.vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (mesh->HasFaces())
	{
		my_mesh->data.num_index = mesh->mNumFaces * 3;
		my_mesh->data.index = new uint[my_mesh->data.num_index]; 
		for (uint i = 0; i < mesh->mNumFaces; ++i)
		{
			if (mesh->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, geometry face with != 3 indices!");
			}	
			else
			{
				memcpy(&my_mesh->data.index[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
				
		}
	}
	glGenBuffers(1, (GLuint*) &(my_mesh->data.id_index));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_mesh->data.id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec)*my_mesh->data.id_index, my_mesh->data.index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	App->scene_intro->scene_objects.push_back(my_mesh);
}
