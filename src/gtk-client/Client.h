#ifndef _CLIENT_H
#define _CLIENT_H

#include "MainWindow.h"
#include <clientlib/ClientStateMachine.h>
#include <memory>

class Client {
    private:
        Glib::RefPtr<Gtk::Builder> builder;
        MainWindow *main_window;

        std::unique_ptr<ClientStateMachine> state_machine;

    private:
        Client();
        virtual ~Client();

    public:
        static Client &get();

        MainWindow &get_window();

        void connect(std::string name, std::string ip_address, unsigned short port);
};

#endif /* _CLIENT_H */
