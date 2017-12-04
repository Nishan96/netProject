#include <iostream>
#include <stdio.h>
#include <sstream>
#include "application.h"

application::application(const string HOST, const string USER, const string PASSWORD, const string DATABASE)
{
db_conn;
        db_conn = mysql_init(NULL);

        if (!db_conn)
                cout << "MySQL initialization failed! ";
        db_conn = mysql_real_connect(db_conn, HOST.c_str(), USER.c_str(), PASSWORD.c_str(), DATABASE.c_str(), 0, NULL, 0);
        if (!db_conn)
                cout << "Connection Error! ";
}

void application::printBeginOption()
{
	char sendline[255];	
	
	        cout<<"Welcome to Networkify"<<endl;
	        cout<<"Press 1 for new User"<<endl;
	        cout<<"Press 2 for old User"<<endl;
	        int resultFromBegining;
		cin >> resultFromBegining;
		if(resultFromBegining == 1)
		{
			createUser();
		}
		else if(resultFromBegining == 2)
		{
			login();
		}
		else 
		{
		cout<<"Invalid choices"<<endl;
		}

}

void application::createUser()
{
bool flag = true;
do{
	string pwd;
	cout<<"Enter Your Name"<<endl;
	cin>>username;
	cout<<"Enter your Password"<<endl;
	cin>> pwd;
	stringstream query;
	 query<< "select count(1) from user where userName = "<< '"'<<  username<<'"'<< ";";

	MYSQL_RES* rset;
	MYSQL_ROW row;	
	string authentication;
	if((mysql_query(db_conn, query.str().c_str()))==0)
	{
		 rset = mysql_use_result(db_conn);
                 row = mysql_fetch_row(rset);
		 authentication = row[0];
		 if(authentication.compare("0") == 0)	
		 {	mysql_free_result(rset);
			accountCreation(pwd);
			login();
			afterlogin();
			flag = false;
		 }
		 else
		 {	
		     cout<<"Account Already Exist"<<endl;
		     continue;
		 }
			
	}
   }while(flag== true);

}

void application:: accountCreation(string pwd)
{
    stringstream ss;
  ss << "INSERT INTO user(userName, pwd)"
      << "values ("  
        <<'"' << username<< '"'<<','
         <<'"'<< pwd << '"'<<");";
    if((mysql_query(db_conn, ss.str().c_str()))==0)
    {cout<<"Account Created Sucessfully"<<endl;}
}


void application::login()
{
 bool flag = false;
   do{
	string pwd;
	cout<<"Enter Your Name"<<endl;
	cin>>username;
	cout<<"Enter your Password"<<endl;
	cin>> pwd;
	stringstream query;
	 query<< "select * from user where userName = "<< '"'<<  username<<'"'<< ";";

	MYSQL_RES* rset;
	MYSQL_ROW row;
	string authentication;
	string returnedUsername;
	
   	if((mysql_query(db_conn, query.str().c_str()))==0)
        {
                 rset = mysql_use_result(db_conn);
                 row = mysql_fetch_row(rset);

                 authentication = row[1];
                	if(authentication.compare(pwd) == 0)
                 	{      mysql_free_result(rset);
				cout<<"login sucessfull"<<endl; 
                	  	afterlogin();
				flag=true;     
                	 }
                 	else
                 	{
                 	    cout<<"Password Did not Match"<<endl;
        	 	    continue;
	         	}
        }else
        {
		cout<<mysql_error(db_conn)<<endl;
        }
      }while(flag == true); 
}

void application::afterlogin()
{
cout<< "For adding friends press 1"<<endl;
cout<< "For removing friends press 2"<<endl;
cout<< "For printing friends name press 3"<<endl;
cout<< "For removing song press 4"<<endl;
cout<< "For  adding playlist press 5"<<endl;
cout<< "For removing playlist press 6"<<endl;
cout<< "For adding song in playlist press 7"<<endl;
cout<< "For removing song from playlist press 8"<<endl;
cout<< "For sharing a playlist 9"<<endl;
char option;
cin>>option;
switch(option){
	case '1':
		 addFriend();
		 afterlogin();
		 
	case '2':
		removeFriend();
		afterlogin();
	}


}

