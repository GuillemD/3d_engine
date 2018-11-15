#include "Application.h"
#include "Importer.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentTransf.h"
#include "ComponentMaterial.h"
#include "Module.h"
#include "Globals.h"
#include "Mesh.h"
#include "Material.h"


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

	App->CreateNewDirectory("Assets\\Mesh");
	App->CreateNewDirectory("Library\\Mesh");

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
		
		std::vector<Material*> scene_mats;
		if (scene->HasMaterials())
		{
			for (uint m = 0; m < scene->mNumMaterials; ++m)
			{
				Material* material = nullptr;
				aiMaterial* curr_mat = scene->mMaterials[m];
				aiString assimp_path;

				curr_mat->GetTexture(aiTextureType_DIFFUSE, 0, &assimp_path);
				std::string m_path = assimp_path.C_Str();
				uint name_pos = m_path.find_last_of("\\");
				tex_path += m_path.substr(name_pos + 1);

				material = App->texture->LoadMaterial(tex_path.c_str());
				scene_mats.push_back(material);
			}
		}
		std::string path = full_path;
		uint start = path.find_last_of("//"); uint end = path.find_last_of(".");
		std::string root_name = path.substr(start + 1, end - start - 1);

		GameObject* root_go = App->scene_loader->CreateGameObject(root_name.c_str());
			
		LoadMesh(scene,scene->mRootNode, root_go, scene_mats);

		aiReleaseImport(scene);
	}
	else
	{
		CONSOLELOG("Error loading scene %s", full_path);
	}
		

	return ret;
}

