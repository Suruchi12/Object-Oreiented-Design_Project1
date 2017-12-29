////////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database													  //	
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
* NoSqlDb.h - key/value pair in-memory database. It adds,edits,deletes and displays the unordered map.   
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
#pragma warning(disable : 4996)

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

using namespace std;
using namespace XmlProcessing;
using SPTr = shared_ptr<AbstractXmlElement>;

using StrData = std::string;

//////////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database        ///
// - in our NoSql database that is just the value in a key/value pair  ///
// - it needs to store child data, something for you to implement      ///
//////////////////////////////////////////////////////////////////////////
template<typename Data>
class Element
{
public:
  using Name = std::string;
  using Category = std::string;
  using TimeDate = std::string;
  using Children = vector<string>;
  using Description = std::string;


  Property<Name> name;            // metadata
  Property<Category> category;    // metadata
  Property<TimeDate> timeDate;    // metadata
  Property<Data> data;            // data
  Property<Data> desc;
  Property <Children> child;


  std::string show();
  std::string timedatefunc();
};

template<typename Data>
std::string Element<Data>::timedatefunc()
{
	time_t time1;
	time(&time1);
	timeDate = ctime(&time1);
	return timeDate;
}
template<typename Data>
std::string Element<Data>::show()
{	
	Children c;
	c = child;
  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  out << "\n    " << std::setw(8) << "name"     << " : " << name;
  out << "\n    " << std::setw(8) << "category" << " : " << category;
  out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
  out << "\n    " << std::setw(8) << "data" << " : " << data;
  out << "\n    " << std::setw(8) << "desc" << " : " << desc;
  out << "\n    " << std::setw(8) << "child" << " : ";
  if (c.empty())
	  out << "No Children present!" << endl;
  else
  {
	  for (std::vector<string>::iterator it = c.begin(); it != c.end(); it++)
		  out << *it << "  ";
  }
  out << "\n";
  return out.str();
}

//////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database   ///
// - stores and retrieves elements						 ////	
/////////////////////////////////////////////////////////////
template<typename Data>
class NoSqlDb
{

public:

  using Key = std::string;
  using Keys = std::vector<Key>;
  using Children = vector<string>;
  template<typename Data>
  friend class queries;
  friend class testexecutive;

  Keys keys();

  Element<Data> value(Key key);
  bool save(Key key, Element<Data> elem);
  
  Keys insertchild(Keys A);
  //void addkeys(Key key);
  bool editkeys(Key key, Element<Data> elem);
  
  void deletekeys(Key key);

  //count
  size_t count();

private:

	using Item = std::pair<Key, Element<Data>>;
	std::unordered_map<Key,Element<Data>> store; 
};




template<typename Data>									// add children to the given key
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::insertchild(Keys A)
{
	Keys temp;
	temp.clear();
	for (std::vector<string>::iterator it = A.begin(); it != A.end(); it++)
	{
		temp.push_back(*it);
	}
	  return temp;
}

template<typename Data>									//edit meta data of given key
bool NoSqlDb<Data>::editkeys(Key key, Element<Data> elem)  
{
	cout << "\nEditing an element" << endl;
	if (store.find(key) != store.end())
	{
		elem.data = "new data";
		elem.category = "new category";
		elem.desc = "new desc";
		elem.timeDate = "Tue Feb  7 01:12:10 2017";
		store[key] = elem;
		return true;
	}	
	else
		return false;
}

template<typename Data>								//delete a key
void NoSqlDb<Data>::deletekeys(Key key)
{cout << "\nDeleting an element" << endl;
	using Children = vector<string>;
	Children tempchildren;
	for (Item item : store)
	{
		Element<Data> ele;
		ele = item.second;
		tempchildren = ele.child;
		for (auto childit = tempchildren.begin(); childit != tempchildren.end(); childit++)
		{
			if (key==*childit)
			{
				tempchildren.erase(childit);
				ele.child = tempchildren;
				store[ele.name] = ele;
				break;
			}
		}
	}
	cout << "After Deleting " << key <<":"<< endl;
	store.erase(key);
	cout << "Printing the name and children of the rest of the keys" << endl;
	for (Item item : store)
	{	cout << item.first<<endl;
		Element<Data> elem = value(item.first);
		vector<string> temp = elem.child;
		if (temp.empty())
			cout << "No children present!" << endl;
		else
		{
			for (auto i = temp.begin(); i != temp.end(); i++)
				cout << "Children:   " << *i << endl;
		}
	}
}

template<typename Data>				//add keys to a vector
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
  Keys keys;
  for (Item item : store)
  {
    keys.push_back(item.first);
	
  }
  return keys;
}

template<typename Data>				// save the value  to a key
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
  if(store.find(key) != store.end())
    return false;
  store[key] = elem;
  return true;
}

template<typename Data>			//access value of a given key
Element<Data> NoSqlDb<Data>::value(Key key)
{

  if (store.find(key) != store.end())
    return store[key];
  return Element<Data>();

}

template<typename Data>
size_t NoSqlDb<Data>::count()
{
  return store.size();
}




