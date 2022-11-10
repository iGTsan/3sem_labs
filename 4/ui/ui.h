#ifndef UI_UI_H_
#define UI_UI_H_

#include <SFML/Graphics.hpp>

namespace sf_my {

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
		int get_x_pos() {return (pos_x);}
		int get_y_pos() {return (pos_y);}
		void set_back_color(sf::Color color);
		void set_outline_color(sf::Color color);
		virtual int is_clicked(int x, int y);
		int is_active(int x, int y);
		virtual void show(sf::RenderWindow &window);
		virtual ~Button() {};
	};

	class CheckButton : public Button {
	protected:
		int checked;
		sf::Font check_font;
	private:
		sf::Text description;
	public:
		CheckButton(int x_pos=0, int y_pos=0, int x_size=0, int y_size=0,
				int return_code=1, const std::string& desc="");
		void set_pos(int x, int y) override;
		void set_size(int x, int y) override;
		void set_desc(const std::string& desc);
		void show(sf::RenderWindow& window) override;
		int is_checked() {return (checked);}
		int is_clicked(int x, int y) override;
		void set_inactive() {checked = 0;}
		void set_active() {checked = 1;}
};

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
		void show(sf::RenderWindow& window);
		Button& operator[](int i) {return (*buttons[i]);}
		void is_active(int x, int y);
		virtual int is_clicked(int x, int y);
		virtual ~CheckButtons();
	};

	class RadioButtons : public CheckButtons {
	private:
		int checked_button;
		bool removable;
	public:
		RadioButtons(int pos_x=0, int pos_y=0, int size_x=0, int size_y=0, bool removable=0);
		int is_clicked(int x, int y) override;
	};

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
		int get_x_pos() {return (x_pos);}
		int get_y_pos() {return (y_pos);}
		void show(sf::RenderWindow &window);
		int is_clicked(int x, int y);
		int is_active(int x, int y);
		~MenuPart();
	};
}

#endif /* UI_UI_H_ */
