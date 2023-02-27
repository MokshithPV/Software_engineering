#include"rdb.h"
//defining basic functions
Relation * Union(Relation * r1, Relation * r2) {//union of two relations
	list <Record *> recs1 = r1->getRecords();//getting records of relation 1
	list <Record *> recs2 = r2->getRecords();//getting records of relation 2
	list <Record *> recs;//list of records of union
	vector <int> attrinds1 = r1->getAttrInds();//getting attribute indices of relation 1
	list <Record *>::iterator it1 = recs1.begin();//iterator for the records of relation 1
	list <Record *>::iterator it2 = recs2.begin();//iterator for the records of relation 2
	int j, k=r1->getAttrCount(),i;
	while (it1 != recs1.end()) {//iterating through the records of relation 1
		vector <Attr *> v1 = (*it1)->getAttrPtr();//getting the attributes of the record
		recs.push_back(*it1);//adding the record to the union
		it1++;//incrementing the iterator
	}
	while (it2 != recs2.end()) {//iterating through the records of relation 2
		it1 = recs1.begin();//resetting the iterator for relation 1
		vector <Attr *> v2 = (*it2)->getAttrPtr();//getting the attributes of the record
		while (it1 != recs1.end()) {//iterating through the records of relation 1
			j = 0;//used as a flag
			vector <Attr *> v1 = (*it1)->getAttrPtr();//getting the attributes of the record
			for (i = 0 ; i < k ; i++){//iterating through the attributes of the record
				if(*v2[attrinds1[i]] != *v1[i]) {//checking if the attributes are equal
					j = 1;//setting the flag
					break;
				};
			}
			if (j == 0) break;//if the attributes are equal, break the loop
			it1++;//incrementing the iterator
		}
		if (j) {//if the attributes are not equal
			Record * r = new Record();//creating a new record
			for ( i = 0; i < k; i++)//iterating through the attributes of the record
            {
                r->addAttr(v2[attrinds1[i]]);//adding the attribute to the record
            }
			recs.push_back(r);//adding the record to the union
		}
		it2++;//incrementing the iterator
	}
	Relation * r = new Relation(k, recs.size(), r1->getAttrNames(), r1->getAttrTypes(), r1->getAttrInds());//creating a new relation
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {//iterating through the records of the union
		r->addRecord(*it);//adding the record to the relation
	}
	return r;//returning the relation
}

Relation * difference(Relation * r1, Relation * r2){//difference of two relations
	list <Record *> recs1 = r1->getRecords();//getting records of relation 1
	list <Record *> recs2 = r2->getRecords();//getting records of relation 2
	list <Record *> recs;//used to maintain list of records of difference
	vector <int> attrinds1 = r1->getAttrInds();//getting attribute indices of relation 1
	list <Record *>::iterator it1 = recs1.begin();//iterator for the records of relation 1
	list <Record *>::iterator it2 = recs2.begin();//iterator for the records of relation 2
	int j, k=r1->getAttrCount(),i;
	while (it1 != recs1.end()) {//iterating through the records of relation 1
		it2 = recs2.begin();//resetting the iterator for relation 2 after each iteration
		vector <Attr *> v1 = (*it1)->getAttrPtr();//getting the attributes of the record
		while (it2 != recs2.end()) {//iterating through the records of relation 2
			j = 0;//used as a flag
			vector <Attr *> v2 = (*it2)->getAttrPtr();//getting the attributes of the record
			for (i = 0 ; i < k ; i++){//iterating through the attributes of the record v2 and v1
				if(*v1[i] != *v2[attrinds1[i]]) {//checking if the attributes are equal
					j = 1;//setting the flag
					break;
				};
			}
			if (j == 0) break;//if the attributes are equal, break the loop
			it2++;
		}
		if (j) {//if the attributes are not equal
			recs.push_back(*it1);//adding the record to the difference
		}
		it1++;
	}
	Relation * r = new Relation(k, recs.size(), r1->getAttrNames(), r1->getAttrTypes(), r1->getAttrInds());//creating a new relation
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {//iterating through the records of the difference
		r->addRecord(*it);//adding the record to the relation
	}
	return r;//returning the relation
}

