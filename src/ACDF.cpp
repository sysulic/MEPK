#include "define2.h"
#include <cmath>

set<string> intersection(const set<string> & set1, const set<string> & set2) {
    set<string> inter;
    for (set<string>::const_iterator s = set1.begin();
    s != set1.end(); ++s) {
        if (set2.find(*s) != set2.end()) inter.insert(*s);
    }
    return inter;
}

bool PropTerm::find(const string & atom) const {
    return literals[atomsByName[atom]*2] || literals[atomsByName[atom]*2+1];
}

bool PropTerm::consistent() const {
    for(size_t i = 0; i < length/2; ++i){
        if(literals[i * 2] && literals[i * 2 + 1] )
            return false;
    }
    return true;
}

bool PropTerm::entails(const PropTerm& prop_term) const {
    if (!this->consistent()) //first PropTerm is false
        return true;
    return prop_term.literals.is_subset_of(literals);
}

bool PropTerm::equals(const PropTerm& prop_term) {
    return prop_term.literals == literals;
}

bool PropTerm::empty() const {
    return literals.none();
}

PropTerm PropTerm::group(const PropTerm& prop_term) const {
    PropTerm result(length);
    for (size_t i = 0; i < length; ++i) {
        if (literals[i] || prop_term.literals[i])
            result.literals[i] = 1;
    }
    return result;
}

PropClause PropTerm::negation() const {
    PropClause result(length);
    for (size_t i = 0; i < literals.size(); i++) {
        if (literals[i]) {
            if (i % 2 == 0)
                result.literals[i + 1] = 1;
            else
                result.literals[i - 1] = 1;
        }
    }
    return result;
}

PropTerm& PropTerm::minimal() {
    if (!consistent())
        literals.set(); // inconsistent means this PropTerm is false,
                        // we can use a dynamic_bitset whose bits are 1.
    return *this;
}

size_t PropTerm::similarity(const PropTerm & term) const {
    boost::dynamic_bitset<> tmp_bitset = literals;
    tmp_bitset &= term.literals;
    return tmp_bitset.count();
}

set<string> PropTerm::get_total_literals() const {
    set<string> total_atoms;
    for (size_t i = 0; i < literals.size(); ++i) {
        if (literals[i]) total_atoms.insert(atomsByIndex[i/2]);
    }
    return total_atoms;
}

set<string> PropTerm::get_diff_literals(const PropTerm & prop_term) const {
// cout << "@@@@@@@@@@@@@@@@ diff atoms @@@@@@@@@@@@@@@@@@@@" << endl;
// print();
// cout << endl << " and ------------------" << endl;
// prop_term.print();
    set<string> diff_atoms;
    // for (size_t i = 0; i < literals.size(); ++i) {
    //     if ((!literals[i] && prop_term.literals[i])
    //     || (literals[i] && !prop_term.literals[i])) diff_atoms.insert(atomsByIndex[i/2]);
    // }
    for (size_t i = 0; i < literals.size(); ++i) {
        if (literals[i] && prop_term.literals[i/2*2+1-i%2]) diff_atoms.insert(atomsByIndex[i/2]);
    }
// cout << endl << " get ------------------" << endl;
// for (set<string>::const_iterator s = diff_atoms.begin();
// s != diff_atoms.end(); ++s)
//     cout << *s << " ";
// cout << endl;
    return diff_atoms;
}

PropTerm PropTerm::covered_by(const PropTerm & prop_term) const {
// cout << endl << "@@@@@@@@@@@@@@@@ prop term @@@@@@@@@@@@@@@@@@@@" << endl;
// print();
// cout << endl << "@@@@@@@@@@@@@@@@ covered by @@@@@@@@@@@@@@@@@@@@" << endl;
// prop_term.print();
    PropTerm new_term = *this;
    for (size_t i = 0; i < prop_term.literals.size(); ++i) {
        if (prop_term.literals[i]) {
            new_term.literals[i] = 1;
            new_term.literals[i/2*2+1-i%2] = 0;
        }
    }
// cout << endl << "@@@@@@@@@@@@ get new covered term @@@@@@@@@@@@@@@@@@" << endl;
// prop_term.print();
// cout << endl;
    return new_term;
}

PropDNF PropTerm::split(string atom) const {
    PropDNF new_dnf;
    new_dnf.prop_terms.push_back(set_bit(atomsByName[atom]*2));
    new_dnf.prop_terms.push_back(set_bit(atomsByName[atom]*2+1));
    return new_dnf;
}

PropTerm PropTerm::set_bit(size_t bit) const {
    PropTerm new_term = *this;
    new_term.literals[bit] = 1;
    return new_term;
}

void PropTerm::show(ofstream & out, size_t indent) const {
    vector<int> id_atoms;
    // 提取原子
    for (size_t i = 0; i < literals.size(); ++i)
        if (literals[i])
            id_atoms.push_back(i);
    if (id_atoms.empty())
        return ;
    // 注意奇数为非
    out << "(" << (id_atoms[0] % 2 ? "¬" : "") << atomsByIndex[id_atoms[0] / 2];
    for (size_t i = 1; i < id_atoms.size(); ++i)
        out << " & " << (id_atoms[i] % 2 ? "¬" : "") << atomsByIndex[id_atoms[i] / 2];
    out << ")";
}

void PropTerm::print() const {
    vector<int> id_atoms;
    // 提取原子
    for (size_t i = 0; i < literals.size(); ++i)
        if (literals[i])
            id_atoms.push_back(i);
    if (id_atoms.empty())
        return ;
    // 注意奇数为非
    cout << "(" << (id_atoms[0] % 2 ? "¬" : "") << atomsByIndex[id_atoms[0] / 2];
    for (size_t i = 1; i < id_atoms.size(); ++i)
        cout << " & " << (id_atoms[i] % 2 ? "¬" : "") << atomsByIndex[id_atoms[i] / 2];
    cout << ")";
}

bool PropDNF::consistent() const {
    for (list<PropTerm>::const_iterator it = prop_terms.begin(); \
        it != prop_terms.end(); ++it) {
        if (it->consistent())
            return true;
    }   
    return false;
}

bool PropDNF::entails(const PropDNF& propDNF) const {
    // if (propDNF.empty()) return true;
    //This reasoning rule is Proposition 3.6 PropDNF |= PropDNF from Yang's paper
    for (list<PropTerm>::const_iterator pre_it = prop_terms.begin(); \
        pre_it != prop_terms.end(); ++pre_it) {
        bool can_entail = false;
        for (list<PropTerm>::const_iterator post_it = propDNF.prop_terms.begin(); \
            post_it != propDNF.prop_terms.end(); ++post_it) {
            if (pre_it->entails(*post_it)) {
                can_entail = true;
                break;
            }
        }
        if (!can_entail) return false;
    }
    return true;
}

bool PropDNF::equals(const PropDNF& propDNF) {
    return this->entails(propDNF) && propDNF.entails(*this);
}

bool PropDNF::empty() const {
    return prop_terms.empty();
}

inline size_t PropDNF::size() const {
    return prop_terms.size();
}

PropDNF PropDNF::group(const PropDNF& propDNF) const {
    if (!empty() && ! propDNF.empty()) {
        PropDNF result;
        for (list<PropTerm>::const_iterator it_i = prop_terms.begin(); \
            it_i != prop_terms.end(); ++it_i) {
            for (list<PropTerm>::const_iterator it_j = propDNF.prop_terms.begin(); \
                it_j != propDNF.prop_terms.end(); ++it_j) 
                result.prop_terms.push_back(it_i->group(*it_j));
        }
        //need to add min and PI method
        return result;
    } else if (empty()) {
        return propDNF;
    } else {
        return *this;
    }
}

