#include"rdb.h"
Relation * Union(Relation * r1, Relation * r2) {
	list <Record *> recs1 = r1->getRecords();
	list <Record *> recs2 = r2->getRecords();
	list <Record *> recs;
	vector <int> attrinds1 = r1->getAttrInds();
	list <Record *>::iterator it1 = recs1.begin();
	list <Record *>::iterator it2 = recs2.begin();
	int j, k=r1->getAttrCount(),i;
	while (it1 != recs1.end()) {
		vector <Attr *> v1 = (*it1)->getAttrPtr();
		recs.push_back(*it1);
		it1++;
	}
	while (it2 != recs2.end()) {
		it1 = recs1.begin();
		vector <Attr *> v2 = (*it2)->getAttrPtr();
		while (it1 != recs1.end()) {
			j = 0;
			vector <Attr *> v1 = (*it1)->getAttrPtr();
			for (i = 0 ; i < k ; i++){
				if(*v2[attrinds1[i]] != *v1[i]) {
					j = 1;
					break;
				};
			}
			if (j == 0) break;
			it1++;
		}
		if (j) {
			Record * r = new Record();
			for ( i = 0; i < k; i++)
			{
				r->addAttr(v2[attrinds1[i]]);
			}
			recs.push_back(r);
		}
		it2++;
	}
	Relation * r = new Relation(k, recs.size(), r1->getAttrNames(), r1->getAttrTypes(), r1->getAttrInds());
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {
		r->addRecord(*it);
	}
	return r;
}

Relation * difference(Relation * r1, Relation * r2){
	list <Record *> recs1 = r1->getRecords();
	list <Record *> recs2 = r2->getRecords();
	list <Record *> recs;
	vector <int> attrinds1 = r1->getAttrInds();
	list <Record *>::iterator it1 = recs1.begin();
	list <Record *>::iterator it2 = recs2.begin();
	int j, k=r1->getAttrCount(),i;
	while (it1 != recs1.end()) {
		it2 = recs2.begin();
		vector <Attr *> v1 = (*it1)->getAttrPtr();
		while (it2 != recs2.end()) {
			j = 0;
			vector <Attr *> v2 = (*it2)->getAttrPtr();
			for (i = 0 ; i < k ; i++){
				if(*v1[i] != *v2[attrinds1[i]]) {
					j = 1;
					break;
				};
			}
			if (j == 0) break;
			it2++;
		}
		if (j) {
			recs.push_back(*it1);
		}
		it1++;
	}
	Relation * r = new Relation(k, recs.size(), r1->getAttrNames(), r1->getAttrTypes(), r1->getAttrInds());
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {
		r->addRecord(*it);
	}
	return r;
}

Relation * catersianproduct(Relation * r1, Relation * r2) {
	list <Record *> recs1 = r1->getRecords();
	list <Record *> recs2 = r2->getRecords();
	list <Record *> recs;
	vector <string> attrnames;
	vector <string> attrtypes;
	vector <string> attrnames1 = r1->getAttrNames();
	vector <string> attrtypes1 = r1->getAttrTypes();
	vector <string> attrnames2 = r2->getAttrNames();
	vector <string> attrtypes2 = r2->getAttrTypes();
	vector <int> attrinds1 = r1->getAttrInds();
	vector <int> attrinds2 = r2->getAttrInds();
	vector <int> attrinds;
	for (int i = 0; i < r1->getAttrCount(); i++) {
		attrnames.push_back(attrnames1[i]);
		attrtypes.push_back(attrtypes1[i]);
		attrinds.push_back(attrinds1[i]);
	}
	for (int i = 0; i < r2->getAttrCount(); i++) {
		attrnames.push_back(attrnames2[i]);
		attrtypes.push_back(attrtypes2[i]);
		attrinds.push_back(attrinds2[i]+r1->getAttrCount());
	}
	int k = r1->getAttrCount() + r2->getAttrCount();
	for (list <Record *>::iterator it1 = recs1.begin(); it1 != recs1.end(); it1++) {
		for (list <Record *>::iterator it2 = recs2.begin(); it2 != recs2.end(); it2++) {
			Record * r = new Record();
			vector <Attr *> v1 = (*it1)->getAttrPtr();
			vector <Attr *> v2 = (*it2)->getAttrPtr();
			for (int i = 0; i < r1->getAttrCount(); i++) {
				r->addAttr(v1[i]);
			}
			for (int i = 0; i < r2->getAttrCount(); i++) {
				r->addAttr(v2[i]);
			}
			recs.push_back(r);
		}
	}
	Relation * r = new Relation(k, recs.size(), attrnames, attrtypes,attrinds);
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {
		r->addRecord(*it);
	}
	return r;
}

