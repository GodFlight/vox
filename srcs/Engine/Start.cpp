#include "Engine/Engine.h"
#include "Engine/Locator.hpp"
#include "Player/Player.h"
#include "World/World.h"

RenderEngineConfig glConfig() {
	RenderEngineConfig config;
	config.windowSize = glm::ivec2(1500, 900);
	config.windowPos = glm::ivec2(900, 100);
	config.windowName = std::string("Test");
	config.windowResizeable = false;
	config.cursorEnabled = true;
	config.cursorRaw = true;
	config.glVersionMajor = 4;
	config.glVersionMinor = 1;
	config.glForwardCompatibility = true;
	config.glDepthTest = true;
	config.glCullFace = false;
	return config;
}

Game::Game() {
	_finished = false;
	Locator::provideLogger(NULL);

	ILogger* log = new TerminalLogger();
	Locator::provideLogger(log);
	
	_renderer = new GLRenderer(this, glConfig());
	_input = new Input();
	_resources = new ResourceLoader();

	Entity* player = new Player(this);
	AddEntity(player);

	_ui = new UIController(this);

	_world = new World(this);
	// RenderModel* monkey = new RenderModel(_renderer, _resources->GetShader("Base"), _resources->GetTexture("Planks"), _resources->GetGeometry("Monkey"));
	// Shard* testShard = new Shard(this, glm::ivec3(0));
};

Game::~Game() {
	delete _input;
	delete _renderer;

	ILogger* log = Locator::getLogger();
	delete log;
};