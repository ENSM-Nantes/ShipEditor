#include <iostream>
#include <gtkmm.h>
#include "main_window.h"
#include "BoatManager.hpp"

int main(int argc, char* argv[]) {
    // Créer l'application GTK
    auto app = Gtk::Application::create("org.gtkmm.ship_editor");

    // Charger les bateaux depuis ton dossier de transformation
    BoatManager manager;
    std::vector<Boat> boats = manager.loadBoats("../../../FileConverter/transformation");

    // Créer la fenêtre principale
    MainWindow win;

    // Charger le premier bateau si disponible
    if (!boats.empty()) {
        win.loadBoat(&boats[0]);
    } else {
        std::cerr << "⚠️ Aucun bateau trouvé dans ../FileConverter/transformation" << std::endl;
    }

    // Lancer l'application
    return app->run(argc, argv);
}
//int main (int argc, char *argv[]) {
//	auto app = Gtk::Application::create("org.gtkmm.ship_editor");
//	return app->make_window_and_run<MainWindow>(argc, argv);
	//return app->run(mainWindow);
//}