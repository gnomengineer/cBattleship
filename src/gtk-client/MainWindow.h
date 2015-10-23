#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <gtkmm/applicationwindow.h>
#include <glibmm/refptr.h>

namespace Gtk {
    class Builder;
    class Dialog;
}

class ConnectDialog;
class MenuBar;

class MainWindow : public Gtk::ApplicationWindow {
    private:
        Glib::RefPtr<Gtk::Builder> builder;
        MenuBar *menubar;
        ConnectDialog *connect_dialog;
        Gtk::Dialog *about_dialog;

    public:
        MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
        virtual ~MainWindow();
};

#endif /* _MAIN_WINDOW_H */
