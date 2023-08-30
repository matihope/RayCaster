
#include <CollisionComponent/CollisionComponent.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include "ResourceManager/ResourceManager.hpp"
#include "Game.hpp"

sf::Vector2f scaleToFit(const sf::Vector2f viewSize, const sf::Vector2u windowSize) {
	sf::Vector2f scale;
	scale.x = viewSize.x / (float) windowSize.x;
	scale.y = viewSize.y / (float) windowSize.y;
	if (scale.x < scale.y) {
		scale.x *= 1 / scale.y;
		scale.y = 1;
	} else {
		scale.y *= 1 / scale.x;
		scale.x = 1;
	}
	return scale;
}

Game &Game::get() {
	static Game instance;
	return instance;
}

bool Game::init(const std::string &settingsPath) {  // initialize variables
	if (!m_game_settings.load(settingsPath)) {
		std::cout
			<< "Could not load settings.json. Make sure settings.json is is the same directory as the executable."
			<< std::endl;
		return false;
	}

	m_window.create(sf::VideoMode(m_game_settings.data["window"]["width"],
	                              m_game_settings.data["window"]["height"]),
	                std::string(m_game_settings.data["window"]["title"]), sf::Style::Default);
	m_window.setVerticalSyncEnabled(m_game_settings.data["window"]["vsync"]);
	setViewportSize({m_game_settings.data["viewport"]["width"],
	                 m_game_settings.data["viewport"]["height"]});

	setPrintFPS(m_game_settings.data["debug"]["printFPS"]);
	m_physics_update_call_freq = 1.f / int(m_game_settings.data["engine"]["physicsUpdateCallFreq"]);
	if (!m_font.loadFromFile(m_game_settings.data["engine"]["fontPath"])) {
		std::cout << "Failed to load font" << std::endl;
	}
	Debug::setDebugCollisionDraw(m_game_settings.data["debug"]["drawCollisionShapes"]);

	m_fps_label.setFont(getFont());
	m_fps_label.setText("0");
	m_fps_label.setTextSize(32);
	m_fps_label.setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::TOP);

	// lastly, set cursor
	m_current_cursor_type = sf::Cursor::Arrow;
	setCursor(sf::Cursor::Arrow);

	return true;
}

void Game::run() {
	while (isRunning()) {
		pollEvents();
		update();
		draw();
	}
}

Game::~Game() { m_window.close(); }

void Game::draw() {
	m_window.clear(sf::Color(21, 21, 21));

	if (!m_scenes_stack.empty()) m_window.draw(*m_scenes_stack.top());

	if (m_enable_print_fps) m_window.draw(m_fps_label);

	m_window.display();
}

void Game::update() {
	m_dt = m_clock.restart().asSeconds();
	m_mouse_pos = getRenderWindow().mapPixelToCoords(sf::Mouse::getPosition(getRenderWindow()));

	while (!m_safe_scene_delete_queue.empty())
		m_safe_scene_delete_queue.pop();

	if (!m_scenes_stack.empty()) {
		m_physics_update_counter += m_dt;
		if (m_physics_update_counter >= m_physics_update_call_freq) {
			m_scenes_stack.top()->physicsUpdate(m_physics_update_call_freq);
			m_physics_update_counter -= m_physics_update_call_freq;
		}
		m_scenes_stack.top()->update(m_dt);
	}

	recalculateAvgFps();
}

void Game::recalculateAvgFps() {
	if (m_enable_print_fps) {
		m_fps_frame_count++;
		m_fps_sum += m_dt;
		if (m_fps_sum >= 1.f) {
			int currentFps = (int) round(m_fps_frame_count / m_fps_sum);
			m_fps_label.setText(std::to_string(currentFps));
			m_fps_sum = 0.0;
			m_fps_frame_count = 0;
		}
	}
}

void Game::addScene(std::unique_ptr<WorldEntity> newScene) {
	newScene->ready();
	m_scenes_stack.push(std::move(newScene));
}

void Game::popScene() {
	auto topScene = std::move(m_scenes_stack.top());
	m_scenes_stack.pop();
	m_safe_scene_delete_queue.push(std::move(topScene));
}

void Game::replaceTopScene(std::unique_ptr<WorldEntity> newScene) {
	popScene();
	addScene(std::move(newScene));
}

void Game::pollEvents() {
	sf::Event event{};
	while (m_window.pollEvent(event)) {
		if (!m_scenes_stack.empty()) m_scenes_stack.top()->handleEvent(event);

		switch (event.type) {
			case sf::Event::Closed:stop();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::Escape:stop();
						break;
					default:
						// skip any other case
						break;
				}
				break;
			case sf::Event::Resized:updateViewportSize();
				break;
			default:
				// skip any other case
				break;
		}
	}
}

bool Game::isRunning() const { return m_run; }

void Game::stop() { m_run = false; }

void Game::setPrintFPS(const bool &printFPS) { m_enable_print_fps = printFPS; }

sf::Vector2u Game::getWindowSize() { return m_window.getSize(); }

sf::Vector2u Game::getViewportSize() {
	return (sf::Vector2u) m_view.getSize();
}

sf::RenderWindow &Game::getRenderWindow() { return m_window; }

void Game::updateViewportSize() {
	sf::Vector2f viewportScale = scaleToFit(m_view.getSize(), getWindowSize());
	m_view.setViewport(sf::FloatRect(
		sf::Vector2f(0.5f - viewportScale.x / 2, 0.5f - viewportScale.y / 2), viewportScale));
	m_window.setView(m_view);
}

sf::Vector2f Game::getMousePos() { return m_mouse_pos; }

sf::Font *Game::getFont() { return &m_font; }

const sf::View * Game::getView() { return &m_view; }

void Game::setCameraCenterAt(const sf::Vector2f &pos) {
	m_view.setCenter(pos);
	m_window.setView(m_view);
	// polsrodek
	m_fps_label.setPosition(
		pos - sf::Vector2f(384 / 2, 216 / 2) +
			sf::Vector2f(float(m_game_settings.data["viewport"]["width"]) - 1, 1));  // a
}

void Game::setCursor(sf::Cursor::Type type) {
	if (m_current_cursor_type == type)
		return;
	m_current_cursor_type = type;

	getRenderWindow().setMouseCursor(ResourceManager::get().getSystemCursor(type));
}

bool Game::isWindowActive() const {
	return m_window.hasFocus();
}

void Game::setViewportSize(sf::Vector2f newSize) {
	m_view.reset(sf::FloatRect(0, 0, newSize.x, newSize.y));
	updateViewportSize();
	m_fps_label.setPosition(newSize.x - 1, 1);
}
