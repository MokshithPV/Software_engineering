#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<typeinfo>
#include<tuple>
using namespace std;
class Attr {//abstract class for attributes
	public:
		virtual bool operator== (const Attr & right) = 0;//pure virtual functions for operators
		virtual bool operator< (const Attr & right) = 0;
		virtual bool operator> (const Attr & right) = 0;
		virtual bool operator<= (const Attr & right) = 0;
		virtual bool operator>= (const Attr & right) = 0;
		virtual bool operator!= (const Attr & right) = 0;
		void setval(int i);//set value of attribute
		int getval();//get value of attribute
};

class integerAttribute : public Attr {//class for integer attributes
	int val;//value of integer attribute
	public:
		integerAttribute(int v) { val = v; }//overloaded constructor
		integerAttribute() { }//default constructor
		bool operator== (const Attr & right);//overloaded operators for integer attributes
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right); 
		bool operator!= (const Attr & right);
		int getval();//function used to get value of integer attribute
		void setval(int i);//function used to set value of integer attribute
};

class floatAttribute : public Attr {//class for float attributes
	float val;//value of float attribute
	public:
		floatAttribute(float v) { val = v; }//overloaded constructor
		floatAttribute() { }//default constructor
		bool operator== (const Attr & right);//overloaded operators for float attributes
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right);
		bool operator!= (const Attr & right);
		float getval();//function used to get value of float attribute
		void setval(float f);//function used to set value of float attribute
};

class stringAttribute : public Attr {//class for string attributes
	string val;//value of string attribute
	public:
		stringAttribute(string v) { val = v; }//overloaded constructor
		stringAttribute() { }//default constructor
		bool operator== (const Attr & right);//overloaded operators for string attributes
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right);
		bool operator!= (const Attr & right);
		string getval();//function used to get value of string attribute
		void setval(string s);//function used to set value of string attribute
};

class boolAttribute : public Attr {//class for boolean attributes
	bool val;//value of boolean attribute
	public:
		boolAttribute(bool v) { val = v; }//overloaded constructor
		boolAttribute() { }//default constructor
		bool operator== (const Attr & right);//overloaded operators for boolean attributes
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right);
		bool operator!= (const Attr & right);
		bool getval();//function used to get value of boolean attribute
		void setval(bool b);//function used to set value of boolean attribute
};

class Record {//class for maintaining records
	vector<Attr *> attrptr;//vector of pointers to attributes
	public:
		void addAttr(Attr * a);//function to add attribute to record
		int getAttrCount();//function to get number of attributes in record
		vector<Attr *> getAttrPtr();//function to get vector of pointers to attributes

};

class Relation {//class for maintaining relations
	int natttr, nrecs;//number of attributes and number of records
	vector<string> attrnames;//vector of attribute names
	vector<string> attrtypes;//vector of attribute types
	vector<int> attrinds; //index of attribute in attrnames
	list<Record *> recs;//list of records
	public:
		Relation(int , int , vector<string> , vector<string> , vector<int> );//overloaded constructor
		void addRecord(Record * r);//function to add record to relation
		void display(int I=0);//function to display relation
		vector<string> getAttrNames();//function to get vector of attribute names
		vector<string> getAttrTypes();//function to get vector of attribute types
		int getAttrCount();//function to get number of attributes in relation
		vector<int> getAttrInds();//function to get vector of attribute indices
		void setAttrInds(vector<int> ati);//function to set vector of attribute indices
		list <Record *> getRecords();//function to get list of records
		int getRecCount();//function to get number of records in relation
		void setAttrNames(vector<string> atn);//function to set vector of attribute names
};

typedef struct DNF_{//struct for maintaining DNF formula
	list<list<tuple<string , char , Attr *>>> ops;//list of lists of tuples of attribute name, operator and attribute value
} DNFformula;
//functions for performing operations on relations
Relation * Union(Relation * r1, Relation * r2);//union of two relations
Relation * difference(Relation * r1, Relation * r2);//difference of two relations
Relation * catersianproduct(Relation * r1, Relation * r2);//catersian product of two relations
Relation * rename(Relation * r1, string s1 , string s2);//rename an attribute in a relation
Relation * projection(Relation * r1, list <string> projectattrs);//projection of a relation
Relation * selection(Relation * r1 , DNFformula * f);//selection of a relation
Relation * naturaljoin(Relation *r1, Relation * r2 , list<string> joinattrs);//natural join of two relations