void application::addFriend()
{
 bool flag = false;
   do{
        string friendName;
        cout<<"Enter Your Friend Name"<<endl;
        cin>>friendName;
 	stringstream query;
        query<< "select count(1) from user where userName = "<< '"'<<  friendName<<'"'<< ";";
        MYSQL_RES* rset;
        MYSQL_ROW row;
        string authentication;
        if((mysql_query(db_conn, query.str().c_str()))==0)
        {
                 rset = mysql_use_result(db_conn);
                 row = mysql_fetch_row(rset);
                 authentication = row[0];
                 if(authentication.compare("1") == 0)
                 {
                         mysql_free_result(rset);
		   	 stringstream queryone;
			 queryone<< "select count(1) from friendhip where userName = "<< '"'<<  username<<'"'<<"and friend = " 
			 <<'"'<<friendName<<'"'<<";";
			
			 if((mysql_query(db_conn, queryone.str().c_str()))==0)
			  {
	                         rset = mysql_use_result(db_conn);
	                         row = mysql_fetch_row(rset);
	                         authentication = row[0];
				if(authentication.compare("0") == 0)		  	 
				 {
					stringstream ss;
			  		 ss << "INSERT INTO friendhip(userName, friend)"
      			  		  << "values ("
    			  		  <<'"' << username<< '"'<<','
                          		 <<'"'<< friendName << '"'<<");";
			  		 mysql_free_result(rset);                         
                          		 if((mysql_query(db_conn, ss.str().c_str()))==0)
                          		 {
						cout<<"Friend Added  Sucessfully"<<endl;
						flag = true;
					   }
			   		else
					  {
						cout<<mysql_error(db_conn)<<endl;
					 }
				}
				else
				{
					cout<<"Friend Already Exist"<<endl;
					 mysql_free_result(rset);
					continue;
				}
			   }else
				{	 mysql_free_result(rset);
					 cout<<mysql_error(db_conn)<<endl;
				}
			
                 }
                 else
                 {	 mysql_free_result(rset);
                 	cout<<"Friend name Not found"<<endl;
                 	continue;
                 }
       	}else
	{
                cout<<mysql_error(db_conn)<<endl;
        }
      }while(flag == false);

}


void application:: removeFriend()
{
bool flag = false;
do {
	string friendName;
        cout<<"Enter Your Friend Name"<<endl;
        cin>>friendName;
        stringstream query;
        query<< "select count(1) from friendhip where userName = "<< '"'<<  username<<'"'<<"and friend = "
                         <<'"'<<friendName<<'"'<<";";
        MYSQL_RES* rset;
        MYSQL_ROW row;
        string authentication;
        if((mysql_query(db_conn, query.str().c_str()))==0)
        {
		 rset = mysql_use_result(db_conn);
                 row = mysql_fetch_row(rset);
                 authentication = row[0];
                 mysql_free_result(rset);
		 if(authentication.compare("1") == 0)
		 {
			stringstream ss;
			ss<<"DELETE FROM friendhip where userName = "<< '"'<<  username<<'"'<<"and friend = "<<'"'<<friendName<<'"'<<";";
			if((mysql_query(db_conn, ss.str().c_str()))==0)
        		 {
				cout<<"Friend Removed Sucessfully"<<endl;
				flag =true;
			 }
			else
			{
				cout<<mysql_error(db_conn)<<endl;
			}
		 }else
		 {
			cout<<"Friend not found in the list"<<endl;
			continue;
		  }
	

	}else
	{
		cout<<mysql_error(db_conn)<<endl;
	}
	
	}while(flag!= true);

}
