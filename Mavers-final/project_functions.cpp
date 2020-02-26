/*Group Project - Mavers
Group Members - Katherine Baumann,1001558704
                Yunika Upadhayaya,1001631183
                Sima Rayamajhi,
                Suresh Mainali, 1001664846
*/

#include "project_header.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

vector <Organization> all_orgs;
string org_name;
string updateEventName;
Organization ORG;
int x;
vector <string> info;

//read in organizations.txt
void ReadFile1()
{
    ifstream inFile;
    string line;
    Organization o;
    string intermediate;
    string whole_line;

    inFile.open("organizations.txt");

    if(!inFile.is_open())
    {
        cout<<"Sorry, unable to open the file.\nExiting...";
        exit(1);
    }
    else {
        while(getline(inFile,whole_line))
        {
            stringstream separate_line(whole_line);

            getline(separate_line,intermediate,',');
            o.name = intermediate;

            getline(separate_line,intermediate,',');
            o.description = intermediate;

            getline(separate_line,intermediate,',');
            o.president = intermediate;

            getline(separate_line,intermediate,',');
            o.members = stoi(intermediate);

            getline(separate_line,intermediate,'\n');
            o.fee = stoi(intermediate);

            all_orgs.push_back(o);
        }
    }
    inFile.close();
}

//reads in events.txt
void ReadFile2()
{
    ifstream inFile;
    string line;
    string intermediate;
    string new_intermediate;
    string whole_line;
    int found_org=-1;

    inFile.open("events.txt");

    if(!inFile.is_open())
    {
        cout<<"Sorry, unable to open the file.\nExiting...";
        exit(1);
    }
    else {
        while(getline(inFile,whole_line))
        {
            stringstream separate_line(whole_line);

            getline(separate_line,intermediate,':');
            string org_name = intermediate;

            int hasEvent = 1;
            while (hasEvent)
            {
                if(getline(separate_line, intermediate, '!'))
                {
                    Event temp;
                    stringstream event_line(intermediate);
                    temp.organization_name = org_name;
                    found_org=-1;
                    for(int i=0; i<all_orgs.size(); i++)
                    {
                        if(temp.organization_name.compare(all_orgs[i].name)==0)
                        {
                            found_org=i;
                        }
                    }
                    getline(event_line,intermediate,',');
                    temp.name = intermediate;
                    getline(event_line,intermediate,',');
                    temp.about = intermediate;
                    getline(event_line,intermediate,',');
                    temp.day = intermediate;
                    getline(event_line,intermediate,',');
                    temp.place = intermediate;
                    getline(event_line,intermediate,',');
                    temp.date = intermediate;
                    getline(event_line,intermediate,',');
                    temp.time = intermediate;
                    getline(event_line,intermediate,',');
                    temp.freefood = intermediate;
                    if(found_org!=-1)
                    {
                        all_orgs[found_org].events.push_back(temp);
                    }
                }
                else
                {
                    hasEvent = 0;
                }
            }
        }
    }
    inFile.close();
}

//outputs file for organizations.txt
void outputFile1()
{
    ofstream output;
    output.open("organizations.txt",ofstream::out|ofstream::trunc);
    for(int i=0; i<all_orgs.size(); i++)
    {
        output<<all_orgs[i].name<<",";
        output<<all_orgs[i].description<<",";
        output<<all_orgs[i].president<<",";
        output<<all_orgs[i].members<<",";
        output<<all_orgs[i].fee<<"\n";
    }
    output.close();
}

//outputs file for events.txt
void outputFile2()
{
    ofstream output;
    output.open("events.txt",ofstream::out|ofstream::trunc);
    for(int i=0; i<all_orgs.size(); i++)
    {
        if(!all_orgs[i].events.empty())
        {
            output<<all_orgs[i].name<<":";
            for(int j=0; j<all_orgs[i].events.size(); j++)
            {
                output<<all_orgs[i].events[j].name<<",";
                output<<all_orgs[i].events[j].about<<",";
                output<<all_orgs[i].events[j].day<<",";
                output<<all_orgs[i].events[j].place<<",";
                output<<all_orgs[i].events[j].date<<",";
                output<<all_orgs[i].events[j].time<<",";
                output<<all_orgs[i].events[j].freefood;
                if(j < all_orgs[i].events.size()-1)
                {
                    output<<"!";
                }
                else if(j==all_orgs[i].events.size()-1)
                {
                    output<<"\n";
                }
            }
        }
    }
    output.close();
}