PropDNF PropDNF::merge(const PropDNF & prop_dnf) const {
    PropDNF new_dnf;
    new_dnf.prop_terms = prop_terms;
    for (list<PropTerm>::const_iterator term = prop_dnf.prop_terms.begin(); \
        term != prop_dnf.prop_terms.end(); ++term) {
        new_dnf.prop_terms.push_back(*term);
    }
    new_dnf = new_dnf.minimal();
    return new_dnf;
}

PropCNF PropDNF::negation_as_CNF() const {
    if (empty()) { PropCNF cnf; return cnf; }  // empty for empty

    PropCNF cnf;
    for (list<PropTerm>::const_iterator term = prop_terms.begin(); \
        term != prop_terms.end(); ++term) {
        cnf.prop_clauses.push_back(term->negation());
    }
    return cnf;
}

PropCNF PropDNF::as_cnf() const {
    PropCNF prop_cnf;
    if (empty()) return prop_cnf;
    // split the first term
    PropTerm first_term = *(prop_terms.begin()); \
    for (size_t i = 0; i < first_term.length; ++i) {
        if (first_term.literals[i]) {
            PropClause clause(first_term.length);
            clause.literals[i] = 1;
            prop_cnf.prop_clauses.push_back(clause);
        }
    }
    // merge following clauses to those added terms one by one
    if (prop_terms.begin() != ++prop_terms.end()) {
        for (list<PropTerm>::const_iterator term = ++prop_terms.begin(); \
            term != prop_terms.end(); ++term) {
            // Careful! The list is increasing!
            list<PropClause>::iterator clauses_end = prop_cnf.prop_clauses.end();
            for (list<PropClause>::iterator clause = prop_cnf.prop_clauses.begin(); \
                clause != clauses_end; ++clause) {
                size_t last;
                for (size_t i = 0; i < term->length; ++i) {
                    if (term->literals[i]) {
                        last = i;
                        PropClause tmp_clause = *clause;
                        tmp_clause.literals[i] = 1;
                        prop_cnf.prop_clauses.push_back(tmp_clause);
                    }
                }
                clause->literals[last] = 1;
                prop_cnf.prop_clauses.pop_back();
            }
        }
    }
    return prop_cnf;
}

// Algorithm: convert a CNF to a PropDNF
PropDNF PropDNF::negation_as_DNF() const {
    // cout << "before nagation DNF" << endl;
    // print();
    if (empty()) return *this;  // empty for empty
    PropCNF cnf = negation_as_CNF();
    PropDNF prop_dnf = cnf.as_dnf();
// cout << "new negated dnf : " << endl;
// prop_dnf.print();
    return prop_dnf;
}

list<PropTerm> PropDNF::get_modals(const set<string> & total_atoms) const {
    list<PropTerm> modals = prop_terms;
    for (set<string>::const_iterator atom = total_atoms.begin(); \
        atom != total_atoms.end(); ++atom) {
        list<PropTerm>::const_iterator old_end = modals.end();
        // if prop_terms is empty at the beginning
        if (modals.empty()) {
            PropTerm tmp_term(atomsByIndex.size()*2);  // initialize with length
            tmp_term.literals[atomsByName[*atom]*2] = 1;
            modals.push_back(tmp_term);
            tmp_term.literals[atomsByName[*atom]*2] = 0;
            tmp_term.literals[atomsByName[*atom]*2+1] = 1;
            modals.push_back(tmp_term);
            continue;
        }
        for (list<PropTerm>::iterator term = modals.begin(); \
            term != old_end; ++term) {
            if (!term->find(*atom)) {
                PropTerm new_term = *term;
                term->literals[atomsByName[*atom]*2] = 1;
                new_term.literals[atomsByName[*atom]*2+1] = 1;
                modals.push_back(new_term);
            }
        }
    }
    return modals;
}

set<string> PropDNF::get_total_literals() const {
    set<string> total_atoms;
    for (list<PropTerm>::const_iterator term = prop_terms.begin(); \
    term != prop_terms.end(); ++term) {
        set<string> part_atoms = term->get_total_literals();
        total_atoms.insert(part_atoms.begin(), part_atoms.end());
    }
    return total_atoms;
}

PropDNF PropDNF::split(const PropDNF & prop_dnf) const {
    PropDNF new_dnf;
    set<string> left_atoms = get_total_literals(), right_atoms = prop_dnf.get_total_literals(), missing_atoms;
    for (set<string>::const_iterator atom = right_atoms.begin(); \
    atom != right_atoms.end(); ++atom) {
        if (left_atoms.find(*atom) == left_atoms.end())
            missing_atoms.insert(*atom);
    }
    for (set<string>::const_iterator missing_atom = missing_atoms.begin(); \
    missing_atom != missing_atoms.end(); ++missing_atom) {
        for (list<PropTerm>::const_iterator term = prop_terms.begin(); \
        term != prop_terms.end(); ++term) {
            new_dnf = new_dnf.merge(term->split(*missing_atom));
        }
    }
    return new_dnf;
}

PropDNF PropDNF::revision(const PropDNF & prop_dnf) const {
    if (empty()) return prop_dnf;
    if (prop_dnf.empty()) return *this;

    // 1. get diff atoms set list of two modals
    list<set<string> > diff_atoms_list;
    for (list<PropTerm>::const_iterator term1 = prop_terms.begin();
    term1 != prop_terms.end(); ++term1)
        for (list<PropTerm>::const_iterator term2 = prop_dnf.prop_terms.begin();
        term2 != prop_dnf.prop_terms.end(); ++term2)
            diff_atoms_list.push_back(term1->get_diff_literals(*term2));

    // 2. remove those sets which are the subsets of others
    size_t fi_size = prop_terms.size(), miu_size = prop_dnf.prop_terms.size();
    boost::dynamic_bitset<> diff_atoms_sets_tag(fi_size*miu_size);
    // cout << diff_atoms_sets_tag.size() << endl;
    size_t index = 0;
    for (list<set<string> >::iterator set1 = diff_atoms_list.begin();
    set1 != diff_atoms_list.end(); ) {
        bool is_delete = false;
        for (list<set<string> >::iterator set2 = diff_atoms_list.begin();
        set2 != diff_atoms_list.end(); ++set2) {
            set<string> tmp_set(*set2);
            tmp_set.insert(set1->begin(), set1->end());
            if (set1 != set2 && set1->size() != set2->size() && *set1 == tmp_set) {
                is_delete = true;
                // cout << "bad term =====================================" << endl;
                // term1->print();
                set1 = diff_atoms_list.erase(set1);
                diff_atoms_sets_tag[index++] = 1;
                break;
            }
        }
        if (!is_delete) {
            ++set1;
            ++index;
        }
    }

    // 3. collect the corresponding modals2 respect to the left common-atom-set
    size_t s = 0;
    PropDNF new_dnf;
    for (list<PropTerm>::const_iterator term1 = prop_terms.begin();
    term1 != prop_terms.end(); ++term1, ++s) {
        size_t t = 0;  // outer loop initialize t !!!
        for (list<PropTerm>::const_iterator term2 = prop_dnf.prop_terms.begin();
        term2 != prop_dnf.prop_terms.end(); ++term2, ++t) {
            if (!diff_atoms_sets_tag[miu_size*s+t]) {
                new_dnf.prop_terms.push_back(term1->covered_by(*term2));
            }
        }
    }
    
    new_dnf = new_dnf.minimal();
    
    return new_dnf;
}

