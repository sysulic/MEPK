#ifndef __ADNF_H__
#define __ADNF_H__

#include "header.h"
// #include "define.h"
#include "enumeration.h"

using namespace std;

class KLDNF;
class PropDNF;

extern map<int, string> findAtomsByIndex;
extern map<string, int> findAtomsByName;
extern int atomNum;
extern set<int> full_atom;

class PropTerm {   // Propositional Term
public:
	vector<AtomType> literal;
	int len;

	PropTerm() {};
	PropTerm(int _len, AtomType t=UNDEFINED);
	~PropTerm();
	bool find(const string &) const;  // find if have some atom
	bool isSatisfiable() const;
	bool canEntail(const PropTerm& pt) const;
	PropTerm conjunction(const PropTerm& pt) const;
	PropTerm minimal();
	vector<PropTerm> negation() const;
	PropDNF negation_as_dnf() const;
	set<string> getTotalLiterals() const;
	bool operator==(const PropTerm&) const;
	
	void print() const;
	void show(ofstream& os) const;
};

class PropDNF {         // Propositional DNF
public:
	list<PropTerm> dnf;

	PropDNF() {};
	PropDNF(const PropDNF& pd);
	~PropDNF();
	int size() const { return dnf.size(); }
	bool isSatisfiable() const;
	bool canEntail(const PropDNF& pd) const;
	bool isEqual(const PropDNF& pd) const;
	bool isEmpty() const;
	PropDNF conjunction(const PropTerm& pd) const;
	PropDNF conjunction(const PropDNF& pd) const;
	PropDNF disjunction(const PropDNF& pd) const;
	PropDNF minimal();
	PropDNF negation() const;
	PropDNF revision(const PropDNF& pd);
	PropDNF revision_cardinality(const PropDNF& pd);
	PropDNF update(const PropDNF& pd);
	PropDNF update_cardinality(const PropDNF& pd);
	
	set<int> cover(const PropTerm& lpt, const PropTerm& rpt, PropTerm& apt);
	PropTerm diff(const PropTerm& lpt, const PropTerm& rpt);
	int minus(const PropTerm& lpt, const PropTerm& rpt1, const PropTerm& rpt2, PropTerm& res);

	void print(size_t indent=0) const;
	void show(ofstream& os) const;

	list<PropTerm> get_modals(const set<string> &) const;  // get the modals of PropDNF
    set<string> get_total_literals() const;  // for modals extracting

};

class KLTerm {       // KTerm
public:
	PropDNF PPart;
	map<string, KLDNF> KPart;
	map<string, list<KLDNF> > LPart;

	KLTerm() {};
	KLTerm(const KLTerm& klt);
	~KLTerm();
	bool isSatisfiable(const PropDNF& constraint);
	bool isSatisfiable(KLTerm& klt, const PropDNF& constraint);
	bool negEntail(KLTerm& klt, const PropDNF& constraint);
	bool strongEntail(KLTerm& klt, const PropDNF& constraint);
	bool strongEquivlent(KLTerm& klt, const PropDNF& constraint);
	bool isEmpty();
	KLTerm minimal(const PropDNF& constraint);
	KLTerm conjunction(KLTerm& klt);
	vector<KLTerm> negation(const PropDNF& constraint);
	KLTerm revision(KLTerm& klt, const PropDNF& constraint);
	KLTerm update(KLTerm& klt, const PropDNF& constraint);

	void print() const;
	void show(ofstream& os) const;
};

class KLDNF {    // ADNF
public:
	list<KLTerm> dnf;

	KLDNF() {};
	KLDNF(const KLTerm& klt);
	KLDNF(const KLDNF& kld);
	~KLDNF();
	bool isSatisfiable(const PropDNF& constraint);
	bool isSatisfiable(KLDNF& kld, const PropDNF& constraint);
	bool negEntail(KLDNF& kld, const PropDNF& constraint);
	bool strongEntail(KLDNF& kld, const PropDNF& constraint);
	bool strongEquivlent(KLDNF& kld, const PropDNF& constraint);
	KLDNF conjunction(KLDNF& kld);
	KLDNF disjunction(KLDNF& kld);
	KLDNF minimal(const PropDNF& constraint);
	KLDNF negation(const PropDNF& constraint);
	KLDNF revision(KLDNF& kld, const PropDNF& constraint);
	KLDNF update(KLDNF& kld, const PropDNF& constraint);

	void print() const;
	void show(ofstream& os) const;
};



#endif