//checks is any organization is found within files
void project_window::no_org_found(string organization)
{
    ostringstream ss;
    ss<<"Your organization "<<organization<< " is not registered within our system. Please try again."<<endl;
    string line = ss.str();
    Gtk::MessageDialog dialog(*this, line, false, Gtk::MESSAGE_INFO);
    dialog.run();
    dialog.close();
}

project_window::project_window():main(Gtk::ORIENTATION_VERTICAL),quit_btn("Exit"),go_back_btn("Back"),about_us_btn("About"),search_btn("Search Events"),register_btn("Join an Organization"),org_btn("Search"),parameters_btn("Search"),yes_btn("Yes"),no_btn("No"),change_details_btn("Change events"),delete_btn("Delete events"),add_btn("Add events")
{
    ReadFile1();
    ReadFile2();
    //main window
    set_title("Mavers");
    set_default_size(800,600);
    set_icon_from_file("new_uta.png");
    set_border_width(10);
    add(main);
    //intitalizing notebook
    nb.set_border_width(20);
    main.pack_start(nb);
    //quit,go back and about button
    main.pack_start(go_back_btn,Gtk::PACK_SHRINK);
    go_back_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::go_back));

    main.pack_start(about_us_btn,Gtk::PACK_SHRINK);
    about_us_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::about_us));

    main.pack_start(quit_btn, Gtk::PACK_SHRINK);
    quit_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::quit));
    //setting up tabs
    nb.append_page(home_page,"Home");
    nb.append_page(students_page,"Students");
    nb.append_page(orgs_page,"Organizations");
    //home page
    home_page.set_orientation(Gtk::ORIENTATION_VERTICAL);
    image_home.set("uta.jpg");
    home_page.pack_start(image_home);
    home_info.set_text("Welcome to the UTA event planner!"
                       " Click the students tab to search for events or join an organization."
                       " Click the organizations tab to alter events for organizations.");
    home_page.pack_start(home_info);
    home_info.set_line_wrap(true);
    //students tab
    students_page.set_border_width(10);
    students_page.set_spacing(10);
    students_page.set_orientation(Gtk::ORIENTATION_VERTICAL);
    //intializing register widgets
    register_info.set_text("Enter the organization you want to register for:");
    org_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::search_orgs));
    entering_info.set_text("Put in your information:");
    entry_name.set_text("Name");
    entry_major.set_text("Major");
    entry_year.set_text("Year in school");
    ask_user.set_text("Would you like to register for this organization?");
    yes_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::yes_toggled));
    no_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::no_toggled));
    //intializing search widgets
    search_info.set_text("Type in one or more fields to search events:");
    entry_day.set_text("Day");
    entry_organization.set_text("Organization");
    parameters_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::search_parameters));
    register_for_org.set_text("Click the button below to register for an organization you see.");
    //packing register and search widgets in order
    students_page.pack_start(register_info);//register widget
    students_page.pack_start(search_info);//find events widget
    students_page.pack_start(entry_day);//find events widget
    students_page.pack_start(entry_organization);//register/find events widget
    students_page.pack_start(parameters_btn);//find events widget
    students_page.pack_start(found_events);//find events widget
    students_page.pack_start(register_for_org);//find events widget
    students_page.pack_start(org_btn);//register widget
    students_page.pack_start(found_org);//register widget
    students_page.pack_start(entering_info);//registering widget
    students_page.pack_start(entry_name);//registering widget
    students_page.pack_start(entry_major);//registering widget
    students_page.pack_start(entry_year);//registering widget
    students_page.pack_start(price_for_org);//registering widget
    students_page.pack_start(ask_user);//registering widget
    students_page.pack_start(yes_btn);//registering widget
    students_page.pack_start(no_btn);//registering widget
    //main students page widgets
    students_page.pack_start(search_btn);
    students_page.pack_start(register_btn);
    image_students.set("students_tab.jpg");
    students_page.pack_start(image_students);
    search_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::find_events));
    register_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::join_org));
    //organization page
    orgs_page.set_border_width(10);
    orgs_page.set_spacing(10);
    orgs_page.set_orientation(Gtk::ORIENTATION_VERTICAL);
    //intializing orgs widgets
    entry_org2.set_text("Organization");
    orgs_info.set_text("Enter your organization's name and select your option:");
    //packing widgets in organizatons page
    orgs_page.pack_start(orgs_info);
    orgs_page.pack_start(entry_org2);
    orgs_page.pack_start(change_details_btn);
    orgs_page.pack_start(delete_btn);
    orgs_page.pack_start(add_btn);

    //working on organizations buttons
    change_details_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::change_clicked));
    add_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::add_clicked));
    delete_btn.signal_clicked().connect(sigc::mem_fun(*this,&project_window::delete_clicked));

    //showing widgets
    main.set_visible(true);
    go_back_btn.set_visible(true);
    about_us_btn.set_visible(true);
    quit_btn.set_visible(true);
    nb.set_visible(true);
    home_page.set_visible(true);
    students_page.set_visible(true);
    orgs_page.set_visible(true);
    image_home.set_visible(true);
    home_info.set_visible(true);
    register_btn.set_visible(true);
    image_students.set_visible(true);
    search_btn.set_visible(true);
    orgs_info.set_visible(true);
    change_details_btn.set_visible(true);
    delete_btn.set_visible(true);
    entry_org2.set_visible(true);
    add_btn.set_visible(true);

    about_us_btn.grab_focus();
}

