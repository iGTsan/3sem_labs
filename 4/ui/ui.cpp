#include "../engine/game_engine.h"
//#include <cstdio>
#include "ui.h"
#include "ui_consts.h"

using namespace ui_consts;

sf_my::Button::Button(int pos_x, int pos_y, int size_x, int size_y, int return_code) :
	pos_x(pos_x), pos_y(pos_y), size_x(size_x), size_y(size_y), return_code(return_code) {
	font.loadFromFile(beauty_font);
	text.setFont(font);
	text.setFillColor(font_color);
	sprite.setFillColor(button_color);
	sprite.setOutlineThickness(1);
	active_outline_color = sf::Color::Green;
	set_outline_color(bourder_color);
	set_size(size_x, size_y);
	set_pos(pos_x, pos_y);
}

void sf_my::Button::set_font(const std::string &filename) {
	font.loadFromFile(filename);
	text.setFont(font);
}

void sf_my::Button::set_text(const std::string &_text) {
	text.setString(_text);
}

void sf_my::Button::set_pos(int x, int y) {
	pos_x = x;
	pos_y = y;
	text.setPosition(x + 1, y - 2);
	sprite.setPosition(x + 1, y + 1);
}

void sf_my::Button::set_size(int x, int y) {
	size_x = x;
	size_y = y;
	sprite.setSize(sf::Vector2f(x - 2, y - 2));
	text.setCharacterSize(y);
}

int sf_my::Button::is_clicked(int x, int y) {
	if (x >= pos_x && x < pos_x + size_x &&
			y >= pos_y && y < pos_y + size_y)
		return (return_code);
	return (0);
}

void sf_my::Button::set_back_color(sf::Color color) {
	sprite.setFillColor(color);
}

void sf_my::Button::set_outline_color(sf::Color color) {
	default_outline_color = color;
	sprite.setOutlineColor(color);
}

int sf_my::Button::is_active(int x, int y) {
	if (x >= pos_x && x < pos_x + size_x &&
		y >= pos_y && y < pos_y + size_y) {
		sprite.setOutlineColor(active_outline_color);
		return (return_code);
	}
	sprite.setOutlineColor(default_outline_color);
	return (0);
}

void sf_my::Button::show(sf::RenderWindow &window) const {
	window.draw(sprite);
	window.draw(text);
}

sf_my::MenuPart::MenuPart(int x_shift, int x_pos, int y_pos, int size) :
	x_pos(x_pos), y_pos(y_pos), x_shift(x_shift), size(size) {
	set_pos(x_pos, y_pos);
	chosen.setFillColor(sf::Color::Transparent);
	chosen.setOutlineColor(sf::Color::Red);
	chosen.setOutlineThickness(1);
	chosen.setSize(sf::Vector2f(cell_size - 2, cell_size - 2));
}

void sf_my::MenuPart::set_pos(int x, int y) {
	x_pos = x;
	y_pos = y;
	chosen.setPosition(x_pos * cell_size + 1, y_pos * cell_size + 1);
}

void sf_my::MenuPart::set_shift(int x) {
	x_shift = x;
	for (auto& button: buttons)
		button->set_pos(x, button->get_y_pos());
}

void sf_my::MenuPart::show(sf::RenderWindow &window) const {
	window.draw(chosen);
	for (auto& button: buttons)
		button->show(window);
}

int sf_my::MenuPart::is_clicked(int x, int y) {
	for (auto button: buttons)
		if (button->is_clicked(x, y))
			return (button->is_clicked(x, y));
	return (0);
}

int sf_my::MenuPart::is_active(int x, int y) {
	int res = 0;
	for (auto button: buttons)
		res += (button->is_active(x, y));
	return (res);
}

sf_my::MenuPart::~MenuPart() {
	for (auto &button: buttons)
		delete button;
}

void sf_my::MenuPart::set_size(int _size) {
	int y = 1;
	for (auto button: buttons) {
		button->set_size(_size, stat_size);
		button->set_pos(x_shift, y);
		y += stat_size + 1;
	}
}

sf_my::CheckButton::CheckButton(int x_pos, int y_pos, int x_size, int y_size,
		int return_code, const std::string &desc) : Button(x_pos, y_pos, y_size, y_size, return_code) {
	check_font.loadFromFile(default_font);
	text.setFont(check_font);
	description.setFont(font);
	set_text("X");
	set_size(x_size, y_size);
	set_pos(x_pos, y_pos);
	set_desc(desc);
}

void sf_my::CheckButton::set_pos(int x, int y) {
	pos_x = x;
	pos_y = y;
	sprite.setPosition(x, y);
	text.setPosition(x + size_y * 0.2, y - size_y * 0.2);
	description.setPosition(x + size_y * 1.2, y);
}

