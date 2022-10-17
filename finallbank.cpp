#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include <iostream>
#include <chrono>
#include<thread>
#include<windows.h>
#include <time.h>
using namespace std;
class password
{
    public:
    int cpin;
    int lpin;
    //string ifsc;
};
class customer:public password
{
    public:
    char cname[25];
    int cid;
    double cbalance;
    int ctype;
    //int cpin;
    void CreateNewUser();
    void DisplayAcc()const;
    void dodeposite(double x);
    void dowithdraw(double x);
    void priAll()const;
    int dyid() const;
    int dtype() const;
    int dybal()const;
    int dypin()const;
};
void customer:: CreateNewUser()
    {
        int random;
        int tbal=0;
        system("cls");
        cout<<endl<<"\t\t\t\tEnter customer name:";
        cin.ignore();
        cin.getline(cname,25);
        cout<<"\n\t\t\t\tPlease wait while your account number is being generated...";
        srand(time(0));
        for(int i=0;i<6;i++)
        {
            cout<<".";
            Sleep(1000);
        }
        cid=rand()%1000+1;
        cout<<"\n\t\t\t\tAcc No:"<<cid;
        cout<<"\n\t\t\t\tEnter you pin:";
        cin>>cpin;
        cout<<endl<<"\t\t\t\tEnter customer account type(1 for savings 2 for current):";
        cin>>ctype;
        cout<<endl<<"\t\t\t\tEnter initial balance:";
        cin>>cbalance;
        if(ctype==2&&cbalance<=0)
        {
            cout<<"\t\t\t\tMin balance in current acc should be greater than 0, enter new initial balance:";
            cin>>tbal;
            cbalance=tbal;
        }
        //cout<<endl<<"\t\t\t\tEnter customer pin:";
        //cin>>cpin;
        
        cout<<endl<<"Account number "<<cid<<" is sucessfully created\n";
    }
int customer:: dybal()const
    {
        return cbalance;
    }
int customer:: dypin()const
{
    return cpin;
}
int customer::dyid()const
    {
        return cid;
    }
int customer::dtype()const
    {
        return ctype;
    }
