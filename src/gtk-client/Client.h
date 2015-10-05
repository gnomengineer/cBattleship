#ifndef _CLIENT_H
#define _CLIENT_H

#include <glibmm/thread.h>
#include <glibmm/threads.h>
#include <glibmm/dispatcher.h>
#include <gtkmm/textview.h>
#include "MainWindow.h"
#include <clientlib/ClientStateMachine.h>
#include <memory>

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
    private:
        Client();
        virtual ~Client();

    public:
        static Client &get();

        MainWindow &get_window();

        void dispatch(std::function<void(void)> func);

        void log(std::string text);

        void connect(std::string name, std::string ip_address, unsigned short port);
};

#endif /* _CLIENT_H */