void sf_my::CheckButton::set_size(int x, int y) {
	size_y = y;
	size_x = x;
	sprite.setSize(sf::Vector2f(y, y));
	text.setCharacterSize(y);
	description.setCharacterSize(y);
	set_pos(pos_x, pos_y);
}

void sf_my::CheckButton::set_desc(const std::string &desc) {
	description.setString(desc);
}

void sf_my::CheckButton::show(sf::RenderWindow &window) const {
	window.draw(sprite);
	window.draw(description);
	if (checked)
		window.draw(text);
}

int sf_my::CheckButton::is_clicked(int x, int y) {
	int res = Button::is_clicked(x, y);
	if (res)
		checked = 1 - checked;
	return (res);
}

sf_my::CheckButtons::CheckButtons(int pos_x, int pos_y, int size_x,
		int size_y) {
	set_pos(pos_x, pos_y);
	set_size(size_x, size_y);
}

void sf_my::CheckButtons::set_pos(int x, int y) {
	pos_x = x;
	pos_y = y;
	double shift = 0;
	for (auto button: buttons) {
		button->set_pos(x, y + shift);
		shift += size_y * 1.2;
	}
}

void sf_my::CheckButtons::set_size(int x, int y) {
	size_x = x;
	size_y = y;
	double shift = 0;
	for (auto button: buttons) {
		button->set_size(size_x, size_y);
		button->set_pos(pos_x, pos_y + shift);
		shift += size_y * 1.2;
	}
}

void sf_my::CheckButtons::add_button(int return_code, const std::string &desc) {
	buttons.push_back(new CheckButton(pos_x, pos_y + size_y * 1.2 * buttons.size(),
			size_x, size_y, return_code, desc));
}

void sf_my::CheckButtons::show(sf::RenderWindow &window) const {
	for (auto button: buttons)
		button->show(window);
}

void sf_my::CheckButtons::is_active(int x, int y) {
	for (auto button: buttons)
		button->is_active(x, y);
}

int sf_my::CheckButtons::is_clicked(int x, int y) {
	int res = 0;
	for (auto button: buttons)
		if ((res = button->is_clicked(x, y)))
			return (res);
	return (res);
}

sf_my::CheckButtons::~CheckButtons() {
	for (auto &button: buttons)
		delete button;
}

sf_my::RadioButtons::RadioButtons(int pos_x, int pos_y, int size_x,
		int size_y, bool removable) : CheckButtons(pos_x, pos_y, size_x, size_y),
				checked_button(-1), removable(removable) {}

int sf_my::RadioButtons::is_clicked(int x, int y) {
	int res = 0;
	for (int i = 0; i < static_cast<int>(buttons.size()); i++)
		if ((res = buttons[i]->is_clicked(x, y))) {
			if (checked_button == -1)
				checked_button = i;
			else if (i == checked_button)
				if (removable)
					checked_button = -1;
				else
					buttons[i]->set_active();
			else {
				buttons[checked_button]->set_inactive();
				checked_button = i;
			}
			return (res);
		}
	return (res);
}

sf_my::Sprite::Sprite(const std::string &filename) {
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
}

void sf_my::Button::resize() {
	sf::Vector2f pos = sprite.getPosition();
	pos_x = pos.x;
	pos_y = pos.y;
	std::cout << pos_x << ' ' << pos_y << std::endl;
}

sf_my::TextField::TextField(int x_pos, int y_pos, int x_size, int y_size) :
	Button(x_pos, y_pos, x_size, y_size) {}

std::string sf_my::TextField::get_text() const {
	return (text.getString());
}

int sf_my::TextField::is_clicked(int x, int y) {
	if (Button::is_clicked(x, y)) {
		if (!clicked) {
			clicked = 1;
			std::string t = text.getString() + '|';
			text.setString(t);
		}
		return (1);
	}
	if (clicked) {
		std::string t = text.getString();
		t.resize(t.size() -1);
		text.setString(t);
		clicked = 0;
	}
	return (0);
}

void sf_my::TextField::button_pressed(sf::Keyboard::Key &key) {
	if (!clicked)
		return;
	if (key >= sf::Keyboard::Key::A && key <= sf::Keyboard::Key::Z) {
		int shift = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			shift = 'A' - 'a';
		std::string t = text.getString();
		t.resize(t.size() -1);
		t += ('a' + key - sf::Keyboard::Key::A + shift);
		t += '|';
		text.setString(t);
	}
	if (key >= sf::Keyboard::Key::Num0 && key <= sf::Keyboard::Key::Num9) {
		std::string t = text.getString();
		t.resize(t.size() -1);
		t += ('0' + key - sf::Keyboard::Key::Num0);
		t += '|';
		text.setString(t);
	}
	if (key == sf::Keyboard::BackSpace) {
		std::string t = text.getString();
		if (t.size() == 1)
			return;
		t.resize(t.size() - 2);
		t += '|';
		text.setString(t);
	}

}
/// саша я тебя люблю