PropDNF PropDNF::update(const PropDNF & prop_dnf) const {
    // cout << "PropDNF ```````````````````" << endl;
    // print();
    // cout << "update with another DNF ```" << endl;
    // prop_dnf.print();
    if (empty()) return prop_dnf;
    if (prop_dnf.empty()) return *this;

    // get the modals of prop_dnf and another prop_dnf
    set<string> total_atoms = get_total_literals(), another_total_atoms = prop_dnf.get_total_literals();
    total_atoms.insert(another_total_atoms.begin(), another_total_atoms.end());

    list<PropTerm> modals1 = get_modals(total_atoms);
    list<PropTerm> modals2 = prop_dnf.get_modals(total_atoms);

    // calculate the minimal modals of latter modals to former modals
    PropDNF minimal_modals;
    for (list<PropTerm>::const_iterator term1 = modals1.begin(); \
        term1 != modals1.end(); ++term1) {
        stack<PropTerm> cloest_terms_stack;  // stack is to store more than one cloest modals
        for (list<PropTerm>::const_iterator term = modals2.begin(); \
            term != modals2.end(); ++term) {
            if (cloest_terms_stack.empty())
                cloest_terms_stack.push(*term);
            else if (cloest_terms_stack.top().similarity(*term1) <
                term->similarity(*term1)) {
                while (!cloest_terms_stack.empty()) cloest_terms_stack.pop();
                cloest_terms_stack.push(*term);
            } else if (cloest_terms_stack.top().similarity(*term1) ==
                term->similarity(*term1)) {
                cloest_terms_stack.push(*term);
            }
        }
        while (!cloest_terms_stack.empty()) {
            minimal_modals.prop_terms.push_back(cloest_terms_stack.top());
            cloest_terms_stack.pop();
        }
    }
    // cout << "get new DNF ````````````````" << endl;
    // minimal_modals.print();
    return minimal_modals;
}

PropDNF& PropDNF::minimal() {
    // cout << "========================" << endl;
    // print();
    // 删除非consistent
    for (list<PropTerm>::iterator it = prop_terms.begin(); \
            it != prop_terms.end(); ) {
        if (!it->consistent())
            it = prop_terms.erase(it);
        else 
            ++it;
    }
    // 处理蕴含关系
    for (list<PropTerm>::iterator it_1 = prop_terms.begin(); \
        it_1 != prop_terms.end(); ) {
        bool is_delete = false;
        for (list<PropTerm>::iterator it_2 = prop_terms.begin(); \
                it_2 != prop_terms.end(); ++it_2) {
            if (it_1 != it_2 && it_1->entails(*it_2)) {
                is_delete = true;
                it_1 = prop_terms.erase(it_1);
                break;
            }
        }
        if (!is_delete)
            ++it_1;
    }
    // cout << "after minimal ===============" << endl;
    // print();
    return *this;
}

void PropDNF::show(ofstream & out, size_t indent) const {
    if (empty()) return ;
    for (size_t i = 0; i < indent; ++i) out << ' ';  // indent
    out << "PropDNF: ( ";
    prop_terms.begin()->show(out, false);
    for (list<PropTerm>::const_iterator it = (++prop_terms.begin());
            it != prop_terms.end(); ++it) {
        out << " | ";
        it->show(out, false);
    }
    out << " )" << endl;
}

void PropDNF::print(size_t indent) const {
    if (empty()) return;
    for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
    cout << "PropDNF: ( ";
    prop_terms.begin()->print();
    for (list<PropTerm>::const_iterator it = (++ prop_terms.begin());
            it != prop_terms.end(); ++ it) {
        cout << " | ";
        it->print();
    }
    cout << " )" << endl;
}

set<string> PropClause::get_total_literals() const {
    set<string> total_atoms;
    for (size_t i = 0; i < literals.size(); ++i) {
        if (literals[i]) total_atoms.insert(atomsByIndex[i/2]);
    }
    return total_atoms;
}

bool PropClause::entails(const PropClause& prop_clause) const
{
    return literals.is_subset_of(prop_clause.literals);
}

PropClause& PropClause::minimal() {
    for (size_t i = 0; i < length; i += 2) {
        if (literals[i] && literals[i + 1]) {
            literals.set(); //This PropClause is true, we can use a dynamic_bitset whose bits are 1.
            break;
        }          
    }
    return *this;
}

void PropClause::print() const {
    vector<int> id_atoms;
    // 提取原子
    for (size_t i = 0; i < literals.size(); ++i)
        if (literals[i])
            id_atoms.push_back(i);
    if (id_atoms.empty())
        return ;
    // 注意奇数为非
    cout << "(" << (id_atoms[0] % 2 ? "¬" : "") << atomsByIndex[id_atoms[0] / 2];
    for (size_t i = 1; i < id_atoms.size(); ++i)
        cout << " & " << (id_atoms[i] % 2 ? "¬" : "") << atomsByIndex[id_atoms[i] / 2];
    cout << ")";
}

void PropClause::show(ofstream & out, size_t indent) const {
    vector<int> id_atoms;
    // 提取原子
    for (size_t i = 0; i < literals.size(); ++i)
        if (literals[i])
            id_atoms.push_back(i);
    if (id_atoms.empty())
        return ;
    // 注意奇数为非
    out << "(" << (id_atoms[0] % 2 ? "¬" : "") << atomsByIndex[id_atoms[0] / 2];
    for (size_t i = 1; i < id_atoms.size(); ++i)
        out << " & " << (id_atoms[i] % 2 ? "¬" : "") << atomsByIndex[id_atoms[i] / 2];
    out << ")";
}

PropDNF PropCNF::as_dnf() const {
    PropDNF prop_dnf;
    if (empty()) return prop_dnf;
    // split the firtst clause
    PropClause first_clause = *(prop_clauses.begin()); \
    for (size_t i = 0; i < first_clause.length; ++i) {
        if (first_clause.literals[i]) {
            PropTerm term(first_clause.length);
            term.literals[i] = 1;
            prop_dnf.prop_terms.push_back(term);
        }
    }
    // merge following clauses to those added terms one by one
    if (prop_clauses.begin() != ++prop_clauses.end()) {
        for (list<PropClause>::const_iterator clause = ++prop_clauses.begin(); \
            clause != prop_clauses.end(); ++clause) {
            // Careful! The list is increasing!
            list<PropTerm>::iterator terms_end = prop_dnf.prop_terms.end();
            for (list<PropTerm>::iterator term = prop_dnf.prop_terms.begin(); \
                term != terms_end; ++term) {
                size_t last;
                for (size_t i = 0; i < clause->length; ++i) {
                    if (clause->literals[i]) {
                        last = i;
                        PropTerm tmp_term = *term;
                        tmp_term.literals[i] = 1;
                        prop_dnf.prop_terms.push_back(tmp_term);
                    }
                }
                term->literals[last] = 1;
                prop_dnf.prop_terms.pop_back();
            }
        }
    }
    return prop_dnf;
}

PropCNF& PropCNF::minimal() {
    // 删除 valid
    for (list<PropClause>::iterator it = prop_clauses.begin(); \
            it != prop_clauses.end(); ) {
        if (it->valid())
            it = prop_clauses.erase(it);
        else 
            ++it;
    }
    // 处理蕴含关系
    for (list<PropClause>::iterator pre_it = prop_clauses.begin(); pre_it != prop_clauses.end(); pre_it++) {
        for (list<PropClause>::iterator post_it = prop_clauses.begin(); post_it != prop_clauses.end(); ) {
            if (post_it != pre_it && pre_it->entails(*post_it)) {
                list<PropClause>::iterator delete_it = post_it;
                ++post_it;
                prop_clauses.erase(delete_it);
            }   
            else
                ++post_it;
        }
    }
    return *this;
}

