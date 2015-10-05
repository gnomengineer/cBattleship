#ifndef _MENU_BAR_H
#define _MENU_BAR_H

#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/builder.h>
#include <glibmm/refptr.h>
#include "ConnectDialog.h"

class MenuBar : public Gtk::MenuBar {
    private:
        Glib::RefPtr<Gtk::Builder> builder;
        Gtk::MenuItem *connect_menuitem;
        Gtk::MenuItem *quit_menuitem;

        ConnectDialog *connect_dialog;

    public:
        MenuBar(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
        virtual ~MenuBar();

        void on_quit_menuitem_activate();
        void on_connect_menuitem_activate();
};

#endif /* _MENU_BAR_H */
