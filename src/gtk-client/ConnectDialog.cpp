#include "ConnectDialog.h"

#include "Client.h"

#include <gtkmm/builder.h>
#include <gtkmm/entry.h>

ConnectDialog::ConnectDialog(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) 
    : Gtk::Dialog(cobject),
    builder(builder),
    name_entry(nullptr), 
    ipaddress_entry(nullptr), 
    port_entry(nullptr),
    connect_cancel_button(nullptr),
    connect_ok_button(nullptr) {

    builder->get_widget("name_entry", name_entry);
    builder->get_widget("ipaddress_entry", ipaddress_entry);
    builder->get_widget("port_entry", port_entry);
    builder->get_widget("connect_cancel_button", connect_cancel_button);
    if(connect_cancel_button) {
        connect_cancel_button->signal_clicked().connect(
            sigc::mem_fun(*this, &ConnectDialog::on_connect_cancel_button_clicked)
        );
    }

    builder->get_widget("connect_ok_button", connect_ok_button);
    if(connect_ok_button) {
        connect_ok_button->signal_clicked().connect(
            sigc::mem_fun(*this, &ConnectDialog::on_connect_ok_button_clicked)
        );
    }
}

ConnectDialog::~ConnectDialog() {
}

void ConnectDialog::on_connect_cancel_button_clicked() {
    this->hide();
}

void ConnectDialog::on_connect_ok_button_clicked() {
    Client::get().run_state_machine(name_entry->get_text(),
                                    ipaddress_entry->get_text(),
                                    atoi(port_entry->get_text().c_str()));
    this->hide();
}
