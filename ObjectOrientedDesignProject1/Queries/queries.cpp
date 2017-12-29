////////////////////////////////////////////////////////////////////////
// queries.cpp														  //	
//Ver 1.0                                                             //
// Application: Demonstration for CSE687 OOD Project 1                //
// Language:    C++ Visual Studio 2015                                //
// Platform:    MacBook Pro, Windows 10(dual boot)					  //
// Source:      Jim Fawcett, CST 4-187, Syracuse University           //
//              (315) 443-3948, jfawcett@twcny.rr.com                 //
// Author:      Suruchi Singh, Syracuse University                    //
//              ssingh11@syr.edu                                      //
////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* queries.cpp uses functions of queries.h and implements them
*//*
* Maintenance:
* ------------
* Required packages: CppProperties,Convert,NoSqlDb,queries,XmlDocument,xmlpersist,StrHelper
*
* Maintenance History:
* --------------------
* ver 1.0
** - first release
*/
#pragma once
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../NoSqlDb/NoSqlDb.h"
#include<fstream>
#include"queries.h"
#include <iostream>
#include<fstream>

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

using namespace std;



int main()
{

	std::cout << "\n  Demonstrating NoSql Helper Code";
	std::cout << "\n =================================\n";

	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";

	//NoSqlDb<StrData> db;
	
	Element<StrData> elem1;
	Element<StrData> elem2;
	Element<StrData> elem3;
	Element<StrData> elem;

    queries<StrData> q;

	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.desc = "elem1's desctiption";
	elem1.timeDate = elem.timedatefunc();

	//Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "data";
	elem2.desc = "elem2's desctiption";
	elem2.timeDate = elem.timedatefunc();
	//Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "category";
	elem3.data = "elem3's StrData";
	elem3.desc = "elem3's desctiption";
	elem3.timeDate = elem.timedatefunc();

	vector<string> A;
	A.push_back(elem2.name);
	A.push_back(elem3.name);
	elem1.child = q.ndb1.insertchild(A);                  //adding a child to the existing key(elem1)
	q.ndb1.save(elem1.name, elem1);

	vector<string> B;

	B = { elem3.name };
	elem2.child = q.ndb1.insertchild(B);                               //adds children for elem2
	q.ndb1.save(elem2.name, elem2);

	vector<string> C;

	C = { elem1.name };
	elem3.child = q.ndb1.insertchild(C);								//adds children for elem3
	q.ndb1.save(elem3.name, elem3);
	
	//cout << "displaying the values:" << endl;
	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << q.ndb1.count() << "\n";

	Keys keys1 = q.ndb1.keys();
	for (Key key : keys1)
	{
		std::cout << "\n  " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

	
	Keys k = q.ndb1.keys();
/*
	Query 1
	The value of a specified key.
*/
	cout << "\n\t******Query 1******"<<endl;
	cout << "\n***FIND VALUE***" << endl;
	Keys values=q.findvalue(k);	//find value
	for (Key key : values)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}
/*
	Query 2
	The children of a specified key.
*/
	cout << "\n\t******Query 2******"<<endl;
	cout << "\n***FIND CHILDREN****" << endl;
	Keys allchildren = q.findchildren(k);	//find children
	
/*
	Query 3
	The set of all keys matching a specified pattern which defaults to all keys.
*/										
	cout << "\n\t******Query 3******"<<endl;
	cout << "\n The set of all keys matching a specified pattern:" << endl;
	Keys pattern = q.findpattern(k);
	for (Key key : pattern)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

/*
	Query 4
	All keys that contain a specified string in their item name
*/

	//********Query = find name********************
	cout << "\n\t******Query 4******" << endl;
	cout << "\n \n All keys that contain 'ele' in their item name:";
	Keys name = q.findnamesubstring(k);
	for (Key key : name)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

/*
	Query 5
	All keys that contain a specified string in their category name
*/
	//**********Query = find category***********
	cout << "\n\t******Query 5******" << endl;
	cout << "\n \n All keys that contain 'cat' in their category name:";
	Keys category = q.findcategorysubstring(k);
	for (Key key : category)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

/*
	Query 6
	All keys that contain a specified string in their template data section when that makes sense.
*/
	cout << "\n\t******Query 6******" << endl;
	cout << "\n \n All keys that contain a 'dat' in their data  when that makes sense.";
	Keys data1 = q.finddata(k);
	
	for (Key key : data1)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

/*
	Query 7
	All keys that contain values written within a specified time - date interval.If only one end of the interval is provided shall take the present as the other end of the interval.
*/

	//*******Query: Time Date Interval**************
	//cout << "\n\t******Query 7******" << endl;
	//cout << "\n \nAll keys that contain values written within a specified time-date interval.";
	//cout<<"If only one end of the interval is provided shall take the present as the other end of the interval.:"<<endl;
	/*Keys timeduration=q.timeinterval(k);
	for (Key key : timeduration)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}*/
	//********************************************
	
/*
	Requirement 8
    Shall support making the same kinds of queries, cited in the requirement above, on the set of keys returned by an earlier query.
*/
	cout << "\n\n\t******Requirement 8******" << endl;
	cout << "Giving input of Query 6 to Query 3:" << endl;
	
	Keys req81 = q.findpattern(data1);
	for (Key key : req81)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

	cout << "Giving input of Query 4 to Query 2:" << endl;
	Keys req82 = q.findchildren(name);


/*
	Requirement 9
	Shall support forming a union of the keys from two or more earlier queries.
	This function ensures no duplicate values are returned.
	This query can take as an input any 2 sets of keys including the output of other queries.
	The query takes the output (list of keys returned by an earlier query) of two different queries.   
*/
	cout << "\n\t******Requirement 9******" << endl;

	cout << "Union of Query 3 with Query 3"<<endl;
	Keys req9 = q.Unionofqueries(pattern, pattern);
	for (Key key : req9)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

	cout << "\nUnion of Query 1 with Query 2" << endl;

	Keys req91 = q.Unionofqueries(values,allchildren);
	for (Key key : req91)
	{
		std::cout << "\n key: " << key << ":";
		std::cout << q.ndb1.value(key).show();
	}

}
