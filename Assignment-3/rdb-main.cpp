#include"rdb.h"
int main()
{
	int n;
	vector <Relation *> rels;
	vector <string> atn;
	vector <string> att;
	cout << "Welcome to the database management system.\n";
	cout << "Select the operation you want to perform:\n";
	cout << "1. Create a table.\n";
	cout << "2. Delete an existing table with all data in it.\n";
	cout << "3. Insert a record into a table.\n";
	cout << "4. Display a table.\n";
	cout << "5. Create a table from existing tables using the above developed operations.\n";
	cout << "6. Exit.\n";
	cin >> n;
	while (n != 6) {
		if (n == 1) {
			int natttr = 1, nrecs;
			vector <string> attrnames;
			vector <string> attrtypes;//attribute types
			vector <int> attrinds; //index of attribute in attrnames
			cout << "Enter the number of attributes: \n";
			cin >> natttr;
			if (natttr <= 0) {
				cout << "Invalid number of attributes. Enter again.\n";
				continue;
			}
			else{
				nrecs = 0;
				for (int i = 0; i < natttr; i++) {
					string s;
					cout << "Enter the name of attribute " << i + 1 << ": \n";
					cin >> s;
					attrnames.push_back(s);
					cout << "Enter the type of attribute " << i + 1 << ": \n";
					cout << "i for integer, f for float, s for string, b for boolean\n";
					cin >> s;
					if(s == "i") attrtypes.push_back("i");
					else if(s == "f") attrtypes.push_back("f");
					else if(s == "s") attrtypes.push_back("NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE");
					else if(s == "b") attrtypes.push_back("b");
					else {
						cout<<"Invalid type. Enter again.\n";
						attrnames.pop_back();
						i--;
					}
				}
				cout << "Did you enter the attributes in the order you want them to be displayed? (y/n)\n";
				char c;
				cin >> c;
				if (c == 'n') {
					for (int i = 0; i < natttr; i++) {
						cout << attrnames[i] << "-"<< i << endl;
					}
					cout<<"Enter the indices of attributes in the order you want them to be displayed.\n";
					int j;
					for (int i = 0; i < natttr; i++) {
						cin >> j;
						attrinds.push_back(j);
					}
				}
				else {
					for (int i = 0; i < natttr; i++) {
						attrinds.push_back(i);
					}
				}
				Relation * r = new Relation(natttr, nrecs, attrnames, attrtypes, attrinds);
				rels.push_back(r);
				cout << "Table created.\n";
			}
		}
		else if (n == 2) {
			if(rels.size() == 0) {
				cout<<"No tables exist.\n";
			}
			else{
				for (int i = 0; i < rels.size(); i++) {
					cout << "Table with id " << i << ": " << endl;
					rels[i]->display();
				}
				cout << "Enter the id of the table you want to delete.\n";
				int id;
				cin >> id;
				if (id >= rels.size()) {
					cout << "Invalid id.\n";
					continue;
				}
				vector<Relation *>::iterator it = rels.begin();
				advance(it, id);
				rels.erase(it);
				cout << "Table deleted.\n";
			}
			//delete table with id id
		}
		else if (n == 3) {
			if(rels.size() == 0) {
				cout<<"No tables exist.\n";
			}
			else{
				int nat;
				for (int i = 0; i < rels.size(); i++) {
					cout << "Table with id " << i << ": " << endl;
					rels[i]->display();
				}
				cout << "Enter the id of the table you want to insert a record into.\n";
				int id;
				cin >> id;
				if (id >= rels.size()) {
					cout << "Invalid id.\n";
					continue;
				}
				vector<Relation *>::iterator it = rels.begin();
				it = it + id;
				atn = (*it)->getAttrNames();
				att = (*it)->getAttrTypes();
				nat = (*it)->getAttrCount();
				Record *r = new Record();
				for (int i = 0; i < nat; i++) {
					cout << "Enter the value of attribute " << "'" << atn[i] << "'" << ": \n";
					if (att[i] == "i") {
						cout << "integer\n";
						int j;
						cin >> j;
						integerAttribute *in = new integerAttribute(j) ;
						r->addAttr(&(*in));
					}
					else if (att[i] == "f") {
						cout << "float\n";
						float j;
						cin >> j;
						floatAttribute *f = new floatAttribute(j);
						r->addAttr(&(*f));
					}
					else if (att[i] == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
						cout << "string\n";
						string j;
						cin >> j;
						stringAttribute *s = new stringAttribute(j);
						r->addAttr(&(*s));
					}
					else if (att[i] == "b") {
						cout << "boolean\n";
						bool j;
						cin >> j;
						boolAttribute *b = new boolAttribute(j);
						r->addAttr(&(*b));
					}
				}
				(*it)->addRecord(r);
				cout << "Record inserted.\n";
			}
			//insert record into table with id id
		}
		else if (n == 4) {
			if(rels.size() == 0) {
				cout<<"No tables exist.\n";
			}
			else{
				int nat;
				for (int i = 0; i < rels.size(); i++) {
					cout << "Table with id " << i << ": " << endl;
					rels[i]->display(1);
				}
				cout << "Enter the id of the table you want to disply.\n";
				int id;
				cin >> id;
				if (id >= rels.size()) {
					cout << "Invalid id.\n";
					continue;
				}
				vector<Relation *>::iterator it = rels.begin();
				it = it + id;
				(*it)->display();
			}
			//display table with name s
		}
		else if (n == 5) {
			cout << "Select the method you want to use to create a table:\n";
			cout << "1. Union: All records of both R1 and R2.\n";
			cout << "2. Difference: Records in R1 but not in R2.\n";
			cout << "3. Cartesian Product: All possible pairs of records from R1 and R2.\n";
			cout << "4. Projection: New relation with a subset of columns from R1.\n";
			cout << "5. Selection: New relation with a subset of records matching a boolean expression in the attribute values in disjunctive normal form.\n";
			cout << "6. Rename: rename an attribute in schema.\n";
			cout << "7. Natural join: join two relations on common attributes.\n";
			cout << "8. Exit.\n";
			int m;
			cin >> m;
			if (m == 1) {
				if(rels.size() == 0) {
					cout<<"No tables exist.\n";
				}
				else{
					int nat;
					for (int i = 0; i < rels.size(); i++) {
						cout << "Table with id " << i << ": " << endl;
						rels[i]->display();
					}
					cout << "Enter the id of the first table you want to perform union on.\n";
					int id1;
					cin >> id1;
					if (id1 >= rels.size() || id1 < 0) {
						cout << "Invalid id.\n";
						continue;
					}
					cout << "Enter the id of the second table you want to perform union on.\n";
					int id2;
					cin >> id2;
					if (id2 >= rels.size() || id2 < 0) {
						cout << "Invalid id.\n";
						continue;
					}
					vector<Relation *>::iterator it1 = rels.begin();
					it1 = it1 + id1;
					vector<Relation *>::iterator it2 = rels.begin();
					it2 = it2 + id2;
					vector <int> stattrin1 = (*it1)->getAttrInds();
					vector <int> atrin1;
					int j = 1,z;
					vector <string> attrn1 = (*it1)->getAttrNames();
					vector <string> attrt1 = (*it1)->getAttrTypes();
					vector <string> attrn2 = (*it2)->getAttrNames();
					vector <string> attrt2 = (*it2)->getAttrTypes();
					if (attrn1.size() != attrn2.size()) {
						cout << "The two tables have different number of attributes.\n";
					}
					else {
						for (int i = 0; i < attrn1.size(); i++) {
							z = 0;
							for (int k = 0; k < attrn2.size(); k++) {
								if (attrn1[i] == attrn2[k]) {
									z = 1;
									if (attrt1[i] != attrt2[k]) {
										cout << "The two tables have different attributes.\n";
										j = 0;
										break;
									}
									else {
										atrin1.push_back(k);
										j = 1;
										break;
									}
								}
							}
							if (z == 0) {
								cout << "The two tables have different attributes.\n";
								j = 0;
								break;
							}
							if (j == 0) {
								break;
							}
						}
						if (j == 1) {

							(*it1)->setAttrInds(atrin1);
							Relation * r = Union(*it1, *it2);
							rels.push_back(r);
							cout << "Table created.\n";
							cout << "Do you want to take a look at the table? (y/n)\n";
							char c;
							cin >> c;
							if (c == 'y') {
								r->display();
							}
						}
					}
				}
			}
			if (m == 2) {
				if(rels.size() == 0) {
					cout<<"No tables exist.\n";
				}
				else{
					int nat;
					for (int i = 0; i < rels.size(); i++) {
						cout << "Table with id " << i << ": " << endl;
						rels[i]->display();
					}
					cout << "Enter the id of the first table you want to perform difference on.\n";
					int id1;
					cin >> id1;
					if (id1 >= rels.size() || id1<0) {
						cout << "Invalid id.\n";
						continue;
					}
					cout << "Enter the id of the second table you want to perform difference on.\n";
					int id2;
					cin >> id2;
					if (id2 >= rels.size() || id2<0) {
						cout << "Invalid id.\n";
						continue;
					}
					vector<Relation *>::iterator it1 = rels.begin();
					it1 = it1 + id1;
					vector<Relation *>::iterator it2 = rels.begin();
					it2 = it2 + id2;
					vector <int> stattrin1 = (*it1)->getAttrInds();
					vector <int> atrin1;
					int j = 1,z;
					vector <string> attrn1 = (*it1)->getAttrNames();
					vector <string> attrt1 = (*it1)->getAttrTypes();
					vector <string> attrn2 = (*it2)->getAttrNames();
					vector <string> attrt2 = (*it2)->getAttrTypes();
					if (attrn1.size() != attrn2.size()) {
						cout << "The two tables have different number of attributes.\n";
					}
					else {
						for (int i = 0; i < attrn1.size(); i++) {
							z = 0;
							for (int k = 0; k < attrn2.size(); k++) {
								if (attrn1[i] == attrn2[k]) {
									z = 1;
									if (attrt1[i] != attrt2[k]) {
										cout << "The two tables have different attributes.\n";
										j = 0;
										break;
									}
									else {
										atrin1.push_back(k);
										j = 1;
										break;
									}
								}
							}
							if (z == 0) {
								cout << "The two tables have different attributes.\n";
								j = 0;
								break;
							}
							if (j == 0) {
								break;
							}
						}
						if (j == 1) {
							(*it1)->setAttrInds(atrin1);
							Relation * r = difference(*it1, *it2);
							rels.push_back(r);
							cout << "Table created.\n";
							cout << "Do you want to take a look at the table? (y/n)\n";
							char c;
							cin >> c;
							if (c == 'y') {
								r->display();
							}
						}
					}
				}
			}
			if (m == 3) {
				if(rels.size() == 0) {
					cout<<"No tables exist.\n";
				}
				else{
					int nat;
					for (int i = 0; i < rels.size(); i++) {
						cout << "Table with id " << i << ": " << endl;
						rels[i]->display();
					}
					cout << "Enter the id of the first table you want to perform cartesian product on.\n";
					int id1;
					cin >> id1;
					if (id1 >= rels.size() || id1<0) {
						cout << "Invalid id.\n";
						continue;
					}
					cout << "Enter the id of the second table you want to perform cartesian product on.\n";
					int id2;
					cin >> id2;
					if (id2 >= rels.size() || id2<0) {
						cout << "Invalid id.\n";
						continue;
					}
					vector<Relation *>::iterator it1 = rels.begin();
					it1 = it1 + id1;
					vector<Relation *>::iterator it2 = rels.begin();
					it2 = it2 + id2;
					vector <int> stattrin1 = (*it1)->getAttrInds();
					vector <int> atrin1;
					int j = 1,z;
					vector <string> attrn1 = (*it1)->getAttrNames();
					vector <string> attrt1 = (*it1)->getAttrTypes();
					vector <string> attrn2 = (*it2)->getAttrNames();
					vector <string> attrt2 = (*it2)->getAttrTypes();
					for (int i = 0; i < attrn1.size(); i++) {
						z = 1;
						for (int k = 0; k < attrn2.size(); k++) {
							if (attrn1[i] == attrn2[k])
								if (attrt1[i] == attrt2[k]) {
									cout << "The two tables have same attributes.\n";
									z = 0;
									j = 0;
									break;
								}
							}
						if (z == 0) {
							break;
						}
						if (j == 0) {
							break;
						}
					}
					if (j == 1 && (*it1)->getRecCount() != 0 && (*it2)->getRecCount() != 0) {
						Relation * r = catersianproduct(*it1, *it2); 
						rels.push_back(r);
						cout << "Table created.\n";
						cout << "Do you want to take a look at the table? (y/n)\n";
						char c;
						cin >> c;
						if (c == 'y') {
							r->display();
						}
					}
					else {
						cout <<"cartesian product cannot be performed on table with 0 records.\n";
					}
				}
			}
			if (m == 4) {
				if (rels.size() == 0) {
					cout << "No tables exist.\n";
				}
				else{
					int nat;
					for (int i = 0; i < rels.size(); i++) {
						cout << "Table with id " << i << ": " << endl;
						rels[i]->display();
					}
					cout << "Enter the id of the table you want to perform projection on.\n";
					int id1;
					cin >> id1;
					if (id1 >= rels.size() || id1 < 0) {
						cout << "Invalid id.\n";
						continue;
					}
					vector<Relation *>::iterator it1 = rels.begin();
					it1 = it1 + id1;
					list <string> attrnp;
					vector <string> attrn = (*it1)->getAttrNames();
					(*it1)->display(1);
					cout << "Enter the number of attributes you want to project on.\n";
					cin >> nat;
					cout << "Enter the names of the attributes you want to project on.\n";
					vector<string>::iterator it;
					for (int i = 0; i < nat; i++) {
						string s;
						cout << "Enter attribute name " << i + 1 << ": ";
						cin >> s;
						for (it = attrn.begin(); it != attrn.end(); it++) {
							if (s == *it) {
								attrnp.push_back(s);
								break;
							}
						}
						if (it == attrn.end()) {
							cout << "Invalid attribute name.\n";
							i--;
						}
					}
					Relation * r = projection(*it1, attrnp);
					rels.push_back(r);
					cout << "Table created.\n";
					cout << "Do you want to take a look at the table? (y/n)\n";
					char c;
					cin >> c;
					if (c == 'y') {
						r->display();
					}
				}
			}
			if (m == 5) {
				if (rels.size() == 0) {
					cout << "No tables exist.\n";
				}
				else {
					int nat;
					for (int i = 0; i < rels.size(); i++) {
						cout << "Table with id " << i << ": " << endl;
						rels[i]->display();
					}
					cout << "Enter the id of the table you want to perform selection on.\n";
					int id1;
					cin >> id1;
					if (id1 >= rels.size() || id1 < 0) {
						cout << "Invalid id.\n";
						continue;
					}
					vector<Relation *>::iterator it1 = rels.begin();
					it1 = it1 + id1;
					cout << "Enter number of clauses you want to apply.\n";
					int z;
					cin >> z;
					vector <string> attrn = (*it1)->getAttrNames();
					vector <string> attrt = (*it1)->getAttrTypes();
					DNFformula *dnf = new DNFformula();
					for (int i = 0; i < z ; i++) {
						list < tuple <string , char , Attr *> > conj;
						cout << "No of conjunctions in clause " << i + 1 << ": ";
						int y, z;
						cin >> y;
						for (int j = 0 ; j < y ; j++) {
							cout << j + 1 << "th conjunction:\n";
							cout << "Enter attribute name: ";
							string s;
							cin >> s;
							for (z = 0; z < attrn.size() ; z++) {
								if (s == attrn[z]) {
									break;
								}
							}
							if (z == attrn.size()) {
								cout << "Invalid attribute name.\n";
								j--;
								continue;
							}
							cout << "Enter operator: ";
							char op;
							cin >> op;
							if (op != '='  && op != '<' && op != '>' && op != '!' ) {
								cout << "Invalid operator.\n";
								j--;
								continue;
							}
							cout << "Enter value: ";
							if (attrt[z] == "i") {
								int val;
								cin >> val;
								integerAttribute * val1 = new integerAttribute(val);
								tuple < string , char , Attr * >  c(s, op, &(*val1));
								conj.push_back(c);
							}
							else if (attrt[z] == "f") {
								float val;
								cin >> val;
								floatAttribute * val1 = new floatAttribute(val);
								tuple < string , char , Attr * >  c(s, op, &(*val1));
								conj.push_back(c);
							}
							else if (attrt[z] == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
								string val;
								cin >> val;
								stringAttribute * val1 = new stringAttribute(val);
								tuple < string , char , Attr * >  c(s, op, &(*val1));
								conj.push_back(c);
							}
							else if (attrt[z] == "b") {
								bool val;
								cin >> val;
								boolAttribute * val1 = new boolAttribute(val);
								tuple < string , char , Attr * >  c(s, op, &(*val1));
								conj.push_back(c);
							}
						}
						(dnf->ops).push_back(conj);
					}
					Relation * r = selection(*it1, dnf);
					rels.push_back(r);
					cout << "Table created.\n";
					cout << "Do you want to take a look at the table? (y/n)\n";
					char c;
					cin >> c;
					if (c == 'y') {
						r->display();
					}
				}
			}
			if (m == 6) {
				if (rels.size() == 0) {
					cout << "No tables exist.\n";
				}
				else {
					int nat;
					for (int i = 0; i < rels.size(); i++) {
						cout << "Table with id " << i << ": " << endl;
						rels[i]->display();
					}
					cout << "Enter the id of the table you want to perform rename on.\n";
					int id1;
					cin >> id1;
					if (id1 >= rels.size() || id1 < 0) {
						cout << "Invalid id.\n";
						continue;
					}
					vector<Relation *>::iterator it1 = rels.begin();
					it1 = it1 + id1;
					vector <string> attrn = (*it1)->getAttrNames();
					(*it1)->display(1);
					cout << "Enter the name of the attribute you want to rename.\n";
					string s1, s2;
					cin >> s1;
					vector<string>::iterator it;
					for (it = attrn.begin(); it != attrn.end(); it++) {
						if (s1 == *it) {
							cout << "Enter the new name of the attribute.\n";
							cin >> s2;
							break;
						}
					}
					if (it == attrn.end()) {
						cout << "Invalid attribute name.\n";
						continue;
					}
					*it1 = rename(*it1, s1, s2);
					cout << "Attribute renamed.\n";
					(*it1)->display(1);
				}
			}
			if (m == 7) {
				if(rels.size() == 0) {
					cout<<"No tables exist.\n";
				}
				else{
					int nat;
					for (int i = 0; i < rels.size(); i++) {
						cout << "Table with id " << i << ": " << endl;
						rels[i]->display();
					}
					cout << "Enter the id of the first table you want to perform natural join on.\n";
					int id1;
					cin >> id1;
					if (id1 >= rels.size() || id1<0) {
						cout << "Invalid id.\n";
						continue;
					}
					cout << "Enter the id of the second table you want to perform natural join on.\n";
					int id2;
					cin >> id2;
					if (id2 >= rels.size() || id2<0) {
						cout << "Invalid id.\n";
						continue;
					}
					vector<Relation *>::iterator it1 = rels.begin();
					it1 = it1 + id1;
					vector<Relation *>::iterator it2 = rels.begin();
					it2 = it2 + id2;
					int j = 1,z;
					vector <string> attrn1 = (*it1)->getAttrNames();
					vector <string> attrt1 = (*it1)->getAttrTypes();
					vector <string> attrn2 = (*it2)->getAttrNames();
					vector <string> attrt2 = (*it2)->getAttrTypes();
					list <string> cattrn;
					for (int i = 0; i < attrn1.size(); i++) {
						for (int j = 0; j < attrn2.size(); j++) {
							if (attrn1[i] == attrn2[j] && attrt1[i] == attrt2[j]) {
								cattrn.push_back(attrn1[i]);
								break;
							}
						}
					}
					if (cattrn.size() == 0) {
						cout << "No common attributes.\n";
					}
					else {
						Relation * r = naturaljoin(*it1, *it2 , cattrn);
						rels.push_back(r);
						cout << "Table created.\n";
						cout << "Do you want to take a look at the table? (y/n)\n";
						char c;
						cin >> c;
						if (c == 'y') {
							r->display();
						}
					}
				}
			}
		}
		else {
			cout << "Invalid input. Enter again.\n";
		}
		cout << "Select the operation you want to perform:\n";
		cout << "1. Create a table.\n";
		cout << "2. Delete an existing table with all data in it.\n";
		cout << "3. Insert a record into a table.\n";
		cout << "4. Display a table.\n";
		cout << "5. Create a table from existing tables using the above developed operations.\n";
		cout << "6. Exit.\n";
		cin >> n;
	}
}