//main window destructor
project_window::~project_window()
{

}

//window for updating events
UpdateEvents_Window::UpdateEvents_Window():new_box(Gtk::ORIENTATION_VERTICAL)
{
    add(new_box);
    set_size_request(600,400);
    set_border_width(10);
    set_title("Mavers");
    set_icon_from_file("new_uta.png");

    ostringstream ss;
    ss<<"Fill up the following entries to update the events!"<<endl;
    string line = ss.str();

    label_Heading.set_text(line);
    new_box.pack_start(label_Heading,Gtk::PACK_SHRINK);

    label_Name.set_text("Change the event name:");
    new_box.pack_start(label_Name,Gtk::PACK_SHRINK);

    Name.set_max_length(75);
    Name.set_text("Name");
    Name.select_region(0,Name.get_text_length());
    new_box.pack_start(Name,Gtk::PACK_SHRINK);

    label_About.set_text("Change the description of the event:");
    new_box.pack_start(label_About,Gtk::PACK_SHRINK);

    About.set_max_length(500);
    About.set_text("About");
    About.select_region(0,About.get_text_length());
    new_box.pack_start(About,Gtk::PACK_SHRINK);

    label_Day.set_text("Change the day of the event:");
    new_box.pack_start(label_Day,Gtk::PACK_SHRINK);

    Day.set_max_length(15);
    Day.set_text("Day");
    Day.select_region(0,Day.get_text_length());
    new_box.pack_start(Day,Gtk::PACK_SHRINK);

    label_Place.set_text("Change the place of the event:");
    new_box.pack_start(label_Place,Gtk::PACK_SHRINK);

    Place.set_max_length(100);
    Place.set_text("Place");
    Place.select_region(0,Place.get_text_length());
    new_box.pack_start(Place,Gtk::PACK_SHRINK);

    label_Date.set_text("Change the date of the event:");
    new_box.pack_start(label_Date,Gtk::PACK_SHRINK);

    Date.set_max_length(25);
    Date.set_text("00/00");
    Date.select_region(0,Date.get_text_length());
    new_box.pack_start(Date,Gtk::PACK_SHRINK);

    label_Time.set_text("Change the time of the event:");
    new_box.pack_start(label_Time,Gtk::PACK_SHRINK);

    Time.set_max_length(10);
    Time.set_text("00 p.m.");
    Time.select_region(0,Time.get_text_length());
    new_box.pack_start(Time,Gtk::PACK_SHRINK);

    label_Food.set_text("Change True for free food, False for none:");
    new_box.pack_start(label_Food,Gtk::PACK_SHRINK);

    Food.set_max_length(10);
    Food.set_text("True");
    Food.select_region(0,Food.get_text_length());
    new_box.pack_start(Food,Gtk::PACK_SHRINK);

    new_box.pack_start(textbox,Gtk::PACK_SHRINK);

    ccc.add_label("Continue");
    ccc.signal_clicked().connect(sigc::mem_fun(*this,&UpdateEvents_Window::on_continue_button));
    new_box.pack_start(ccc,Gtk::PACK_SHRINK);

    close_button.add_label("Exit");
    close_button.signal_clicked().connect(sigc::mem_fun(*this,&UpdateEvents_Window::on_exit));
    new_box.pack_start(close_button,Gtk::PACK_SHRINK);

    show_all_children();
};

