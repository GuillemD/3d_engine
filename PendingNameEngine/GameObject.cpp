#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentTransf.h"
#include "OpenGL.h"
#include "ImGui/imgui.h"
#include "Material.h"



GameObject::GameObject(std::string _name, GameObject* parent_go, bool _active)
{
	parent = parent_go;
	active = _active;
	name = _name;
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

/*void GameObject::Draw()
{
	
	
	for (std::vector<Component*>::iterator comp = components.begin(); comp != components.end(); comp++)
	{
		if ((*comp)->GetType() == ComponentType::MATERIAL)
		{
			ComponentMaterial* c_m = (ComponentMaterial*)(*comp);
			if (c_m->mat != nullptr)
			{
				glBindTexture(GL_TEXTURE_2D, c_m->mat->GetID());
			}
		}
		
	}
	for (std::vector<Component*>::iterator comp = components.begin(); comp != components.end(); comp++)
	{
		if ((*comp)->GetType() == ComponentType::MESH)
		{
			ComponentMesh* c_mesh = (ComponentMesh*)(*comp);
			if (c_mesh->my_mesh != nullptr)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, c_mesh->my_mesh->data.id_vertex);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_mesh->my_mesh->data.id_index);

				if (c_mesh->my_mesh->data.num_texture_coords != 0)
				{
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glBindBuffer(GL_ARRAY_BUFFER, c_mesh->my_mesh->data.id_texture_coords);
					glTexCoordPointer(3, GL_FLOAT, 0, NULL);
				}


				glDrawElements(GL_TRIANGLES, c_mesh->my_mesh->data.num_index, GL_UNSIGNED_INT, NULL);
			}
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			break;
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	if (!children.empty())
	{
		for (std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); it++)
		{
			if ((*it)->active)
			{
				(*it)->Draw();
			}
		}
		
	}
	
}*/

void GameObject::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	ComponentMesh* aux_mesh = (ComponentMesh*)GetComponent(MESH);
	//ComponentMaterial* aux_material = (ComponentMaterial*)GetComponent(MATERIAL);
	//ComponentTransf* aux_transform = (ComponentTransf*)GetComponent(TRANSFORMATION);

	//glPushMatrix();
	//glMultMatrixf(aux_transform->trans_matrix_g.Transposed().ptr());

	if (aux_mesh != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, aux_mesh->my_mesh->data.id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, aux_mesh->my_mesh->data.id_index);

		if (aux_mesh->my_mesh->data.num_texture_coords != 0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, aux_mesh->my_mesh->data.id_texture_coords);
			glTexCoordPointer(3, GL_FLOAT, 0, NULL);
		}
		//glBindTexture(GL_TEXTURE_2D, aux_material->mat->id_texture);

		glDrawElements(GL_TRIANGLES, aux_mesh->my_mesh->data.num_index, GL_UNSIGNED_INT, NULL);
	}
	


	//Unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//Disable Client
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glPopMatrix();


}

void GameObject::DrawInHierarchy()
{
	for (uint i = 0; i < children.size(); i++)
	{
		uint flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (bool draw_node = ImGui::TreeNodeEx(children[i]->name.c_str(), flags))
		{
			children[i]->DrawInHierarchy();
			ImGui::TreePop();
		}
	}
}

void GameObject::DrawInInspector()
{
	ImGui::Text(name.c_str());
	ImGui::Separator();
	ImGui::Checkbox("active", &active);
	ImGui::SameLine();
	ImGui::Checkbox("static", &staticgo);

	for (std::vector<Component*>::const_iterator c_it = components.begin(); c_it != components.end(); c_it++)
	{
		(*c_it)->DrawInInspector();
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

GameObject * GameObject::GetParent() const
{
	return parent;
}

void GameObject::SetParent(GameObject * _parent)
{
	parent = _parent;
}

GameObject * GameObject::CreateChild(std::string _name)
{
	GameObject* child_go = new GameObject(_name, this, true);
	PushChild(child_go);
	return child_go;
}

void GameObject::PushChild(GameObject* _child)
{
	children.push_back(_child);
}
