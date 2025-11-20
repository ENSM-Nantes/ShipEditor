#include <iostream>

#include "main_window.h"

int main (int argc, char *argv[]) {
	auto app = Gtk::Application::create("org.gtkmm.ship_editor");
	return app->make_window_and_run<MainWindow>(argc, argv);
	//return app->run(mainWindow);
}