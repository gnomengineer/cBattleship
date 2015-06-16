#include <glibmm/refptr.h>
#include <gtkmm.h>

int main(int argc, char **argv) {
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv);

    Glib::RefPtr<Gtk::Builder> builder =
        Gtk::Builder::create_from_file("gui-design.glade");

    Gtk::ApplicationWindow *window;
    builder->get_widget("main_window", window);
    app->run(*window);
    delete window;
    return 0;
}
