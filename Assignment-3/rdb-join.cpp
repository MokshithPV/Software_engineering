#include"rdb.h"
//defining the function of naturaljoin
Relation * naturaljoin(Relation *r1, Relation * r2 , list <string> joinattrs) {//natural join of two relations
	list <Record *> recs1 = r1->getRecords();//getting the list of records of relation 1
	list <Record *> recs2 = r2->getRecords();//getting the list of records of relation 2
	list <Record *> recs;//used to store the records of the resultant relation
	vector <string> attrnames;//used to store the attribute names of the resultant relation
	vector <string> attrtypes;//used to store the attribute types of the resultant relation
	vector <int> attrinds;//used to store the attribute indices of the resultant relation
	vector <string> attrnames1 = r1->getAttrNames();//getting the attribute names of relation 1
	vector <string> attrtypes1 = r1->getAttrTypes();//getting the attribute types of relation 1
	vector <int> attrinds1 = r1->getAttrInds();//getting the attribute indices of relation 1
	vector <string> attrnames2 = r2->getAttrNames();//getting the attribute names of relation 2
	vector <string> attrtypes2 = r2->getAttrTypes();//getting the attribute types of relation 2
	vector <int> attrinds2 = r2->getAttrInds();//getting the attribute indices of relation 2
	int k = 0;
	for (int i = 0; i < r1->getAttrCount(); i++) {//adding the attributes of relation 1 to the resultant relation
		attrnames.push_back(attrnames1[i]);
		attrtypes.push_back(attrtypes1[i]);
		attrinds.push_back(k);
		k++;
	}
	for (int i = 0; i < r2->getAttrCount(); i++) {//adding the attributes of relation 2 to the resultant relation
		int flag = 0;//used to check if the attribute is a join attribute
		for (list <string>::iterator it = joinattrs.begin(); it != joinattrs.end(); it++) {//checking if the attribute is a join attribute
			if (attrnames2[i] == *it) {//if the attribute is a join attribute
				flag = 1;//setting the flag to 1
				break;
			}
		}
		if (flag == 0) {//if the attribute is not a join attribute
			attrnames.push_back(attrnames2[i]);//adding the attribute to the resultant relation
			attrtypes.push_back(attrtypes2[i]);
			attrinds.push_back(k);
			k++;
		}
	}
	for (list <Record *>::iterator it1 = recs1.begin(); it1 != recs1.end(); it1++) {//iterating over the records of relation 1
		vector <Attr *> v1 = (*it1)->getAttrPtr();//getting the attributes of the record
		for (list <Record *>::iterator it2 = recs2.begin(); it2 != recs2.end(); it2++) {//iterating over the records of relation 2
			vector <Attr *> v2 = (*it2)->getAttrPtr();//getting the attributes of the record
			int flag = 1;//used to check if the records are compatible
			for (list <string>::iterator it = joinattrs.begin(); it != joinattrs.end(); it++) {//iterating over the join attributes
				int i1, i2;//used to store the indices of the attributes
                //getting the indices of the attributes
				for (i1 = 0; i1 < r1->getAttrCount(); i1++) {
					if (attrnames1[i1] == *it) {
						break;
					}
				}
				for (i2 = 0; i2 < r2->getAttrCount(); i2++) {
					if (attrnames2[i2] == *it) {
						break;
					}
				}
				if (*v1[i1] != *v2[i2]) {//if the attributes are not equal
					flag = 0;
					break;
				}
			}
			if (flag == 1) {//if the records are compatible
				Record * r = new Record();//creating a new record
				for (int i = 0; i < r1->getAttrCount(); i++) {//adding the attributes of the record to the resultant relation
					r->addAttr(v1[i]);
				}
				for (int i = 0; i < r2->getAttrCount(); i++) {//adding the attributes of the record to the resultant relation
					int flag = 0;
					for (list <string>::iterator it = joinattrs.begin(); it != joinattrs.end(); it++) {
						if (attrnames2[i] == *it) {
							flag = 1;
							break;
						}
					}
					if (flag == 0) {
						r->addAttr(v2[i]);
					}
				}
				recs.push_back(r);//adding the record to the resultant relation
			}
		}
	}
	Relation * r = new Relation(attrnames.size(), recs.size(), attrnames, attrtypes, attrinds);//creating a new relation
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {//adding the records to the resultant relation
		r->addRecord(*it);//adding the record to the resultant relation
	}
	return r;//returning the resultant relation
}
