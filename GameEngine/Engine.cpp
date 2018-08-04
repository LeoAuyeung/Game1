#include "Engine.h"

//Additional include files
#include "System.h"
#include "Game.h"

#ifndef _DELETEMACRO_H
	#include "deletemacros.h"
#endif
#ifndef _STRING_H
	#include "string.h"
#endif

EngineState Engine::m_EngineState = EngineState::Invalid;

Engine::Engine() {
	m_EngineState = EngineState::Constructing;
}

Engine::~Engine() {
	m_EngineState = EngineState::Destroying;
}

//--------------------Public methods--------------------
#pragma region Public Methods
int Engine::runLoop() {

	Context context;

	//If fail to initialize, return 0
	if (!this->initialize())
		return 0;

	srand(GetTickCount());

	MSG msg = {};

	m_EngineState = EngineState::Running;

	while (msg.message != WM_QUIT && m_EngineState == EngineState::Running)
	{
		//CheckResize();

		//If there is a message, translate & dispatch message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		this->update(context);
		this->draw(context);
	}

	//Logger:Log("Ending the program");
	//Logger::WriteLogFile();

	//If fail to shutdown, return 0
	if (!this->shutDown())
		return 0;

	return msg.wParam;
}
#pragma endregion
//--------------------End Public Methods--------------------

//--------------------Private Methods--------------------
#pragma region Private Methods
int Engine::initialize() {
	m_EngineState = EngineState::Initializing;

	Game* game = CreateGame();

	if (!game) { return false; }

	//Add some systems

	return true;

}
int Engine::draw(const Context& context) {
	return true;
}
int Engine::update(const Context& context) {
	return true;
}
int Engine::shutDown() {
	m_EngineState = EngineState::ShuttingDown;

	for (std::pair<SystemType, System*> psys : m_mapSystems) {
		//if (!psys.second->ShutDown()) {
			//Log::Logger("Failed to shutdown system" + psys->GetSystemType());
			//continue;
		//}
		SafeDelete(psys.second);
	}

	return true;
}

//Add a core system to the engine
int Engine::AddSystem(System* psys) {
	auto element = m_mapSystems.insert(std::make_pair(psys->GetType(), psys));
	if (element.second) return true;

	return false;
}

//Create the game instance
Game* Engine::CreateGame() {

	if (!AddSystem(new Game(GameData())))
		return nullptr;
	
	Game* game = GetSystem<Game> (SystemType::Sys_Game);

	if (!game)
		return nullptr;

	/*if (!game->Initialize())
		return nullptr;*/

	return game;
}
#pragma endregion
//--------------------End Private Methods--------------------