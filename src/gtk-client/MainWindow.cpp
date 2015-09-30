#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
    : Gtk::ApplicationWindow(cobject),
    builder(builder),
    menubar(nullptr) {

    builder->get_widget_derived("menubar", menubar);
}

MainWindow::~MainWindow() {
}
