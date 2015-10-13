#ifndef _MENU_BAR_H
#define _MENU_BAR_H

#include <glibmm/refptr.h>
#include <gtkmm/menubar.h>

namespace Gtk {
    class Builder;
    class MenuItem;
}

class ConnectDialog;

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
