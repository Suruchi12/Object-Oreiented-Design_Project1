#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../NoSqlDb/NoSqlDb.h"
#include<fstream>
#include"xmlpersist.h"
#include <iostream>
#include<fstream>

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{
	std::cout << "\n  Demonstrating NoSql Helper Code";
	std::cout << "\n =================================\n";

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
	A.push_back(elem2.name);
	A.push_back(elem3.name);
	elem1.child = db.insertchild(A);                  //adding a child to the existing key(elem1)
	db.save(elem1.name, elem1);

	vector<string> B;

	B = { elem3.name };
	elem2.child = db.insertchild(B);                               //adds children for elem2
	db.save(elem2.name, elem2);

	vector<string> C;

	C = { elem1.name };
	elem3.child = db.insertchild(C);								//adds children for elem3
	db.save(elem3.name, elem3);
	//cout << "displaying the values:" << endl;
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

    std::ofstream Project1Xml;
	Project1Xml.open("../XmlFile.xml");

	persistxml<StrData> p;
	string s=p.toXml(db);
	Project1Xml << s;
	cout << "To xml" << s;
	cout << "\n \n";
	Project1Xml.close();
	
	persistxml<StrData> p1;
	cout << "**********FROM XML***********" << endl;
	if (!(Project1Xml.eof()))
	{
		Element<StrData> db12;
		std::ifstream ifs("../XmlFile.xml");
		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		db12 = p1.fromXml(content);

	}

}