void Importer::LoadMesh(const aiScene* _scene, const aiNode * node, GameObject* parent_go,const std::vector<Material*>& mats)
{
	aiString s_name = node->mName;
	GameObject* first = parent_go;
	bool discard = false;

	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion quat_rot;
	node->mTransformation.Decompose(scaling, quat_rot, translation);

	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		GameObject* aux;
		if (parent_go == nullptr)
			aux = new GameObject(s_name.C_Str());
		else
			aux = parent_go->CreateChild(s_name.C_Str());

		if (i == 0)
			first = aux;

		Mesh* my_mesh = new Mesh();
		aiMesh* aimesh = _scene->mMeshes[node->mMeshes[i]];

		if (aimesh->HasPositions() && aimesh != nullptr) //Vertex
		{
			my_mesh->num_vertex = aimesh->mNumVertices;
			my_mesh->vertex = new float[my_mesh->num_vertex*3];
			memcpy(my_mesh->vertex, aimesh->mVertices, sizeof(vec)*my_mesh->num_vertex);
			CONSOLELOG("New Mesh with:");
			CONSOLELOG("   - %d vertices", my_mesh->num_vertex);

			glGenBuffers(1, (GLuint*) &(my_mesh->id_vertex));

			glBindBuffer(GL_ARRAY_BUFFER, my_mesh->id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec)*my_mesh->num_vertex, my_mesh->vertex, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
		else
		{
			CONSOLELOG("WARNING! Mesh has no vertices");
		}
		if (aimesh->HasFaces())
		{
			my_mesh->num_index = aimesh->mNumFaces * 3;
			my_mesh->index = new uint[my_mesh->num_index];
			CONSOLELOG("   - %d indices", my_mesh->num_index);

			for (uint i = 0; i < aimesh->mNumFaces; ++i)
			{
				if (aimesh->mFaces[i].mNumIndices != 3)
				{
					CONSOLELOG("WARNING, geometry face with != 3 indices!");
					discard = true;
				}
				else
				{
					memcpy(&my_mesh->index[i * 3], aimesh->mFaces[i].mIndices, sizeof(uint) * 3);	

				}
			}
			CONSOLELOG("   - %d triangles", my_mesh->num_index / 3);

			//index
			glGenBuffers(1, (GLuint*) &(my_mesh->id_index));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_mesh->id_index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * my_mesh->num_index, my_mesh->index, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else
		{
			CONSOLELOG("WARNING! Mesh with no faces. Will not load.");
		}

		if (aimesh->HasTextureCoords(0)) {

			my_mesh->num_texture_coords = aimesh->mNumVertices;
			my_mesh->TexCoords = new float[my_mesh->num_texture_coords * 3];

			memcpy(my_mesh->TexCoords, aimesh->mTextureCoords[0], sizeof(float)*my_mesh->num_texture_coords * 3);

			CONSOLELOG("   - %d texture coords", my_mesh->num_texture_coords);

			glGenBuffers(1, (GLuint*)&my_mesh->id_texture_coords);

			glBindBuffer(GL_ARRAY_BUFFER, my_mesh->id_texture_coords);
			glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * my_mesh->num_texture_coords * 3, my_mesh->TexCoords, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
		else
		{
			CONSOLELOG("Warning, mesh has no Texture Coords.");
			discard = true;
		}
		if (discard)
		{
			my_mesh->UnloadVRAMBuffers();
			CONSOLELOG("Error loading mesh");
		}
		else
		{
			BinarySave(my_mesh);
			//DEBUG BOX
			AABB debug_box(float3::zero, float3::zero);
			debug_box.Enclose((float3*)aimesh->mVertices, aimesh->mNumVertices);
			my_mesh->outside_box = debug_box;

			ComponentMesh* cmp_mesh = new ComponentMesh(aux);
			cmp_mesh->AttachMesh(my_mesh);
			cmp_mesh->Enable();
			aux->AddComponent((ComponentMesh*)cmp_mesh);

			ComponentMaterial* cmp_mat = new ComponentMaterial(aux);
			cmp_mat->Enable();
			cmp_mat->mat = mats[aimesh->mMaterialIndex];
			cmp_mat->mat->path = tex_path;
			aux->AddComponent((ComponentMaterial*)cmp_mat);
		}

		ComponentTransf* cmp_transf = (ComponentTransf*)aux->GetComponentByType(TRANSFORMATION);
		float3 _pos(translation.x, translation.y, translation.z);
		float3 _scale(scaling.x, scaling.y, scaling.z);
		Quat _rot(quat_rot.x, quat_rot.y, quat_rot.z, quat_rot.w);
		cmp_transf->SetTransform(_pos, _scale, _rot);


		App->scene_loader->scene_objects.push_back(aux);
		App->camera->Focus(my_mesh->outside_box);

	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		LoadMesh(_scene, node->mChildren[i], first, mats);
	}
	
}

void Importer::BinarySave(Mesh * mesh)
{
	uint elements_num[3] = { mesh->num_index, mesh->num_vertex * 3, mesh->num_texture_coords * 3 };
	uint total_size = sizeof(elements_num) + sizeof(uint)*mesh->num_index + sizeof(float)*(mesh->num_vertex * 3 + mesh->num_texture_coords * 3);

	char* data = new char[total_size];
	char* cursor = data;

	//number of elements
	uint size = sizeof(elements_num);
	memcpy(cursor, elements_num, size);
	cursor += size;

	//indices
	size = sizeof(uint)*elements_num[0];
	memcpy(cursor, mesh->index, size);
	cursor += size;

	//vertices
	size = sizeof(float)*elements_num[1];
	memcpy(cursor, mesh->vertex, size);
	cursor += size;

	//texture_coords
	size = sizeof(float)*elements_num[2];
	memcpy(cursor, mesh->TexCoords, size);
	cursor += size;

	//Serialize data to file
	char file[69];
	sprintf_s(file, "Library\\Mesh\\Mesh_%d.pn", num_mesh++);

	FILE* f = fopen(file, "wb");
	fwrite(data, sizeof(char), total_size, f);
	fclose(f);

	RELEASE_ARRAY(data);

	CONSOLELOG("Created %s.", file);
}

void* Importer::BinaryLoad(const char * file_path)
{
	Mesh* mesh = new Mesh();
	//Open file path + size
	FILE* file = fopen(file_path, "rb");
	fseek(file, 0L, SEEK_END);
	uint total_size = ftell(file);
	rewind(file);

	// Copy file to buffer
	char* data = new char[total_size];
	char* cursor = data;
	fread(data, sizeof(char), total_size, file);
	fclose(file);

	//Read num_elements
	uint elements_num[3];
	uint size = sizeof(elements_num);
	memcpy(elements_num, cursor, size);
	cursor += size;

	//Read index
	uint* ind = new uint[elements_num[0]];
	size = sizeof(uint)*elements_num[0];
	memcpy(ind, cursor, size);
	cursor += size;

	//Read vertex
	float* vert = new float[elements_num[1]];
	size = sizeof(float)*elements_num[1];
	memcpy(vert, cursor, size);
	cursor += size;

	//Read TexCoords
	float* tex_coords = new float[elements_num[2]];
	size = sizeof(float)*elements_num[2];
	memcpy(tex_coords, cursor, size);
	cursor += size;

	//Fill mesh with info
	mesh->num_index = elements_num[0];
	mesh->index = ind;
	mesh->num_vertex = elements_num[1] / 3;
	mesh->vertex = vert;
	mesh->num_texture_coords = elements_num[2] / 3;
	mesh->TexCoords = tex_coords;
	
	GameObject* go = App->scene_loader->CreateGameObject("GameObject");
	ComponentMesh* cmp_mesh = new ComponentMesh(go);
	
	cmp_mesh->AttachMesh(mesh);
	go->AddComponent((ComponentMesh*)cmp_mesh);

	RELEASE_ARRAY(data);

	return mesh;
}


void AssimpToConsoleLog(const char * str, char * userData)
{
	CONSOLELOG("%s", str);
}