//window for changing events
ChangeEvents_window::ChangeEvents_window():box(Gtk::ORIENTATION_VERTICAL)
{
    add(box);
    set_size_request(400,200);
    set_border_width(10);
    set_title("Mavers");
    set_icon_from_file("new_uta.png");

    ostringstream ss;
    ss<<"Choose from the following events that you want to change for " <<org_name<<"."<<endl;
    string line = ss.str();
    label.set_text(line);
    box.pack_start(label,Gtk::PACK_SHRINK);
    int found = -1;
    for(int i = 0; i<all_orgs.size(); i++)
    {
        if(!all_orgs[i].events.empty())
        {
            if(all_orgs[i].name == org_name)
            {
                for(int j = 0; j<all_orgs[i].events.size(); j++)
                {
                    Gtk::RadioButton* b = new Gtk::RadioButton(all_orgs[i].events[j].name);
                    all_buttons.push_back(b);
                    found = 1;
                }
            }
        }
    }
    for(int i = 1 ; i< all_buttons.size(); i++)
    {
        all_buttons[i]->join_group(*all_buttons[0]);
    }

    for(int i = 0; i<all_buttons.size(); i++)
    {
        box.pack_start(*all_buttons[i]);
    }
    ctn_btn.add_label("Continue");
    box.pack_start(ctn_btn);
    ctn_btn.signal_clicked().connect(sigc::mem_fun(*this,&ChangeEvents_window::on_ctn_btn));

    exit.add_label("Close");
    exit.signal_clicked().connect(sigc::mem_fun(*this,&ChangeEvents_window::on_exit_btn));
    box.pack_start(exit);

    show_all_children();
};

//continue button for Changeevents
void ChangeEvents_window::on_ctn_btn()
{
    for (int k=0; all_buttons.size(); k++)
    {
        if (all_buttons[k]->get_active())
        {
            // Get event name from the selected organization on the basis of the
            // radio button clicked
            for (int i=0; i<all_orgs.size(); i++)
            {
                if (all_orgs[i].name == org_name)
                {
                    updateEventName = all_orgs[i].events[k].name;
                    break;
                }
            }
            break;
        }
    }
    UpdateEvents_Window U;
    Gtk::Main::run(U);
    hide();
}

//continue button for Updateevents
void UpdateEvents_Window::on_continue_button()
{
    string get_name = Name.get_text();
    string get_about = About.get_text();
    string get_day = Day.get_text();
    string get_date = Date.get_text();
    string get_place = Place.get_text();
    string get_food = Food.get_text();
    string get_time = Time.get_text();

    for(int i =0; i<all_orgs.size(); i++)
    {
        for(int j = 0; j<all_orgs[i].events.size(); j++)
        {
            if(all_orgs[i].name == org_name && all_orgs[i].events[j].name == updateEventName)
            {
                all_orgs[i].events[j].name = get_name;
                all_orgs[i].events[j].about = get_about;
                all_orgs[i].events[j].day = get_day;
                all_orgs[i].events[j].date = get_date;
                all_orgs[i].events[j].place = get_place;
                all_orgs[i].events[j].freefood = get_food;
                all_orgs[i].events[j].time = get_time;
            }
        }
    }
    outputFile2();
    Gtk::MessageDialog dialog(*this,"Event successfully updated!");
    dialog.run();
    hide();
}

//exit button for Changeevents
void ChangeEvents_window::on_exit_btn()
{
    hide();
}

//exit button for Updateevents
void UpdateEvents_Window::on_exit()
{
    hide();
}

//window for deleting events
DeleteEvents_Window::DeleteEvents_Window():box(Gtk::ORIENTATION_VERTICAL)
{
    add(box);
    set_size_request(400,200);
    set_border_width(10);
    set_title("Mavers");
    set_icon_from_file("new_uta.png");

    ostringstream ss;
    ss<<"Choose from the following events that you want to delete for " <<org_name<<"."<<endl;
    string line = ss.str();
    label.set_text(line);
    box.pack_start(label,Gtk::PACK_SHRINK);
    int found = -1;
    for(int i = 0; i<all_orgs.size(); i++)
    {
        if(!all_orgs[i].events.empty())
        {
            if(all_orgs[i].name == org_name)
            {
                for(int j = 0; j<all_orgs[i].events.size(); j++)
                {
                    Gtk::RadioButton* b = new Gtk::RadioButton(all_orgs[i].events[j].name);
                    all_buttons.push_back(b);
                    found = 1;
                }
            }
        }
    }
    for(int i = 1 ; i< all_buttons.size(); i++)
    {
        all_buttons[i]->join_group(*all_buttons[0]);
    }

    for(int i = 0; i<all_buttons.size(); i++)
    {
        box.pack_start(*all_buttons[i]);
    }
    ctn_btn.add_label("Continue");
    box.pack_start(ctn_btn);
    ctn_btn.signal_clicked().connect(sigc::mem_fun(*this,&DeleteEvents_Window::on_ctn_btn));

    exit.add_label("Close");
    exit.signal_clicked().connect(sigc::mem_fun(*this,&DeleteEvents_Window::on_exit_btn));
    box.pack_start(exit);

    show_all_children();
};

