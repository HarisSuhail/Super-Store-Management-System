# include <iostream>
# include <fstream>
# include "managesales.h"
# include "errorcheck.h"
# include <windows.h>
# include "menu.h"
# include <iomanip>
# include <sstream>
# include <ctime>
# define MAX 20
# define FILENAME "INVOICE_RECORD_OF_"


using namespace std;

//--------------------------------------------------------------------------

	void caseE(electronics ,int&, int&, fstream&,int, float&);
	void caseP(sports ,int&, int&, fstream&,int,float&);
	void caseT(stationery ,int&, int&, fstream&,int, float&);
	void drawRectangle(int x, int y, int a, int b, int delay = 0, char c ='*');
	void clean();
	int search(string);
	int barsearch(string);
	int othermenu();
	void cleanlowerbox();
	string makefile();

//--------------------------------------------------------------------------

	void Edit_electronics(fstream& file, electronics& E, int N)
	{
		E.setID(N);												//!!! E.SetAll() over here !!!
		file.seekg((N - 1)*sizeof(electronics), ios::beg);
		E.write(file);
	}

//*************************** Function Separator *****************************//

	
	int managesalecase ()
	{
		fstream salesfile(makefile().c_str(), ios::out|ios::app);
		
		//salesfile<<"------------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------"<<endl;
		//salesfile<<",ID,TITLE,BARCODE,QUANTITY,RATE,PRICE"<<endl;
		salesfile.close();



		managesales sale('c');
		
		//managesales receipt[MAX];
		//electronics *earray;
		//sports *parray;
		//int quantity;
		//int num;

		electronics tempelec;
		sports tempsports;
		stationery tempstat;
		string filename;
		float total=0;
		int index = 0;
		fstream myfile;
		int listx=20, listy=25;
		int paid;
		
		//myfile.open(sale.get_filename().c_str(), ios::in|ios::binary);
		//myfile.seekg(0, ios::end);
		//num = myfile.tellg();
		//num = num / sizeof(sale);
		//int location;
		//myfile.seekg(0, ios::beg);
		//myfile.close();

		int out = 0;

	//************************************************************************//

		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col=12;
        FlushConsoleInputBuffer(hConsole);
    
	//************************************************************************//
			
		SetConsoleTextAttribute(hConsole, 121);
		system("cls");
			
		int id;
		string title, barcode;

		do{
			switch(othermenu())
			{
				case 0:	out= 1;
						gotoxy(20,8);
						id=geti(1, 2999);
						sale.set_id(id);
						sale.set_type();
						gotoxy(30, 40);
				
						////
						//cout<<sale.get_type();
						//_getch();
						////
	
						switch(sale.get_type())
						{
							case 'E':	caseE(tempelec, listx, listy, myfile,id, total);
										break;
			
							case 'P':	caseP(tempsports, listx, listy, myfile,id, total);
										break;
			
							case 'T':	caseT(tempstat, listx, listy, myfile,id, total);
										break;
						}
						break;

				case 1: gotoxy(60,8);
						getstring(title); 
						id=search(title);
						out= 1;
						if(id==0)break;
						sale.set_id(id);
						sale.set_type();
						gotoxy(30, 40);
		
						////
						//cout<<sale.get_type();
						//_getch();
						////
						switch(sale.get_type())
						{
							case 'E':	caseE(tempelec, listx, listy, myfile,id, total);			
										break;
	
							case 'P':	caseP(tempsports, listx, listy, myfile,id, total);
										break;
			
							case 'T':	caseT(tempstat, listx, listy, myfile,id, total);
										break;
						}
		
						break;

				case 2: gotoxy(100,8);
						getstring(barcode);
						id = barsearch(barcode);
						out= 1;
						if(id==0)break;
						sale.set_id(id);
						sale.set_type();
						gotoxy(30, 40);
			
						////
						//cout<<sale.get_type();
						//_getch();
						////
						
						switch(sale.get_type())
						{
							case 'E':	caseE(tempelec, listx, listy, myfile,id, total);
										break;	
		
							case 'P':	caseP(tempsports, listx, listy, myfile,id, total);
										break;
			
							case 'T':	caseT(tempstat, listx, listy, myfile,id, total);
										break;
						}
						break;
	
				case 3: do
						{
							gotoxy(118, 49);
							cout<<" PAID  :";
							SetConsoleTextAttribute(hConsole, 124);
							paid=getf(0, 2147483640);
							SetConsoleTextAttribute(hConsole, 121);
							if(paid<total)
							{
								gotoxy(118, 49);
								cout<<" PAID  :         ";
							}
						}while(paid<total);
						
						SetConsoleTextAttribute(hConsole, 121);
						gotoxy(119, 50 );
						cout<<"-----------";
						gotoxy(119, 51);
						cout<<"CHANGE:";
						SetConsoleTextAttribute(hConsole, 124);
						cout<<paid -total;
						SetConsoleTextAttribute(hConsole, 121);
						gotoxy(119, 52 );
						cout<<"-----------";
							
						_getch();
						listy=25;
						cleanlowerbox();
						if(salesfile.is_open()){salesfile.close();}
						salesfile.open(makefile().c_str(), ios::out|ios::app);
						salesfile<<endl<<endl<<",,,,,,,TOTAL:"<<total<<endl;
						salesfile<<"------------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------"<<endl;
						salesfile<<",ID,TITLE,BARCODE,QUANTITY,RATE,PRICE"<<endl;
						total=0;	
	
						break;

				case 4:
					{
						if(total!=0)
						{salesfile.open(makefile().c_str(), ios::out|ios::app);
						salesfile<<endl<<endl<<",,,,,,,TOTAL:"<<total<<endl;
						salesfile<<"------------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------,-----------"<<endl;
						}
						if(total == 0 ) return 1;

							gotoxy(118, 49);
							cout<<" PAID  :";
							SetConsoleTextAttribute(hConsole, 124);
							paid=getf(0, 2147483640);
							SetConsoleTextAttribute(hConsole, 121);
							if(paid<total)
							{
								gotoxy(118, 49);
								cout<<" PAID  :         ";
							}
						}while(paid<total);
						
						SetConsoleTextAttribute(hConsole, 121);
						gotoxy(119, 50 );
						cout<<"-----------";
						gotoxy(119, 51);
						cout<<"CHANGE:";
						SetConsoleTextAttribute(hConsole, 124);
						cout<<paid -total;
						SetConsoleTextAttribute(hConsole, 121);
						gotoxy(119, 52 );
						cout<<"-----------";
							
						_getch();
						listy=25;
						
						
						
						total=0;	
	
					
					return 1;
						break;
			}
		}while(1);
		_getch();
	}	

