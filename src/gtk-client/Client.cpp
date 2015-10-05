#include "Client.h"

Client::Client()
    : builder(Gtk::Builder::create_from_resource("/gui/gui-design.glade")),
    main_window(nullptr),
    state_machine(nullptr) {
    builder->get_widget_derived("main_window", main_window);
}

Client::~Client() {
}

Client &Client::get() {
    static Client client;
    return client;
}

MainWindow &Client::get_window() {
    return *main_window;
}

void Client::connect(std::string name, std::string ip_address, unsigned short port) {
    // TODO: port is not used as of now
    state_machine = std::unique_ptr<ClientStateMachine>(new ClientStateMachine(ip_address));
}
