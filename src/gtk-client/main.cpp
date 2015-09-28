#include <glibmm/refptr.h>
#include <gtkmm.h>
#include <iostream>


int main(int argc, char **argv) {
ClienStateMachine stateMachine
    try {
        Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv);

        Glib::RefPtr<Gtk::Builder> builder =
            Gtk::Builder::create_from_resource("/gui/gui-design.glade");

        Gtk::ApplicationWindow *window;
        builder->get_widget("main_window", window);
        app->run(*window);
    } catch (const Glib::Error &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
