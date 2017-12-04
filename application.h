#ifndef APPLICATION_H	
#define APPLICATION_H
#include <mysql/mysql.h>
#include <string.h>
using namespace std;
class application
{
	private:
	string  username;
	MYSQL * db_conn;

	public:
	application(const string HOST, const string USER, const string PASSWORD, const string DATABASE);
	void printBeginOption();
	void afterlogin();
	void printExistingUser();
	void createUser();
	void login();
	void accountCreation(string);
	void addFriend();
	void removeFriend();
};
#endif
