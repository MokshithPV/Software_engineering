#include"rdb.h"
Relation * naturaljoin(Relation *r1, Relation * r2 , list <string> joinattrs) {
	list <Record *> recs1 = r1->getRecords();
	list <Record *> recs2 = r2->getRecords();
	list <Record *> recs;
	vector <string> attrnames;
	vector <string> attrtypes;
	vector <int> attrinds;
	vector <string> attrnames1 = r1->getAttrNames();
	vector <string> attrtypes1 = r1->getAttrTypes();
	vector <int> attrinds1 = r1->getAttrInds();
	vector <string> attrnames2 = r2->getAttrNames();
	vector <string> attrtypes2 = r2->getAttrTypes();
	vector <int> attrinds2 = r2->getAttrInds();
	int k = 0;
	for (int i = 0; i < r1->getAttrCount(); i++) {
		attrnames.push_back(attrnames1[i]);
		attrtypes.push_back(attrtypes1[i]);
		attrinds.push_back(k);
		k++;
	}
	for (int i = 0; i < r2->getAttrCount(); i++) {
		int flag = 0;
		for (list <string>::iterator it = joinattrs.begin(); it != joinattrs.end(); it++) {
			if (attrnames2[i] == *it) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			attrnames.push_back(attrnames2[i]);
			attrtypes.push_back(attrtypes2[i]);
			attrinds.push_back(k);
			k++;
		}
	}
	for (list <Record *>::iterator it1 = recs1.begin(); it1 != recs1.end(); it1++) {
		vector <Attr *> v1 = (*it1)->getAttrPtr();
		for (list <Record *>::iterator it2 = recs2.begin(); it2 != recs2.end(); it2++) {
			vector <Attr *> v2 = (*it2)->getAttrPtr();
			int flag = 1;
			for (list <string>::iterator it = joinattrs.begin(); it != joinattrs.end(); it++) {
				int i1, i2;
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
				if (*v1[i1] != *v2[i2]) {
					flag = 0;
					break;
				}
			}
			if (flag == 1) {
				Record * r = new Record();
				for (int i = 0; i < r1->getAttrCount(); i++) {
					r->addAttr(v1[i]);
				}
				for (int i = 0; i < r2->getAttrCount(); i++) {
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
				recs.push_back(r);
			}
		}
	}
	Relation * r = new Relation(attrnames.size(), recs.size(), attrnames, attrtypes, attrinds);
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {
		r->addRecord(*it);
	}
	return r;
}
