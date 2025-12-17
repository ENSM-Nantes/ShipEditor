#include <iostream>

#include "main_window.h"
#include "BoatManager.hpp"

int main (int argc, char *argv[]) {
	// Configure the path to boat transformation folder
	BoatManager::transformationPath = "../FileConverter/transformation";
	
	auto app = Gtk::Application::create("org.gtkmm.ship_editor");
	return app->make_window_and_run<MainWindow>(argc, argv);
	//return app->run(mainWindow);
}