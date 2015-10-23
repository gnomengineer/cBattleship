#ifndef _CONNECT_DIALOG_H
#define _CONNECT_DIALOG_H

#include <gtkmm/dialog.h>
#include <glibmm/refptr.h>

namespace Gtk {
    class Builder;
    class Button;
    class Entry;
}

class ConnectDialog : public Gtk::Dialog {
    private:
        Glib::RefPtr<Gtk::Builder> builder;

        Gtk::Entry *name_entry;
        Gtk::Entry *ipaddress_entry;
        Gtk::Entry *port_entry;

        Gtk::Button *connect_cancel_button;
        Gtk::Button *connect_ok_button;

    public:
        ConnectDialog(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);
        virtual ~ConnectDialog();



        void on_connect_cancel_button_clicked();
        void on_connect_ok_button_clicked();
};

#endif /* _CONNECT_DIALOG_H */
