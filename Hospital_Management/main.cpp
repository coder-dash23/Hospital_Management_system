#include <iostream>
#include<winsock.h>
#include<windows.h>
#include<sstream>
#include<ctime>
#include<string>
#include<mysql.h>
#include<cstring>
#include<conio.h>
#include<cstring>
#include<map>

using namespace std;
int users =0;
int count_attempt=0;
int curr_user=0;
int user_no=0;
map <string,string> issued;
string loggedin_user="";


void showDoctorsDetails()
    {
        system("cls");
        cout<<"<==========================================================>"<<endl;
        cout<<"                     Dr. Waqar                              "<<endl;
        cout<<"           -----------Timing-----------                     "<<endl;
        cout<<"           Monday To Friday        9AM - 5PM                "<<endl;
        cout<<"           Saturday                10AM - 1PM               "<<endl;
        cout<<"           Sunday                  OFF                      "<<endl;
        cout<<"<==========================================================>"<<endl;

        cout<<"<==========================================================>"<<endl;
        cout<<"                     Dr. Shankar                            "<<endl;
        cout<<"           -----------Timing-----------                     "<<endl;
        cout<<"           Monday To Friday        1PM - 9PM                "<<endl;
        cout<<"           Saturday                1PM - 5PM               "<<endl;
        cout<<"           Sunday                  OFF                      "<<endl;
        cout<<"<==========================================================>"<<endl;

        cout<<"<==========================================================>"<<endl;
        cout<<"                     Dr. Krishna                            "<<endl;
        cout<<"           -----------Timing-----------                     "<<endl;
        cout<<"           Monday To Friday        8AM - 6PM                "<<endl;
        cout<<"           Saturday                10AM - 1PM               "<<endl;
        cout<<"           Sunday                  3PM - 5PM                "<<endl;
        cout<<"<==========================================================>"<<endl;

        cout<<"<==========================================================>"<<endl;
        cout<<"                     Dr. Roy                                "<<endl;
        cout<<"           -----------Timing-----------                     "<<endl;
        cout<<"           Monday To Friday        9AM - 5PM                "<<endl;
        cout<<"           Saturday                10AM - 1PM               "<<endl;
        cout<<"           Sunday                  7PM - 9PM                "<<endl;
        cout<<"<==========================================================>"<<endl;
    }


class user
{
private:
string username;
string password;
public:

// This method is used to take user input and check against the data in the database to login to the system
void login()
{
	if(curr_user==1)
	{
	cout<<" \t \t \t \t \t Already logged in";
	return;
	}
	if(count_attempt==3)
	{
		cout<<endl<<endl;
		cout<<" \t \t \t \t \t No more attempts";
		exit(0);
	}
	cout<<"Enter Username and Password to Login"<<endl;
	string user_name;
	string pass_word;

	cout<<"Username:";
	cin>>user_name;
	cout<<"Password:";
	cin>>pass_word;
	cin.ignore();
	system("cls");

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn ,"localhost" ,"root", "", "hospitalmanagement" ,0,NULL,0);
	if(conn)
    {
        int qstate = mysql_query(conn,"SELECT username,password FROM users");
        bool flag=false;
        if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                {
                if(row[0]==user_name && row[1]==pass_word)
                {
                        loggedin_user = row[0];

                        cout<<" \t \t \t \t \t \tLogin Successful"<<endl<<endl;
                        cout<<"\t\t\t==============================================================="<<endl;
                        cout<<"\t\t\t                         Welcome Admin                         "<<endl;
                        cout<<"\t\t\t==============================================================="<<endl;
                        curr_user=1;
                        flag=true;
                        break;
                }
                }
                if(!flag)
                {
                    cout<<" \t \t \t \t \t \t Incorrect Username or Password"<<endl;
                    cout<<" \t \t \t \t \t \t Press Enter and Try again"<<endl;
                    cin.ignore();
                    system("cls");
                    count_attempt++;
                    login();
                }


        }
        else
        {
            cout<<" \t \t \t \t \t No Accounts Registered";
        }

    }
}

	void logout()
	{
	    cout<<"Logout Successful"<<endl;
		curr_user=0;
	}


};
class hospital : public user
{
	public:
        // This method is used to view all the appointment details from the database
		void allAppointment()
		{
            if(loggedin_user=="")
			{
				cout<<" \t \t \t \t \t Please Login"<<endl;
				return ;
			}
			MYSQL* conn;
            MYSQL_ROW row;
            MYSQL_RES* res;
            conn = mysql_init(0);
            conn = mysql_real_connect(conn ,"localhost" ,"root", "", "hospitalmanagement" ,0,NULL,0);
            if(conn)
            {
            int qstate = mysql_query(conn,"SELECT doctor, patientname, time, age, contactno, symptoms from appointment");
            if(!qstate)
            {
                res = mysql_store_result(conn);
                system("cls");

                cout<<"Appointments for today are"<<endl;
                cout<<endl;
                while(row = mysql_fetch_row(res))
                {
                    cout<<"Doctor: "<<row[0]<<endl;
                    cout<<"Patient Name: "<<row[1]<<endl;
                    cout<<"Appointment Time: "<<row[2]<<endl;
                    cout<<"Age: "<<row[3]<<endl;
                    cout<<"Contact No: "<<row[4]<<endl;
                    cout<<"Symptoms: "<<row[5]<<endl;
                    cout<<endl;
                }
            }
            }
            else cout<<"Failed"<<endl;
		}

