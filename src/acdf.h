#ifndef __ACDF_H__
#define __ACDF_H__

#include "header.h"
#include "adnf.h"
// #include "define.h"
#include "enumeration.h"

using namespace std;

class ACDFTerm;
class ACDF;
class ACDFList;
struct EpisAction;
struct OntiAction;

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
    ACDFTerm conjunction(const ACDFTerm &) const; // conjunct two ACDFTerm
    ACDFTerm conjunction(const PropDNF &) const; // conjunction of ACDFTerm and PropDNF
    ACDFTerm involve(const PropDNF &) const; // involve DNF gammma
    bool unsatisfiable() const;  // if the term is satisfiable
    bool objective() const;
    void mergeCover();
    ACDFTerm& minimal(const PropDNF &);
    int kb_size() const;
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
    ACDF ontic_prog(const OntiAction &, const PropDNF &) const;
    ACDF revision(const ACDF &, const PropDNF &) const;
    ACDF update(const ACDF &, const PropDNF &) const;
    ACDF involve(const PropDNF &) const; // involve DNF gammma
    ACDF conjunction(const ACDF &) const; // conjunct two ACDF
    ACDF disjunction(const ACDF &) const; // disjunct two ACDF
    bool unsatisfiable() const;  // if the ACDF is satisfiable
    bool objective() const;
    bool obj_consistent(const ACDF &, const PropDNF &) const;
    ACDF negation_as_acdf(const PropDNF & cstt) const;
    ACDF& minimal(const PropDNF &);
    int kb_size() const;
};


class ACDFList {
public:
    list<ACDF> acdfs;
public:
    size_t get_size() const { return acdfs.size(); }
    void show(ofstream &, size_t) const;
    void print(size_t indent = 2) const;
    ACDF all_in_one() const;
    ACDFList& minimal(const PropDNF &);  // the argu determines minimal manipulation
                                        // for outmost layer or not
    ACDFList conjunction(const ACDFList &) const; // conjunct two ACDFList
    ACDFList disjunction(const ACDFList &) const; // disjunct two ACDFList
    ACDFList involve(const PropDNF &) const;
    bool empty() const { return acdfs.empty(); }
    int kb_size() const;
};


#endif
