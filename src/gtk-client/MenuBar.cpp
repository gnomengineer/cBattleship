#include "MenuBar.h"
#include <gtkmm/applicationwindow.h>

MenuBar::MenuBar(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
    : Gtk::MenuBar(cobject),
      builder(builder),
      connect_menuitem(nullptr),
      quit_menuitem(nullptr),
      connect_dialog(nullptr) {
    
    builder->get_widget("connect_menuitem", connect_menuitem);
    if(connect_menuitem) {
        connect_menuitem->signal_activate().connect(
            sigc::mem_fun(*this, &MenuBar::on_connect_menuitem_activate)
        );
    }

    builder->get_widget("quit_menuitem", quit_menuitem);
    if(quit_menuitem) {
        quit_menuitem->signal_activate().connect(
            sigc::mem_fun(*this, &MenuBar::on_quit_menuitem_activate)
        );
    }

    builder->get_widget_derived("connect_dialog", connect_dialog);
}

MenuBar::~MenuBar() {
}

void MenuBar::on_quit_menuitem_activate() {
    Gtk::ApplicationWindow *window = dynamic_cast<Gtk::ApplicationWindow *>(this->get_toplevel());
    window->hide();
}

void MenuBar::on_connect_menuitem_activate() {
    if(connect_dialog != nullptr) {
        connect_dialog->show_all();
    }
}