//*************************** Function Separator *****************************//

	int othermenu ()
	{

	//************************************************************************//
	
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col=12;
		FlushConsoleInputBuffer(hConsole);

	//************************************************************************//
	

		drawRectangle(10,5,150,20);
		drawRectangle(10,23,150,60);
		gotoxy(20, 24);
		SetConsoleTextAttribute(hConsole, 121);			//Lower Box Print Function//
		cout<<setw(10)<<"ID"
			<<setw(20)<<"Title"
			<<setw(20)<<"BarCode"
			<<setw(20)<<"Quantity"
			<<setw(20)<<"Rate per item"
			<<setw(20)<<"Price";
		SetConsoleTextAttribute(hConsole, 121);
		
		gotoxy(20,7);									//Upper Box Print Function//
		SetConsoleTextAttribute(hConsole, 124);
		cout<<"ID";
		SetConsoleTextAttribute(hConsole, 121);
		gotoxy(60, 7);
		cout<<"Title";
		gotoxy(100,7);
		cout<<"Barcode";
		gotoxy(140,17);
		cout<<"END";
		gotoxy(140,18);
		cout<<"EXIT";
	
		
		int choice = 0, prevchoice = 0,temp;
		while(1)
		{
			temp =_getch();
			if(temp == 77 || temp == 75 || temp == 13) goto cn;
			 
		cn:
			if(temp == 13) return choice;			
			
			if(temp==77)
			{   
				prevchoice = choice;
				choice++;
				if(choice > 4) choice = 0;
			}

			if(temp==75)
			{    
				prevchoice = choice;
				choice --;
				if(choice < 0 ) choice = 4;
			}

			switch(prevchoice)
			{
				case 0:	gotoxy(20,7);
						SetConsoleTextAttribute(hConsole, 121);
						cout<<"ID";
						break;

				case 1:	gotoxy(60,7);
						SetConsoleTextAttribute(hConsole, 121);
						cout<<"Title";
						break;				

				case 2:	gotoxy(100,7);
						SetConsoleTextAttribute(hConsole, 121);
						cout<<"Barcode";
						break;
			
				case 3:	gotoxy(140,17);
						SetConsoleTextAttribute(hConsole, 121);
						cout<<"END";
						break;
			
				case 4:	gotoxy(140,18);
						SetConsoleTextAttribute(hConsole, 121);
						cout<<"EXIT";
						break;
			}

			switch(choice)
			{
				case 0:	gotoxy(20,7);
						SetConsoleTextAttribute(hConsole, 124);
						cout<<"ID";
						SetConsoleTextAttribute(hConsole, 121);
						break;
				
				case 1:	gotoxy(60,7);
						SetConsoleTextAttribute(hConsole, 124);
						cout<<"Title";
						SetConsoleTextAttribute(hConsole, 121);
						break;

				case 2:	gotoxy(100,7);
						SetConsoleTextAttribute(hConsole, 124);
						cout<<"Barcode";
						SetConsoleTextAttribute(hConsole, 121);
						break;

				case 3:	gotoxy(140,17);
						SetConsoleTextAttribute(hConsole, 124);
						cout<<"END";
						SetConsoleTextAttribute(hConsole, 121);
						break;

				case 4:	gotoxy(140,18);
						SetConsoleTextAttribute(hConsole, 124);
						cout<<"EXIT";
						SetConsoleTextAttribute(hConsole, 121);
						break;
			}							//switch statement ends//
		}								//while  loop  ends    //
	}							

