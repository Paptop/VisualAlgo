#ifndef GOMANAGER_H
#define GOMANAGER_H

#include <list>

namespace Vi
{
	class GameObject;
	class Window;

	class GoManager
	{
	public:
		static GoManager& GetInstance()
		{
			static GoManager manager;
			return manager;
		}

		void Add(GameObject* go);
		void Remove(GameObject* go);
		void Update(float fDeltaTime);
		void Render(Window* window);

	private:
		GoManager()
		{
		}

	private:
		std::list<GameObject*> m_lGameObjects;
	};

	#define GOM GoManager::GetInstance()
}

#endif // GoManager