#include <glibmm/refptr.h>
#include <gtkmm.h>
#include <iostream>
#include "MainWindow.h"
#include "Client.h"


int main(int argc, char **argv) {
    try {
        Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv);

        app->run(Client::get().get_window());
    } catch (const Glib::Error &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