void PropCNF::show(ofstream & out, size_t indent) const {
    if (empty()) return ;
    for (size_t i = 0; i < indent; ++i) out << ' ';  // indent
    out << "PropCNF: ( ";
    prop_clauses.begin()->show(out, false);
    for (list<PropClause>::const_iterator it = (++prop_clauses.begin());
            it != prop_clauses.end(); ++it) {
        out << " | ";
        it->show(out, false);
    }
    out << " )" << endl;
}

void PropCNF::print(size_t indent) const {
    if (empty()) return;
    for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
    cout << "PropCNF: ( ";
    prop_clauses.begin()->print();
    for (list<PropClause>::const_iterator it = (++prop_clauses.begin());
            it != prop_clauses.end(); ++ it) {
        cout << " | ";
        it->print();
    }
    cout << " )" << endl;
}

size_t ACDFTerm::get_size() const {
    size_t size = 0;
    for (map<string, ACDFList>::const_iterator it = covers.begin();
    it != covers.end(); ++it) {
        size += it->second.get_size();
    }
    return size;
}

void ACDFTerm::show(ofstream & out, size_t indent) const {
    if (valid()) {
        for (size_t i = 0; i < indent; ++i) out << ' ';  // indent
        out << "True Term" << endl;
        return;
    }
    propDNF.show(out, indent);
    for (map<string, ACDFList>::const_iterator it = covers.begin();
    it != covers.end(); ++it) {
        for (size_t i = 0; i < indent; ++i) out << ' ';  // indent
        out << it->first << " :" << endl;
        it->second.show(out, indent+2);
    }
}

void ACDFTerm::print(size_t indent) const {
    if (valid()) {
        for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
        cout << "True Term" << endl;
        return;
    }
    propDNF.print(indent);
    for (map<string, ACDFList>::const_iterator it = covers.begin();
            it != covers.end(); ++it) {
        for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
        cout << it->first << " :" << endl;
        it->second.print(indent+2);
    }
}

bool ACDFTerm::empty() const {
    return propDNF.empty() && covers.empty() && !valid();
}

bool ACDFTerm::neg_entails(const ACDF & acdf, const PropDNF & cstt, bool try_goal, int* value) const {
    for(list<ACDFTerm>::const_iterator post_term = acdf.acdf_terms.begin();
    post_term != acdf.acdf_terms.end(); ++post_term) {
        if (neg_entails(*post_term, cstt, try_goal, value)) {
            return false;
        } else if (try_goal) {
            // (*value)++;
        }
    }
    return true;
}

bool ACDFTerm::neg_entails(const ACDFTerm & acdf_term, const PropDNF & cstt, bool try_goal, int* value) const {
    ACDFTerm tmp_term = acdf_term;
// cout << "neg entails =====================================" << endl;
// print();
// cout << "=====================================" << endl;
// acdf_term.print();

    if (!propDNF.group(acdf_term.propDNF).group(cstt).consistent()) {
        if (try_goal) (*value)++;
        return true;
    }

    // cout << "haha 1" << endl;
    for (map<string, ACDFList>::const_iterator cover1 = covers.begin();
        cover1 != covers.end(); ++cover1) {
        if (tmp_term.covers.find(cover1->first) == tmp_term.covers.end())
            continue;

        ACDFList acdflist_tmp = tmp_term.covers[cover1->first];

        for (list<ACDF>::const_iterator acdf1 = cover1->second.acdfs.begin();
            acdf1 != cover1->second.acdfs.end(); ++acdf1) {
            bool flag = true;
            for (list<ACDF>::const_iterator acdf2 = acdflist_tmp.acdfs.begin();
            acdf2 != acdflist_tmp.acdfs.end(); ++acdf2) {
                if (!acdf1->neg_entails(*acdf2, cstt, try_goal, value)) {
                    flag = false;
                    break;
                } else if (try_goal) {
                    // (*value)++;
                }
            }
            if (flag) return true;
        }

    // cout << "haha 2" << endl;
        for (list<ACDF>::const_iterator acdf2 = acdflist_tmp.acdfs.begin();
            acdf2 != acdflist_tmp.acdfs.end(); ++acdf2) {
            bool flag = true;
            for (list<ACDF>::const_iterator acdf1 = cover1->second.acdfs.begin();
            acdf1 != cover1->second.acdfs.end(); ++acdf1) {
                if (!acdf1->neg_entails(*acdf2, cstt, try_goal, value)) {
                    flag = false;
                    break;
                } else if (try_goal) {
                    // (*value)++;
                }
            }
            if (flag) return true;
        }
    // cout << "haha 3" << endl;
    }
        // cout << "fail =====================================" << endl;

    return false;
}

