#include "Application.h"
#include "Importer.h"
#include "Module.h"
#include "Globals.h"
#include "Mesh.h"


void AssimpToConsoleLog(const char* str, char* userData);

Importer::Importer(bool start_enabled) : Module(start_enabled)
{
}

Importer::~Importer()
{
}

bool Importer::Init(rapidjson::Document& document)
{
	LOG("Init Importer");
	bool ret = true;

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	stream.callback = AssimpToConsoleLog;
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

bool Importer::Import(const std::string &full_path)
{
	bool ret = true;

	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			const aiMesh* mesh = scene->mMeshes[i];
			
			LoadMesh(scene,mesh);

		}
		aiReleaseImport(scene);
	}
	else
	{
		CONSOLELOG("Error loading scene %s", full_path);
	}
		

	return ret;
}

void Importer::LoadMesh(const aiScene* _scene, const aiMesh * mesh)
{
	Mesh* my_mesh = new Mesh();
	bool correct_num_faces = false;

	
	if (mesh->HasPositions())
	{
		my_mesh->data.num_vertex = mesh->mNumVertices;
		my_mesh->data.vertex = new vec[my_mesh->data.num_vertex];
		memcpy(my_mesh->data.vertex, mesh->mVertices, sizeof(vec)*my_mesh->data.num_vertex);
		CONSOLELOG("New Mesh with:");
		CONSOLELOG("   - %d vertices", my_mesh->data.num_vertex);

	}
	//vertex
	glGenBuffers(1, (GLuint*) &(my_mesh->data.id_vertex));

	glBindBuffer(GL_ARRAY_BUFFER, my_mesh->data.id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec)*my_mesh->data.num_vertex, my_mesh->data.vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (mesh->HasFaces())
	{
		my_mesh->data.num_index = mesh->mNumFaces * 3;
		my_mesh->data.index = new uint[my_mesh->data.num_index];
		CONSOLELOG("   - %d indices", my_mesh->data.num_index);
		for (uint i = 0; i < mesh->mNumFaces; ++i)
		{
			if (mesh->mFaces[i].mNumIndices != 3)
			{
				CONSOLELOG("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&my_mesh->data.index[i * 3], mesh->mFaces[i].mIndices, sizeof(uint) * 3);
				correct_num_faces = true;

			}
		}
		CONSOLELOG("   - %d triangles", my_mesh->data.num_index / 3);
		
	}
	//index
	glGenBuffers(1, (GLuint*) &(my_mesh->data.id_index));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_mesh->data.id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * my_mesh->data.num_index, my_mesh->data.index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	if (mesh->HasNormals())
	{
		my_mesh->data.num_normals = mesh->mNumVertices * 3;
		my_mesh->data.normals = new vec[my_mesh->data.num_normals];
		memcpy(my_mesh->data.normals, mesh->mNormals, sizeof(float)*my_mesh->data.num_normals);

		CONSOLELOG("   - %d normals", my_mesh->data.num_normals);
	
	}
	glGenBuffers(1, (GLuint*)&(my_mesh->data.id_normals));

	glBindBuffer(GL_ARRAY_BUFFER, my_mesh->data.id_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec)*my_mesh->data.num_normals, my_mesh->data.normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	if (mesh->HasTextureCoords(0)) {
		my_mesh->data.num_texture_coords = mesh->mNumVertices;
		my_mesh->data.TexCoords = new float[my_mesh->data.num_texture_coords * 3];
		
		memcpy(my_mesh->data.TexCoords, mesh->mTextureCoords[0], sizeof(float)*my_mesh->data.num_texture_coords*3);

		CONSOLELOG("   - %d texture coords", my_mesh->data.num_texture_coords);

		if (App->texture->current != nullptr)
		{
			if (App->scene_loader->first_mesh == true)
			{
				
				my_mesh->id_texture = (GLuint)App->texture->LoadTexFromPath(".//Assets//Baker_House.png");
				App->texture->current = ".//Assets//Baker_House.png";
				initial_aux++;
				if(initial_aux == 2)
					App->scene_loader->first_mesh = false;
			}
			else
			{
				my_mesh->id_texture = (GLuint)App->texture->LoadTexFromPath(App->texture->current);
			}
				
		}
		else
		{
			CONSOLELOG("Texture path is null.");
		}
					
	}
	else
	{
		CONSOLELOG("Warning, mesh has no Texture Coords.");
	}
	glGenBuffers(1, (GLuint*)&my_mesh->data.id_texture_coords);

	glBindBuffer(GL_ARRAY_BUFFER, my_mesh->data.id_texture_coords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * my_mesh->data.num_texture_coords * 3, my_mesh->data.TexCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//POSITION-SCALING-ROTATION
	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion quat_rot;

	_scene->mRootNode->mTransformation.Decompose(scaling, quat_rot, translation);

	math::Quat math_quat(quat_rot.x, quat_rot.y, quat_rot.z, quat_rot.w); // to be able to pass to EULER

	my_mesh->t.pos = { translation.x, translation.y, translation.z };
	CONSOLELOG("Mesh position { %f,%f,%f }",  my_mesh->t.pos.x, my_mesh->t.pos.y, my_mesh->t.pos.z);
	my_mesh->t.scale = { scaling.x, scaling.y, scaling.z };
	CONSOLELOG("Mesh  scale { %f,%f,%f }",  my_mesh->t.scale.x, my_mesh->t.scale.y, my_mesh->t.scale.z);
	my_mesh->t.rot = math::RadToDeg(math_quat.ToEulerXYZ());
	CONSOLELOG("Mesh rotation { %f,%f,%f }",  my_mesh->t.rot.x, my_mesh->t.rot.y, my_mesh->t.rot.z);

	//DEBUG BOX
	AABB debug_box(float3::zero, float3::zero);
	//debug_box.MinimalEnclosingAABB((float3*)mesh->mVertices, mesh->mNumVertices);
	debug_box.Enclose((float3*)mesh->mVertices, mesh->mNumVertices);
	my_mesh->outside_box = debug_box;

	//DECIDE TO LOAD OR NOT
	if (correct_num_faces && mesh->HasPositions())
	{
		App->scene_loader->scene_objects.push_back(my_mesh);

		App->camera->Focus(my_mesh->outside_box);
		
	}
	else
		LOG("Error Loading Mesh");
}

void AssimpToConsoleLog(const char * str, char * userData)
{
	CONSOLELOG("%s", str);
}
