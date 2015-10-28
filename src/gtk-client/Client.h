#ifndef _CLIENT_H
#define _CLIENT_H

#include <glibmm/dispatcher.h>
#include <glibmm/threads.h>
#include <memory>
#include <string>

class MainWindow;
class ClientStateMachine;
namespace Gtk {
    class TextView;
    class Builder;
}
namespace Glib { class Thread; }

class Client {
    private:
        Glib::RefPtr<Gtk::Builder> builder;
        MainWindow *main_window;
        Gtk::TextView *log_textview;

        std::unique_ptr<ClientStateMachine> state_machine;

        Glib::Dispatcher dispatcher;
        mutable Glib::Threads::Mutex dispatch_mutex;
        sigc::connection dispatch_connection;

        Glib::Thread *state_machine_thread;

        std::string player_name;
        std::string ip_address;
        unsigned int port;
    private:
        Client();
        virtual ~Client();

    public:
        static Client &get();

        MainWindow &get_window();

        void dispatch(std::function<void(void)> func);

        void log(std::string text);

        void run_state_machine(std::string name, std::string ip_address, unsigned short port);
        void initialize_state_machine();
};

#endif /* _CLIENT_H */
