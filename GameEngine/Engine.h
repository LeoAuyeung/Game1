#ifndef _ENGINE_H
#define _ENGINE_H

//C Runtime Header Files
#ifndef _WINDOWS_
	#include <Windows.h>
#endif // !_WINDOWS_

#ifndef _MAP_
	#include <map>
#endif

//Forward Declaration
class System;

//State enumeration
enum EngineState {
	Invalid,
	Constructing,
	Initializing,
	Running,
	ShuttingDown,
	Destroying
};

class Engine
{
public:
	Engine();
	~Engine();

	void* operator new(size_t size);
	void operator delete(void* pdelete);

	static EngineState getEngineState() { return m_EngineState; }

private:

	int initialize();
	int draw();
	int update();
	int shutDown();

	//Add a core system to the engine
	int AddSystem(System* psys);
	//Retrieve a core system form the engine
	template<typename T>
	T* GetSystem(SystemType systype) {

	}

	static EngineState m_EngineState;

};

#endif