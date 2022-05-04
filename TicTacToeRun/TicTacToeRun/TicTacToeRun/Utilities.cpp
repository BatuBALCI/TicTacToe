#include "Utilities.h"

void Utilities::createStrip(static const char* vertices, static const char* indices, std::vector<Mesh*>& meshList)
{
	Mesh* obj1 = new Mesh();
	Mesh* obj2 = new Mesh();
	Mesh* obj3 = new Mesh();
	Mesh* obj4 = new Mesh();

	auto vertexVector = Mesh::ReadFloatsFromFile(vertices);
	auto indexVector = Mesh::ReadFloatsFromFile(indices);

	obj1->CreateMesh(vertexVector, indexVector, GL_TRIANGLES);
	obj2->CreateMesh(vertexVector, indexVector, GL_TRIANGLES);
	obj3->CreateMesh(vertexVector, indexVector, GL_TRIANGLES);
	obj4->CreateMesh(vertexVector, indexVector, GL_TRIANGLES);


	meshList.push_back(obj1);
	meshList.push_back(obj2);
	meshList.push_back(obj3);
	meshList.push_back(obj4);
}

void Utilities::createGrid(std::vector<Mesh*> meshList, GLuint uniformModel)
{
	// 4x4 matrix with zeros;
	glm::mat4 model;
	//First apply translation than apply rotation glm automatically combine this two movement.
	model = glm::translate(model, glm::vec3(-0.3333333f, 0.0f, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.0025f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	meshList.at(0)->RenderMesh();

	glm::mat4 model1;
	model1 = glm::translate(model1, glm::vec3(0.333333f, 0.0f, 0.0f));
	model1 = glm::rotate(model1, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model1 = glm::scale(model1, glm::vec3(0.0025f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model1));
	meshList.at(1)->RenderMesh();

	glm::mat4 model2;
	model2 = glm::translate(model2, glm::vec3(0.0f, -0.3333333f, 0.0f));
	model2 = glm::rotate(model2, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model2 = glm::scale(model2, glm::vec3(1.0f, 0.0025f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model2));
	meshList.at(2)->RenderMesh();

	glm::mat4 model3;
	model3 = glm::translate(model3, glm::vec3(0.0f, 0.33333333f, 0.0f));
	model3 = glm::rotate(model3, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model3 = glm::scale(model3, glm::vec3(1.0f, 0.0025f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model3));
	meshList.at(3)->RenderMesh();
}

void Utilities::createXO(static const char* vertices, static const char* indices, std::vector<Mesh*>& meshList)
{
	Mesh* obj1 = new Mesh();

	auto vertexVector = Mesh::ReadFloatsFromFile(vertices);
	auto indexVector = Mesh::ReadFloatsFromFile(indices);

	obj1->CreateMesh(vertexVector, indexVector, GL_TRIANGLES);

	meshList.push_back(obj1);
}

void Utilities::drawX(std::vector<Mesh*> meshList, GLuint uniformModel, float xOffset, float yOffset)
{
	// 4x4 matrix with zeros;
	glm::mat4 model;
	//First apply translation than apply rotation glm automatically combine this two movement.
	model = glm::translate(model, glm::vec3(xOffset, yOffset, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	meshList.at(5)->RenderMesh();
}

void Utilities::drawO(std::vector<Mesh*> meshList, GLuint uniformModel, float xOffset, float yOffset)
{
	// 4x4 matrix with zeros;
	glm::mat4 model;
	//First apply translation than apply rotation glm automatically combine this two movement.
	model = glm::translate(model, glm::vec3(xOffset, yOffset, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	meshList.at(4)->RenderMesh();
}

// this method is called to get the name and the type of the players.
void Utilities::GetTypeAndNameForm(Player::Player* playerObj, Window& window, char* name, int* currentItems, const char* items[], const char* formName)
{

	ImGui::NewFrame();
	ImGui::Begin(formName);

	ImGui::SetWindowPos({ (float)window.GetBufferWidth() / 2 - 140, (float)window.GetBufferHeight() / 2 - 140 });
	ImGui::SetWindowSize({ 280,280 });

	ImGui::InputText("Enter Name", name, IM_ARRAYSIZE(name));
	
	
	if (ImGui::Combo("Type", currentItems, items, 2)) {
		auto typeVal = Types::IntegarGame(*currentItems);
		playerObj->SetType(typeVal);
	}

	if (ImGui::Button("Submit") == true)
	{
		wstring nameStr(&name[0], &name[IM_ARRAYSIZE(name)]);
		auto nameVal = Types::StringGame(nameStr);
		playerObj->SetName(nameVal);
	}



	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	window.swapBuffers();
}
