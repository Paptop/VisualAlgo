#include "Src/Vi/Sys/GoManager.h"
#include "Src/Vi/GO/GameObject.h"
#include "Src/Vi/Sys/Window.h"

void Vi::GoManager::Add(GameObject* go)
{
	m_lGameObjects.push_back(go);
}

void Vi::GoManager::Remove(GameObject* go)
{
	auto iter = std::find(m_lGameObjects.begin(), m_lGameObjects.end(), go);
	if (iter != m_lGameObjects.end())
	{
		m_lGameObjects.remove(*iter);
	}
}

void Vi::GoManager::Update(float fDeltatime)
{
	for (GameObject* go : m_lGameObjects)
	{
		go->Update(fDeltatime);
	}
}

void Vi::GoManager::Render(Window* window)
{
	for (GameObject* go: m_lGameObjects)
	{
		go->Render(window);
	}
}