//*************************** Function Separator *****************************//

	void caseE(electronics tempelec,int& listx,int& listy,fstream& myfile, int id, float& total)
	{
		
	//************************************************************************//

		HANDLE  hConsole;
	    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col=12;
        FlushConsoleInputBuffer(hConsole);

	//************************************************************************//
	
		string filename;
		fstream salefile (makefile().c_str(),ios::out|ios::app);
		int num, out=0;
		float quantity;
		
		filename = "electronics.dat";
		if(myfile.is_open())myfile.close();
		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(electronics);
		
		
		for(int i = 0; i < num ; i++)
		{
			myfile.seekg(i*sizeof(electronics), ios::beg);
			if(!myfile.is_open()){

				gotoxy(20, 15);
				cout<<"No items of this category present"; 
				gotoxy(20, 15);
				Sleep(1000);
				cout<<"                                 "; 

				return;
			}
			myfile.read(reinterpret_cast<char*>(&tempelec), sizeof(tempelec));
			if(tempelec.getID() == id)
			{
				gotoxy(20, 8);
				cout<<tempelec.getID();
				gotoxy(60, 8);
				cout<<tempelec.getTitle();
				gotoxy(100, 8);
				cout<<tempelec.getBarcode();
				gotoxy(20, 15);
				cout<<"Enter Quantity:";
				cin>>quantity;
				if(quantity>tempelec.getQuantity()||quantity<0)
				{
					gotoxy(20, 16);
					cout<<"Not enough Items present.";
					out = 1;
					Sleep(1000);
					myfile.close();
					clean();
					break;
				}
				gotoxy(20,15);
				cout<<"                                   ";
				gotoxy(20, 16);
				cout<<"                                   ";
				tempelec.setQuantity((tempelec.getQuantity()-quantity));
				tempelec.setID(id);												//!!! E.SetAll() over here !!!
	
				gotoxy(listx,listy++);
				cout<<setw(10)<<tempelec.getID()
					<<setw(20)<<tempelec.getTitle()
					<<setw(20)<<tempelec.getBarcode()
					<<setw(20)<<quantity
					<<setw(20)<<tempelec.getRate()
					<<setw(20)<<quantity * tempelec.getRate();
				salefile
					<<","<<tempelec.getID()
					<<","<<tempelec.getTitle()
					<<","<<tempelec.getBarcode()
					<<","<<quantity
					<<","<<tempelec.getRate()
					<<","<<quantity * tempelec.getRate()<<endl;

				total += quantity * tempelec.getRate();
				clean();
				out = 1;
				break;

			}
			if(out==1)
				break;
		}
		myfile.clear();
			
		
		myfile.seekg((id- 1)*sizeof(electronics), ios::beg);
		if(myfile.fail())
		{
			
			myfile.clear();
			
		}
		else
		{
			if(out!=0)tempelec.write(myfile);
			if(myfile.fail()){cout<<"XXXPPPXXX";}
		}

			//*****Blinking Function*****//
		if(out == 0)							
		{
			SetConsoleTextAttribute(hConsole, 124);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";		
			Sleep(200);
			gotoxy(20, 16);
			cout<<"                     ";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"                     ";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";
			_getch();
			SetConsoleTextAttribute(hConsole, 121);
			clean();
			if(myfile.is_open())myfile.close();			
		}		

		for (int k = 6 ; k < 40 ; k++)
		{
			gotoxy(0,k);
			cout<<" ";
		}
		gotoxy(119, 48);
		cout<<"TOTAL :";
		SetConsoleTextAttribute(hConsole, 124);
		cout<<total;
		SetConsoleTextAttribute(hConsole, 121);
	}										