//continue button for Deleteevents
void DeleteEvents_Window::on_ctn_btn()
{
    for (int k=0; all_buttons.size(); k++)
    {
        if (all_buttons[k]->get_active())
        {
            ORG.events.erase(ORG.events.begin()+k);
            all_orgs[x].events=ORG.events;
            break;
        }
    }
    outputFile2();

    Gtk::MessageDialog dialog(*this,"Event successfully deleted!");
    dialog.run();
    hide();
}

//exit button for Deleteevents
void DeleteEvents_Window::on_exit_btn()
{
    hide();
}

//window for adding events
AddEvents_Window::AddEvents_Window():new_box(Gtk::ORIENTATION_VERTICAL)
{
    add(new_box);
    set_size_request(600,400);
    set_border_width(10);
    set_title("Add Events");
    set_icon_from_file("new_uta.png");

    ostringstream ss;
    ss<<"Fill up the following entries to add the events!"<<endl;
    string line = ss.str();

    label_Heading.set_text(line);
    new_box.pack_start(label_Heading,Gtk::PACK_SHRINK);

    label_Name.set_text("Enter the event name:");
    new_box.pack_start(label_Name,Gtk::PACK_SHRINK);

    Name.set_max_length(75);
    Name.set_text("Name");
    Name.select_region(0,Name.get_text_length());
    new_box.pack_start(Name,Gtk::PACK_SHRINK);

    label_About.set_text("Provide a brief description of the event:");
    new_box.pack_start(label_About,Gtk::PACK_SHRINK);

    About.set_max_length(500);
    About.set_text("About");
    About.select_region(0,About.get_text_length());
    new_box.pack_start(About,Gtk::PACK_SHRINK);

    label_Day.set_text("Enter the day of the event:");
    new_box.pack_start(label_Day,Gtk::PACK_SHRINK);

    Day.set_max_length(15);
    Day.set_text("Day");
    Day.select_region(0,Day.get_text_length());
    new_box.pack_start(Day,Gtk::PACK_SHRINK);

    label_Place.set_text("Enter the place of the event:");
    new_box.pack_start(label_Place,Gtk::PACK_SHRINK);

    Place.set_max_length(100);
    Place.set_text("Place");
    Place.select_region(0,Place.get_text_length());
    new_box.pack_start(Place,Gtk::PACK_SHRINK);

    label_Date.set_text("Enter the date of the event:");
    new_box.pack_start(label_Date,Gtk::PACK_SHRINK);

    Date.set_max_length(25);
    Date.set_text("00/00");
    Date.select_region(0,Date.get_text_length());
    new_box.pack_start(Date,Gtk::PACK_SHRINK);

    label_Time.set_text("Enter the time of the event:");
    new_box.pack_start(label_Time,Gtk::PACK_SHRINK);

    Time.set_max_length(10);
    Time.set_text("00 p.m");
    Time.select_region(0,Time.get_text_length());
    new_box.pack_start(Time,Gtk::PACK_SHRINK);

    label_Food.set_text("Enter True for free food, False for none:");
    new_box.pack_start(label_Food,Gtk::PACK_SHRINK);

    Food.set_max_length(10);
    Food.set_text("True");
    Food.select_region(0,Food.get_text_length());
    new_box.pack_start(Food,Gtk::PACK_SHRINK);

    new_box.pack_start(textbox,Gtk::PACK_SHRINK);

    continue_button.add_label("Continue");
    continue_button.signal_clicked().connect(sigc::mem_fun(*this,&AddEvents_Window::on_continue_button));
    new_box.pack_start(continue_button,Gtk::PACK_SHRINK);

    close_button.add_label("Exit");
    close_button.signal_clicked().connect(sigc::mem_fun(*this,&AddEvents_Window::on_exit));
    new_box.pack_start(close_button,Gtk::PACK_SHRINK);

    show_all_children();
};

