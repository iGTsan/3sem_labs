#include "engine_ui.h"
#include <iostream>
#include "../classes/vector.h"
#include "../tests/tests.h"

using namespace engine_ui;

int main(int argc, char **argv)
{
#ifdef RUN
	return (tests::run_tests(&argc, argv));
#else
	StartMenu menu;
	menu.loop();
#endif
}
