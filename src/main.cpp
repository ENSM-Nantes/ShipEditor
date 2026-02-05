#include <iostream>

#include "main_window.h"

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.ship_editor");

  auto css = Gtk::CssProvider::create();
  css->load_from_path("../res/style.css");

  Gtk::StyleContext::add_provider_for_display(
					      Gdk::Display::get_default(),
					      css,
					      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
					      );

	
  return app->make_window_and_run<MainWindow>(argc, argv);
	
}
