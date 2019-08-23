// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<libpq-fe.h>
using namespace std;

bool ConnectToDB(PGconn *&conn, char *pghost,char* pgport, char * dbname,char* user, char* pwd){
	char* pgoptions,pgtty;
	pgoptions = NULL;
	pgtty = NULL;

	conn = PQsetdbLogin(pghost,pgport,pgoptions,(const char*)pgtty,dbname,user,pwd);

	//PGconn *conn1 = PQsetdbLogin("127.0.0.1", "5432", NULL, NULL, "postgres", "postgres", "123");

	if(PQstatus(conn) == CONNECTION_BAD){
		cout <<"Connection db"<<dbname<< "Failed!"<<endl;
		cout<<PQerrorMessage(conn)<<endl;
		return false;
	}
	else{
		cout <<"Connection db"<<dbname<< "Sucess!"<<endl;
		//cout<<PQerrorMessage(conn)<<endl;
		return true;
	}

}

bool ExecSQL(PGconn* conn,const char* SQL){
	PGresult *res = NULL;
	if(conn == NULL){
		cout<<"Conn is null"<<endl;
		return false;
	}
	else{
		res = PQexec(const_cast<PGconn *>(conn),SQL);
		if(res == NULL){
			return false;
		}
		else{
			int tuple_num = PQntuples(res);
			int field_num = PQnfields(res);
			for(int i = 0; i < tuple_num; ++i){
				for(int j = 0; j < field_num; ++j){
					cout<<PQgetvalue(res,i,j)<<" ";
				} 
			}
			PQclear(res);
			return true;
		}
	}
}

bool StopConn(PGconn* conn){
	if(conn != NULL){
		PQfinish(conn);
		conn = NULL;
	}
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{

	//PGconn *conn = PQsetdbLogin("127.0.0.1", "5432", NULL, NULL, "postgres", "postgres", "123");
	PGconn * conn = NULL;
	

	if(!ConnectToDB(conn,"127.0.0.1","5433","tutorial","postgres","123")){
		cout<<"connect ERROR"<<endl;
	}
	//const char* SQL3 = "CREATE TABLE conditions (time TIMESTAMPTZ NOT NULL,location TEXT NOT NULL,temperature DOUBLE PRECISION  NULL);";
	//if(ExecSQL(conn,SQL3))
	{
		//cout<<"create success"<<endl;
	}
	//else
	{
		//cout<<"create ERROR"<<endl;
	}
	//INSERT INTO conditions(time, location, temperature, humidity)VALUES (NOW(), 'office', 70.0, 50.0);
	
	const char* SQL3 = "INSERT INTO conditions(time, location, temperature, humidity)VALUES (NOW(), 'office', 70.0, 50.0);";
	if(ExecSQL(conn,SQL3)){
		cout<<"insert success"<<endl;
	}
	else{
		cout<<"insert ERROR"<<endl;
	}

	const char* SQL4 = "SELECT * from conditions;";
	if(ExecSQL(conn,SQL4)){
		cout<<"SELECT success"<<endl;
	}
	else{
		cout<<"SELECT ERROR"<<endl;
	}


	StopConn(conn);

	getchar();
	return 0;
}

