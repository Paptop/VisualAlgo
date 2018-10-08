#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Src/Vi/Sys/Window.h"

#include "Src/Vi/Math/ViMath.h"

namespace Vi
{
	class GameObject
	{
	public:
		virtual void Update(float fDeltaTime){}
		virtual void Render(Window* win) {}
		virtual ~GameObject(){}
	protected:
		Vector2 m_position;
	};
}


#endif // NODE_H
