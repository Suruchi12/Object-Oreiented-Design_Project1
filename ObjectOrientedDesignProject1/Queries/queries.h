////////////////////////////////////////////////////////////////////////
// queries.h													  //	
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
* queries.h support queries for:
	The value of a specified key.
	The children of a specified key.
	The set of all keys matching a specified pattern which defaults to all keys.
	All keys that contain a specified string in their item name	
	All keys that contain a specified string in their category name
	All keys that contain a specified string in their template data section when that makes sense.
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
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include<iterator>
#include<time.h>
#include<ctime>
#include<chrono>
#include<regex>
#include "../CppProperties/CppProperties.h"
#include"../XmlDocument/XmlDocument/XmlDocument.h"
#include"../XmlDocument/XmlElement/XmlElement.h"
#include "../Convert/Convert.h"
#include"../CppProperties/CppProperties.h"
#include "../StrHelper.h"
#include"../NoSqlDb/NoSqlDb.h"
#include<fstream>


using namespace XmlProcessing;
using namespace std;

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

using namespace std;

template<typename Data>
class queries
{
  public:
	  NoSqlDb<Data> ndb1;
	  friend class testexecutive;
	  //Queries
	  Keys findvalue(Keys k);
	  Keys findchildren(Keys k);
	  Keys findpattern(Keys k);
	  Keys findnamesubstring(Keys key);
	  Keys findcategorysubstring(Keys k);
	  Keys finddata(Keys k);
	  Keys timeinterval(Keys k);
	  Keys Unionofqueries(Keys inputList1, Keys inputList2);
};

/*	
	Query 1
    The value of a specified key.

	Takes a set of keys stored in an unordered map as an input. Uses this set of keys to find the associated
	value(i.e, the metadata of the key) by traversing the set one by one. If the 
*/

template<typename Data>
typename Keys queries<Data>::findvalue(Keys k)
{
	cout << "\nQuery1" << endl; cout << "Find value" << endl;
	Keys keys;
	std::vector<string> vec_keys;
	for (std::vector<string>::iterator keyit = k.begin(); keyit != k.end(); keyit++)
	{
		if (ndb1.store.find(*keyit) != ndb1.store.end())
		{
			Element<Data> ele = ndb1.value(*keyit);
			vec_keys.push_back(*keyit);
		}
		else
			cout << "Element not found!"<<endl;
	}
	return vec_keys;
}


/*
	Query 2
	The children of a specified key.
*/

template<typename Data>
typename Keys queries<Data>::findchildren(Keys k)
{
	cout << "\nQuery2" << endl; cout << "Fiding children" << endl;
	Keys keys; 
	std::vector<string> vec_child;
	for (std::vector<string>::iterator keyit = k.begin(); keyit != k.end(); keyit++)
	{
		if (ndb1.store.find(*keyit) != ndb1.store.end())
		{
			std::cout << "\n Printing : " << *keyit << "'s children:" << endl;
			Element<Data> ele = ndb1.value(*keyit);
			using Children = vector<string>;

			Children c = ele.child;
			for (std::vector<string>::iterator it = c.begin(); it != c.end(); it++)
			{
				cout << "child:" << *it << "\t";
				vec_child.push_back(*it);
			}
		}
		else
			cout << "Key doesn't exist!";
	}
		return vec_child;
}


/*
	Query 3
	The set of all keys matching a specified pattern which defaults to all keys.
*/
template<typename Data>
typename Keys queries<Data>::findpattern(Keys k)
{
	cout << "\nQuery3" << endl; cout << "Fiding element with pattern(where the name ends with 1)" << endl;
	Keys keys;
	for (std::vector<string>::iterator it = k.begin(); it != k.end(); it++)
	{
		if (std::regex_match(*it, std::regex("(.*)([1])")))
		{
			keys.push_back(*it);
		}
	}
	if (!keys.empty())
		return keys;
	else
	{ 
		cout << "Default to all keys! Printing all keys!" << endl;
		return k;
	}
}

/*
	Query 4
	All keys that contain a specified string in their item name
*/
template<typename Data>
typename  Keys  queries<Data>::findnamesubstring(Keys k)
{
	cout << "\nQuery4" << endl; cout << "Fiding element where the name containes 'ele'" << endl;
	Keys keys;
	for (std::vector<string>::iterator it = k.begin(); it != k.end(); it++)
	{
		Element<Data> ele = ndb1.value(*it);
		using Name = string;
		Name n = ele.name;
		std::size_t found = n.find("ele");
		if (found != std::string::npos)
			keys.push_back(*it);
	}
	return keys;
}

/*
	Query 5
	All keys that contain a specified string in their category name
*/
template<typename Data>
typename Keys queries<Data>::findcategorysubstring(Keys k)
{
	cout << "\nQuery5" << endl; cout << "Fiding element where the category containes 'cat'" << endl;
	Keys catkeys;
	for (std::vector<string>::iterator it = k.begin(); it != k.end(); it++)
	{
		Element<Data> ele = ndb1.value(*it);
		using Name = string;
		Name n = ele.category;
		std::size_t found = n.find("cat");
		if (found != std::string::npos)
			catkeys.push_back(*it);
	}
	return catkeys;
}
/*
	Query 6
	All keys that contain a specified string in their template data section when that makes sense.
*/

template<typename Data>
typename Keys queries<Data>::finddata(Keys k)
{
	cout << "\nQuery6" << endl; cout << "Fiding data where the category containes 'dat'" << endl;
	Keys datakeys;
	for (std::vector<string>::iterator it = k.begin(); it != k.end(); it++)
	{
		Element<Data> ele = ndb1.value(*it);
		using Name = string;
		Name n = ele.data;
		std::size_t found = n.find("dat");
		if (found != std::string::npos)
			datakeys.push_back(*it);
	}
	return datakeys;
}

/*
	Query 7
	All keys that contain values written within a specified time - date interval.If only one end of the interval is provided shall take the present as the other end of the interval.
*/
template<typename Data>
typename Keys queries<Data>::timeinterval(Keys k)
{
	Keys tkey;
	using TimeDate = string;
	Property<TimeDate> t1;
	double a[10];
	for (std::vector<string>::iterator it = k.begin(); it != k.end(); it++)
	{
		if (ndb1.store.find(*it) != ndb1.store.end())
		{

			Element<Data> ele = ndb1.value(*it);
			TimeDate td = ele.timeDate;
			cout << "ele.timedate:: " << td << endl;
			
			t1 = " Thu Feb  9 01:12:10 2017";

			double diff = difftime(t1,td);
			double diff1 = difftime(t1,ele.timeDate);
			if(diff==diff1)
					tkey.push_back(ele.name);
		}
	}

	return tkey;
}
/*
	Shall support forming a union of the keys from two or more earlier queries.
*/
template<typename Data>
Keys queries<Data>::Unionofqueries(Keys Query1, Keys Query2)
{
	cout << "\n\nMerging Queries!" << endl;
	Keys result_vector;
	auto i = Query1.begin();
	auto j = Query2.begin();
	
	result_vector = Query1;
	while (j != Query2.end())
	{
		auto ite = result_vector.begin();
		if (std::find(result_vector.begin(), result_vector.end(), *j) != result_vector.end())
			j++;
		else
			result_vector.push_back(*ite);
	}
	return result_vector;
}