Relation * catersianproduct(Relation * r1, Relation * r2) {//catersian product of two relations
	list <Record *> recs1 = r1->getRecords();//getting records of relation 1
	list <Record *> recs2 = r2->getRecords();//getting records of relation 2
	list <Record *> recs;//used to maintain list of records of catersian product
	vector <string> attrnames;//used to maintain list of attribute names of catersian product
	vector <string> attrtypes;//used to maintain list of attribute types of catersian product
	vector <string> attrnames1 = r1->getAttrNames();//getting attribute names of relation 1
	vector <string> attrtypes1 = r1->getAttrTypes();//getting attribute types of relation 1
	vector <string> attrnames2 = r2->getAttrNames();//getting attribute names of relation 2
	vector <string> attrtypes2 = r2->getAttrTypes();//getting attribute types of relation 2
	vector <int> attrinds1 = r1->getAttrInds();//getting attribute indices of relation 1
	vector <int> attrinds2 = r2->getAttrInds();//getting attribute indices of relation 2
	vector <int> attrinds;//used to maintain list of attribute indices of catersian product
	for (int i = 0; i < r1->getAttrCount(); i++) {//iterating through the attributes of relation 1
		attrnames.push_back(attrnames1[i]);//adding the attribute name to the list
		attrtypes.push_back(attrtypes1[i]);//adding the attribute type to the list
		attrinds.push_back(attrinds1[i]);//adding the attribute index to the list
	}
	for (int i = 0; i < r2->getAttrCount(); i++) {//iterating through the attributes of relation 2
		attrnames.push_back(attrnames2[i]);//adding the attribute name to the list
		attrtypes.push_back(attrtypes2[i]);//adding the attribute type to the list
		attrinds.push_back(attrinds2[i]+r1->getAttrCount());//adding the attribute index to the list
	}
	int k = r1->getAttrCount() + r2->getAttrCount();//calculating number of attributes of the catersian product
	for (list <Record *>::iterator it1 = recs1.begin(); it1 != recs1.end(); it1++) {//iterating through the records of relation 1
		for (list <Record *>::iterator it2 = recs2.begin(); it2 != recs2.end(); it2++) {//iterating through the records of relation 2
			Record * r = new Record();//creating a new record
			vector <Attr *> v1 = (*it1)->getAttrPtr();//getting the attributes of the record of relation 1
			vector <Attr *> v2 = (*it2)->getAttrPtr();//getting the attributes of the record pf relation 2
			for (int i = 0; i < r1->getAttrCount(); i++) {//iterating through the attributes of the record
				r->addAttr(v1[i]);//adding the attribute to the record
			}
			for (int i = 0; i < r2->getAttrCount(); i++) {
				r->addAttr(v2[i]);//adding the attribute to the record
			}
			recs.push_back(r);//adding the record to the list of records of catersian product
		}
	}
	Relation * r = new Relation(k, recs.size(), attrnames, attrtypes,attrinds);//creating a new relation
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {//iterating through the records of the catersian product
		r->addRecord(*it);//adding the record to the relation
	}
	return r;//returning the relation
}

Relation * rename(Relation * r1, string s1 , string s2) {//renaming an attribute of a relation
	vector <string> attrnames = r1->getAttrNames();//getting the attribute names of the relation
	for (int i = 0; i < r1->getAttrCount(); i++) {//iterating through the attribute names
		if (attrnames[i] == s1) {//checking if the attribute name is equal to the attribute to be renamed
			attrnames[i] = s2;//renaming the attribute
			break;
		}
	}
	r1->setAttrNames(attrnames);//setting the new attribute names of the relation
	return r1;//returning the relation
}

