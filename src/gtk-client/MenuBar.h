#ifndef _MENU_BAR_H
#define _MENU_BAR_H

#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/builder.h>
#include <glibmm/refptr.h>

class MenuBar : public Gtk::MenuBar {
    private:
        Glib::RefPtr<Gtk::Builder> builder;
        Gtk::MenuItem *quit_menuitem;

    public:
        MenuBar(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
        virtual ~MenuBar();

        void on_quit_menuitem_activate();
};

#endif /* _MENU_BAR_H */
