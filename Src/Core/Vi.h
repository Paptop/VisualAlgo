#ifndef VI_H
#define VI_H

#include <iostream>

namespace Vi
{
	class Window;
	class Model;

	class ViAl
	{
	public:
		ViAl();
		~ViAl();
		void Start();

	private:
		void Loop();
		void Init();

	private:
		Window* m_pcWindow;
		Model*  m_pcModel;
		bool m_bIsRunning;

	};
}



#endif