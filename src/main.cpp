#include <iostream>
#include <unistd.h>
#include "main_window.h"

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.ship_editor");


 if(0 != chdir("../res/"))//Launch from builded sources
    {
      if(0 != chdir("/usr/share/ShipEditor"))//Launch from install
        {
          std::cout << "Ship Editor not able to get resources files" << std::endl;
          exit(-1);
        }
    }
 char cwd[1024]={0};
 if(getcwd(cwd, sizeof(cwd)) != NULL) printf("Launcher::Working Directory : %s\n", cwd);
 
  auto css = Gtk::CssProvider::create();
  css->load_from_path("style.css");

  Gtk::StyleContext::add_provider_for_display(
					      Gdk::Display::get_default(),
					      css,
					      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
					      );

	
  return app->make_window_and_run<MainWindow>(argc, argv);
	
}
