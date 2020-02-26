/*Group Project - Mavers
Group Members - Katherine Baumann,1001558704
                Yunika Upadhayaya,1001631183
                Sima Rayamajhi,
                Suresh Mainali,
*/

#ifndef project_h
#define project_h
#include <gtkmm.h>

using namespace std;

void ReadFile1();
void ReadFile2();
void outputFile1();
void outputFile2();

class Event
{
public:
    string organization_name;
    string name;
    string about;
    string day;
    string place;
    string date;
    string time;
    string freefood;
};

class Organization
{
public:
    string name;
    string description;
    string president;
    int members;
    int fee;
    vector <Event> events;
};

class project_window:public Gtk::Window
{
public:
    project_window();
    virtual ~project_window();


protected:
    void quit();
    void find_events();
    void join_org();
    void go_back();
    void search_orgs();
    void search_parameters();
    void no_toggled();
    void yes_toggled();
    void change_clicked();
    void add_clicked();
    void delete_clicked();
    void about_us();
    void no_org_found(string organization);
    Gtk::Notebook nb;
    Gtk::Box main, home_page,students_page,orgs_page;
    Gtk::Button quit_btn,register_btn,search_btn,go_back_btn,about_us_btn,org_btn,parameters_btn,change_details_btn,delete_btn,add_btn,yes_btn,no_btn;
    Gtk::Image image_home,image_students;
    Gtk::Label home_info,search_info,register_info,entering_info,found_org,price_for_org,ask_user,register_for_org,found_events,orgs_info;
    Gtk::Entry entry_day,entry_organization,entry_name,entry_major,entry_year,entry_org2;
    Gtk:: AboutDialog dialog= {};
};

class ChangeEvents_window:public Gtk::Window
{
public:
    ChangeEvents_window();

protected:
    Gtk::Box box;
    Gtk::Label label;
    vector<Gtk::RadioButton*> all_buttons;
    Gtk::Button ctn_btn;
    Gtk::Button exit;
    Gtk::Button radiobtn;

    void on_ctn_btn();
    void on_exit_btn();
};

class AddEvents_Window:public Gtk::Window
{
public:
    AddEvents_Window();

protected:
    Gtk::Box new_box;
    Gtk::Label label_Heading;
    Gtk::Label label_Name;
    Gtk::Label label_About;
    Gtk::Label label_Day;
    Gtk::Label label_Food;
    Gtk::Label label_Time;
    Gtk::Label label_Date;
    Gtk::Label label_Place;

    Gtk::Button continue_button;
    Gtk::Button close_button;

    Gtk::Entry Name;
    Gtk::Entry About;
    Gtk::Entry Date;
    Gtk::Entry Place;
    Gtk::Entry Day;
    Gtk::Entry Food;
    Gtk::Entry Time;
    Gtk::Box textbox;

    void on_continue_button();
    void on_exit();

};

class DeleteEvents_Window:public Gtk::Window
{
public:
    DeleteEvents_Window();
protected:
    Gtk::Box box;
    Gtk::Label label;
    vector<Gtk::RadioButton*> all_buttons;
    Gtk::Button ctn_btn;
    Gtk::Button exit;

    void on_ctn_btn();
    void on_exit_btn();
};

class UpdateEvents_Window:public Gtk::Window
{
public:
    UpdateEvents_Window();

protected:
    Gtk::Box new_box;
    Gtk::Label label_Heading;
    Gtk::Label label_Name;
    Gtk::Label label_About;
    Gtk::Label label_Day;
    Gtk::Label label_Food;
    Gtk::Label label_Time;
    Gtk::Label label_Date;
    Gtk::Label label_Place;

    Gtk::Button ccc;
    Gtk::Button close_button;

    Gtk::Entry Name;
    Gtk::Entry About;
    Gtk::Entry Date;
    Gtk::Entry Place;
    Gtk::Entry Day;
    Gtk::Entry Food;
    Gtk::Entry Time;
    Gtk::Box textbox;

    void on_continue_button();
    void on_exit();

};

class ViewEvents_Window:public Gtk::Window
{
public:
    ViewEvents_Window();

protected:
    Gtk::Box box;
    Gtk::Label events;
    Gtk::Button close_button;

    void on_exit_view();
};

#endif
