#include "Application.h"
#include "Importer.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentTransf.h"
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
		std::string path = full_path;
		uint start = path.find_last_of("//"); uint end = path.find_last_of(".");
		std::string root_name = path.substr(start + 1, end - start - 1);

		GameObject* root_go = App->scene_loader->CreateGameObject(root_name.c_str());
			
		LoadMesh(scene,scene->mRootNode, root_go);

		aiReleaseImport(scene);
	}
	else
	{
		CONSOLELOG("Error loading scene %s", full_path);
	}
		

	return ret;
}

void Importer::LoadMesh(const aiScene* _scene, const aiNode * node, GameObject* parent_go)
{
	aiString s_name = node->mName;
	GameObject* go = new GameObject(s_name.C_Str());
	bool correct_num_faces = false;

	if (node->mNumMeshes >= 1)
	{
		if (_scene != nullptr && _scene->HasMeshes())
		{
			for (uint i = 0; i < node->mNumMeshes; i++)
			{
				GameObject* child_go = new GameObject(go->name, go); 
				
				Mesh* my_mesh = new Mesh();
				aiMesh* aimesh = _scene->mMeshes[node->mMeshes[i]];

				if (aimesh->HasPositions()) //Vertex
				{
					my_mesh->data.num_vertex = aimesh->mNumVertices;
					my_mesh->data.vertex = new vec[my_mesh->data.num_vertex];
					memcpy(my_mesh->data.vertex, aimesh->mVertices, sizeof(vec)*my_mesh->data.num_vertex);
					CONSOLELOG("New Mesh with:");
					CONSOLELOG("   - %d vertices", my_mesh->data.num_vertex);

					glGenBuffers(1, (GLuint*) &(my_mesh->data.id_vertex));

					glBindBuffer(GL_ARRAY_BUFFER, my_mesh->data.id_vertex);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vec)*my_mesh->data.num_vertex, my_mesh->data.vertex, GL_STATIC_DRAW);
					glBindBuffer(GL_ARRAY_BUFFER, 0);

				}
				else
				{
					CONSOLELOG("WARNING! Mesh has no vertices");
				}
				if (aimesh->HasFaces())
				{
					my_mesh->data.num_index = aimesh->mNumFaces * 3;
					my_mesh->data.index = new uint[my_mesh->data.num_index];
					CONSOLELOG("   - %d indices", my_mesh->data.num_index);

					for (uint i = 0; i < aimesh->mNumFaces; ++i)
					{
						if (aimesh->mFaces[i].mNumIndices != 3)
						{
							CONSOLELOG("WARNING, geometry face with != 3 indices!");
						}
						else
						{
							memcpy(&my_mesh->data.index[i * 3], aimesh->mFaces[i].mIndices, sizeof(uint) * 3);
							correct_num_faces = true;

						}
					}
					CONSOLELOG("   - %d triangles", my_mesh->data.num_index / 3);

					//index
					glGenBuffers(1, (GLuint*) &(my_mesh->data.id_index));

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_mesh->data.id_index);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * my_mesh->data.num_index, my_mesh->data.index, GL_STATIC_DRAW);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				}
				else
				{
					CONSOLELOG("WARNING! Mesh with no faces. Will not load.");
				}

				if (aimesh->HasNormals())
				{
					my_mesh->data.num_normals = aimesh->mNumVertices * 3;
					my_mesh->data.normals = new vec[my_mesh->data.num_normals];
					memcpy(my_mesh->data.normals, aimesh->mNormals, sizeof(float)*my_mesh->data.num_normals);

					CONSOLELOG("   - %d normals", my_mesh->data.num_normals);
					glGenBuffers(1, (GLuint*)&(my_mesh->data.id_normals));

					glBindBuffer(GL_ARRAY_BUFFER, my_mesh->data.id_normals);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vec)*my_mesh->data.num_normals, my_mesh->data.normals, GL_STATIC_DRAW);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}
				else
				{
					CONSOLELOG("WARNING! Mesh has no normals");
				}

				if (aimesh->HasTextureCoords(0)) {

					my_mesh->data.num_texture_coords = aimesh->mNumVertices;
					my_mesh->data.TexCoords = new float[my_mesh->data.num_texture_coords * 3];

					memcpy(my_mesh->data.TexCoords, aimesh->mTextureCoords[0], sizeof(float)*my_mesh->data.num_texture_coords * 3);

					CONSOLELOG("   - %d texture coords", my_mesh->data.num_texture_coords);

					glGenBuffers(1, (GLuint*)&my_mesh->data.id_texture_coords);

					glBindBuffer(GL_ARRAY_BUFFER, my_mesh->data.id_texture_coords);
					glBufferData(GL_ARRAY_BUFFER, sizeof(uint) * my_mesh->data.num_texture_coords * 3, my_mesh->data.TexCoords, GL_STATIC_DRAW);
					//glBindBuffer(GL_ARRAY_BUFFER, 0);

				}
				else
				{
					CONSOLELOG("Warning, mesh has no Texture Coords.");
				}

				//DEBUG BOX
				AABB debug_box(float3::zero, float3::zero);
				debug_box.Enclose((float3*)aimesh->mVertices, aimesh->mNumVertices);
				my_mesh->outside_box = debug_box;

				ComponentMesh* cmp_mesh = new ComponentMesh(child_go);
				cmp_mesh->AttachMesh(my_mesh);
				cmp_mesh->Enable();

				child_go->components.push_back(cmp_mesh);
				
				if (node != nullptr)
				{
					aiVector3D translation;
					aiVector3D scaling;
					aiQuaternion quat_rot;

					node->mTransformation.Decompose(scaling, quat_rot, translation);

					ComponentTransf* cmp_transf = new ComponentTransf(child_go);

					cmp_transf->position = { translation.x,translation.y, translation.z };
					CONSOLELOG("Mesh position { %f,%f,%f }", translation.x, translation.y, translation.z);
					cmp_transf->scale = { scaling.x,scaling.y, scaling.z };
					CONSOLELOG("Mesh  scale { %f,%f,%f }", scaling.x, scaling.y, scaling.z);
					
					math::Quat math_quat(quat_rot.x, quat_rot.y, quat_rot.z, quat_rot.w); // to be able to pass to EULER
					cmp_transf->quatRotation = { quat_rot.x, quat_rot.y, quat_rot.z, quat_rot.w };
					cmp_transf->eulerRotation = math::RadToDeg(math_quat.ToEulerXYZ());

					CONSOLELOG("Mesh rotation { %f,%f,%f }", cmp_transf->eulerRotation.x, cmp_transf->eulerRotation.y, cmp_transf->eulerRotation.z);

					child_go->components.push_back(cmp_transf);
				}

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				parent_go->children.push_back(child_go);

				if (correct_num_faces)
				{
					App->scene_loader->scene_objects.push_back(child_go);

					App->camera->Focus(my_mesh->outside_box);
				}
				else
				{
					CONSOLELOG("Mesh not pushed into scene");
				}

			}
			go = parent_go;
		}
		else
		{
			CONSOLELOG("ERROR! Cannot load mesh");
		}
	}
	else
	{
		
		if (parent_go != nullptr)
			parent_go->children.push_back(go);

		
		if (node != nullptr)
		{
			aiVector3D translation;
			aiVector3D scaling;
			aiQuaternion quat_rot;

			node->mTransformation.Decompose(scaling, quat_rot, translation);

			ComponentTransf* cmp_transf = new ComponentTransf(go);

			cmp_transf->position = { translation.x,translation.y, translation.z };
			CONSOLELOG("Mesh position { %f,%f,%f }", translation.x, translation.y, translation.z);
			cmp_transf->scale = { scaling.x,scaling.y, scaling.z };
			CONSOLELOG("Mesh  scale { %f,%f,%f }", scaling.x, scaling.y, scaling.z);

			math::Quat math_quat(quat_rot.x, quat_rot.y, quat_rot.z, quat_rot.w); // to be able to pass to EULER
			cmp_transf->quatRotation = { quat_rot.x, quat_rot.y, quat_rot.z, quat_rot.w };
			cmp_transf->eulerRotation = math::RadToDeg(math_quat.ToEulerXYZ());

			CONSOLELOG("Mesh rotation { %f,%f,%f }", cmp_transf->eulerRotation.x, cmp_transf->eulerRotation.y, cmp_transf->eulerRotation.z);

			go->components.push_back(cmp_transf);
		}
		App->scene_loader->scene_objects.push_back(go);
	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		LoadMesh(_scene, node->mChildren[i], go);
	}
	
}

void AssimpToConsoleLog(const char * str, char * userData)
{
	CONSOLELOG("%s", str);
}
