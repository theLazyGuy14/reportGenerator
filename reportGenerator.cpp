/***************************
 HEADER FILES USED
****************************/
#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>
int y=8;
/***************************
 CLASS USED
****************************/
class student
{
	int rno;
	char name[50];
	int p,c,m,e,cs;
	float per;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata();
	void show_tabular();
	int retrno();
};

void student::calculate()
{
	per=(p+c+m+e+cs)/5.0;
	if(per>90)
       grade='A';
    else if(per>70)
		grade='B';
	else if(per>50)
		grade='C';
	else if(per>33)
		grade='D';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rno;
	cout<<"\n\nEnter The Name of student ";
	gets(name);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>p;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>c;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>m;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>e;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>cs;
	calculate();
}

void student::showdata()
{
	cout<<"\nRoll number of student : "<<rno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<p;		
	cout<<"\nMarks in Chemistry : "<<c;
	cout<<"\nMarks in Maths : "<<m;
	cout<<"\nMarks in English : "<<e;
	cout<<"\nMarks in Computer Science :"<<cs;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}

void student::show_tabular()
{   cout<<setprecision(1);
	gotoxy(2,::y);
	cout<<rno<<setw(6)<<" "<<name ;
	gotoxy(24,::y);
	cout<<p;
	gotoxy(28,::y);
	cout<<c;
	gotoxy(32,::y);
	cout<<m;
	gotoxy(36,::y);
	cout<<e;
	gotoxy(40,::y);
	cout<<cs;
	gotoxy(46,::y);
	cout<<per;
	gotoxy(53,::y);
	cout<<" "<<grade<<endl;
	::y++;
}

int  student::retrno()
{
	return rno;
}
void write_student();
void disp_all();
void disp_sp(int);
void modify_student(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();

void main()
{
	char ch;
	clrscr();
	intro();
	textcolor(14);
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1': result();
					  break;
			case '2': entry_menu();
					  break;
			case '3': break;	

			default : cout<<" Wrong choice ";
		}
	}while(ch!='3');
}

void write_student()
{
	student s;
	ofstream f("student.dat",ios::binary|ios::app);
	s.getdata();
	f.write((char *) &s, sizeof(s));
	f.close();
	textcolor(2+BLINK);
	cout<<"\n\n";
	cprintf("Student record Has Been Created ");
	getch();
	textcolor(14);
}

void disp_all()
{
	student s;
	ifstream f("student.dat",ios::binary);
	if(!f)
	{
		cout<<"File could not be opened !! Press any Key...";
		getch();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(f.read((char *) &s, sizeof(s)))
	{
		s.showdata();
	

		cout<<"\n\n====================================\n";
	}
	f.close();
	getch();
}

void disp_sp(int n)
{
	student s;
	ifstream f("student.dat",ios::binary);
	if(!f)
	{
		cout<<"File could not be opened !! Press any Key...";
		getch();
		return;
	}

	int flag=0;
	while(f.read((char *) &s, sizeof(s)))
	{
		if(s.retrno()==n)
		{
			 s.showdata();
			 flag=1;
		}
	}
	f.close();
	if(flag==0)
	{	textcolor(3+BLINK);
		cout<<"\n\n";
		cprintf("record not exist");
	}
	getch();
	

	textcolor(14);
}

void modify_student(int n)
{
	int found=0;
	student s;
	fstream f("student.dat",ios::binary|ios::in|ios::out);
	if(!f)
	{
		cout<<"File could not be opened !! Press any Key...";
		getch();
		return;
	}
	while(f.read((char *) &s, sizeof(s)) && found==0)
	{
		if(s.retrno()==n)
		{
			s.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			s.getdata();
				int pos=(-1)*sizeof(s);
				f.seekp(pos,ios::cur);
				f.write((char *) &s, sizeof(s));
				textcolor(5+BLINK);
				cout<<"\n\n\t";
				cprintf("Record Updated");
				found=1;
				textcolor(14);
		}
	}
	f.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";

	getch();
}

void delete_student(int n)
{
	student s;
	ifstream f("student.dat",ios::binary);
	if(!f)
	{
		cout<<"File could not be opened !! Press any Key...";
		getch();
		return;
	}
	ofstream f1("Temp.dat",ios::out);
	f.seekg(0,ios::beg);
	while(f.read((char *) &s, sizeof(s)))
	{
		if(s.retrno()!=n)
		{
			f1.write((char *) &s, sizeof(s));
		}
	}
	f1.close();
	f.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\t";
	textcolor(9+BLINK);
	cprintf(" Record Deleted ..");
	getch();
	textcolor(14);
}
void class_result()
{   textcolor(14);

	student s;
	ifstream f("student.dat",ios::binary);
	if(!f)
	{
		cout<<"File could not be opened !! Press any Key...";
		getch();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(f.read((char *) &s, sizeof(s)))
	{
		s.show_tabular();
	}
	getch();
	f.close();
}

void result()
{
	char ch;
	int rno;
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	clrscr();



16 | P a g e
	switch(ch)
	{
		case '1' :class_result(); break;
		case '2' :cout<<"\n\n\tEnter Roll Number Of Student : ";
				  cin>>rno;
				  disp_sp(rno); break;
		case '3' :break;
		default  :cout<<"Wrong choice";
	}
}

void intro()
{   textcolor(14);
	cout<<"\t\t";
	cprintf("WELCOME TO STUDENT REPORT CARD MANAGEMENT..");
	cout<<"============================================================";
	cout<<"\n\n\n\t\t ";  cprintf("CBSE CLASS 12 INVESTIGATORY PROJECT");
	cout<<"\n\n\t\t ";  cprintf(" MADE BY : C V Srivatsan");
	cout<<"\n\n\t\t ";  cprintf(" SCHOOL : Kendriya Vidyalaya Picket");
	cout<<"\n\n\t\t ";  cprintf("YEAR : 2018-19 ");
	cout<<"\n\n\t PRESS ANY KEY TO CONTINUE....";
	getch();
}

void entry_menu()
{
	char ch;
	int num;
	clrscr();
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";											
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	clrscr();
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	disp_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number ";
				cin>>num;
				disp_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number ";
				cin>>num;
				modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number ";
				cin>>num;
				delete_student(num);break;
	case '6':	break;
	default :	entry_menu();
	}
}