Relation * projection(Relation * r1, list <string> projectattrs) {//projection of a relation
	list <Record *> recs1 = r1->getRecords();//getting the records of the relation
	list <Record *> recs;//used to maintain the list of records of the projection
	vector <string> attrnames;//used to maintain the list of attribute names of the projection
	vector <string> attrtypes;//used to maintain the list of attribute types of the projection
	vector <int> attrinds;//used to maintain the list of attribute indices of the projection
	vector <string> attrnames1 = r1->getAttrNames();//getting the attribute names of the relation 1
	vector <string> attrtypes1 = r1->getAttrTypes();//getting the attribute types of the relation 1
	vector <int> arb;//used to store the indices of the projectattrs in the relation 1 such that it becomes easy to access the attributes of the record 1 while comparing with relation 2
	int k=0;
	for (list <string>::iterator it = projectattrs.begin(); it != projectattrs.end(); it++) {//iterating through the attributes to be projected
		for (int i = 0; i < r1->getAttrCount(); i++) {//iterating through the attributes of the relation 1
			if (attrnames1[i] == *it) {//checking if the attribute name is equal to the attribute to be projected
				attrnames.push_back(attrnames1[i]);//adding the attribute name to the list if it is equal
				attrtypes.push_back(attrtypes1[i]);//adding the attribute type to the list if it is equal
				attrinds.push_back(k);//adding the attribute index to the list if it is equal
				k++;//incrementing the index
				arb.push_back(i);//adding the index of the attribute to the list for future use
				break;
			}
		}
	}
	for (list <Record *>::iterator it1 = recs1.begin(); it1 != recs1.end(); it1++) {//iterating through the records of relation 1
		Record * r = new Record();//creating a new record
		vector <Attr *> v1 = (*it1)->getAttrPtr();//getting the attributes of the record of relation 1
		for (int i = 0; i < k; i++) {//iterating through the attributes of the record
			r->addAttr(v1[arb[i]]);//adding the attribute to the record
		}
		recs.push_back(r);//adding the record to the list of records of projection
	}
	Relation * r = new Relation(k, recs.size(), attrnames, attrtypes, attrinds);//creating a new relation
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {//iterating through the records of the projection
		r->addRecord(*it);//adding the record to the relation
	}
	return r;//returning the relation
}

Relation * selection(Relation * r1 , DNFformula * f) {//selection of a relation
	list <Record *> recs1 = r1->getRecords();//getting the records of the relation
	list <Record *> recs;//used to maintain the list of records of the selection
	vector <string> attrnames = r1->getAttrNames();//getting the attribute names of the relation 
	list <Record *>::iterator it1 = recs1.begin();//iterator for the records of relation 
	list <list < tuple <string , char , Attr *>>>::iterator it2;//iterator for the list of tuples of the DNF formula
	list < tuple <string , char , Attr *>>::iterator it3;//iterator for the tuples of the DNF formula
	int i,flag;//used to check if the record satisfies the condition
	for (;it1 != recs1.end();it1++) {//iterating through the records of relation 
		vector <Attr *> v1 = (*it1)->getAttrPtr();//getting the attributes of the record of relation 
		it2 = f->ops.begin();//initializing the iterator for the list of tuples of the DNF formula
		for (;it2 != f->ops.end();it2++) {//iterating through the list of tuples of the DNF formula
			flag = 1;
			for (it3 = (*it2).begin();it3 != (*it2).end();it3++) //iterating through the tuples of the DNF formula
			{
				flag = 1;
				string s1 = get<0>(*it3);//getting the attribute name of the tuple
				for (i=0;i<r1->getAttrCount();i++) {//iterating through the attribute names of the relation
					if (attrnames[i] == s1) {//checking if the attribute name is equal to the attribute name of the tuple
						break;
					}
				}
				Attr * a1 = v1[i];//getting the attribute of the record
				Attr * a2 = get<2>(*it3);//getting the attribute of the tuple
				char c = get<1>(*it3);//getting the operator of the tuple
				if (c == '=') {//checking if the operator is equal to '='
					if (*a1 != *a2) {//checking if the attributes are not equal
						flag = 0;//setting the flag to 0
						break;
					}
				}
				else if (c == '>') {//checking if the operator is equal to '>'
					if (*a1 <= *a2) {//checking if the attribute of the record is less than or equal to the attribute of the tuple
						flag = 0;//setting the flag to 0
						break;
					}
				}
				else if (c == '<') {//checking if the operator is equal to '<'
					if (*a1 >= *a2) {//checking if the attribute of the record is greater than or equal to the attribute of the tuple
						flag = 0;//setting the flag to 0
						break;
					}
				}
				else if (c == '!') {//checking if the operator is equal to '!'
					if (*a1 == *a2) {//checking if the attributes are equal
						flag = 0;//setting the flag to 0
						break;
					}
				}
			}
			if (flag == 1) {//checking if the flag is equal to 1
				break;
			}
		}
		if (flag == 1) {//checking if the flag is equal to 1(if the record satisfies the condition)
			recs.push_back(*it1);//adding the record to the list of records of selection
		}
	}
	Relation * r = new Relation(r1->getAttrCount(), recs.size(), attrnames, r1->getAttrTypes(), r1->getAttrInds());//creating a new relation
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {//iterating through the records of the selection
		r->addRecord(*it);//adding the record to the relation
	}
	return r;//returning the relation
}
