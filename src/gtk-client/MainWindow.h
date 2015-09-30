#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <glibmm/refptr.h>
#include "MenuBar.h"

class MainWindow : public Gtk::ApplicationWindow {
    private:
        Glib::RefPtr<Gtk::Builder> builder;
        MenuBar *menubar;

    public:
        MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
        virtual ~MainWindow();
};

#endif /* _MAIN_WINDOW_H */