//exit button for Addevents
void AddEvents_Window::on_exit()
{
    hide();
}

//continue button for Addevents
void AddEvents_Window::on_continue_button()
{
    Event temp;
    string get_name = Name.get_text();
    string get_about = About.get_text();
    string get_day = Day.get_text();
    string get_date = Date.get_text();
    string get_place = Place.get_text();
    string get_food = Food.get_text();
    string get_time = Time.get_text();

    int found_org=-1;
    for(int i=0; i<all_orgs.size(); i++)
    {
        if(org_name.compare(all_orgs[i].name)==0)
        {
            found_org=i;
        }
    }
    temp.name = get_name;
    temp.about = get_about;
    temp.day = get_day;
    temp.date = get_date;
    temp.place = get_place;
    temp.freefood = get_food;
    temp.time = get_time;

    if(found_org!=-1)
    {
        all_orgs[found_org].events.push_back(temp);
    }
    outputFile2();
    Gtk::MessageDialog dialog(*this,"Event successfully Added!");
    dialog.run();
    hide();
}

//ViewEvents window
ViewEvents_Window::ViewEvents_Window():box(Gtk::ORIENTATION_VERTICAL),close_button("Exit")
{
    add(box);
    set_size_request(600,200);
    set_border_width(10);
    set_title("Mavers");
    set_icon_from_file("new_uta.png");
    string events_results="The events found:";
    for(int i = 0; i<info.size(); i++)
    {
        events_results=events_results+"\n"+info[i];
    }
    events.set_text(events_results);
    box.pack_start(events);
    close_button.signal_clicked().connect(sigc::mem_fun(*this,&ViewEvents_Window::on_exit_view));
    box.pack_start(close_button,Gtk::PACK_SHRINK);
    show_all_children();
}

//exit function for ViewEvents
void ViewEvents_Window::on_exit_view()
{
    hide();
}

//goes back to main page of all pages
void project_window::go_back()
{
    //hiding options
    register_info.set_visible(false);
    search_info.set_visible(false);
    entry_day.set_visible(false);
    entry_organization.set_visible(false);
    org_btn.set_visible(false);
    parameters_btn.set_visible(false);
    register_for_org.set_visible(false);
    org_btn.set_visible(false);
    entering_info.set_visible(false);
    entry_name.set_visible(false);
    entry_major.set_visible(false);
    entry_year.set_visible(false);
    price_for_org.set_visible(false);
    ask_user.set_visible(false);
    yes_btn.set_visible(false);
    no_btn.set_visible(false);
    found_org.set_visible(false);
    found_events.set_visible(false);
    //showing main
    register_btn.set_visible(true);
    image_students.set_visible(true);
    search_btn.set_visible(true);
    orgs_info.set_visible(true);
    change_details_btn.set_visible(true);
    delete_btn.set_visible(true);
    entry_org2.set_visible(true);
    add_btn.set_visible(true);
}

//shows about information
void project_window::about_us()
{

    dialog.set_transient_for(*this);
    dialog.set_program_name("Mavers");
    auto logo = Gdk::Pixbuf::create_from_file("new_uta.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 0.1.0");
    dialog.set_copyright("Copyright 2019");
    dialog.set_comments("This is a class project application.");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"Katherine Baumann","Yunika Upadhayaya","Sima Rayamajhi","Suresh Mainali"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {
        "StudentOrgs logo is licensed under The University of Texas at Arlington(UTA) partnered with Learfield Licensing Partners (LLP). https://www.uta.edu/ucomm/collegetown/licensing",
        "Home tab picture of UTA is taken from the blog of favorite spot for UTA grduation picture. https://blog.uta.edu/social/2017/10/19/our-favorite-spots-for-graduation-photos/",
        "The horse in the students tab is taken from the instagaram post for #maverickcountry. https://www.picbear.org/tag/maverickcountry"
    };
    dialog.set_artists(artists);
    dialog.run();
    dialog.hide();
}

//exits program
void project_window::quit()
{
    hide();
}

//shows widgets for finding events
void project_window::find_events()
{
    //hiding widgets
    image_students.set_visible(false);
    search_btn.set_visible(false);
    entry_organization.set_visible(false);
    register_info.set_visible(false);
    org_btn.set_visible(false);
    found_org.set_visible(false);
    price_for_org.set_visible(false);
    entering_info.set_visible(false);
    entry_name.set_visible(false);
    entry_major.set_visible(false);
    entry_year.set_visible(false);
    price_for_org.set_visible(false);
    ask_user.set_visible(false);
    yes_btn.set_visible(false);
    no_btn.set_visible(false);
    //showing find events widgets
    search_info.set_visible(true);
    entry_day.set_visible(true);
    entry_organization.set_visible(true);
    parameters_btn.set_visible(true);
    register_for_org.set_visible(true);
    found_events.set_visible(true);
}

