# NO SQL DATABASE

## CSE 687 
## Object Oriented Design 
## Project 1

Constructed a non SQL database using key-value pairs using C++. 
It can persist the database contents to an XML file such that the process is reversible. 
Along with performing functions such as addition or /and deletion of the relationships, it can edit metadata associated with the key-value pair. 
Metadata consists of a finite number of child relationships with other values, a variable to record the time and date when the value was written 
to the database along with the name, category and a text description. 
It supports the functionalities of various queries performed on the database, 
for example: finding the value associated with a key or finding the children keys when given any key as an input or finding a set of all keys matching a specified pattern. 
The queries take as their input and also return a set of keys such that the output of one query can be used as an input for the other. 
The database also supports the union of two or more queries.