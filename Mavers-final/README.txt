README
**************
File included: 
project.cpp 
makefile
project.h 
project_functions.cpp
events.txt
organizations.txt
new_uta.png
students_tab.jpg
uta.jpg

**************
->The above file compiles and runs on a Gtk window. 
->The program is a campus organization event posting board.There are two tabs, one for students and one for organizations.
->On the students tab, students will be able to search the events hosted by different organization by enterting their preffered day and name of organization.
->Students will also be able to register for the organization they like in the students tab. 
->On the organizations tab, organization staffs will be able to add, update, and delete the events of their organization as per their wish.
->Program reads in event.txt file to extract the events and their details hosted by the particular organization.
->It also reads in organization.txt file to extract the organizations and their details 
->Exceptional handling(check for uppercase/lowercase, check string/interger input) has not been done in the program and
  it is expected that the user enters what has been read from the file.

The format of the event.txt file is:
Name of the organization:Event_name1,Event_about1,Event_day1,Event_place1,Event_date1,Event_time1,Event_freefood1!Event_name2,Event_about2,Event_day2,Event_place2,Event_date2,Event_time2,Event_freefood2
--------------
UTA Volunteers:Angel Tree,Adopt an angel in Christmas,Thursday,University Center(UC),12/06,12 p.m.,False!Party all Night,fun and drinks,Thursday,University Center(UC),12/06,12 p.m.,True!General Body Meeting,Learn about the organization,Friday,University Center(UC),01/20,12 p.m.,True
International Student Association:I-week,Celebartion of International students at UTA,Friday,Bluebonnet UC,12/05,5 p.m.,True!General Body Meeting,Talk about the organization,Monday,Trimbel Hall,12/03,2 p.m.,False
Freshmen Leaders on Campus:Leadership Institute,Learn leadership and interpersonal skills,Tuesday,University Hall (UH),12/07,10 a.m,True
Engineering Student Council:General Body Meeting,Talk about the organization,Tuesday,01/30,12 p.m.,False
--------------

The format of the organizations.txt is:
Name of the organization,Category,President,Number of students,Total fees
--------------
UTA Volunteers,Service/Social,Joe Smith,55,10
International Student Association,Cultural/International,Kayla Kay,30,10
Freshmen Leaders on Campus,Social/Special Interest,Sheryoshii Endow,60,0
Excel Campus Activities,Social/Special Interest,Cali Duncan,75,0
Alpha Lamda Delta,Recognition Societies/Sororities,Karissa Cordero,36,10
Honors College Council,Recognition Societies,Larry David,40,0
Accounting Society,Academics,Johan Paul,74,20
Engineering Student Council,Academics,Rajvi Tiwari,46,10
--------------

**************
Compilation instructions:
->This is built in a Lubuntu virtual machine
->In terminal:
	make
	./project

