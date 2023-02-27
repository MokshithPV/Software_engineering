#include"rdb.h"
//defining the functions of the class Attr
void Attr::setval(int i) { }
int Attr::getval() { return 0; }
//defining the functions of the class integerAttribute
bool stringAttribute::operator== (const Attr &right) { return (val == ((stringAttribute &)right).val); }
bool stringAttribute::operator< (const Attr &right) { return (val < ((stringAttribute &)right).val); }
bool stringAttribute::operator> (const Attr &right) { return (val > ((stringAttribute &)right).val); }
bool stringAttribute::operator<= (const Attr &right) { return (val <= ((stringAttribute &)right).val); }
bool stringAttribute::operator>= (const Attr &right) { return (val >= ((stringAttribute &)right).val); }
bool stringAttribute::operator!= (const Attr &right) { return (val != ((stringAttribute &)right).val); }
string stringAttribute::getval() { return val; }
void stringAttribute::setval(string s) { val = s; }
//defining the functions of the class integerAttribute
bool integerAttribute::operator== (const Attr &right) { return (val == ((integerAttribute &)right).val); }
bool integerAttribute::operator< (const Attr &right) { return (val < ((integerAttribute &)right).val); }
bool integerAttribute::operator> (const Attr &right) { return (val > ((integerAttribute &)right).val); }
bool integerAttribute::operator<= (const Attr &right) { return (val <= ((integerAttribute &)right).val); }
bool integerAttribute::operator>= (const Attr &right) { return (val >= ((integerAttribute &)right).val); }
bool integerAttribute::operator!= (const Attr &right) { return (val != ((integerAttribute &)right).val); }
int integerAttribute::getval() { return val; }
void integerAttribute::setval(int i) { val = i; }
//defining the functions of the class floatAttribute
bool floatAttribute::operator== (const Attr &right) { return (val == ((floatAttribute &)right).val); }
bool floatAttribute::operator< (const Attr &right) { return (val < ((floatAttribute &)right).val); }
bool floatAttribute::operator> (const Attr &right) { return (val > ((floatAttribute &)right).val); }
bool floatAttribute::operator<= (const Attr &right) { return (val <= ((floatAttribute &)right).val); }
bool floatAttribute::operator>= (const Attr &right) { return (val >= ((floatAttribute &)right).val); }
bool floatAttribute::operator!= (const Attr &right) { return (val != ((floatAttribute &)right).val); }
float floatAttribute::getval() { return val; }
void floatAttribute::setval(float f) { val = f; }
//defining the functions of the class boolAttribute
bool boolAttribute::operator== (const Attr &right) { return (val == ((boolAttribute &)right).val); }
bool boolAttribute::operator< (const Attr &right) { return (val < ((boolAttribute &)right).val); }
bool boolAttribute::operator> (const Attr &right) { return (val > ((boolAttribute &)right).val); }
bool boolAttribute::operator<= (const Attr &right) { return (val <= ((boolAttribute &)right).val); }
bool boolAttribute::operator>= (const Attr &right) { return (val >= ((boolAttribute &)right).val); }
bool boolAttribute::operator!= (const Attr &right) { return (val != ((boolAttribute &)right).val); }
bool boolAttribute::getval() { return val; }
void boolAttribute::setval(bool b) { val = b; }
//defining the functions of the class Record
void Record::addAttr(Attr * a) { attrptr.push_back(a); }
int Record::getAttrCount() { return attrptr.size(); }
vector <Attr *> Record::getAttrPtr() { return attrptr; }
//defining the functions of the class Relation
Relation::Relation(int na , int nr , vector <string> atn , vector <string> att , vector <int> ati): natttr(na) , nrecs(nr) , attrnames(atn) , attrtypes(att) , attrinds(ati) {}
void Relation::addRecord(Record * r) {
	recs.push_back(r);//adding the record to the list of records
	nrecs++;//incrementing the number of records
}
void Relation:: display(int I ) {
	if (I){//if I is 1 then displays only names of attributes
		//creating strings to make the display of the table more beautiful
		cout<<" ";
		cout<<string(33*natttr-1, '-')<<endl<<"|";//printing the top line of the table
		for (int i = 0; i < natttr; i++) {
			cout << attrnames[attrinds[i]] << string(32 - attrnames[attrinds[i]].length(), ' ') << "|";//printing the names of attributes
		}
		cout << endl << " ";
		cout<<string(33*natttr-1, '-')<<endl ;//printing the bottom line of the table
		cout<<" ";
		cout<<string(33*natttr-1, '-')<<endl;
	}
	else {//if I is 1 then display the relation in the form of a table
		//creating strings to make the display of the table more beautiful
		cout<<" ";
		cout<<string(33*natttr-1, '-')<<endl<<"|";
		for (int i = 0; i < natttr; i++) {
			cout << attrnames[attrinds[i]] << string(32 - attrnames[attrinds[i]].length(), ' ') << "|";//printing the names of attributes
		}
		cout << endl << " ";
		cout<<string(33*natttr-1, '-')<<endl ;
		cout<<" ";
		cout<<string(33*natttr-1, '-')<<endl;
		for (list <Record *>::iterator it = recs.begin(); it != recs.end(); ) {//printing the records
			if(it == recs.begin()) cout << "|";
			vector <Attr *> v = (*it)->getAttrPtr();
			for (int i = 0; i < natttr; i++) {
				if (attrtypes[attrinds[i]] == "i") cout << ((integerAttribute *)v[attrinds[i]])->getval() << string(32 - to_string(((integerAttribute *)v[attrinds[i]])->getval()).length(), ' ') << "|";
				else if (attrtypes[attrinds[i]] == "f") cout << fixed << ((floatAttribute *)v[attrinds[i]])->getval() << string(32 - to_string(((floatAttribute *)v[attrinds[i]])->getval()).length(), ' ') << "|";
				else if (attrtypes[attrinds[i]] == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") cout << ((stringAttribute *)v[attrinds[i]])->getval() << string(32 - ((stringAttribute *)v[attrinds[i]])->getval().length(), ' ') << "|";
				else if (attrtypes[attrinds[i]] == "b") cout << ((boolAttribute *)v[attrinds[i]])->getval() << string(32 - to_string(((boolAttribute *)v[attrinds[i]])->getval()).length(), ' ') << "|";
			}
			cout << endl << " ";
			cout<<string(33*natttr-1, '-')<<endl;
			it++;
			if( it!= recs.end()) cout << "|" ;
		}
	}
}
vector <string> Relation:: getAttrNames() { return attrnames; }
vector <string> Relation:: getAttrTypes() { return attrtypes; }
int Relation:: getAttrCount() { return natttr; }
vector <int> Relation:: getAttrInds() { return attrinds; }
void Relation::setAttrInds(vector <int> ati) { attrinds = ati; }
list <Record *> Relation::getRecords() { return recs; }
int Relation::getRecCount() { return nrecs; }
void Relation::setAttrNames(vector <string> atn) { attrnames = atn; }