//*************************** Function Separator *****************************//

	void caseP(sports tempsports,int& listx,int& listy,fstream& myfile, int id, float&total)
	{
		
	//************************************************************************//
	
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col=12;
		FlushConsoleInputBuffer(hConsole);
    
	//************************************************************************//
	
		fstream salefile(makefile().c_str(),ios::out|ios::app);
		string filename;
		int  num, out=0;
		float quantity;

		filename = "sports.dat";
		if(myfile.is_open())myfile.close();
		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(sports);
		/////
		//cout<<" ASD" <<num;
		//_getch();
		/////
		for(int i = 0; i < num ; i++)
		{
			myfile.seekg(i*sizeof(sports), ios::beg);
			if(!myfile.is_open()){
				
				gotoxy(20, 15);
				cout<<"No items of this category present"; 
				gotoxy(20, 15);
				Sleep(1000);
				cout<<"                                 "; 

				return;
			}
			myfile.read(reinterpret_cast<char*>(&tempsports), sizeof(tempsports));
			///
			//cout<<"-"<<tempsports.getID();
			///
			if(tempsports.getID() == id)
			{
				gotoxy(20, 8);
				cout<<tempsports.getID();
				gotoxy(60, 8);
				cout<<tempsports.getTitle();
				gotoxy(100, 8);
				cout<<tempsports.getBarcode();
				gotoxy(20, 15);
				cout<<"Enter Quantity:";
				cin>>quantity;
				if(quantity>tempsports.getQuantity()||quantity<0)
				{
					gotoxy(20, 16);
					cout<<"Not enough Items present.";
					out = 1;
					Sleep(1000);
					myfile.close();
					gotoxy(20, 8);
					clean();
					out = 1;
					break;
				}
				gotoxy(20,15);
				cout<<"                                   ";
				gotoxy(20, 16);
				cout<<"                                   ";
				int temp = tempsports.getQuantity();
				temp = temp - quantity;
				tempsports.setQuantity(temp);
				tempsports.setID(id);				//!!! E.SetAll() over here !!!
				
				//cout<<"temp"<<tempsports.getQuantity();
				//myfile.seekg(id-1,ios::beg);
				//myfile.write(reinterpret_cast<char*>(&tempsports), sizeof(tempsports));
				//myfile.close();

				gotoxy(listx,listy++);
				cout<<setw(10)<<tempsports.getID()
					<<setw(20)<<tempsports.getTitle()
					<<setw(20)<<tempsports.getBarcode()
					<<setw(20)<<quantity
					<<setw(20)<<tempsports.getRate()
					<<setw(20)<<quantity * tempsports.getRate();
				salefile
					<<","<<tempsports.getID()
					<<","<<tempsports.getTitle()
					<<","<<tempsports.getBarcode()
					<<","<<quantity
					<<","<<tempsports.getRate()
					<<","<<quantity * tempsports.getRate()<<endl;
				total += quantity * tempsports.getRate();
				clean();
				out = 1;
				break;

			}
		}
		myfile.clear();
		myfile.seekg((id- 1000)*sizeof(sports), ios::beg);
		if(myfile.fail())
		{
			cout<<".";
			myfile.clear();
			fstream check("sport.dat", ios::binary|ios::in|ios::out);
			tempsports.write(check);
			check.close();
		}
		else
		{
			if(out!=0)
			tempsports.write(myfile);
			if(myfile.fail()){cout<<".";}
		}
		
		if(out == 0)
		{
			SetConsoleTextAttribute(hConsole, 124);		//*****Blinking Function*****\\

			gotoxy(20, 16);
			cout<<"Item Does not Exist.";		
			Sleep(200);
			gotoxy(20, 16);
			cout<<"                     ";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"                     ";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";
			_getch();
			SetConsoleTextAttribute(hConsole, 121);
			clean();
			if(myfile.is_open())myfile.close();
		}
	
		for (int i = 6 ; i < 40 ; i++)
		{
			gotoxy(0,i);
			cout<<"      ";
		}
		gotoxy(119, 48);
		cout<<"TOTAL :";
		SetConsoleTextAttribute(hConsole, 124);
		cout<<total;
		SetConsoleTextAttribute(hConsole, 121);
	}												
	