		// This method is used to add a new appointment in the database
		void addappointment(){

		    string doc, name, time, symptoms;
		    long long int age, contactno;

		    if(loggedin_user=="")
			{
				cout<<" \t \t \t \t \t Please Login"<<endl;
				return ;
			}

            cout<<"Choose Doctor from the list of availble doctors:"<<endl;
            cout<<"1. Dr. Waqar"<<endl;
            cout<<"2. Dr. Shankar"<<endl;
            cout<<"3. Dr. Krishna"<<endl;
            cout<<"4. Dr. Roy"<<endl;
			cout<<"\nEnter Doctor Name:"<<endl;
			cin.ignore();
            getline(cin,doc);

            cout<<"\nEnter Patient Name:"<<endl;
            cin>>name;

            cout<<"\nEnter Appointment Time:"<<endl;
            cin.ignore();
            getline(cin,time);

            cout<<"\nEnter Patient Age:"<<endl;
            cin>>age;

            cout<<"\nEnter Patient Contact no:"<<endl;
            cin>>contactno;

            cout<<"\nEnter Patient Symptoms:"<<endl;
			cin.ignore();
            getline(cin,symptoms);

            string nul="";
			MYSQL* conn;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn ,"localhost" ,"root", "", "hospitalmanagement" ,0,NULL,0);
			stringstream ss;
			ss<<"INSERT INTO appointment(doctor, patientname, time, age, contactno, symptoms) VALUES('"<<doc<<"','"<<name<<"','"<<time<<"','"<<age<<"', '"<<contactno<<"','"<<symptoms<<"')";
			int qstate=0;
			string query =  ss.str();
            const char* q= query.c_str();
            qstate = mysql_query(conn,q);
            if(qstate==0)
            {
            cout<<" \t \t \t \t \t Appointment added Successfully!"<<endl;
            return;
            }
            else
            {
                cout<<" \t \t \t \t \t Failed"<<endl;
                return;
            }

		}

		// This method is used to add a new staff entry in the database
		void addstaff(){
            string name, position;
		    long long int age, contactno, salary;

		    if(loggedin_user=="")
			{
				cout<<" \t \t \t \t \t Please Login"<<endl;
				return ;
			}

			cout<<"\nEnter Staff Name:"<<endl;
			cin.ignore();
            getline(cin,name);

            cout<<"\nEnter Staff Age:"<<endl;
            cin>>age;

            cout<<"\nEnter Staff Salary:"<<endl;
            cin>> salary;

            cout<<"\nEnter Staff Contact No:"<<endl;
            cin>>contactno;

            cout<<"\nEnter Staff Position:"<<endl;
            cin>>position;

            string nul="";
			MYSQL* conn;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn ,"localhost" ,"root", "", "hospitalmanagement" ,0,NULL,0);
			stringstream ss;
			ss<<"INSERT INTO staff(name, age, salary, contactno, position) VALUES('"<<name<<"','"<<age<<"','"<<salary<<"','"<<contactno<<"','"<<position<<"')";
			int qstate=0;
			string query =  ss.str();
            const char* q= query.c_str();
            qstate = mysql_query(conn,q);
            if(qstate==0)
            {
            cout<<" \t \t \t \t \t Staff Information added Successfully!"<<endl;
            return;
            }
            else
            {
                cout<<" \t \t \t \t \t Failed"<<endl;
                return;
            }
		}

		// This method is used to view all the available staff details in the database
		void allstaff(){

            if(loggedin_user=="")
			{
				cout<<" \t \t \t \t \t Please Login"<<endl;
				return ;
			}


		    MYSQL* conn;
            MYSQL_ROW row;
            MYSQL_RES* res;
            conn = mysql_init(0);
            conn = mysql_real_connect(conn ,"localhost" ,"root", "", "hospitalmanagement" ,0,NULL,0);
            if(conn)
            {
            int qstate = mysql_query(conn,"SELECT name, age, salary, contactno, position from staff");
            if(!qstate)
            {
                res = mysql_store_result(conn);
                system("cls");
                cout<<"--------------All Staffs Details------------"<<endl;
                cout<<endl;
                while(row = mysql_fetch_row(res))
                {
                    cout<<"Name: "<<row[0]<<endl;
                    cout<<"Age: "<<row[1]<<endl;
                    cout<<"Salary: "<<row[2]<<endl;
                    cout<<"Contact No: "<<row[3]<<endl;
                    cout<<"Position: "<<row[4]<<endl;
                    cout<<endl;
                }
            }
            }
            else cout<<"Failed"<<endl;
		}

		// This method is used to check the number of available beds randomly
		void checkBeds(){

            if(loggedin_user=="")
			{
				cout<<" \t \t \t \t \t Please Login"<<endl;
				return ;
			}

			system("cls");

            cout<<endl;
		    int random_no_of_beds = 0;
		    int N = 200;
		    random_no_of_beds = rand() % 200; //this will keep the random number within the range of 200

		    cout<<"Number of beds available today are: "<<random_no_of_beds<<endl;
		}

};


