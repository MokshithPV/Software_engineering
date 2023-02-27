#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<typeinfo>
#include<tuple>
using namespace std;
class Attr {
	public:
		virtual bool operator== (const Attr & right) = 0;
		virtual bool operator< (const Attr & right) = 0;
		virtual bool operator> (const Attr & right) = 0;
		virtual bool operator<= (const Attr & right) = 0;
		virtual bool operator>= (const Attr & right) = 0;
		virtual bool operator!= (const Attr & right) = 0;
		void setval(int i);
		int getval();
};

class integerAttribute : public Attr {
	int val;
	public:
		integerAttribute(int v) { val = v; }
		integerAttribute() { }
		bool operator== (const Attr & right);
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right); 
		bool operator!= (const Attr & right);
		int getval();
		void setval(int i);
};

class floatAttribute : public Attr {
	float val;
	public:
		floatAttribute(float v) { val = v; }
		floatAttribute() { }
		bool operator== (const Attr & right);
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right);
		bool operator!= (const Attr & right);
		float getval();
		void setval(float f);
};

class stringAttribute : public Attr {
	string val;
	public:
		stringAttribute(string v) { val = v; }
		stringAttribute() { }
		bool operator== (const Attr & right);
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right);
		bool operator!= (const Attr & right);
		string getval();
		void setval(string s);
};

class boolAttribute : public Attr {
	bool val;
	public:
		boolAttribute(bool v) { val = v; }
		boolAttribute() { }
		bool operator== (const Attr & right);
		bool operator< (const Attr & right);
		bool operator> (const Attr & right);
		bool operator<= (const Attr & right);
		bool operator>= (const Attr & right);
		bool operator!= (const Attr & right);
		bool getval();
		void setval(bool b);
};

class Record {
	vector<Attr *> attrptr;
	public:
		void addAttr(Attr * a);
		int getAttrCount();
		vector<Attr *> getAttrPtr();

};

class Relation {
	int natttr, nrecs;
	vector<string> attrnames;
	vector<string> attrtypes;//attribute types
	vector<int> attrinds; //index of attribute in attrnames
	list<Record *> recs;
	public:
		Relation(int , int , vector<string> , vector<string> , vector<int> );
		void addRecord(Record * r);
		void display(int I=0);
		vector<string> getAttrNames();
		vector<string> getAttrTypes();
		int getAttrCount();
		vector<int> getAttrInds();
		void setAttrInds(vector<int> ati);
		list <Record *> getRecords();
		int getRecCount();
		void setAttrNames(vector<string> atn);
};

typedef struct DNF_{
	list<list<tuple<string , char , Attr *>>> ops;
} DNFformula;

Relation * Union(Relation * r1, Relation * r2);
Relation * difference(Relation * r1, Relation * r2);
Relation * catersianproduct(Relation * r1, Relation * r2);
Relation * rename(Relation * r1, string s1 , string s2);
Relation * projection(Relation * r1, list <string> projectattrs);
Relation * selection(Relation * r1 , DNFformula * f);
Relation * naturaljoin(Relation *r1, Relation * r2 , list<string> joinattrs);
