////////////////////////////////////////////////////////////////////////
// xmlpersist.h														  //	
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
* This package provides functions to read and write from xml file
*//*
* Maintenance:
* ------------
* Required packages: CppProperties,XmlDocument,NoSqlDb,convert,StrHelper
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



using SPTr = shared_ptr<AbstractXmlElement>;

template<typename Data>
  class persistxml
  {
   public:
	   string toXml(NoSqlDb<Data> & ele);
	   Element<StrData>fromXml(const std::string& xml);
	   string xmlstruct();

  };
 /*
	 Shall be submitted with contents, in the form of an XML file, that describe your project's package structure and 
	 dependency relationships that can be loaded when your project is graded.
*/
  template<typename Data>
  std::string persistxml<Data>::xmlstruct()
  {std::string xml;
	  XmlDocument doc;
	  SPTr pRoot = makeTaggedElement("Project");
	  doc.docElement() = pRoot;
		  SPTr pElem = makeTaggedElement("Dependents");
		  SPTr pDepend1Elem = makeTaggedElement("Depenendence1");
		  SPTr pcpp = makeTaggedElement("NoSqlDb");
		  SPTr pcpptext = makeTextElement("Cpp Properties");
		  pcpp->addChild(pcpptext);
		  SPTr pcontext = makeTextElement("Convert");
		  pcpp->addChild(pcontext);
		  pDepend1Elem->addChild(pcpp);
		  pElem->addChild(pDepend1Elem);
		  SPTr pDepend2Elem = makeTaggedElement("Depenendence2");
		  SPTr pqe = makeTaggedElement("Queries");
		  SPTr pqetext= makeTextElement("NoSqlDb");
		  pqe->addChild(pqetext);
		  SPTr pqcontext = makeTextElement("Convert");
		  pqe->addChild(pqcontext);
		  pDepend2Elem->addChild(pqe);
		  pElem->addChild(pDepend2Elem);
		  SPTr pDepend3Elem = makeTaggedElement("Depenendence3");
		  SPTr pxmlTextElem = makeTaggedElement("xmlpersist");
		  SPTr pndbxmltext = makeTextElement("NoSqlDb");
		  pxmlTextElem->addChild(pndbxmltext);
		  SPTr pxmldtext = makeTextElement("XmlDocument");
		  pxmlTextElem->addChild(pxmldtext);
		  pDepend3Elem->addChild(pxmlTextElem);
		  pElem->addChild(pDepend3Elem);
		  pRoot->addChild(pElem);
	  xml = doc.toString();
	  return xml;
  }

  template<typename Data>
  string persistxml<Data>::toXml(NoSqlDb<Data> & ndb)
  {
	  std::string xml;
	  XmlDocument doc;
	  SPTr pRoot = makeTaggedElement("DB");
	  doc.docElement() = pRoot;
	  Keys ndbkeys = ndb.keys(); 
	  for (Key k:ndbkeys)
	  {
		  Element<Data> e = ndb.value(k);
		  SPTr pElem = makeTaggedElement("ELement");
		  SPTr pNameElem = makeTaggedElement("Name");
		  SPTr pNameTextElem = makeTextElement(e.name);
		  pNameElem->addChild(pNameTextElem);
		  pElem->addChild(pNameElem);
		  SPTr pCategoryElem = makeTaggedElement("Category");
		  SPTr pcategoryTextElem = makeTextElement(e.category);
		  pCategoryElem->addChild(pcategoryTextElem);
		  pElem->addChild(pCategoryElem);
		  SPTr pDataElem = makeTaggedElement("Data");
		  SPTr pdataTextElem = makeTextElement(e.data);
		  pDataElem->addChild(pdataTextElem);
		  pElem->addChild(pDataElem);
		  SPTr pDescElem = makeTaggedElement("Description");
		  SPTr pdescTextElem = makeTextElement(e.desc);
		  pDescElem->addChild(pdescTextElem);
		  pElem->addChild(pDescElem);
		  SPTr pTimedataeElem = makeTaggedElement("Time Date");
		  SPTr ptimedateTextElem = makeTextElement(e.timeDate);
		  pTimedataeElem->addChild(ptimedateTextElem);
		  pElem->addChild(pTimedataeElem);
		  using Children = vector<string>;
		  Children c = e.child;
		  SPTr pchildElem = makeTaggedElement("Child");
		  for (std::vector<string>::iterator it = c.begin(); it != c.end(); it++)
		  { 
			  SPTr pchildTextElem = makeTextElement(*it);
			  pchildElem->addChild(pchildTextElem);
		  }
		pElem->addChild(pchildElem);
		pRoot->addChild(pElem);
	  }
	  xml = doc.toString();
	  return xml;
  }

  template<typename Data>
  Element<StrData> persistxml<Data>::fromXml(const std::string& xml)
  {
	  try {
		  Element<Data> elem;
		  XmlDocument doc(xml, XmlDocument::str);
		  std::vector<SPTr> desc = doc.elements("DB").select();
		  for (SPTr elem : desc)
		  {
			  std::cout << "Name :" << elem->children()[0]->children()[0]->value();
			  std::cout << "Category :" << elem->children()[1]->children()[0]->value();
			  std::cout << "Data :" << elem->children()[2]->children()[0]->value();
			  std::cout << "Description : " << elem->children()[3]->children()[0]->value();
			  std::cout << "Time Date : " << elem->children()[4]->children()[0]->value();
			  std::cout << "Children :" << elem->children()[5]->children()[0]->value();
			  elem->tag();
		  }
		  return elem;
	  }
	  catch (exception e)
	  {
		  cout << e.what();

	  }
  }
