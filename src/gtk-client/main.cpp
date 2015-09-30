#include <glibmm/refptr.h>
#include <gtkmm.h>
#include <iostream>
#include "MainWindow.h"


int main(int argc, char **argv) {
    try {
        Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv);

        Glib::RefPtr<Gtk::Builder> builder =
            Gtk::Builder::create_from_resource("/gui/gui-design.glade");

        MainWindow *main_window = nullptr;
        builder->get_widget_derived("main_window", main_window);
        app->run(*main_window);
    } catch (const Glib::Error &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