//*************************** Function Separator *****************************//

	void caseT(stationery tempstat, int &listx, int &listy,fstream& myfile, int id , float&total)
	{

	//************************************************************************//
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col=12;
		FlushConsoleInputBuffer(hConsole);

	//************************************************************************//
	
		string filename;
		int  num, out=0;
		fstream salefile(makefile().c_str(), ios::out|ios::app);
		float quantity;
	
		filename = "stationery.dat";
		if(myfile.is_open())myfile.close();
		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(stationery);
		/////
		//cout<<" ASD" <<num;
		//_getch();
		/////
		for(int i = 0; i < num ; i++)
		{
			myfile.seekg(i*sizeof(stationery), ios::beg);
			if(!myfile.is_open())
			{
				gotoxy(20, 15);
				cout<<"No items of this category present"; 
				gotoxy(20, 15);
				Sleep(1000);
				cout<<"                                 "; 

				return;
			}
			myfile.read(reinterpret_cast<char*>(&tempstat), sizeof(tempstat));
			if(tempstat.getID() == id)
			{
				gotoxy(20, 8);
				cout<<tempstat.getID();
				gotoxy(60, 8);
				cout<<tempstat.getTitle();
				gotoxy(100, 8);
				cout<<tempstat.getBarcode();
				gotoxy(20, 15);
				cout<<"Enter Quantity:";
				cin>>quantity;
				if(quantity>tempstat.getQuantity()||quantity<0)
				{
					gotoxy(20, 16);
					cout<<"Not enough Items present.";
					out = 1;
					Sleep(1000);
					myfile.close();
					gotoxy(20, 8);
					clean();
					break;
				}
				gotoxy(20,15);
				cout<<"                                   ";
				gotoxy(20, 16);
				cout<<"                                   ";
				tempstat.setQuantity((tempstat.getQuantity()-quantity));
				tempstat.setID(id);								//!!! E.SetAll() over here !!!
	
				//myfile.seekg(id-1,ios::beg);
				//myfile.write(reinterpret_cast<char*>(&tempstat), sizeof(tempstat));
				
				gotoxy(listx,listy++);
				cout<<setw(10)<<tempstat.getID()
					<<setw(20)<<tempstat.getTitle()
					<<setw(20)<<tempstat.getBarcode()
					<<setw(20)<<quantity
					<<setw(20)<<tempstat.getRate()
					<<setw(20)<<quantity * tempstat.getRate();
				salefile<<","<<tempstat.getID()
					<<","<<tempstat.getTitle()
					<<","<<tempstat.getBarcode()
					<<","<<quantity
					<<","<<tempstat.getRate()
					<<","<<quantity * tempstat.getRate()<<endl;
			
				
				
				total += quantity * tempstat.getRate();
				clean();
				out = 1;
				break;
			}
		}
		myfile.clear();
		myfile.seekg((id- 2000)*sizeof(stationery), ios::beg);
		if(myfile.fail())
		{
			cout<<".";
			myfile.clear();
			fstream check("stationery.dat", ios::binary|ios::in|ios::out);
			tempstat.write(check);
			check.close();
		}
		else
		{
			if(out!=0)tempstat.write(myfile);
			if(myfile.fail()){cout<<".";}
		}
		
		if(out == 0)
		{
			SetConsoleTextAttribute(hConsole, 124);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";					
			Sleep(200);
			gotoxy(20, 16);
			cout<<"                     ";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"                     ";
			Sleep(200);
			gotoxy(20, 16);
			cout<<"Item Does not Exist.";
			_getch();
			SetConsoleTextAttribute(hConsole, 121);
			if(!myfile.is_open()){myfile.close();}
			clean();
			if(myfile.is_open())myfile.close();
		}

		for (int i = 6 ; i < 40 ; i++)
		{
			gotoxy(0,i);
			cout<<"      ";
		}

		gotoxy(119, 48);
		cout<<"TOTAL :";
		SetConsoleTextAttribute(hConsole, 124);	
		cout<<total;
		SetConsoleTextAttribute(hConsole, 121);			
	}												// CaseT ends here \\

	