Relation * rename(Relation * r1, string s1 , string s2) {
	vector <string> attrnames = r1->getAttrNames();
	for (int i = 0; i < r1->getAttrCount(); i++) {
		if (attrnames[i] == s1) {
			attrnames[i] = s2;
			break;
		}
	}
	r1->setAttrNames(attrnames);
	return r1;
}

Relation * projection(Relation * r1, list <string> projectattrs) {
	list <Record *> recs1 = r1->getRecords();
	list <Record *> recs;
	vector <string> attrnames;
	vector <string> attrtypes;
	vector <int> attrinds;
	vector <string> attrnames1 = r1->getAttrNames();
	vector <string> attrtypes1 = r1->getAttrTypes();
	vector <int> arb;
	int k=0;
	for (list <string>::iterator it = projectattrs.begin(); it != projectattrs.end(); it++) {
		for (int i = 0; i < r1->getAttrCount(); i++) {
			if (attrnames1[i] == *it) {
				attrnames.push_back(attrnames1[i]);
				attrtypes.push_back(attrtypes1[i]);
				attrinds.push_back(k);
				k++;
				arb.push_back(i);
				break;
			}
		}
	}
	for (list <Record *>::iterator it1 = recs1.begin(); it1 != recs1.end(); it1++) {
		Record * r = new Record();
		vector <Attr *> v1 = (*it1)->getAttrPtr();
		for (int i = 0; i < k; i++) {
			r->addAttr(v1[arb[i]]);
		}
		recs.push_back(r);
	}
	Relation * r = new Relation(k, recs.size(), attrnames, attrtypes, attrinds);
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {
		r->addRecord(*it);
	}
	return r;
}

Relation * selection(Relation * r1 , DNFformula * f) {
	list <Record *> recs1 = r1->getRecords();
	list <Record *> recs;
	vector <string> attrnames = r1->getAttrNames();
	list <Record *>::iterator it1 = recs1.begin();
	list <list < tuple <string , char , Attr *>>>::iterator it2;
	list < tuple <string , char , Attr *>>::iterator it3;
	int i,flag;
	for (;it1 != recs1.end();it1++) {
		vector <Attr *> v1 = (*it1)->getAttrPtr();
		it2 = f->ops.begin();
		for (;it2 != f->ops.end();it2++) {
			flag = 1;
			for (it3 = (*it2).begin();it3 != (*it2).end();it3++) 
			{
				flag = 1;
				string s1 = get<0>(*it3);
				for (i=0;i<r1->getAttrCount();i++) {
					if (attrnames[i] == s1) {
						break;
					}
				}
				Attr * a1 = v1[i];
				Attr * a2 = get<2>(*it3);
				char c = get<1>(*it3);
				if (c == '=') {
					if (*a1 != *a2) {
						flag = 0;
						break;
					}
				}
				else if (c == '>') {
					if (*a1 <= *a2) {
						flag = 0;
						break;
					}
				}
				else if (c == '<') {
					if (*a1 >= *a2) {
						flag = 0;
						break;
					}
				}
				else if (c == '!') {
					if (*a1 == *a2) {
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1) {
				break;
			}
		}
		if (flag == 1) {
			recs.push_back(*it1);
		}
	}
	Relation * r = new Relation(r1->getAttrCount(), recs.size(), attrnames, r1->getAttrTypes(), r1->getAttrInds());
	for (list <Record *>::iterator it = recs.begin(); it != recs.end(); it++) {
		r->addRecord(*it);
	}
	return r;
}
