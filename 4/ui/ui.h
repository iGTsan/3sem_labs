/** \file
 *  \brief Мое дополнение к SFML
 *  Содержит кнопки, тексовые поля
 *  шаблоны меню и класс, инициализирующий спрайты
 */

#ifndef UI_UI_H_
#define UI_UI_H_

#include <SFML/Graphics.hpp>
#include "../classes/vector.h"

/// Мое дополнение к SFML
namespace sf_my {
	/// Класс кнопка
	class Button {
	protected:
		sf::Font font;
		sf::RectangleShape sprite;
		sf::Text text;
		sf::Color default_outline_color;
		sf::Color active_outline_color;
		int pos_x;
		int pos_y;
		int size_x;
		int size_y;
		int return_code;
	public:
		Button(int pos_x=0, int pos_y=0, int size_x=0, int size_y=0, int return_code=1);
		void set_font(const std::string& filename);
		void set_text(const std::string& _text);
		virtual void set_pos(int x, int y);
		virtual void set_size(int x, int y);
		void set_return_code(int code) {return_code = code;}
		int get_x_pos() const {return (pos_x);}
		int get_y_pos() const {return (pos_y);}
		void set_back_color(sf::Color color);
		void set_outline_color(sf::Color color);
		virtual int is_clicked(int x, int y);
		int is_active(int x, int y);
		virtual void show(sf::RenderWindow &window) const;
		void resize();
		virtual ~Button() {};
	};

	/// Класс кнопка-флаг
	class CheckButton : public Button {
	protected:
		int checked = 0;
		sf::Font check_font;
	private:
		sf::Text description;
	public:
		CheckButton(int x_pos=0, int y_pos=0, int x_size=0, int y_size=0,
				int return_code=1, const std::string& desc="");
		void set_pos(int x, int y) override;
		void set_size(int x, int y) override;
		void set_desc(const std::string& desc);
		void show(sf::RenderWindow& window) const override;
		int is_checked() const {return (checked);}
		int is_clicked(int x, int y) override;
		void set_inactive() {checked = 0;}
		void set_active() {checked = 1;}
	};

	/// Класс-коллекция кнопок-флагов
	class CheckButtons {
	protected:
		std::vector<CheckButton *> buttons;
	private:
		int pos_x;
		int pos_y;
		int size_x;
		int size_y;
	public:
		CheckButtons(int pos_x=0, int pos_y=0, int size_x=0, int size_y=0);
		void set_pos(int x, int y);
		void set_size(int x, int y);
		void add_button(int return_code=1, const std::string& desc="");
		void show(sf::RenderWindow& window) const;
		Button& operator[](int i) {return (*buttons[i]);}
		void is_active(int x, int y);
		virtual int is_clicked(int x, int y);
		virtual ~CheckButtons();
	};

	/// Класс-коллекция кнопок-переключателей
	class RadioButtons : public CheckButtons {
	private:
		int checked_button;
		bool removable;
	public:
		RadioButtons(int pos_x=0, int pos_y=0, int size_x=0, int size_y=0, bool removable=0);
		int is_clicked(int x, int y) override;
	};

	/// Класс-шаблон для меню
	class MenuPart {
	private:
		sf::RectangleShape chosen;
		int x_pos;
		int y_pos;
		int x_shift;
		int size;
	protected:
		std::vector<sf_my::Button *> buttons;
	public:
		MenuPart(int x_shift=0, int x_pos=0, int y_pos=0, int size=0);
		void set_pos(int x, int y);
		void set_shift(int x);
		void set_size(int _size);
		int get_x_pos() const {return (x_pos);}
		int get_y_pos() const {return (y_pos);}
		void show(sf::RenderWindow &window) const;
		int is_clicked(int x, int y);
		int is_active(int x, int y);
		~MenuPart();
	};

	/// Класс инициализирующий спрайт
	class Sprite {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
	public:
		Sprite(const std::string &filename);
		sf::Sprite& get_sprite() {return (sprite);}
	};

	/// Класс текстовое поле
	class TextField : public Button {
	private:
		int clicked = 0;
	public:
		TextField(int x_pos=0, int y_pos=0, int x_size=0, int y_size=0);
		std::string get_text() const;
		int is_clicked(int x, int y) override;
		void button_pressed(sf::Keyboard::Key &key);
	};

	class ButtonMatrix {
		std::MyVector<std::MyVector<Button>> buttons;
	public:
		ButtonMatrix(int x_size = 0, int y_size = 0);
		void set_size(int x_size, int y_size);
		void show(sf::RenderWindow& window) const;
		int is_clicked(int x, int y);
		int is_clicked(int x, int y, int& i, int& j);
		int is_active(int x, int y);
	};
}

#endif