//shows widgets for registering to an organization
void project_window::join_org()
{
    //hiding widgets
    image_students.set_visible(false);
    search_btn.set_visible(false);
    register_btn.set_visible(false);
    search_info.set_visible(false);
    entry_day.set_visible(false);
    entry_organization.set_visible(false);
    parameters_btn.set_visible(false);
    register_for_org.set_visible(false);
    found_events.set_visible(false);
    //showing register widgets
    entry_organization.set_visible(true);
    register_info.set_visible(true);
    org_btn.set_visible(true);
    found_org.set_visible(true);
}

//finds events student is searching for
void project_window::search_parameters()
{
    int found=0;
    string day=entry_day.get_text();
    string org=entry_organization.get_text();
    string build;
    if(day.compare("Day")!=0&&(org.compare("Organization")==0||org.compare("")==0))//user only searching for day
    {
        for(int i=0; i<all_orgs.size(); i++)
        {
            if(!all_orgs[i].events.empty())
            {
                for(int j=0; j<all_orgs[i].events.size(); j++)
                {
                    if(all_orgs[i].events[j].day.compare(day)==0)
                    {
                        found=1;
                        if(all_orgs[i].events[j].freefood.compare("True")==0)
                        {
                            build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time+" There will be free food.";
                        }
                        else
                        {
                            build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time;
                        }
                        info.push_back(build);
                    }
                }
            }
        }
        if(found==1)
        {
            for(int i=0; i<info.size(); i++)
            {
                ViewEvents_Window A;
                Gtk::Main::run(A);
                info.clear();
            }
            found_events.set_markup("<span color='red'>Events found!</span>");
        }
        else
        {
            found_events.set_markup("<span color='red'>No events found.</span>");
        }
    }
    else if((day.compare("Day")==0||day.compare("")==0)&&org.compare("Organization")!=0)//user only searching for organization
    {
        for(int i=0; i<all_orgs.size(); i++)
        {
            if(org.compare(all_orgs[i].name)==0)
            {
                for(int j=0; j<all_orgs[i].events.size(); j++)
                {
                    found=1;
                    if(all_orgs[i].events[j].freefood.compare("True")==0)
                    {
                        build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time+" There will be free food.";
                    }
                    else
                    {
                        build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time;
                    }
                    info.push_back(build);
                }
            }
        }
        if(found==1)
        {
            for(int i=0; i<info.size(); i++)
            {
                ViewEvents_Window A;
                Gtk::Main::run(A);
                info.clear();
            }
            found_events.set_markup("<span color='red'>Events found!</span>");
        }
        else
        {
            found_events.set_markup("<span color='red'>No events found.</span>");
        }
    }
    else if(day.compare("Day")!=0&&org.compare("Organization")!=0)//user searching for both
    {
        for(int i=0; i<all_orgs.size(); i++)
        {
            if(!all_orgs[i].events.empty())
            {
                for(int j=0; j<all_orgs[i].events.size(); j++)
                {
                    if(all_orgs[i].events[j].day.compare(day)==0&&all_orgs[i].name.compare(org)==0)
                    {
                        found=1;
                        if(all_orgs[i].events[j].freefood.compare("True")==0)
                        {
                            build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time+" There will be free food.";
                        }
                        else
                        {
                            build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time;
                        }
                        info.push_back(build);
                    }
                }
            }
        }
        if(found==1)
        {
            for(int i=0; i<info.size(); i++)
            {
                ViewEvents_Window A;
                Gtk::Main::run(A);
                info.clear();
            }
            found_events.set_markup("<span color='red'>Events found!</span>");
        }
        else
        {
            found_events.set_markup("<span color='red'>No events found.</span>");
        }
    }
    else if((day.compare("Day")==0)&&(org.compare("Organization")==0))//user wants to see all events
    {
        for(int i=0; i<all_orgs.size(); i++)
        {
            if(!all_orgs[i].events.empty())
            {
                for(int j=0; j<all_orgs[i].events.size(); j++)
                {
                    found=1;
                    if(all_orgs[i].events[j].freefood.compare("True")==0)
                    {
                        build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time+" There will be free food.";
                    }
                    else
                    {
                        build=all_orgs[i].events[j].name+" hosted by "+all_orgs[i].name+", at "+all_orgs[i].events[j].place+" on "+all_orgs[i].events[j].day+", the "+all_orgs[i].events[j].date+" at "+all_orgs[i].events[j].time;
                    }
                    info.push_back(build);
                }
            }
        }
        if(found==1)
        {
            for(int i=0; i<info.size(); i++)
            {
                ViewEvents_Window A;
                Gtk::Main::run(A);
                info.clear();
            }
            found_events.set_markup("<span color='red'>Events found!</span>");
        }
        else
        {
            found_events.set_markup("<span color='red'>No events found.</span>");
        }
    }
}