bool ACDFTerm::strong_entails(const ACDFTerm & acdf_term, const PropDNF & cstt) const {
    if (valid() || acdf_term.valid()) return ((valid() && acdf_term.valid()) ? true : false);
// cout << "strong entails =====================================" << endl;
// print();
// cout << "=====================================" << endl;
// acdf_term.print();
// cout << "haha" << endl;
// cstt.print();
    if (!acdf_term.propDNF.empty() && !propDNF.group(cstt).entails(acdf_term.propDNF)) return false;
// cout << "haha0" << endl;
// cout << "strong entails: prop_term entails =====================================" << endl;
// propDNF.group(cstt).minimal().print();
// cout << "         ====================================" << endl;
// acdf_term.propDNF.group(cstt).minimal().print();
    // if (!propDNF.group(cstt).minimal().entails(tmp_term.propDNF.group(cstt).minimal())) return false;
// cout << "haha1" << endl;
    ACDFTerm tmp_term = acdf_term;
    for (map<string, ACDFList>::const_iterator cover = covers.begin();
        cover != covers.end(); ++cover) {
        if (tmp_term.covers.find(cover->first) == tmp_term.covers.end())
            return false;

// cout << "jump0" << endl;
        ACDFList acdflist_tmp = tmp_term.covers[cover->first];

        for (list<ACDF>::const_iterator acdf1 = cover->second.acdfs.begin();
            acdf1 != cover->second.acdfs.end(); ++acdf1) {
            bool found = false;
            for (list<ACDF>::const_iterator acdf2 = acdflist_tmp.acdfs.begin();
            acdf2 != acdflist_tmp.acdfs.end(); ++acdf2) {
                if (acdf1->strong_entails(*acdf2, cstt)) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
// cout << "jump1" << endl;

        for (list<ACDF>::const_iterator acdf2 = acdflist_tmp.acdfs.begin();
        acdf2 != acdflist_tmp.acdfs.end(); ++acdf2) {
            bool found = false;
            for (list<ACDF>::const_iterator acdf1 = cover->second.acdfs.begin();
            acdf1 != cover->second.acdfs.end(); ++acdf1) {
                if (acdf1->strong_entails(*acdf2, cstt)) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
// cout << "jump2" << endl;
    }
    // cout << "success =====================================" << endl;
    return true;
}

// ¬ACDFTerm -> ACDF
ACDF ACDFTerm::negation_as_acdf(const PropDNF & cstt) const {
    // cout << "negation acdf ############################" << endl;
    // print();
    ACDF new_acdf;
    ACDFTerm dnf_term;
    dnf_term.propDNF = propDNF.negation_as_DNF();
    new_acdf.acdf_terms.push_back(dnf_term);
    // ¬Cover -> ACDF
    for (map<string, ACDFList>::const_iterator cover = covers.begin();
        cover != covers.end(); ++cover) {
        ACDFList covered = cover->second;
        string agent = cover->first;
        // ¬K(ACDFList) -> Cover(T, ¬ACDFList)
        ACDFTerm tmp_term;
        tmp_term.covers[agent].acdfs.push_back(covered.all_in_one().negation_as_acdf(cstt));
        ACDF true_term(true);
        tmp_term.covers[agent].acdfs.push_back(true_term);
        new_acdf.acdf_terms.push_back(tmp_term);
        // each K(ACDF) -> Cover(¬ACDF)
        for (list<ACDF>::const_iterator acdf = covered.acdfs.begin();
        acdf != covered.acdfs.end(); ++acdf) {
            ACDFList tmp_acdflist;
            tmp_acdflist.acdfs.push_back(acdf->negation_as_acdf(cstt));
            tmp_term.covers[agent] = tmp_acdflist;
            new_acdf.acdf_terms.push_back(tmp_term);  // add i
        }
    }
    // cout << "after negation ############################" << endl;
    // new_acdf.print();
    // cout << "###########################################" << endl;
    return new_acdf.minimal(cstt);
}

ACDF ACDFTerm::revision(const ACDF & acdf, const PropDNF & cstt) const {
    ACDF tmp_acdf;
    tmp_acdf.acdf_terms.push_back(*this);
    return tmp_acdf.revision(acdf, cstt);
}

ACDFTerm ACDFTerm::revision(const ACDFTerm & acdf_term, const PropDNF & cstt) const {
// cout << "Term ```````````````````" << endl;
// print();
// cout << "revision with ````````````" << endl;
// acdf_term.print();
    if (valid()) return acdf_term;
    if (acdf_term.valid()) return *this;
    ACDFTerm new_term;
    PropDNF empty_dnf;
    new_term.propDNF = propDNF.group(empty_dnf).minimal().revision(acdf_term.propDNF.group(cstt).minimal());
    // revision all agent-covers of those agents in left
    bool two_consis = !(group(acdf_term).minimal(cstt, true).unsatisfiable());
    for (map<string, ACDFList>::const_iterator cover = covers.begin(); \
        cover != covers.end(); ++cover) {
        if (acdf_term.covers.find(cover->first) == acdf_term.covers.end()) {
            new_term.covers[cover->first] = cover->second;
        } else {
            if (two_consis) {
    // cout << "two term consistent ? ```````````````````" << endl;
    // group(acdf_term).minimal(cstt).print();
                // case 3:
    // cout << "inconsistent" << endl;
                // calculate \Phi^*
                ACDFList acdflist1, acdflist2;  // 1: consistent revision; 2: all
                bool found_consis = false;
                for (list<ACDF>::const_iterator acdf1 = cover->second.acdfs.begin();
                acdf1 != cover->second.acdfs.end(); ++acdf1) {
                    for (list<ACDF>::const_iterator acdf2 = acdf_term.covers.at(cover->first).acdfs.begin();
                    acdf2 != acdf_term.covers.at(cover->first).acdfs.end(); ++acdf2) {
                        bool consis = !(acdf1->group(*acdf2).unsatisfiable());
                        ACDF revisioned_acdf;
                        if (!found_consis) {
                            revisioned_acdf = acdf1->revision(*acdf2, cstt);
                            if (consis) {
                                acdflist1.acdfs.push_back(revisioned_acdf);
                                found_consis = true;
                            }
                            acdflist2.acdfs.push_back(revisioned_acdf);
                        } else {
                            if (consis)
                                acdflist1.acdfs.push_back(acdf1->revision(*acdf2, cstt));
                        }
                    }    
                }
                if (found_consis)
                    new_term.covers[cover->first] = acdflist1;
                else
                    new_term.covers[cover->first] = acdflist2;
                
                ACDFList tmp_acdflist = new_term.covers[cover->first];
// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
// tmp_acdflist.print();
// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
                ACDFList tmp_acdflist2;
                for (list<ACDF>::const_iterator post_acdf = acdf_term.covers.at(cover->first).acdfs.begin();
                post_acdf != acdf_term.covers.at(cover->first).acdfs.end(); ++post_acdf) {
                    for (list<ACDF>::const_iterator revision_acdf = tmp_acdflist.acdfs.begin();
                    revision_acdf != tmp_acdflist.acdfs.end(); ++revision_acdf) {
                        if (!revision_acdf->neg_entails(post_acdf->negation_as_acdf(cstt), cstt))
                            tmp_acdflist2.acdfs.push_back(*post_acdf);
                    }
                }
// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
// tmp_acdflist2.print();
// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
                new_term.covers[cover->first] = tmp_acdflist.merge(tmp_acdflist2);
            } else {
                // case 2:
        // cout << "consistent" << endl;
                for (list<ACDF>::const_iterator acdf = cover->second.acdfs.begin();
                acdf != cover->second.acdfs.end(); ++acdf) {
                    new_term.covers[cover->first].acdfs.push_back(acdf->revision(acdf_term.covers.at(cover->first).all_in_one(), cstt));
                }
                for (list<ACDF>::const_iterator acdf = acdf_term.covers.at(cover->first).acdfs.begin();
                acdf != acdf_term.covers.at(cover->first).acdfs.end(); ++acdf) {
                    new_term.covers[cover->first].acdfs.push_back(acdf->revision(cover->second.all_in_one(), cstt));
                }
            }
        }
    }
    // add those agent-covers appear in the right, but not in left
    for (map<string, ACDFList>::const_iterator cover = acdf_term.covers.begin(); \
    cover != acdf_term.covers.end(); ++cover)
        if (covers.find(cover->first) == covers.end()) {
            new_term.covers[cover->first] = cover->second;
        }
    new_term = new_term.minimal(cstt, true);
// cout << "get ````````````````````" << endl;
// new_term.print();
    return new_term;
}

ACDF ACDFTerm::update(const ACDF & acdf, const PropDNF & cstt) const {
    // cout << "Half Term ``````````````" << endl;
    // print();
    // cout << "update with ````````````" << endl;
    // acdf.print();
    bool exist = false;
    ACDF new_acdf1, new_acdf2;
    for (list<ACDFTerm>::const_iterator term = acdf.acdf_terms.begin(); \
    term != acdf.acdf_terms.end(); ++term) {
        bool consis = !(group(term->group(cstt)).unsatisfiable());
        ACDFTerm updated_term;
        if (!exist) {

            updated_term = update(*term, cstt);
            if (consis) {
                new_acdf1.acdf_terms.push_back(updated_term);
                exist = true;
            }
            new_acdf2.acdf_terms.push_back(updated_term);
        } else {
            
            if (consis)
                new_acdf1.acdf_terms.push_back(update(*term, cstt));
        }
    }

    // cout << "get ````````````````````" << endl;
    // exist ? new_acdf1.print() : new_acdf2.print();
    return exist ? new_acdf1 : new_acdf2;
}

ACDFTerm ACDFTerm::update(const ACDFTerm & acdf_term, const PropDNF & cstt) const {
// cout << "Term ```````````````````" << endl;
// print();
// cout << "update with ````````````" << endl;
// acdf_term.print();
    if (valid()) return acdf_term;
    if (acdf_term.valid()) return *this;
    ACDFTerm new_term;
    PropDNF empty_dnf;
    new_term.propDNF = propDNF.group(empty_dnf).minimal().update(acdf_term.propDNF.group(cstt).minimal());
    // new_term.propDNF.print();
    // update all agent-covers of those agents in left
    for (map<string, ACDFList>::const_iterator cover = covers.begin(); \
        cover != covers.end(); ++cover) {
        if (acdf_term.covers.find(cover->first) == acdf_term.covers.end()) {
            new_term.covers[cover->first] = cover->second;
        } else {
    // cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
    // cover->second.print();
    // cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
    // acdf_term.covers.at(cover->first).print();
    // cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
    // cover->second.update(acdf_term.covers.at(cover->first), cstt).print();
    // cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
            // calculate \Phi^*
            ACDFList acdflist;
            for (list<ACDF>::const_iterator acdf1 = cover->second.acdfs.begin();
            acdf1 != cover->second.acdfs.end(); ++acdf1) {
                acdflist.acdfs.push_back(acdf1->update(acdf_term.covers.at(cover->first).all_in_one(), cstt));
            }

// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
// acdflist.print();
// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
            ACDFList acdflist2;
            for (list<ACDF>::const_iterator post_acdf = acdf_term.covers.at(cover->first).acdfs.begin();
            post_acdf != acdf_term.covers.at(cover->first).acdfs.end(); ++post_acdf) {
                for (list<ACDF>::const_iterator update_acdf = acdflist.acdfs.begin();
                update_acdf != acdflist.acdfs.end(); ++update_acdf) {
                    if (!update_acdf->neg_entails(post_acdf->negation_as_acdf(cstt), cstt))
                        acdflist2.acdfs.push_back(*post_acdf);
                }
            }
// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
// acdflist2.print();
// cout << "_+_+_+_+_+_++_+_++__++ ```````````````````" << endl;
            new_term.covers[cover->first] = acdflist.merge(acdflist2);
        }
    }
    // add those agent-covers appear in the right, but not in left
    for (map<string, ACDFList>::const_iterator cover = acdf_term.covers.begin(); \
    cover != acdf_term.covers.end(); ++cover) {
        if (covers.find(cover->first) == covers.end()) {
            new_term.covers[cover->first] = cover->second;
        }
    }
    new_term = new_term.minimal(cstt, true);
// cout << "get ````````````````````" << endl;
// new_term.print();
    return new_term;
}


ACDFTerm ACDFTerm::group(const ACDFTerm & acdf_term) const {
// cout << "Term ```````````````````" << endl;
// print();
// cout << "group with ````````````" << endl;
// acdf_term.print();
    if (valid()) return acdf_term;
    if (acdf_term.valid()) return *this;
    ACDFTerm new_term = *this;
    new_term.propDNF = propDNF.group(acdf_term.propDNF);
    for (map<string, ACDFList>::const_iterator cover = acdf_term.covers.begin();
        cover != acdf_term.covers.end(); ++cover)
        if (new_term.covers.find(cover->first) == new_term.covers.end())
            new_term.covers[cover->first] = cover->second;
        else
            new_term.covers[cover->first] =
                new_term.covers[cover->first].group(cover->second);
// cout << "get new term ````````````" << endl;
// new_term.print();
    return new_term;
}

ACDFTerm ACDFTerm::group(const PropDNF & prop_dnf) const {
    ACDFTerm new_term = *this;  // in case that K_a in *this, not in latter
    // PropDNF
    new_term.propDNF = propDNF.group(prop_dnf);
    if (!prop_dnf.empty()) new_term.is_true = false;
    return new_term;
}

ACDFTerm ACDFTerm::involve(const PropDNF & prop_dnf) const {
    ACDFTerm new_term;  // in case that K_a in *this, not in latter
    // PropDNF
    new_term.propDNF = propDNF.group(prop_dnf);
    for (map<string, ACDFList>::const_iterator cover = covers.begin();
    cover != covers.end(); ++cover) {
        new_term.covers[cover->first] = cover->second.involve(prop_dnf);
    }
    return new_term;
}

bool ACDFTerm::unsatisfiable() const {
    // cout << "check satisfiable =-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    // print();
    if (!propDNF.empty() && !propDNF.consistent()) return true;
    ACDF tmp;
    for (map<string, ACDFList>::const_iterator cover = covers.begin();
    cover != covers.end(); ++cover) {
        tmp = cover->second.all_in_one();
        if (tmp.unsatisfiable() || tmp.empty()) {
            return true;
        }
    }
    // cout << "this is consistent =-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    return false;
}

bool ACDFTerm::objective() const {
    if (valid()) return false;
    if (covers.size() != 0) return false;
    return true;
}

ACDFTerm& ACDFTerm::minimal(const PropDNF & cstt, bool midpro) {
    // cout << "before minimal =====================================" << endl;
    // print();
    // 1. minimal DNF
    propDNF = propDNF.minimal();
    for (map<string, ACDFList>::iterator cover = covers.begin();
    cover != covers.end(); ++cover) {
        // 2. minimal cover
        cover->second = cover->second.minimal(cstt, false, midpro);
    }
    // cout << "after minimal =====================================" << endl;
    // print();
    return *this;
}

void ACDF::show(ofstream & out, size_t indent) const {
    size_t i = 1;
    for (list<ACDFTerm>::const_iterator it = acdf_terms.begin();
    it != acdf_terms.end(); ++it) {
        for (size_t i = 0; i < indent; ++i) out << ' ';  // indent
        out << "ACDFTerm " << i++ << ":" << endl;
        it->show(out, indent+2);
    }
}

void ACDF::print(size_t indent) const {
    size_t i = 1;
    for (list<ACDFTerm>::const_iterator it = acdf_terms.begin();
    it != acdf_terms.end(); ++it) {
        for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
        cout << "ACDFTerm " << i++ << ":" << endl;
        it->print(indent+2);
    }
}

/*
 * Author: Frank
 * 
 * This function determins if a ACDF entails the complementation of another ACDF
 */
bool ACDF::neg_entails(const ACDF & acdf, const PropDNF & cstt, bool try_goal, int* value) const {
    for (list<ACDFTerm>::const_iterator acdf_term1 = acdf_terms.begin();
    acdf_term1 != acdf_terms.end(); ++acdf_term1) {
        for (list<ACDFTerm>::const_iterator acdf_term2 = acdf.acdf_terms.begin();
        acdf_term2 != acdf.acdf_terms.end(); ++acdf_term2) {
            if (!acdf_term1->neg_entails(*acdf_term2, cstt, try_goal, value)) {
                return false;
            } else if (try_goal) {
                // (*value)++;
            }
        }
    }
    return true;
}

bool ACDF::strong_entails(const ACDF & acdf, const PropDNF & cstt) const {
    // cout << "ACDF strong entails  ```````````````````" << endl;
    // print();
    // cout << "try entail  ````````````" << endl;
    // acdf.print();
    for (list<ACDFTerm>::const_iterator acdf_term1 = acdf_terms.begin();
    acdf_term1 != acdf_terms.end(); ++acdf_term1) {
        bool found = false;
        for (list<ACDFTerm>::const_iterator acdf_term2 = acdf.acdf_terms.begin();
        acdf_term2 != acdf.acdf_terms.end(); ++acdf_term2) {
            if (acdf_term1->strong_entails(*acdf_term2, cstt))
                found = true;
        }
        if (!found) return false;
    }
    // cout << "strong entail success  ````````````" << endl;
    return true;
}

bool ACDF::equals(const ACDF & acdf, const PropDNF & cstt) const {
    return strong_entails(acdf, cstt) && acdf.strong_entails(*this,cstt);
}

bool ACDF::valid() const {
    // return false;

    PropDNF p;
    ACDF tmp_acdf = *this;
    tmp_acdf = tmp_acdf.minimal(p);
    // cout << "This ACDF is valid ?????????" << endl;
    // tmp_acdf.print();
    bool exist_cover = false;
    set<string> all_atoms;
    for (list<ACDFTerm>::const_iterator term1 = tmp_acdf.acdf_terms.begin();
    term1 != tmp_acdf.acdf_terms.end(); ++term1) {
        if (term1->valid()) return true;
        if (!term1->covers.empty()) {
            exist_cover = true;
            break;
        }
        set<string> one_term_atoms = term1->propDNF.get_total_literals();
        all_atoms.insert(one_term_atoms.begin(), one_term_atoms.end());
    }

    // for very sepecific case: Cover{ø}, Cover{¬ø}, Cover{ø,¬ø}
    // if (exist_cover) {
    //     if (acdf_terms.size() == 3) {
    //         bool is_true = true;
    //         for (list<ACDFTerm>::const_iterator term = acdf_terms.begin();
    //         term != acdf_terms.end(); ++term) {
    //             if (!term->propDNF.empty()) {
    //                 is_true = false;
    //                 break;
    //             }
    //             for (map<string, ACDFList>::const_iterator cover = term->covers.begin();
    //             cover != term->covers.end(); ++cover) {
    //                 if (!(cover->second.acdf_terms.size() == 1) && !(cover->second.acdf_terms.size() == 2)) {
    //                     is_true = false;
    //                     break;
    //                 }
    //             }
    //         }
    //         if (is_true) {
    //             // print();
    //             // cout << "this is valid --=-=-=-=--=-=-" << endl;
    //             return true;
    //         }
    //     }
    // }

    // for (set<string>::const_iterator s = all_atoms.begin(); s != all_atoms.end(); ++s)
    //     cout << *s << " ";
    // cout << endl;

    PropDNF modals;
    for (list<ACDFTerm>::const_iterator term1 = tmp_acdf.acdf_terms.begin();
    term1 != tmp_acdf.acdf_terms.end(); ++term1) {
        PropDNF p; p.prop_terms = term1->propDNF.get_modals(all_atoms);
        modals = modals.merge(p);
    }
    modals = modals.minimal();
    // modals.print();
    // cout << pow(2.0, (double)all_atoms.size()) << endl;
    bool valid = modals.size() == pow(2.0, (double)all_atoms.size());
    // if (valid) cout << "valid!!!" << endl;
    return valid;
}

vector<ACDF> ACDF::epistemic_prog(const EpisAction & epis_action, const PropDNF & cstt) const {
    // cout << epis_action.name << endl;
    vector<ACDF> updated_acdf_terms;

    // positive and negative updated result from epistemic progression
    updated_acdf_terms.push_back(revision(epis_action.pos_res, cstt).minimal(cstt));
    updated_acdf_terms.push_back(revision(epis_action.neg_res, cstt).minimal(cstt));
    return updated_acdf_terms;
}

ACDF ACDF::ontic_prog(const OnticAction & ontic_action, const PropDNF & cstt) const {
    // cout << ontic_action.name << endl;
    ACDF updated_kb = *this;
    vector<ConEffect> entailed_effects;
    for (vector<ConEffect>::const_iterator effect = ontic_action.con_eff.begin(); \
    effect != ontic_action.con_eff.end(); ++effect) {
        if (neg_entails(effect->condition, cstt)) {
            entailed_effects.push_back(*effect);
        }
    }
    for (vector<ConEffect>::const_iterator entailed_effect = entailed_effects.begin(); \
    entailed_effect != entailed_effects.end(); ++entailed_effect) {
        switch (ontic_action.category) {
            case ONTIC:
            case COMMUNICATION:
                updated_kb = updated_kb.update(entailed_effect->effect, cstt).minimal(cstt);
                break;
            case OBSERVATION:
            case SENSING:
                updated_kb = updated_kb.revision(entailed_effect->effect, cstt).minimal(cstt);
                break;
            default:
                break;
        }

    }
    return updated_kb;
}

ACDF ACDF::revision(const ACDF & acdf, const PropDNF & cstt) const {
// cout << "ACDF ```````````````````" << endl;
// print();
// cout << "revision another ACDF ```````````````````" << endl;
// acdf.print();
    ACDF new_acdf1, new_acdf2;
    bool found_consis = false;
    for (list<ACDFTerm>::const_iterator acdf_term1 = acdf_terms.begin();
    acdf_term1 != acdf_terms.end(); ++acdf_term1) {
        for (list<ACDFTerm>::const_iterator acdf_term2 = acdf.acdf_terms.begin();
        acdf_term2 != acdf.acdf_terms.end(); ++acdf_term2) {
            bool consis = !(acdf_term1->group(*acdf_term2).unsatisfiable());
            ACDFTerm revisioned_term;
            if (!found_consis) {
                revisioned_term = acdf_term1->revision(*acdf_term2, cstt);
                if (consis) {
                    new_acdf1.acdf_terms.push_back(revisioned_term);
                    found_consis = true;
                }
                new_acdf2.acdf_terms.push_back(revisioned_term);
            } else {
                if (consis)
                    new_acdf1.acdf_terms.push_back(acdf_term1->revision(*acdf_term2, cstt));
            }
        }
    }
// cout << "get new ```````````````````" << endl;
// if (exist) cout << "````` exist `````` " << endl;
// else cout << "````` not exist `````` " << endl;
// (exist ? new_acdf1 : new_acdf2).print();
    return found_consis ? new_acdf1 : new_acdf2;
}

ACDF ACDF::update(const ACDF & acdf, const PropDNF & cstt) const {
    // cout << "ACDF ```````````````````" << endl;
    // print();
    // cout << "update another ACDF ```````````````````" << endl;
    // acdf.print();
    ACDF new_acdf;
    for (list<ACDFTerm>::const_iterator acdf_term = acdf_terms.begin(); \
    acdf_term != acdf_terms.end(); ++acdf_term)
        new_acdf = new_acdf.merge(acdf_term->update(acdf, cstt));
    // cout << "get ````````````````````" << endl;
    // new_acdf.print();
    return new_acdf;
}

ACDF ACDF::involve(const PropDNF & prop_dnf) const {
    ACDF new_acdf;
    for (list<ACDFTerm>::const_iterator term1 = acdf_terms.begin();
    term1 != acdf_terms.end(); ++term1) {
        new_acdf.acdf_terms.push_back(term1->involve(prop_dnf));
    }
    return new_acdf;
}

ACDF ACDF::group(const ACDF & acdf) const {
    ACDF new_acdf;
    for (list<ACDFTerm>::const_iterator term1 = acdf_terms.begin();
    term1 != acdf_terms.end(); ++term1) {
        for (list<ACDFTerm>::const_iterator term2 = acdf.acdf_terms.begin();
        term2 != acdf.acdf_terms.end(); ++term2) {
            new_acdf.acdf_terms.push_back(term1->group(*term2));
        }
    }
    return new_acdf;
}

ACDF ACDF::merge(const ACDF & acdf) const {
    ACDF new_acdf;
    for (list<ACDFTerm>::const_iterator term = acdf_terms.begin();
    term != acdf_terms.end(); ++term)
        new_acdf.acdf_terms.push_back(*term);
    for (list<ACDFTerm>::const_iterator term = acdf.acdf_terms.begin();
    term != acdf.acdf_terms.end(); ++term)
        new_acdf.acdf_terms.push_back(*term);
    return new_acdf;
}

/*
 * Determine where a ACDF inside a Cover is satisfiable
 * Notice: once a element(ACDFTerm) inside a Cover is unsatisfiable,
 *         it can entail other terms, so we will remove other terms
 *         firstly, then this ACDF is unsatisfiable too. This case is
 *         different from the outmost layer ACDFTerm, because we don't
 *         do minimal for the outmost layer.
 */
bool ACDF::unsatisfiable() const {
    for (list<ACDFTerm>::const_iterator term = acdf_terms.begin();
    term != acdf_terms.end(); ++term) {
        if (term->unsatisfiable())
            return true;
    }
    return false;
}

bool ACDF::objective() const {
    for (list<ACDFTerm>::const_iterator term = acdf_terms.begin();
    term != acdf_terms.end(); ++term) {
        if (term->valid()) return false;
        if (term->covers.size() != 0) return false;
    }
    return true;
}

bool ACDF::obj_consistent(const ACDF & acdf, const PropDNF & cstt) const {
    for (list<ACDFTerm>::const_iterator term1 = acdf_terms.begin();
    term1 != acdf_terms.end(); ++term1)
        for (list<ACDFTerm>::const_iterator term2 = acdf.acdf_terms.begin();
        term2 != acdf.acdf_terms.end(); ++term2)
            if (term1->propDNF.group(term2->propDNF).consistent())
                return true;
    return false;
}

ACDF ACDF::negation_as_acdf(const PropDNF & cstt) const {
    ACDF new_acdf;
    for (list<ACDFTerm>::const_iterator term = acdf_terms.begin();
    term != acdf_terms.end(); ++term) {
        new_acdf = new_acdf.group(term->negation_as_acdf(cstt));
    }
    return new_acdf.minimal(cstt);
}

/*
 * Author: Frank
 * minimal algos, remove the term that can be implied by other terms
 */
ACDF& ACDF::minimal(const PropDNF & cstt, bool outmost_layer, bool midpro) {
    PropDNF empty_dnf;
    // cout << "before minimal =====================================" << endl;
    // print();
    // 1. remove inconsistent terms and minimal others
    for (list<ACDFTerm>::iterator term = acdf_terms.begin();
    term != acdf_terms.end(); ) {
        *term = term->minimal(empty_dnf, midpro);
        if (term->empty() || term->unsatisfiable()) {
            term = acdf_terms.erase(term);
        }
        else {
            ++term;
        }
    }
    // cout << "middle minimal =====================================" << endl;
    // print();
    // 2. remove terms that can be entailed by other terms
    for (list<ACDFTerm>::iterator term1 = acdf_terms.begin();
    term1 != acdf_terms.end(); ) {
        bool is_delete = false;
        for (list<ACDFTerm>::iterator term2 = acdf_terms.begin();
        term2 != acdf_terms.end(); ++term2) {
// cout << "**********************************" << endl;
// cout << (outmost_layer ? "outmost" : "not outmost") << endl;
// term2->print();
// cout << " strong entails ******************" << endl;
// term1->print();
            // if (term1 != term2 && ((!(outmost_layer||midpro) && term2->strong_entails(*term1, cstt))
            // || ((outmost_layer||midpro) && term2->strong_entails(*term1, cstt) &&
                // term1->strong_entails(*term2, cstt))) ) {
            if (term1 != term2 && ((term1->objective() && term2->objective() &&
            term1->strong_entails(*term2, empty_dnf)) || (term2->strong_entails(*term1, empty_dnf)
            && term1->strong_entails(*term2, empty_dnf))) ) {
                // cout << " ------------ term 2 can strong entails term1 ******************" << endl;

                is_delete = true;
                // cout << "bad term =====================================" << endl;
                // term1->print();
                term1 = acdf_terms.erase(term1);
                break;
            }
                // cout << " ------------ term 2 can't' strong entails term1 ******************" << endl;
                // cout << "**********************************" << endl;
        }
        if (!is_delete)
            ++term1;
    }
    // cout << "aafter minimal =====================================" << endl;
    // print();
    return *this;
}

void ACDFList::show(ofstream & out, size_t indent) const {
    size_t i = 1;
    for (list<ACDF>::const_iterator it = acdfs.begin();
    it != acdfs.end(); ++it) {
        for (size_t i = 0; i < indent; ++i) out << ' ';  // indent
        out << "ACDF " << i++ << ":" << endl;
        it->show(out, indent+2);
    }
}

void ACDFList::print(size_t indent) const {
    size_t i = 1;
    for (list<ACDF>::const_iterator it = acdfs.begin();
    it != acdfs.end(); ++it) {
        for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
        cout << "ACDF " << i++ << ":" << endl;
        it->print(indent+2);
    }
}

ACDF ACDFList::all_in_one() const {
    ACDF new_acdf;
    for (list<ACDF>::const_iterator acdf = acdfs.begin();
    acdf != acdfs.end(); ++acdf) {
        new_acdf = new_acdf.merge(*acdf);
    }
    return new_acdf;
}

ACDFList& ACDFList::minimal(const PropDNF & cstt, bool outmost_layer, bool midpro) {
// cout << "before minimal =====================================" << endl;
// print();
    // 1. remove inconsistent acdfs and minimal others
    for (list<ACDF>::iterator acdf = acdfs.begin();
    acdf != acdfs.end(); ) {
        *acdf = acdf->minimal(cstt, midpro);
        if (acdf->empty() || acdf->unsatisfiable()) {
            acdf = acdfs.erase(acdf);
        }
        else {
            ++acdf;
        }
    }
    // 2. remove acdfs that can be entailed by other acdfs
    for (list<ACDF>::iterator acdf1 = acdfs.begin();
    acdf1 != acdfs.end(); ) {
        bool is_delete = false;
        for (list<ACDF>::iterator acdf2 = acdfs.begin();
        acdf2 != acdfs.end(); ++acdf2) {
            if (acdf1 != acdf2 && (acdf2->strong_entails(*acdf1, cstt) &&
                acdf1->strong_entails(*acdf2, cstt)) ) {
                // cout << " ------------ acdf 2 can strong entails acdf1 ******************" << endl;

                is_delete = true;
                // cout << "bad term =====================================" << endl;
                // acdf1->print();
                acdf1 = acdfs.erase(acdf1);
                break;
            }
                // cout << " ------------ acdf 2 can't' strong entails acdf1 ******************" << endl;
                // cout << "**********************************" << endl;
        }
        if (!is_delete)
            ++acdf1;
    }
// cout << "aafter minimal =====================================" << endl;
// print();
// cout << "====================================================" << endl;
    return *this;
}

/*
 * Cover Merge Algo
 */
ACDFList ACDFList::group(const ACDFList & acdflist) const {
// cout << "ACDFList ```````````````````" << endl;
// print();
// cout << "group another ACDFList ```````````````````" << endl;
// acdflist.print();
    ACDFList new_acdflist;
    if (empty()) return acdflist;
    if (acdflist.empty()) return *this;

    if (acdflist.all_in_one().valid()) new_acdflist = *this;
    else {
        // Set 1
        for (list<ACDF>::const_iterator acdf = acdfs.begin();
        acdf != acdfs.end(); ++acdf) {
            new_acdflist.acdfs.push_back(acdf->group(acdflist.all_in_one()));
        }
    }
    // cout << "half get ````````````````````" << endl;
    // new_acdf.print();
    if (all_in_one().valid()) new_acdflist = new_acdflist.merge(acdflist);
    else {
        // Set 2
        for (list<ACDF>::const_iterator acdf = acdflist.acdfs.begin();
        acdf != acdflist.acdfs.end(); ++acdf) {
            new_acdflist.acdfs.push_back(acdf->group(all_in_one()));
        }
    }
// cout << "get new ACDFList ````````````````````" << endl;
// new_acdflist.print();
    return new_acdflist;
}

ACDFList ACDFList::merge(const ACDFList & acdflist) const {
    ACDFList new_acdflist = *this;
    for (list<ACDF>::const_iterator acdf = acdflist.acdfs.begin();
    acdf != acdflist.acdfs.end(); ++acdf) {
        new_acdflist.acdfs.push_back(*acdf);
    }
    return new_acdflist;
}

ACDFList ACDFList::involve(const PropDNF & prop_dnf) const {
    ACDFList new_acdflist;
    for (list<ACDF>::const_iterator acdf = acdfs.begin();
    acdf != acdfs.end(); ++acdf) {
        new_acdflist.acdfs.push_back(acdf->involve(prop_dnf));
    }
    return new_acdflist;
}
