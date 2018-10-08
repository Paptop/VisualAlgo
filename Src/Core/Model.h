#ifndef MODEL_H
#define MODEL_H

namespace Vi
{
	class Model
	{
	public:
		virtual void Init() = 0;
		virtual void PrintToConsole() = 0;
		virtual ~Model(){}
	};
}

#endif // !MODEL_H
