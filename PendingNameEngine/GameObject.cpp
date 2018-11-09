#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentTransf.h"
#include "OpenGL.h"
#include "ImGui/imgui.h"
#include "Material.h"



GameObject::GameObject(std::string _name, GameObject* parent_go, bool _active) : parent(parent_go), active(_active), name(_name)
{
	if (parent_go != nullptr)
	{
		parent_go->PushChild(this);
	}
	//TODO bounding box
	//TODO serialization

	/*if (parent_go->IsStatic())
		staticgo = true;
	else
		staticgo = false;*/
}



GameObject::~GameObject()
{
}

void GameObject::Update()
{
	/*for (uint i = 0; i < children.size(); i++) {
		children[i]->Update();
	}

	for (uint i = 0; i < components.size(); i++) {
		components[i]->Update();
	}*/
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

bool GameObject::IsSelected() const
{
	return selected;
}

void GameObject::SetSelected(bool _selected)
{
	selected = _selected;
}

void GameObject::SetName(const std::string & n)
{
	name = n;
}

std::string GameObject::GetName() const
{
	return name;
}

void GameObject::Draw()
{
	
	ComponentMesh* aux_mesh = (ComponentMesh*)this->GetComponentByType(MESH);
	ComponentMaterial* aux_material = (ComponentMaterial*)this->GetComponentByType(MATERIAL);
	ComponentTransf* aux_transform = (ComponentTransf*)this->GetComponentByType(TRANSFORMATION);

	if (aux_mesh != nullptr)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//glMultMatrixf(aux_transform->GetLocalTransform().Transposed().ptr());

		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, aux_mesh->my_mesh->id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, aux_mesh->my_mesh->id_index);

		if (aux_mesh->my_mesh->num_texture_coords != 0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, aux_mesh->my_mesh->id_texture_coords);
			glTexCoordPointer(3, GL_FLOAT, 0, NULL);
		}

		if (aux_material != nullptr)
		{
			App->renderer3D->color_material = false;
			App->renderer3D->update_color_material();
			glBindTexture(GL_TEXTURE_2D, (GLuint)aux_material->mat->GetID());
		}

		glDrawElements(GL_TRIANGLES, aux_mesh->my_mesh->num_index, GL_UNSIGNED_INT, NULL);

		//Unbind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Disable Client
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		

		App->renderer3D->color_material = true;
		App->renderer3D->update_color_material();

	}
	for (uint i = 0; i < children.size(); i++)
	{
		if (children[i]->IsActive())
			children[i]->Draw();
	}
	glPopMatrix();


}

void GameObject::DrawInHierarchy()
{

	uint flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	if (bool draw_node = ImGui::TreeNodeEx(name.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
		{
			for (uint j = 0; j < App->scene_loader->scene_objects.size(); j++)
			{
				if (App->scene_loader->scene_objects[j]->IsSelected())
				{
					App->scene_loader->scene_objects[j]->SetSelected(false);
				}
				this->selected = true;
			}
			
		}
		for (uint i = 0; i < children.size(); i++)
		{
			children[i]->DrawInHierarchy();
		}
		
		ImGui::TreePop();
	}
	
}

void GameObject::DrawInInspector()
{
	ImGui::Text(name.c_str());
	ImGui::SameLine();
	ImGui::Checkbox("active", &active);
	ImGui::SameLine();
	ImGui::Checkbox("static", &staticgo);

	for (std::vector<Component*>::const_iterator c_it = components.begin(); c_it != components.end(); c_it++)
	{
		(*c_it)->DrawInInspector();
	}

}

Component * GameObject::GetComponentByType(ComponentType type) const
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

std::vector<Component*> GameObject::GetComponents() const
{
	return components;
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

std::vector<GameObject*> GameObject::GetChildren() const
{
	return children;
}