//finds organization student is searching for
void project_window::search_orgs()
{
    int found=0;
    string fee;
    string org=entry_organization.get_text();
    for(int i=0; i<all_orgs.size(); i++)
    {
        if(all_orgs[i].name.compare(org)==0&&found==0)
        {
            fee=to_string(all_orgs[i].fee);
            found=1;
        }
    }
    if(found==1)//inside for loop
    {
        found_org.set_markup("<span color='red'>Found organization!</span>");
        price_for_org.set_text("Cost to join is: $"+fee);//needs to have price of joining org
        entering_info.set_visible(true);
        entry_name.set_visible(true);
        entry_major.set_visible(true);
        entry_year.set_visible(true);
        price_for_org.set_visible(true);
        ask_user.set_visible(true);
        yes_btn.set_visible(true);
        no_btn.set_visible(true);
    }
    else
    {
        found_org.set_markup("<span color='red'>No organizations found.</span>");
        entering_info.set_visible(false);
        entry_name.set_visible(false);
        entry_major.set_visible(false);
        entry_year.set_visible(false);
        price_for_org.set_visible(false);
        ask_user.set_visible(false);
        yes_btn.set_visible(false);
        no_btn.set_visible(false);
    }
}

//runs dialog to show the user was registered and outputs new updated file
void project_window::yes_toggled()
{
    string org=entry_organization.get_text();
//updating member count
    for(int i=0; i<all_orgs.size(); i++)
    {
        if(all_orgs[i].name.compare(org)==0)
        {
            all_orgs[i].members++;
        }
    }
    Gtk::MessageDialog dialog(*this, "Okay! You have successfully joined.");
    dialog.run();
    //function call to output new updated file
    outputFile1();
}

//runs dialog to tell the user they weren't registered
void project_window::no_toggled()
{
    Gtk::MessageDialog dialog(*this, "You have not joined.");
    dialog.run();
    go_back();
}

//changing events
void project_window::change_clicked()
{
    org_name = entry_org2.get_text();
    int found=-1;
    for(int i = 0; i<all_orgs.size(); i++)
    {
        if(all_orgs[i].name == org_name)
        {
            found=1;
            ORG = all_orgs[i];
            x= i;
            if(all_orgs[i].events.empty())
            {
                Gtk::MessageDialog dialog(*this, "The organization you entered does not have any events registered.");
                dialog.run();
            }
            else
            {
                DeleteEvents_Window D;
                Gtk::Main::run(D);
            }
        }
    }
    if(found==-1)
    {
        project_window::no_org_found(org_name);
    }
}
//deleting events
void project_window::delete_clicked()
{
    org_name = entry_org2.get_text();
    int found=-1;
    for(int i = 0; i<all_orgs.size(); i++)
    {
        if(all_orgs[i].name == org_name)
        {
            found=1;
            ORG = all_orgs[i];
            x= i;
            if(all_orgs[i].events.empty())
            {
                Gtk::MessageDialog dialog(*this, "The organization you entered does not have any events registered.");
                dialog.run();
            }
            else
            {
                DeleteEvents_Window D;
                Gtk::Main::run(D);
            }
        }
    }
    if(found==-1)
    {
        project_window::no_org_found(org_name);
    }
}

//adding events
void project_window::add_clicked()
{
    org_name = entry_org2.get_text();
    int found=-1;
    for(int i = 0; i<all_orgs.size(); i++)
    {
        if(all_orgs[i].name.compare(org_name)!=0)
        {
        }
        else
        {
            found=1;
            AddEvents_Window A;
            Gtk::Main::run(A);
        }
    }
    if(found==-1)
    {
        project_window::no_org_found(org_name);
    }
}
