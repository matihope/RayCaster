#pragma once
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <GUI/Label.hpp>
#include <memory>
#include <iostream>
#include <stack>
#include <queue>
#include <WorldEntity/WorldEntity.hpp>

class Game {

	// variables
	bool m_run = true;
	float m_dt = 0; // delta time
	double m_fps_sum = 0.0;
	unsigned int m_fps_frame_count = 0;
	bool m_enable_print_fps = false;
	float m_physics_update_call_freq = 1. / 60.;
	float m_physics_update_counter = 0.f;
	sf::Cursor::Type m_current_cursor_type;

	// objects
	sf::Clock m_clock;
	JsonBridge m_game_settings;
	sf::RenderWindow m_window;
	std::stack<std::unique_ptr<WorldEntity>> m_scenes_stack;
	sf::View m_view;
	sf::Font m_font;
	GUI::Label m_fps_label;
	sf::Vector2f m_mouse_pos;

	// it's a singleton after all
	Game() = default;

	// helper functions
	void updateViewportSize();
	void recalculateAvgFps();
	std::queue<std::unique_ptr<WorldEntity>> m_safe_scene_delete_queue;

 public:
	// some more singleton stuff
	Game(Game &other) = delete;
	void operator=(const Game &) = delete;
	static Game &get();

	// the rest
	~Game();
	bool init(const std::string &settingsPath);
	void run();
	void draw();
	void update();
	void pollEvents();
	void setPrintFPS(const bool &printFPS);
	void stop();
	bool isRunning() const;
	sf::Vector2u getWindowSize();
	sf::Vector2u getViewportSize();
	void setViewportSize(sf::Vector2f newSize);
	sf::RenderWindow &getRenderWindow();
	bool isWindowActive() const;
	void addScene(std::unique_ptr<WorldEntity> newScene);
	void replaceTopScene(std::unique_ptr<WorldEntity> newScene);
	void popScene();
	sf::Vector2f getMousePos();
	sf::Font *getFont();
	const sf::View * getView();
	void setCameraCenterAt(const sf::Vector2f &pos);
	void setCursor(sf::Cursor::Type type);
};
