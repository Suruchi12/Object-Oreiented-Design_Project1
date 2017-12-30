# Key/Value Database

#### CSE 687 
#### Object Oriented Design 
#### Project 1

## Workings of the Project

Constructed a non SQL database using key-value pairs using C++. 
It can persist the database contents to an XML file such that the process is reversible. 
Along with performing functions such as addition or /and deletion of the relationships, it can edit metadata associated with the key-value pair. 
Metadata consists of a finite number of child relationships with other values, a variable to record the time and date when the value was written 
to the database along with the name, category and a text description. 
It supports the functionalities of various queries performed on the database, 
for example: finding the value associated with a key or finding the children keys when given any key as an input or finding a set of all keys matching a specified pattern. 
The queries take as their input and also return a set of keys such that the output of one query can be used as an input for the other. 
The database also supports the union of two or more queries.

## Requirements:

***Requirement 1***

Shall be implemented in C++ using the facilities of the standard C++ Libraries and Visual Studio 2015, as provided in the ECS clusters.

***Requirement 2***

Shall implement a template class providing key/value in-memory databases where each value consists of:
Metadata:
* An item name string
* A category name string
* A text description of the item
* A time-date string recording the date and time the value was written to the database.
  a finite number (possibly zero) of child relationships with other values. Each element of the child relationships collection   is the key of another item in the database. Any item holding a key in this collection is the parent of the element accessed   by the key.

An instance of the template type(1). This might be a string, a container of a set of values of the same type, or some other collection of data captured in some, perhaps custom, data structure.

***Requirement 3***

Shall support addition and deletion of key/value pairs.

***Requirement 4***

Shall support editing of values including the addition and/or deletion of relationships, editing text metadata, and replacing an existing value's instance with a new instance. Editing of keys is forbidden.

***Requirement 5***

Shall, on command, persist database contents to an XML file(2). It is intended that this process be reversible, e.g., the database can be restored or augmented(3) from an existing XML file as well as write its contents out to an XML file.

***Requirement 6***

Shall accept a positive time interval or number of writes after which the database contents are persisted. This scheduled "save" process shall continue until cancelled. By default, timed saving is turned off.

***Requirement 7***

Shall support queries for:
* The value of a specified key.
* The children of a specified key.
* The set of all keys matching a specified pattern which defaults to all keys.
* All keys that contain a specified string in their item name
* All keys that contain a specified string in their category name
* All keys that contain a specified string in their template data section when that makes sense.
* All keys that contain values written within a specified time-date interval. If only one end of the interval is provided       shall take the present as the other end of the interval.
* Each query accepts a list of keys(4) and returns a collection of keys from the list that match the query.

***Requirement 8***

Shall support making the same kinds of queries, cited in the requirement above, on the set of keys returned by an earlier query.

***Requirement 9***

Shall support forming a union of the keys from two or more earlier queries.

***Requirement 10***

Shall be submitted with contents, in the form of an XML file, that describe your project's package structure and dependency relationships that can be loaded when your project is graded.

***Requirement 11***

Shall be accompanied by a test executive that clearly demonstrates you've met all the functional requirements #2-#9, above. The XML file you supply in the previous requirement will be used as part of that demonstration. If you do not demonstrate a requirement you will not get credit for it even if you have implemented it correctly.

***Bonus***

(only counted if you have implemented all other requirements):

Support regular expression matching for the query types described above.

```
(1) This instance of the template type is the "data" that we store in the database. Metadata simply provides information about this "data".

(2) XML is easy to parse with existing tools, like the XmlDocument class provided in the Repository. So it makes a good storage mechanism for data that will be examined by other tools. It is not very space-efficient so a "production" version of this database might use some other more efficient, but more complex storage implementation.

(3) By augmented we mean that the database already contains data and the contents of the XML file are read and inserted into the database without destroying the original data.

(4) So, the first query starts with a list of all the keys in the database. Each subsequent query, if any, use the list returned by the previous query or a union of keys from previous queries.
```

## Purpose:
There is currently a lot of technical interest in "Big Data". Extreme examples are: data collection and analyses from the Large Hadron Collider, the Sloan Sky Survey, analyses of Biological Genomes, measuring weather patterns, collecting data for global climate models, and analyzing client interactions in social networks.

Conventional SQL databases are not well suited for these kinds of applications. While they have worked very well for many business applications and record keeping, they get overwhelmed by massive streams of data. Developers are turning to "noSQL" databases like MongoDB, couchDB, Redis, and Big Table to handle massive data collection and analyses.

In this project we will explore how a non SQL database can be constructed and used.

## What you need to know:
In order to successfully meet these requirements you will need to:

* Write C++ code and use basic facilities of the standard C++ libraries.

* Use the STL Containers.

* Read, Edit, and Write XML files using the XmlDocument class.
