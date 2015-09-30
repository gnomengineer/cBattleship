#include "MenuBar.h"
#include <gtkmm/applicationwindow.h>

MenuBar::MenuBar(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
    : Gtk::MenuBar(cobject),
      builder(builder),
      quit_menuitem(nullptr) {
    
    builder->get_widget("quit_menuitem", quit_menuitem);
    if(quit_menuitem) {
        quit_menuitem->signal_activate().connect(
            sigc::mem_fun(*this, &MenuBar::on_quit_menuitem_activate)
        );
    }
}

MenuBar::~MenuBar() {
}

void MenuBar::on_quit_menuitem_activate() {
    Gtk::ApplicationWindow *window = dynamic_cast<Gtk::ApplicationWindow *>(this->get_toplevel());
    window->hide();
}
