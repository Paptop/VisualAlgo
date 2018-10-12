#ifndef MODEL_H
#define MODEL_H
#include "Src/Vi/GO/GameObject.h"

namespace Vi
{
	class Model : public GameObject
	{
	public:
		virtual void Init() = 0;
		virtual void PrintToConsole() = 0;
		virtual ~Model(){}
	};
}

#endif // !MODEL_H
