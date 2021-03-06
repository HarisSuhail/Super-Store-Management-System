#include "employee.h"
//#include "manageemployees.h"
#include "ManageEmployeeCase.h"
#include "ManageSales.h"
#include "UpdateInventory.h"
#include <windows.h>
#include "electronics.h"
#include <iostream>
#include <conio.h>
//#include "inputexception.h"
#include <time.h>
#include "electronics.h"
#include <iomanip>
#include "otherdisplaycase.h"
#include "miscfunc.h"
#include "errorcheck.h"
#include "menu.h"
#define EMPDIR "employee.dat"


/////////////////////
int getint(int, int);
float getfloat(float, float);
void startup (fstream&);
void caseone();
int login_screen(fstream&, bool&);
void MainMenu(int,int);
void Password(string &);
void drawRectangle(int x, int y, int a, int b, int delay = 0, char c ='*');

////////////////////


using namespace std;

int main()
{
	
	bool is_manager;
	int employeeid;
	fstream datafile;
	int position;


	datafile.open(EMPDIR,ios::app);
	datafile.seekg(0,ios::end);
	position = datafile.tellg();
	datafile.close();
	if(position==0)
	{
		startup(datafile);
	}
	
	system ("mode 168");
	 ///////////////////////////////////////////////////////////////NEW
	for(int _i = 0 ; _i<4; _i++)
	{
	employeeid= login_screen(datafile, is_manager);
	if(employeeid)
		break;
	}


	
	

	if(employeeid)
	MainMenu(is_manager,employeeid);
	 return 0;	
}








int login_screen(fstream& myfile, bool & is_manager)
{
	myfile.open(EMPDIR, ios::binary | ios::in );
	system("cls");
	string password="\0";
	int username;
	system("color 79");
	drawRectangle(30,10,140,45);
			gotoxy(85-(strlen("OOP Store Mangement System")/2),12);
	string a = "OOP Store Mangement System";
	int i = 0;
	while(a[i]!='\0')
	{
		cout<<a[i];
		Sleep(70);               ////////////////////////////
		i++;
	}
	Sleep(1000);
	gotoxy(85-strlen("Employee Id:"),16);
	cout<<"Employee Id:";
	username = geti(1001, 2000);
	gotoxy(85-strlen("Employee Id:"),17);
	cout<<"Password   :";
	i=0;
	
	
	if(!myfile)
	{
		gotoxy(85-strlen("Employee Id:"),44);
		cerr<<"File cannot be found";

		
		_getch();
		
	}
	
	Employee tempemp(1);
	tempemp.read_from_file(myfile, username-1000);
	if(myfile.fail())
	{
		gotoxy(85-strlen("Employee Id:"),44);
		cout<<"This ID is not registered";
		Sleep(1000);
		
		myfile.clear();
		
		myfile.seekg(0, ios::beg);
		myfile.close();
		return false;
		
	}
	is_manager = tempemp.get_is_manager();
	myfile.close();

	Password(password);

	if(tempemp.get_password() == password)
	{
		gotoxy(85-strlen("Employee Id:"),44);
	cout<<"Login Successful.";
	Sleep(1000);
	return username;
	}
	else 
	{
		gotoxy(85-strlen("Employee Id:"),44);
		cout<<"Id or password incorrect.";
		Sleep(1000);
		return false;
	}
}






void MainMenu(int is_manager,int id)
{   int x;
	if(is_manager)
	{
		x=5;
	}
	else
	{
	 x= 4;
	}


	int o;
	if(x==5)o=6;
	else o = 4;
	Menu MainMenu(o);
	MainMenu.changecolour(121,121);
	MainMenu.setRectangle(60,10,110,25);
	if(x==5)
	{
		MainMenu.setoptions(4, "Manage Employees");
		MainMenu.setoptions(1, "Open Inventory");
		MainMenu.setoptions(2, "Update Inventory");
		MainMenu.setoptions(3, "Invoice Management");	
		MainMenu.setoptions(5, "Show account details");
		MainMenu.setoptions(6, "Logout");
	}
	if(x==4)
	{
		MainMenu.setoptions(4, "Logout");
		MainMenu.setoptions(1, "Open Inventory");
		MainMenu.setoptions(2, "Show Account details");
		MainMenu.setoptions(3, "Invoice Management");	
		
	}
	





		do{
	switch(MainMenu.displaymenu(74,15))///////////////////////
	{
	case 1:
		//elec_menu();
	
		caseone();



		break;
	case 2:
		if(x==5)
		update_inventory();
		else
		{	
		accountdetails(id);
		}
		
		break;
	case 3:
		
		managesalecase ();
		break;
	case 4:
		if(x==5)
		manageemployees();
		else
		{return;}
		
			
		break;
	case 5:
		accountdetails(id);
		break;
		 
	case 6:
		return;
	default:
		return;
		break;
	}
		}while(1);
}

/*
		Menu MainMenu(5);
		MainMenu.setoptions(1, "Manage Employees");	
		MainMenu.setoptions(2, "Open Inventory");
		MainMenu.setoptions(3, "Update Inventory");
		MainMenu.setoptions(4, "Manage Sales");
		MainMenu.setoptions(5, "Exit");
*/


void Password (string& password)
{
	int x=wherex()-1,y=wherey();
	int i=0;char c,pass[100];
	do
	{
		c=_getch();
		if(c!='\r')
		{
			if(c=='\b')
			{
				if((wherex()-1)==x){}
				else
				{
					gotoxy(wherex()-1,wherey());
					cout<<'\0';
					gotoxy(wherex()-1,wherey());
					if(i>0){i--;}
				}
			}
			else 
			{	
				pass[i]=c;
				cout<<"*";i++;
			}
		}
		else
		{
			pass[i]='\0';
			break;
		}
	}while(1);
	password=pass;
	if(password[0]=='\0')
	{
		password = "W!R!O@N!G!@!@#!@#";
	}
}

void drawRectangle(int x, int y, int a, int b, int delay, char c)
{
     gotoxy(x,y);
     for(int i = x;i<=a;i++)
     { 
             Sleep(delay);
             cout<<c;
             gotoxy(i, y);
             
             
     }
      gotoxy(a, y);
      for(int i = y;i<=b+1;i++)
     { 
              Sleep(delay);
             cout<<c;
             gotoxy(a, i);
         }
         gotoxy(x, y);
           for(int i = y;i<=b;i++)
     { 
              Sleep(delay);
              
             cout<<c;
             gotoxy(x, i);
             
             
             
             }
     gotoxy(x, b);
      for(int i = x;i<=a;i++)
     { 
              Sleep(delay);
            cout<<c;
             
             gotoxy(i, b);
         }
             
    
             
     
     }

void startup(fstream& datafile)
{
	datafile.open(EMPDIR, ios::app);
	Employee temp;
	temp.set_first_name("admin");
	temp.set_last_name("admin");
	temp.set_password("admin");
	temp.set_is_manager(1);
	temp.write_to_file(datafile);
	datafile.close();



}

void caseone()
{
	Menu caseone(4);
	caseone.setoptions(1,"Electronics");
	
	caseone.setoptions(2,"Sports Items");
	
	caseone.setoptions(3,"Stationery");
	
	caseone.setoptions(4,"Back");



	caseone.changecolour(121,121);
	caseone.setRectangle(60,10,110,25);
	do{
	switch(caseone.displaymenu(74,15))
	{
	case 1:
	
		elec_menu();
		break;
	case 2:
		sports_menu();
		break;
	case 3:
		stat_menu();
		break;
	case 4:
		return;
		
	case 5:
		return ;

	}

	}while(1);
}