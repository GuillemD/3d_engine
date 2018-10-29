#include "GameObject.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "OpenGL.h"



GameObject::GameObject()
{
	parent = nullptr;
	active = true;
}

GameObject::GameObject(GameObject * parent_go, std::string _name)
{
}



GameObject::~GameObject()
{
}

bool GameObject::IsActive() const
{
	return active;
}

void GameObject::SetActive(bool _active)
{
	if (active != _active)
	{
		active = _active;
	}
}

bool GameObject::IsStatic() const
{
	return staticgo;
}

void GameObject::SetStatic(bool _static)
{
	staticgo = _static;
}

void GameObject::Draw()
{
	if (active)
	{
		if (!children.empty())
		{
			for (std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); it++)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				ComponentMesh* mesh_it = (ComponentMesh*)(*it)->GetComponent(MESH);
				if (mesh_it != nullptr)
				{
					glBindBuffer(GL_ARRAY_BUFFER, mesh_it->my_mesh->data.id_vertex);
					glVertexPointer(3, GL_FLOAT, 0, NULL);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_it->my_mesh->data.id_index);

					if (mesh_it->my_mesh->data.num_texture_coords != 0)
					{
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glBindBuffer(GL_ARRAY_BUFFER, mesh_it->my_mesh->data.id_texture_coords);
						glTexCoordPointer(3, GL_FLOAT, 0, NULL);
					}
					//ComponentMaterial* mat_it = (ComponentMaterial*)(*it)->GetComponent(MATERIAL);
					//glBindTexture(GL_TEXTURE_2D, mat_it->id_texture);

					glDrawElements(GL_TRIANGLES, mesh_it->my_mesh->data.num_index, GL_UNSIGNED_INT, NULL);
				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			
		}
	}
}

Component * GameObject::GetComponent(ComponentType type) const
{
	Component* ret = nullptr;

	for (std::vector<Component*>::const_iterator cmp_it = components.begin(); cmp_it != components.end(); cmp_it++)
	{
		if ((*cmp_it)->GetType() == type)
		{
			ret = (*cmp_it);
			break;
		}
	}

	return ret;
}

void GameObject::AddComponent(Component * cp)
{
	components.push_back(cp);
}
