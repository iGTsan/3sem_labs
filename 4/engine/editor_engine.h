/** \file
 * \brief Файл с редактором уровней
 */

#ifndef ENGINE_EDITOR_ENGINE_H_
#define ENGINE_EDITOR_ENGINE_H_

#include "../classes/basic.h"

namespace GC = game_consts;
namespace GO = game_objects;

namespace editor_engine {
	class Editor {
	private:
		GO::Landscape land;
	public:
		Editor() {};
		void set_size(int x, int y);
		void save(const std::string& filename) const;
		void load(const std::string& filename);
		void set_cell(int x, int y, char symb);
		char get_cell(int x, int y) const;
		int get_x_size() const;
		int get_y_size() const;
	};
}

#endif
