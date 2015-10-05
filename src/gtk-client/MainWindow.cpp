#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
    : Gtk::ApplicationWindow(cobject),
    builder(builder),
    menubar(nullptr),
    connect_dialog(nullptr),
    about_dialog(nullptr){

    builder->get_widget_derived("menubar", menubar);
    builder->get_widget_derived("connect_dialog", connect_dialog);
    builder->get_widget("about_dialog", about_dialog);
}

MainWindow::~MainWindow() {
}