void customer::priAll()const
{
    cout<<cid<<setw(7)<<" "<<cname<<setw(10)<<"\t"<<"  "<<ctype<<setw(10)<<"\t"<<cbalance<<endl;
}
void customer:: DisplayAcc()const
{
    cout<<"\n\t\t\t\tAccount number:"<<cid;
    cout<<"\n\t\t\t\tName on account:"<<cname;
    cout<<"\n\t\t\t\tAccount type:"<<ctype;
    cout<<"\n\t\t\t\tAccount balance:"<<cbalance<<endl;
}
void customer::dowithdraw(double amt)
{
    cbalance-=amt;
}
void customer::dodeposite(double amt)
{
    cbalance+=amt;
}
class operations: public customer
{
    public:
    void ShowBalance(int n,int p)
    {
        operations ac;
	    bool flag=false;
	    ifstream inFile;
	    inFile.open("account.dat",ios::binary);
	    if(!inFile)
	    {
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    cout<<"\n\t\t\t\tBALANCE DETAILS\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
	    {
		    if(ac.dyid()==n)
		    {   
                if(ac.dypin()==p)
                {
			    ac.DisplayAcc();
			    flag=true;
                }
                else
                {
                    cout<<"\n\t\t\t\t\tWrong password";
                }
		    }
	    }
        inFile.close();
	    if(flag==false){
            cout<<"\n\n\t\t\tAccount number does not exist";
        }
    }
    void Pushdetails()
    {
	    operations ac;
	    ofstream outFile;
	    outFile.open("account.dat",ios::binary|ios::app);
	    ac.CreateNewUser();
	    outFile.write(reinterpret_cast<char *> (&ac), sizeof(customer));
	    outFile.close();
    }
    void Withdraw(int n,int p)
    {
        double amt;
	    bool found=false;
	    operations ac;
	    fstream File;
        File.open("account.dat", ios::binary|ios::in|ios::out);
	    if(!File)
	    {
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    while(!File.eof() && found==false)
	    {
		    File.read(reinterpret_cast<char *> (&ac), sizeof(customer));
		    if(ac.dyid()==n)
		    {
                if(ac.dypin()==p)
                {
			    ac.DisplayAcc();
				//cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.dybal()-amt;
				if(bal<0)
					cout<<"Sorry !! Insufficience balance..";
				else
					//ac.Withdraw(amt);
                    ac.dowithdraw(amt);
			    int pos=(-1)*static_cast<int>(sizeof(customer));
			    File.seekp(pos,ios::cur);
			    File.write(reinterpret_cast<char *> (&ac), sizeof(customer));
			    cout<<"\n\n\t\t\tSuccess... Record Updated Successfully";
			    found=true;
                }
                else{
                    cout<<"\n\t\t\t\tWrong password";
                }
	       }
         }
        File.close();
    	if(found==false)
		cout<<"\n\n\t\t\tOops! We Couldn't find your record";
    }
    void Deposite(int n,int p)
    {
        double amt;
	    bool found=false;
	    operations ac;
	    fstream File;
        File.open("account.dat", ios::binary|ios::in|ios::out);
	    if(!File)
    	{
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    while(!File.eof() && found==false)
	    {
		    File.read(reinterpret_cast<char *> (&ac), sizeof(customer));
		    if(ac.dyid()==n)
		    {
                if(ac.dypin()==p)
                {
			    ac.DisplayAcc();
				//cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
                ac.dodeposite(amt);
			    int pos=(-1)*static_cast<int>(sizeof(customer));
			    File.seekp(pos,ios::cur);
			    File.write(reinterpret_cast<char *> (&ac), sizeof(customer));
			    cout<<"\n\n\t\t\tSuccess... Record Updated Successfully";
			    found=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
	        }
        }
        File.close();
	    if(found==false)
		cout<<"\n\n\t\t\tOops! We Couldn't find your record";
    }
    void ncloseacc(int n,int p)
    {
	    operations ac;
        ifstream inFile;
        ofstream outFile;
        bool found=false;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        outFile.open("Temp.dat",ios::binary);
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
            if(ac.dyid()!=n)
            {
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(customer));
                found=true;
            }
        }
        inFile.close();
        outFile.close();
        if(found==false)
        cout<<"\n\n\t\t\tOops! We Couldn't find your record";
        else
        {
            remove("account.dat");
            rename("Temp.dat","account.dat");
            cout<<"\n\n\t\tRecord Deleted .."<<endl;
        }
    }
    void ndisplayrecords()
    {
	    system("cls");
        int t1;
        cout<<"\t\t\t\tEnter admin password:";
        cin>>t1;
        if(t1==123)
        {
	    operations ac;
	    ifstream inFile;
	    inFile.open("account.dat",ios::binary);
	    if(!inFile)
	    {
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    cout<<"\n\n\t\tACCOUNT HOLDERS DETAILS\n\n";
	    cout<<"--------------------------------------------------------\n";
	    cout<<"A/c no.      NAME                Type            Balance\n";
	    cout<<"--------------------------------------------------------\n";
	    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
	    {
		    ac.priAll();
	    }
    	inFile.close();
        }
        else
        {
            cout<<"\n\t\t\t\tWrong admin password";
        }
    }
};
class loancustomer:public password
{
    public:
    char lname[25];
    int lid;
    double lamount;
    int lyears;
    float lrate;
    void lCreateNewUser();
    void lDisplayAcc()const;
    void ldodeposite(double x);
    void lpriAll()const;
    int ldyid()const;
    int ldybal()const;
    int ldypin()const;
    void lemi()const;

};
int loancustomer:: ldypin()const
{
    return lpin;
}
void loancustomer::lCreateNewUser()
{
    int random;
    system("cls");
    cout<<endl<<"\t\t\t\tEnter customer name:";
    cin.ignore();
    cin.getline(lname,25);
    cout<<"\n\t\t\t\tPlease wait while your account number is being generated...";
    srand(time(0));
    for(int i=0;i<6;i++)
    {
        cout<<".";
        Sleep(1000);
    }
    lid=rand()%1000+1;
    cout<<"\n\t\t\t\tAcc No:"<<lid<<endl;
    cout<<endl<<"\t\t\t\tEnter account pin:";
    cin>>lpin;
    cout<<endl<<"\t\t\t\tEnter initial remaining amount:";
    cin>>lamount;
    //cout<<endl<<"\t\t\t\tEnter customer pin:";
    //cin>>cpin;
    cout<<endl<<"\t\t\t\tEnter loan duration in years:";
    cin>>lyears;
    cout<<endl<<"\t\t\t\tEnter loan interest rate:";
    cin>>lrate;
    cout<<endl<<"Account number "<<lid<<" is sucessfully created\n";
}
int loancustomer::ldybal()const
{
    return lamount;
}
int loancustomer::ldyid()const
{
    return lid;
}
void loancustomer::lpriAll()const
{
    cout<<lid<<setw(7)<<" "<<lname<<setw(10)<<"\t"<<"  "<<lyears<<setw(10)<<"\t"<<lamount<<endl;
}
void loancustomer::lDisplayAcc()const
{
    cout<<"\n\t\t\t\tAccount number:"<<lid;
    cout<<"\n\t\t\t\tName on account:"<<lname;
    cout<<"\n\t\t\t\tAccount loan duration:"<<lyears;
    cout<<"\n\t\t\t\tAccount loan balance amount:"<<lamount<<endl;
}
void loancustomer::lemi()const
{
    double emi=0;
    double r;
    r=lrate/(12*100);
    //cout<<"\n\t\t\t\t"<<r<<" "<<pow(1+r,lyears);
    emi=lamount * r * pow(1+r,lyears*12)/(pow(1+r,lyears*12)-1);
    cout<<"\n\t\t\t\tMonthly EMI will be RS "<<emi<<endl;
}
void loancustomer::ldodeposite(double amt)
{
    lamount-=amt;
}

class loanoperations :public loancustomer
{
    public:
   void lShowBalance(int n,int p)
   {
        loanoperations ac;
	    bool flag=false;
	    ifstream inFile;
	    inFile.open("Laccount.dat",ios::binary);
	    if(!inFile)
	    {
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    cout<<"\n\t\t\tLOAN BALANCE DETAILS\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer)))
	    {
		    if(ac.ldyid()==n)
		    {
                if(ac.ldypin()==p)
                {
			    ac.lDisplayAcc();
			    flag=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
		    }
	    }
        inFile.close();
	    if(flag==false){
            cout<<"\n\n\t\t\tLoan Account of such number does not exist";
        }
   }
   void lPushdetails()
   {
        loanoperations ac;
	    ofstream outFile;
	    outFile.open("Laccount.dat",ios::binary|ios::app);
	    ac.lCreateNewUser();
	    outFile.write(reinterpret_cast<char *> (&ac), sizeof(loancustomer));
	    outFile.close();
   }
   void lDeposite(int n,int p)
   {
        double amt;
	    bool found=false;
	    loanoperations ac;
	    fstream File;
        File.open("Laccount.dat", ios::binary|ios::in|ios::out);
	    if(!File)
    	{
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    while(!File.eof() && found==false)
	    {
		    File.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer));
		    if(ac.ldyid()==n)
		    {
                if(ac.ldypin()==p)
		        {
			    ac.lDisplayAcc();
				//cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be repay: ";
				cin>>amt;
                ac.ldodeposite(amt);
			    int pos=(-1)*static_cast<int>(sizeof(loancustomer));
			    File.seekp(pos,ios::cur);
			    File.write(reinterpret_cast<char *> (&ac), sizeof(loancustomer));
			    cout<<"\n\n\t\t\tSuccess... Record Updated Successfully";
			    found=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
	        }
        }
        File.close();
	    if(found==false)
		cout<<"\n\n\t\t\tOops! We Couldn't find your record";
   }
    void lcalcemi(int n,int p)
    {
        loanoperations ac;
	    bool flag=false;
	    ifstream inFile;
	    inFile.open("Laccount.dat",ios::binary);
	    if(!inFile)
	    {
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    cout<<"\n\t\t\tLOAN BALANCE DETAILS\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer)))
	    {
		    if(ac.ldyid()==n)
		    {
                if(ac.ldypin()==p)
		        {
			    ac.lemi();
			    flag=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
		    }
	    }
        inFile.close();
	    if(flag==false){
            cout<<"\n\n\t\t\tLoan Account of such number does not exist";
        }
	    
    }
//    void lcloseacc(int n)
//    {
//         loanoperations ac;
// 	    ifstream inFile;
// 	    ofstream outFile;
//         bool found=false;
// 	    inFile.open("Laccount.dat",ios::binary);
// 	    if(!inFile)
// 	    {
// 		    cout<<"File could not be open !! Press any Key...";
// 		    return;
// 	    }
// 	    outFile.open("LTemp.dat",ios::binary);
// 	    inFile.seekg(0,ios::beg);
// 	    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer)))
// 	    {
// 		    if(ac.ldyid()!=n)
// 		    {
// 			    outFile.write(reinterpret_cast<char *> (&ac), sizeof(loancustomer));
//                 found=true;
// 		    }
// 	    }
//         inFile.close();
// 	    outFile.close();
//         if(found==false)
//         cout<<"\n\n\t\t\tOops! We Couldn't find your loan account";
//         else
//         {
// 	    remove("Laccount.dat");
// 	    rename("LTemp.dat","Laccount.dat");
// 	    cout<<"\n\n\t\tLoan Account Deleted .."<<endl;
//         }
//    }
   void ldisplayrecords()
   {
        int t1;
        cout<<"\t\t\t\tEnter admin password:";
        cin>>t1;
        if(t1==123)
        {
        system("cls");
	    loanoperations ac;
	    ifstream inFile;
	    inFile.open("Laccount.dat",ios::binary);
	    if(!inFile)
	    {
		    cout<<"File could not be open !! Press any Key...";
		    return;
	    }
	    cout<<"\n\n\t\tACCOUNT HOLDERS DETAILS\n\n";
	    cout<<"----------------------------------------------------------------\n";
	    cout<<"A/c no.      NAME                Years             Remaining Sum\n";
	    cout<<"----------------------------------------------------------------\n";
	    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer)))
	    {
		    ac.lpriAll();
	    }
    	inFile.close();
        }
        else
        {
            cout<<"\n\t\t\t\tWrong admin password";
        }
   }
};
class menu :public operations,loanoperations
{
    public:
    void m()
    {
        system("Color 0A");
        int id;
        int ip;
        int choice_profm;
        cout<<"\t\t\t\tPress\n";
        cout<<"\t\t\t\t1--If you are a new user\n";
        cout<<"\t\t\t\t2--To check remaining balance\n";
        cout<<"\t\t\t\t3--To withdraw money in your account\n";
        cout<<"\t\t\t\t4--To deposite money from your account\n";
        cout<<"\t\t\t\t5--To display acc info\n";
        cout<<"\t\t\t\t6--To close your account\n";
        cout<<"\t\t\t\t7--To exit\n";
        cin>>choice_profm;
        if(choice_profm==1)
        {
            Pushdetails();
            m();
        }
        else if(choice_profm==2)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            ShowBalance(id,ip);
            m();
        }
        else if(choice_profm==3)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            Withdraw(id,ip);
            m();
        }
        else if(choice_profm==4)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            Deposite(id,ip);
            m();
        }
        else if(choice_profm==5)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            //cin>>id;
            ndisplayrecords();
            m();
        }
        else if(choice_profm==6)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            ncloseacc(id,ip);
            m();
        }
        else if(choice_profm==7)
        {
            cout<<"\t\t*****************Bye*******************";
            system("Color 07");
        }
        else
        {
            cout<<"\t\t\t\tInvalid choice returning to main menu........\n";
            menu();
        }
    }
    void m2()
    {
        
        int id;
        int ip;
        int lchoice_profm;
        system("Color E4");
        cout<<"\t\t\t\tPress\n";
        cout<<"\t\t\t\t1--If you want to open a new loan account\n";
        cout<<"\t\t\t\t2--To display amount of loan remaining to repay\n";
        cout<<"\t\t\t\t3--To repay loan\n";
        cout<<"\t\t\t\t4--To calculate emi on loan\n";
        cout<<"\t\t\t\t5--To display all records\n";
        cout<<"\t\t\t\t6--to exit\n";
        cin>>lchoice_profm;
        if(lchoice_profm==1)
        {
            lPushdetails();
            m2();
        }
        else if(lchoice_profm==2)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            lShowBalance(id,ip);
            m2();
        }
        else if(lchoice_profm==3)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            lDeposite(id,ip);
            m2();
        }
        else if(lchoice_profm==4)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            lcalcemi(id,ip);
            m2();
        }
        else if(lchoice_profm==5)
        {
            // cout<<"\n\n\n\t\t\t\tEnter your account number\n";
            // cin>>id;
            ldisplayrecords();
            m2();
        }
        else if(lchoice_profm==6)
        {
            system("Color 07");
            cout<<"\t\t*****************Bye*******************";
        }
        else
        {
            cout<<"\t\t\t\tInvalid choice returning to main menu........\n";
            menu();
        }
    }
     
     menu()
     {
        system("CLS");
        cout<<endl<<endl<<endl;
        cout<<"\t\t\t****************************************************************\n";
        cout<<"\t\t\t       -----------------------------------------------          \n";
        cout<<"\t\t\t          |||||| WELCOME TO THE NATIONAL BANK||||||             \n";
        cout<<"\t\t\t       -----------------------------------------------          \n";
        cout<<"\t\t\t**************                               *******************\n";
        cout<<"\t\t\t************************             ***************************\n";
        cout<<"\t\t\t****************************      ******************************\n";
        cout<<"\t\t\t****************************************************************\n";
        cout<<"\n";
        int choice_prof;
        cout<<"Press Enter- key to continue to main menu\n";
        getchar();
        cout<<"LOADING...";
        for(int i=0;i<6;i++)
        {
            cout<<".";
            Sleep(1000);
        }
        cout<<endl;
        // for(int i=0;i<20;i++)
        // {
                //delay for LOADING
        //     delay(100);
        //     cout<<i;
        // }
        cout<<"\t\t\t\tPress\n";
        cout<<"\t\t\t\t1 For savings/current account login\n";
        cout<<"\t\t\t\t2 For loan account login\n";
        cin>>choice_prof;
        if(choice_prof==1)
        {
            m();
        }
        else if(choice_prof==2)
        {
            m2();
        }
        else
        {
            cout<<"\t\t\t\tInvalid choice returning to main menu........\n";
            menu();
        }
     }
};
int main()
{
    menu();
    return 0;
}