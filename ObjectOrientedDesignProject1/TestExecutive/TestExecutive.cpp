////////////////////////////////////////////////////////////////////////
// TestExecutive.cpp													  //	
//Ver 1.0                                                             //
// Application: Demonstration for CSE687 OOD Project 1                //
// Language:    C++ Visual Studio 2015                                //
// Platform:    MacBook Pro, Windows 10(dual boot)					  //
// Source:      Jim Fawcett, CST 4-187, Syracuse University           //
//              (315) 443-3948, jfawcett@twcny.rr.com                 //
// Author:      Suruchi Singh, Syracuse University                    //
//              ssingh11@syr.edu                                      //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* Test executive demonstrates all the functional requirements
*//*
* Maintenance:
* ------------
* Required packages: NoSqlDb,queries,XmlDocument,xmlpersist
*
* Maintenance History:
* --------------------
* ver 1.0
** - first release
*/
#pragma once
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../NoSqlDb/NoSqlDb.h"
#include"../Queries/queries.h"
#include"../xmlpersist/xmlpersist.h"
#include<fstream>
#include <iostream>


using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

using namespace std;

static void require8(Keys string1,Keys string2, queries<StrData> q1)
{
	cout << "\n\n\t******Requirement 8******" << endl;
	cout << "Giving input of query 6 to query 3:" << endl;

	Keys req81 = q1.findpattern(string2);
	for (Key key : req81)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q1.ndb1.value(key).show();
	}

	cout << "Giving input of query 4 to query 2:" << endl;
	Keys req82 = q1.findchildren(string2);
}
static void display(Keys keys1, queries<StrData> q1)
{
	
	for (Key key : keys1)
	{
		std::cout << "\n  " << key << ":";
		std::cout << q1.ndb1.value(key).show();
	}
}
int main()
{
	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";
	Element<StrData> elem1;
	Element<StrData> elem2;
	Element<StrData> elem3;
	Element<StrData> elem;
	queries<StrData> q1;

	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.desc = "elem1's desctiption";
	elem1.timeDate = elem.timedatefunc();

	//Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";
	elem2.desc = "elem2's desctiption";
	elem2.timeDate = elem.timedatefunc();
	//Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";
	elem3.desc = "elem3's desctiption";
	elem3.timeDate = elem.timedatefunc();
	vector<string> A;

	A = { elem2.name, elem3.name };
	elem1.child = q1.ndb1.insertchild(A);                  //adding a child to the existing key(elem1)
	q1.ndb1.save(elem1.name, elem1);

	vector<string> B;

	B = { elem3.name };
	elem2.child = q1.ndb1.insertchild(B);                               //adds children for elem2
	q1.ndb1.save(elem2.name, elem2);

	vector<string> C;

	C = { elem1.name };
	elem3.child = q1.ndb1.insertchild(C);								//adds children for elem3
	q1.ndb1.save(elem3.name, elem3);

	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << q1.ndb1.count() << "\n";
	//Keys keys = db.keys();
	Keys keys1 = q1.ndb1.keys();
	display(keys1,q1);

//===========================================================================================================

	Keys k = q1.ndb1.keys();
    Keys values = q1.findvalue(k);	//find value
	display(values,q1);
	Keys allchildren = q1.findchildren(k);	//find children
	Keys pattern = q1.findpattern(k);
	display(pattern, q1);
	Keys name = q1.findnamesubstring(k);
	display(name, q1);
	Keys category = q1.findcategorysubstring(k);
	display(category,q1);
	Keys data1 = q1.finddata(k);
	display(data1, q1);
	require8(data1, name, q1);
	Keys req9 = q1.Unionofqueries(pattern, pattern);
	display(req9,q1);
	std::ofstream Project1Xml;
	Project1Xml.open("../XmlFile.xml");
	persistxml<StrData> p,p1,p2;
	string s = p.toXml(q1.ndb1);
	Project1Xml << s;cout << "To xml" << s;cout << "\n \n";
	Project1Xml.close();cout << "**********FROM XML***********" << endl;
	if (!(Project1Xml.eof()))
	{
		Element<StrData> db12;
		std::ifstream ifs("../XmlFile.xml");
		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		db12 = p1.fromXml(content);

	}

	Element<StrData> elem4;
	elem4.name = "elem4";
	elem4.category = "elem4 test";
	elem4.data = "elem4's StrData";
	elem4.desc = "elem4's desctiption";
	elem4.timeDate = elem.timedatefunc();
	vector<string> D;
	D = { elem2.name };
	elem4.child = q1.ndb1.insertchild(D);  
	cout << "\nAdding an element!" << endl;
	cout << "Adding a new element" << elem4.name<< "to database :"  << endl;
	q1.ndb1.save(elem4.name, elem4);

	Keys newelem = q1.ndb1.keys();
	for (Key key : newelem)
	{
		std::cout << "\n  " << key << ":";
		std::cout << q1.ndb1.value(key).show();
	}

	cout << "******Editing existing element in the database******" <<endl;
	q1.ndb1.editkeys(elem1.name, elem1);               //edits the keys
	cout << "New values of:"<<elem1.name<<endl;
	cout << q1.ndb1.value(elem1.name).show();
	cout << "*******Deleting an element from the database!********" << endl;
	q1.ndb1.deletekeys(elem3.name);
	Keys delelem = q1.ndb1.keys();
	for (Key key : delelem)
	{
		std::cout << "\n  " << key << ":";
		std::cout << q1.ndb1.value(key).show();
	}
 	 std::ofstream Project1Xml1;
	 Project1Xml1.open("../StructXmlFile.xml");
		string s1 = p2.xmlstruct();
		Project1Xml1 << s1;
		cout << "Structure of the Project:" << s1;	cout << "\n \n";
		Project1Xml1.close();
}