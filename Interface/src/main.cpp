#include <iostream>
#include <gtkmm.h>
#include "main_window.h"
#include "BoatManager.hpp"

int main(int argc, char* argv[]) {
    // Créer l'application GTK
    auto app = Gtk::Application::create("org.gtkmm.ship_editor");

    // Charger les bateaux depuis ton dossier de transformation
    BoatManager manager;
    std::vector<Boat> boats = manager.loadBoats("../../FileConverter/transformation");

    // Créer la fenêtre principale (ne pas l'ajouter tout de suite)
    MainWindow win;

    // Connecter la présentation de la fenêtre au signal "activate" de l'application
    // La fenêtre doit être ajoutée après l'émission du signal startup/activate.
    app->signal_activate().connect([&]() {
        if (!boats.empty()) {
            // For testing: choose the first boat that has sails data, otherwise the first boat
            int chosen = 0;
            for (size_t i = 0; i < boats.size(); ++i) {
                if (!boats[i].sails.sails.empty()) { chosen = (int)i; break; }
            }
            win.loadBoat(&boats[chosen]);
        } else {
            std::cerr << "⚠️ Aucun bateau trouvé dans ../../FileConverter/transformation" << std::endl;
        }

        app->add_window(win);
        win.present();
    });

    // Lancer l'application (passer argc/argv pour la gestion des arguments)
    return app->run(argc, argv);
}
//int main (int argc, char *argv[]) {
//	auto app = Gtk::Application::create("org.gtkmm.ship_editor");
//	return app->make_window_and_run<MainWindow>(argc, argv);
	//return app->run(mainWindow);
//}