//*************************** Function Separator *****************************//
	
	void clean()
	{
		gotoxy(20, 8);
		cout<<"                              ";
		gotoxy(60, 8);
		cout<<"                              ";
		gotoxy(100, 8);
		cout<<"                     ";
		gotoxy(20, 15);
		cout<<"                                   ";
		gotoxy(20, 16);
		cout<<"                                   ";
	}

//*************************** Function Separator *****************************//

	int search(string a)
	{
		string filename;
		sports tempsports;
		electronics tempelec;
		stationery tempstat;
		fstream myfile;
		int  num, out=0;
	
	//------------------------------*****----------------------------//
		filename = "electronics.dat";
		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(electronics);
	
		for(int i = 0; i < num ; i++)
		{			
			myfile.seekg(i*sizeof(electronics), ios::beg);
			if(!myfile.is_open())	{cout<<"Could not find file"; _getch();}
			myfile.read(reinterpret_cast<char*>(&tempelec), sizeof(tempelec));
			if(tempelec.getTitle() == a){return tempelec.getID();}
		}
		myfile.close();
	
	//------------------------------*****----------------------------//
		filename = "sports.dat";

		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(sports);
		
		for(int i = 0; i < num ; i++)
		{	
			myfile.seekg(i*sizeof(sports), ios::beg);
			if(!myfile.is_open()){cout<<"Could not find file"; _getch();}
			myfile.read(reinterpret_cast<char*>(&tempsports), sizeof(tempsports));
			if(tempsports.getTitle() == a){return tempsports.getID();}
		}
		myfile.close();

	//------------------------------*****----------------------------//
		filename = "stationery.dat";

		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(stationery);
		/////
		//cout<<" ASD" <<num;
		//_getch();
		/////
		for(int i = 0; i < num ; i++)
		{		
			myfile.seekg(i*sizeof(stationery), ios::beg);
			if(!myfile.is_open())
			{
				gotoxy(20, 15);
				cout<<"Could not find file"; _getch();gotoxy(20,15);cout<<"                   ";
			}
			myfile.read(reinterpret_cast<char*>(&tempstat), sizeof(tempstat));
			///
			//cout<<"-"<<tempstat.getID();
			///
			if(tempstat.getTitle() == a){return tempstat.getID();}
		}
		myfile.close();

	//------------------------------*****----------------------------//
		
	//************************************************************************//
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col=12;
		FlushConsoleInputBuffer(hConsole);

	//************************************************************************//
	
		SetConsoleTextAttribute(hConsole, 124);
		gotoxy(20, 16);
		cout<<"Item Does not Exist.";	
		Sleep(200);
		gotoxy(20, 16);
		cout<<"                     ";
		Sleep(200);
		gotoxy(20, 16);
		cout<<"Item Does not Exist.";
		Sleep(200);
		gotoxy(20, 16);
		cout<<"                     ";
		Sleep(200);
		gotoxy(20, 16);
		cout<<"Item Does not Exist.";
		_getch();
		SetConsoleTextAttribute(hConsole, 121);
		clean();
		return 0;
	}

