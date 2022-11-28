#include "editor_engine.h"

void editor_engine::Editor::set_size(int x, int y) {
	land.set_size(x, y);
}

void editor_engine::Editor::save(const std::string &filename) const {
	land.save(filename);
}

void editor_engine::Editor::load(const std::string &filename) {
	land.load(filename);
}

void editor_engine::Editor::set_cell(int x, int y, char symb) {
	land.set_main_cell(x, y, symb);
}

char editor_engine::Editor::get_cell(int x, int y) const {
	return (land.get_main_cell(x, y));
}

int editor_engine::Editor::get_x_size() const {
	return (land.get_x_size());
}

int editor_engine::Editor::get_y_size() const {
	return (land.get_y_size());
}
