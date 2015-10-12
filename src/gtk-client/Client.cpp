#include "Client.h"

Client::Client()
    : builder(Gtk::Builder::create_from_resource("/gui/gui-design.glade")),
    main_window(nullptr),
    log_textview(nullptr),
    state_machine(nullptr),
    dispatcher(), 
    dispatch_mutex(),
    dispatch_connection(),
    state_machine_thread(nullptr) {
    builder->get_widget_derived("main_window", main_window);
    builder->get_widget("log_textview", log_textview);
}

Client::~Client() {
}

Client &Client::get() {
    static Client client;
    return client;
}

void Client::dispatch(std::function<void(void)> func) {
    Glib::Threads::Mutex::Lock lock(dispatch_mutex);
    dispatch_connection.disconnect();
    dispatch_connection = dispatcher.connect(func);
    dispatcher.emit();
}

MainWindow &Client::get_window() {
    return *main_window;
}

void Client::log(std::string text) {
    dispatch([this, text](){
        Glib::RefPtr<Gtk::TextBuffer> buffer = log_textview->get_buffer();
        buffer->insert(buffer->end(), "\n" + Glib::ustring(text));
    });
}

void Client::connect(std::string name, std::string ip_address, unsigned short port) {
    if(state_machine_thread != nullptr) {
        state_machine->stop();
        state_machine_thread->join();
    }

    state_machine = std::unique_ptr<ClientStateMachine>(new ClientStateMachine(ip_address, port));

    state_machine->events.connecting.connect([this](std::string host, unsigned short port) {
        log("connecting to " + host);
    });

    state_machine->events.connected.connect([this]() {
        log("connected");
    });

    state_machine->events.get_player_name.connect([name, this](std::string &player_name) {
        player_name = name;
    });

    state_machine_thread = Glib::Thread::create(
        sigc::mem_fun(*state_machine, &ClientStateMachine::run),
        true
    );
}