//*************************** Function Separator *****************************//

	int barsearch(string a)
	{
		string filename;
		sports tempsports;
		electronics tempelec;
		stationery tempstat;
		fstream myfile;
		int  num, out=0;

	//------------------------------*****----------------------------//
		filename = "electronics.dat";
		
		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(electronics);
		/////
		//cout<<" ASD" <<num;
		//_getch();
		/////
		for(int i = 0; i < num ; i++)
		{	
			myfile.seekg(i*sizeof(electronics), ios::beg);
			if(!myfile.is_open())	{cout<<"Could not find file"; _getch();}
			myfile.read(reinterpret_cast<char*>(&tempelec), sizeof(tempelec));
			///
			//cout<<"-"<<tempelec.getID();
			///
			if(tempelec.getBarcode() == a){return tempelec.getID();}
		}
		myfile.close();

	//------------------------------*****----------------------------//		
		filename = "sports.dat";
		
		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(sports);
		/////
		//cout<<" ASD" <<num;
		//_getch();
		/////
		for(int i = 0; i < num ; i++)
		{	
			myfile.seekg(i*sizeof(sports), ios::beg);
			if(!myfile.is_open()){cout<<"Could not find file"; _getch();}
			myfile.read(reinterpret_cast<char*>(&tempsports), sizeof(tempsports));
			///
			//cout<<"-"<<tempsports.getID();
			///
			if(tempsports.getBarcode() == a){return tempsports.getID();}
		}
		myfile.close();

	//------------------------------*****----------------------------//	
		filename = "stationery.dat";
		
		myfile.open(filename.c_str(), ios::in|ios::binary|ios::out);
		myfile.seekg(0, ios::end);
		num  = myfile.tellg();
		num = num / sizeof(stationery);
		/////
		//cout<<" ASD" <<num;
		//_getch();
		/////
		for(int i = 0; i < num ; i++)
		{	
			myfile.seekg(i*sizeof(stationery), ios::beg);
			if(!myfile.is_open())
			{
				gotoxy(20, 15);
				cout<<"Could not find file"; _getch();gotoxy(20,15);cout<<"                   ";
			}
			myfile.read(reinterpret_cast<char*>(&tempstat), sizeof(tempstat));
			///
			//cout<<"-"<<tempstat.getID();
			///
			if(tempstat.getBarcode() == a){return tempstat.getID();}
		}
		myfile.close();

	//------------------------------*****----------------------------//	

	//************************************************************************//
	
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int col=12;
	    FlushConsoleInputBuffer(hConsole);

    //************************************************************************//
	
	//------------------------------*****----------------------------//	
		SetConsoleTextAttribute(hConsole, 124);					//*****Blinking Function*****//

		gotoxy(20, 16);
		cout<<"Item Does not Exist.";			
		Sleep(200);
		gotoxy(20, 16);
		cout<<"                     ";
		Sleep(200);
		gotoxy(20, 16);
		cout<<"Item Does not Exist.";
		Sleep(200);
		gotoxy(20, 16);
		cout<<"                     ";
		Sleep(200);
		gotoxy(20, 16);
		cout<<"Item Does not Exist.";
		_getch();
		SetConsoleTextAttribute(hConsole, 121);
		clean();
		return 0;
	}

//*************************** Function Separator *****************************//

void cleanlowerbox()
{
	int __x=17,__y=25;
	for (;__y<55;__y++)
	{	
		gotoxy(__x,__y);
		cout<<setw(120)<<" ";                                                            
	}	   
}


//*************************** Function Separator *****************************//

string makefile()
{


	fstream myfile;
	string filename, temp;
	ostringstream mystream;
   time_t now = time(0);
   tm *ltm = localtime(&now);
   mystream<<"_"<< ltm->tm_mday <<"_"<< 1 + ltm->tm_mon << "_" << 1900 + ltm->tm_year<<".csv";
   filename = FILENAME;
   temp = mystream.str();
   filename = filename + temp;
   temp = "Salesrecord\\";
   filename = temp + filename;
   
   myfile.open( filename.c_str(),ios::app|ios::out);
   if(!myfile.is_open())
   {
	   cout<<"File Not open";
	   _getch();

   }
   myfile.close();
   return filename;



   
}
//------------------------------------------------------------------------//