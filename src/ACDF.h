#ifndef ACDF_H
#define ACDF_H


#include "define2.h"
#include <boost/dynamic_bitset.hpp>

class ACDFTerm;
class ACDF;
class ACDFList;
class PropClause;
class PropCNF;
class PropDNF;
struct EpisAction;
struct OnticAction;

extern list<string> agents;

extern map<int, string> atomsByIndex;
extern map<string, int> atomsByName;


class PropTerm {
public:
    boost::dynamic_bitset<> literals;  //一个原子对应两位，那两位分别表示该原子构成的正文字和负文字
    size_t length;
public:
    PropTerm(size_t len) { literals.resize(length = len); }
    PropTerm() {}
    ~PropTerm() {}
    bool find(const string &) const;  // find if have some atom
    bool consistent() const; //判断该命题项是否一致
    bool entails(const PropTerm &) const; //判断该命题项能够推出另外一个命题项
    bool equals(const PropTerm &);  //判断两个命题项是否等价
    bool empty() const;
    PropTerm group(const PropTerm &) const; //merge two PropTerms
    PropClause negation() const; //this function is used to judge ontic progression
    PropTerm& minimal(); //化简命题项，在这里其实就是若该命题项中同时出现一个原子的正负文字两个方面，那么该命题项就是False
    size_t similarity(const PropTerm &) const;  // calculate the number of same literals
    set<string> get_total_literals() const;  // get all atoms that exists in this prop term
    set<string> get_diff_literals(const PropTerm &) const;  // exist in left, not right
    PropTerm covered_by(const PropTerm &) const;
    PropDNF split(string atom) const;
    PropTerm set_bit(size_t b) const;
    void show(ofstream &, size_t indent = 2) const;
    void print() const;
};


class PropDNF {
public:
    list<PropTerm> prop_terms; //存储了多个命题项，这就构成了命题层面的DNF
public:
    bool consistent() const; //判断该命题DNF是否一致
    bool entails(const PropDNF &) const; //判断该命题DNF是否可以推出另外一个命题DNF
    bool equals(const PropDNF &); //判断两个命题DNF是否等价
    bool empty() const;
    size_t size() const;
    PropDNF& minimal(); //化简命题DNF，即若PropTerm1能够推出PropTerm2， 则从prop_terms中把PropTerm1删除
    PropDNF group(const PropDNF &) const; //conjunct two PropDNF
    PropDNF merge(const PropDNF &) const; //disjunct two PropDNF
    PropCNF negation_as_CNF() const;
    PropCNF as_cnf() const;
    PropDNF negation_as_DNF() const;
    PropDNF revision(const PropDNF &) const;
    PropDNF update(const PropDNF &) const;
    list<PropTerm> get_modals(const set<string> &) const;  // get the modals of PropDNF
    set<string> get_total_literals() const;  // for modals extracting
    PropDNF split(const PropDNF & prop_dnf) const;  // split with different atoms
    void show(ofstream &, size_t indent = 2) const;
    void print(size_t indent = 2) const;
};


class PropClause {
public:
    size_t length;
    boost::dynamic_bitset<> literals;
public:
    PropClause(int len) { literals.resize(length = len); }
    bool valid() { return literals.count() == length; }
    set<string> get_total_literals() const;  // get all atoms that exists in this prop term
    bool entails(const PropClause& prop_clause) const;
    PropClause& minimal();
    void print() const;
    void show(ofstream &, size_t) const;
};


class PropCNF {
public:
    list<PropClause> prop_clauses;
public:
    PropDNF as_dnf() const;
    PropCNF& minimal();
    void print(size_t indent = 2) const;
    void show(ofstream &, size_t) const;
    bool empty() const { return prop_clauses.empty(); }
};


class ACDFTerm {
public:
    PropDNF propDNF;
    map<string, ACDFList> covers;  // conjunction for any two of them
    bool is_true = false;
public:
    ACDFTerm(bool true_term = false) { is_true = true_term; }
    size_t get_size() const;
    void show(ofstream &, size_t) const;
    void print(size_t indent = 2) const;
    bool empty() const;
    bool valid() const { return is_true; }
    bool neg_entails(const ACDFTerm &, const PropDNF &, bool try_goal = false, int* value = NULL) const;
    bool neg_entails(const ACDF &, const PropDNF &, bool try_goal = false, int* value = NULL) const;
    bool strong_entails(const ACDFTerm &, const PropDNF &) const;
    ACDF negation_as_acdf(const PropDNF &) const;
    ACDF revision(const ACDF &, const PropDNF &) const;
    ACDFTerm revision(const ACDFTerm &, const PropDNF &) const;
    ACDF update(const ACDF &, const PropDNF &) const;
    ACDFTerm update(const ACDFTerm &, const PropDNF &) const;
    ACDFTerm group(const ACDFTerm &) const; // conjunct two ACDFTerm
    ACDFTerm group(const PropDNF &) const; // conjunction of ACDFTerm and PropDNF
    ACDFTerm involve(const PropDNF &) const; // involve DNF gammma
    bool unsatisfiable() const;  // if the term is satisfiable
    bool objective() const;
    void mergeCover();
    ACDFTerm& minimal(const PropDNF &, bool midpro);
};


class ACDF {
public:
    list<ACDFTerm> acdf_terms;  // disjuntction for any two of them
public:
    ACDF() {}
    ACDF(bool true_term) { ACDFTerm t_term(true_term); acdf_terms.push_back(t_term); }
    size_t get_size() const { return acdf_terms.size(); }
    void show(ofstream &, size_t) const;
    void print(size_t indent = 2) const;
    bool neg_entails(const ACDF &, const PropDNF &, bool try_goal = false, int* value = NULL) const;
    bool strong_entails(const ACDF &, const PropDNF &) const;
    bool equals(const ACDF &, const PropDNF &) const;
    bool empty() const { return acdf_terms.empty(); }
    bool valid() const;
    vector<ACDF> epistemic_prog(const EpisAction &, const PropDNF &) const;
    ACDF ontic_prog(const OnticAction &, const PropDNF &) const;
    ACDF revision(const ACDF &, const PropDNF &) const;
    ACDF update(const ACDF &, const PropDNF &) const;
    ACDF involve(const PropDNF &) const; // involve DNF gammma
    ACDF group(const ACDF &) const; // conjunct two ACDF
    ACDF merge(const ACDF &) const; // disjunct two ACDF
    bool unsatisfiable() const;  // if the ACDF is satisfiable
    bool objective() const;
    bool obj_consistent(const ACDF &, const PropDNF &) const;
    ACDF negation_as_acdf(const PropDNF &) const;
    ACDF& minimal(const PropDNF &, bool outmost = true, bool midpro = false);  // the argu determines minimal manipulation
                                        // for outmost layer or not
};


class ACDFList {
public:
    list<ACDF> acdfs;
public:
    size_t get_size() const { return acdfs.size(); }
    void show(ofstream &, size_t) const;
    void print(size_t indent = 2) const;
    ACDF all_in_one() const;
    ACDFList& minimal(const PropDNF &, bool outmost = true, bool midpro = false);  // the argu determines minimal manipulation
                                        // for outmost layer or not
    ACDFList group(const ACDFList &) const; // conjunct two ACDFList
    ACDFList merge(const ACDFList &) const; // disjunct two ACDFList
    ACDFList involve(const PropDNF &) const;
    bool empty() const { return acdfs.empty(); }
};


#endif
