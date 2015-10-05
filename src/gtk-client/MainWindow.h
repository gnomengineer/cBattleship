#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <gtkmm/applicationwindow.h>
#include <gtkmm/dialog.h>
#include <gtkmm/builder.h>
#include <glibmm/refptr.h>
#include "ConnectDialog.h"
#include "MenuBar.h"

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