int main()
{
    system("Color DE");

	 cout<<"\t\t\t=============================================================================="<<endl;
    cout<<"\t\t\t                          Hospital Management System                            "<<endl;
    cout<<"\t\t\t=============================================================================="<<endl;
	user u1;
	int x;
	int choice=0;
	hospital h;
	do
	{
		cout<<endl;
		cout<<"\t----------choose from below----------"<<endl;
		cout<<"\t1. Login"<<endl;
		cout<<"\t2. Available Doctors"<<endl;
		cout<<"\t3. Check All Appointments"<<endl;
		cout<<"\t4. Add new Doctor Appointment"<<endl;
		cout<<"\t5. Check no of beds available"<<endl;
		cout<<"\t6. Store new Staff Information"<<endl;
		cout<<"\t7. Check all Staff Information"<<endl;
		cout<<"\t8. Logout"<<endl;
		cout<<"\t0 to exit"<<endl;
		cout<<"\t-------------------------------------"<<endl;
		cin>>x;
	switch(x)
	{
		case 1 : u1.login();
				 break;
		case 2 : showDoctorsDetails();
				 break;
		case 3 : h.allAppointment();
				 break;
		case 4 : h.addappointment();
                 break;
		case 5 : h.checkBeds();
				 break;
		case 6 : h.addstaff();
				 break;
		case 7 : h.allstaff();
				 break;
		case 8 : u1.logout();
				 break;
		case 0 : choice=1;

	}
	}
	while(choice==0);
}
