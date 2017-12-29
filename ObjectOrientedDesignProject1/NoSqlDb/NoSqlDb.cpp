////////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database
//Ver 1.0                                                             //
// Application: Demonstration for CSE687 OOD Project 1                //
// Language:    C++ Visual Studio 2015                                //
// Platform:    Dell Inspiron 13, Core-i7, Windows 10                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University          //
//              (315) 443-3948, jfawcett@twcny.rr.com                //
// Author:      Suruchi Singh, Syracuse University                    //
//              ssingh11@syr.edu                                      //
//////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package uses functions of NoSqlDb.h and implements them.
*//*
* Maintenance:
* ------------
* Required packages: CppProperties,XmlDocument,NoSqlDb
*
* Maintenance History:
* --------------------
* ver 1.0
** - first release
*/
#include "NoSqlDb.h"
#include <iostream>
#include<fstream>

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{
	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";
	NoSqlDb<StrData> db;
	Element<StrData> elem1;
	Element<StrData> elem2;
	Element<StrData> elem3;
	Element<StrData> elem;
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
	elem1.child = db.insertchild(A);                  //adding a child to the existing key(elem1)
	db.save(elem1.name, elem1);


	/*cout << "Displaying without edit:"<<endl;      //prints non edited(original) values
	Keys keys1 = db.keys();
	for (Key key : keys1)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	cout << "End edit"<<endl;

	*/

	/********************************************************/
	/*cout << "Editing keys" << endl;
	db.editkeys(elem1.name, elem1);   //edits the keys
	db.value(elem1.name).show();*/
	/********************************************************/
	vector<string> B;

	B = { elem3.name };
	elem2.child = db.insertchild(B);                               //adds children for elem2
	db.save(elem2.name, elem2);

	vector<string> C;

	C = { elem1.name };
	elem3.child = db.insertchild(C);								//adds children for elem3
	db.save(elem3.name, elem3);
	//cout << "displaying the values:" << endl;

	Keys k = db.keys();




	std::cout << "\n\n";


	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	//Keys keys = db.keys();
	Keys keys1 = db.keys();
	for (Key key : keys1)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	db.deletekeys(elem3.name);
}

	/*Keys keys2 = db.keys();
	for (Key key : keys2)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}*/
/*
	std::cout << "\n  Creating and saving NoSqlDb elements with int data";
	std::cout << "\n ----------------------------------------------------\n";

	NoSqlDb<intData> idb;

	Element<intData> ielem1;
	Element<intData> ielem2;
	Element<intData> ielem3;
	Element<intData> ielem4;

	ielem1.name = "elem1";
	ielem1.category = "test";
	ielem1.data = 1;

	idb.save(ielem1.name, ielem1);

	
	ielem2.name = "elem2";
	ielem2.category = "test";
	ielem2.data = 2;

	idb.save(ielem2.name, ielem2);

	
	ielem3.name = "elem3";
	ielem3.category = "test";
	ielem3.data = 3;

	idb.save(ielem3.name, ielem3);

	
	ielem4.name = "elem4";
	ielem4.category = "test";
	ielem4.data = 4;
	
	idb.save(ielem4.name, ielem4);

	std::cout << "\n  Retrieving elements from NoSqlDb<int>";
	std::cout << "\n ---------------------------------------\n";

	std::cout << "\n  size of idb = " << idb.count() << "\n";
	Keys ikeys = idb.keys();
	for (Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	}
	std::cout << "\n\n";*/

