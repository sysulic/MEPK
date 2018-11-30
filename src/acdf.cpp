#include "define.h"
#include "acdf.h"



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
    propDNF.show(out);
    out << endl;
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
    if (!propDNF.dnf.empty()){
        propDNF.print(indent);
        cout << endl;
    }
    for (map<string, ACDFList>::const_iterator it = covers.begin();
            it != covers.end(); ++it) {
        for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
        cout << it->first << " :" << endl;
        it->second.print(indent+2);
    }
}

bool ACDFTerm::empty() const {
    return propDNF.isEmpty() && covers.empty() && !valid();
}

bool ACDFTerm::neg_entails(const ACDF & acdf, const PropDNF & cstt, bool try_goal, int* value) const {
    for(list<ACDFTerm>::const_iterator post_term = acdf.acdf_terms.begin();
    post_term != acdf.acdf_terms.end(); ++post_term) {
        if (neg_entails(*post_term, cstt, try_goal, value)) {
            return false;
        } else if (try_goal) {
            (*value)++;
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

    if (!propDNF.conjunction(acdf_term.propDNF).conjunction(cstt).isSatisfiable()) {
        if (try_goal) (*value)++;
    // cout << "success 1" << endl;
        return true;
    }

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
                    (*value)++;
                }
            }
            if (flag) {
                // cout << "success 2" << endl;
                return true;
            }
        }

        for (list<ACDF>::const_iterator acdf2 = acdflist_tmp.acdfs.begin();
            acdf2 != acdflist_tmp.acdfs.end(); ++acdf2) {
            bool flag = true;
            for (list<ACDF>::const_iterator acdf1 = cover1->second.acdfs.begin();
            acdf1 != cover1->second.acdfs.end(); ++acdf1) {
                if (!acdf1->neg_entails(*acdf2, cstt, try_goal, value)) {
                    flag = false;
                    break;
                } else if (try_goal) {
                    (*value)++;
                }
            }
            if (flag) {
                // cout << "success 3" << endl;
                return true;
            }
        }
    }
        // cout << "fail =====================================" << endl;

    return false;
}

bool ACDFTerm::strong_entails(const ACDFTerm & acdf_term, const PropDNF & cstt) const {
    if (valid() || acdf_term.valid()) return ((valid() && acdf_term.valid()) ? true : false);

    if (!acdf_term.propDNF.isEmpty() && !propDNF.conjunction(cstt).canEntail(acdf_term.propDNF)) return false;

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
    dnf_term.propDNF = propDNF.negation();
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
    new_term.propDNF = propDNF.conjunction(empty_dnf).minimal().revision(acdf_term.propDNF.conjunction(cstt).minimal());
    // revision all agent-covers of those agents in left
    bool two_consis = !(conjunction(acdf_term).minimal(cstt).unsatisfiable());
    for (map<string, ACDFList>::const_iterator cover = covers.begin(); \
        cover != covers.end(); ++cover) {
        if (acdf_term.covers.find(cover->first) == acdf_term.covers.end()) {
            new_term.covers[cover->first] = cover->second;
        } else {
            if (two_consis) {
    // cout << "two term consistent ? ```````````````````" << endl;
    // conjunction(acdf_term).minimal(cstt).print();
                // case 3:
    // cout << "inconsistent" << endl;
                // calculate \Phi^*
                ACDFList acdflist1, acdflist2;  // 1: consistent revision; 2: all
                bool found_consis = false;
                for (list<ACDF>::const_iterator acdf1 = cover->second.acdfs.begin();
                acdf1 != cover->second.acdfs.end(); ++acdf1) {
                    for (list<ACDF>::const_iterator acdf2 = acdf_term.covers.at(cover->first).acdfs.begin();
                    acdf2 != acdf_term.covers.at(cover->first).acdfs.end(); ++acdf2) {
                        bool consis = !(acdf1->conjunction(*acdf2).unsatisfiable());
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
                new_term.covers[cover->first] = tmp_acdflist.disjunction(tmp_acdflist2);
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
    new_term = new_term.minimal(cstt);
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
        bool consis = !(conjunction(term->conjunction(cstt)).unsatisfiable());
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
    new_term.propDNF = propDNF.conjunction(empty_dnf).minimal().update(acdf_term.propDNF.conjunction(cstt).minimal());
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
            new_term.covers[cover->first] = acdflist.disjunction(acdflist2);
        }
    }
    // add those agent-covers appear in the right, but not in left
    for (map<string, ACDFList>::const_iterator cover = acdf_term.covers.begin(); \
    cover != acdf_term.covers.end(); ++cover) {
        if (covers.find(cover->first) == covers.end()) {
            new_term.covers[cover->first] = cover->second;
        }
    }
    new_term = new_term.minimal(cstt);
// cout << "get ````````````````````" << endl;
// new_term.print();
    return new_term;
}


ACDFTerm ACDFTerm::conjunction(const ACDFTerm & acdf_term) const {
// cout << "Term ```````````````````" << endl;
// print();
// cout << "group with ````````````" << endl;
// acdf_term.print();
    if (valid()) return acdf_term;
    if (acdf_term.valid()) return *this;
    ACDFTerm new_term = *this;
    new_term.propDNF = propDNF.conjunction(acdf_term.propDNF);
    for (map<string, ACDFList>::const_iterator cover = acdf_term.covers.begin();
        cover != acdf_term.covers.end(); ++cover)
        if (new_term.covers.find(cover->first) == new_term.covers.end())
            new_term.covers[cover->first] = cover->second;
        else
            new_term.covers[cover->first] =
                new_term.covers[cover->first].conjunction(cover->second);
// cout << "get new term ````````````" << endl;
// new_term.print();
    return new_term;
}

ACDFTerm ACDFTerm::conjunction(const PropDNF & prop_dnf) const {
    ACDFTerm new_term = *this;  // in case that K_a in *this, not in latter
    // PropDNF
    new_term.propDNF = propDNF.conjunction(prop_dnf);
    if (!prop_dnf.isEmpty()) new_term.is_true = false;
    return new_term;
}

ACDFTerm ACDFTerm::involve(const PropDNF & prop_dnf) const {
    ACDFTerm new_term;  // in case that K_a in *this, not in latter
    // PropDNF
    new_term.propDNF = propDNF.conjunction(prop_dnf);
    for (map<string, ACDFList>::const_iterator cover = covers.begin();
    cover != covers.end(); ++cover) {
        new_term.covers[cover->first] = cover->second.involve(prop_dnf);
    }
    return new_term;
}

bool ACDFTerm::unsatisfiable() const {
    // cout << "check satisfiable =-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    // print();
    if (!propDNF.isEmpty() && !propDNF.isSatisfiable()) return true;
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

ACDFTerm& ACDFTerm::minimal(const PropDNF & cstt) {
    // cout << "before minimal =====================================" << endl;
    // print();
    // 1. minimal DNF
    propDNF = propDNF.minimal();
    for (map<string, ACDFList>::iterator cover = covers.begin();
    cover != covers.end(); ++cover) {
        // 2. minimal cover
        cover->second = cover->second.minimal(cstt);
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
                (*value)++;
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

return false;

// cout << "second ?????????" << endl;
    PropDNF modals;
    for (list<ACDFTerm>::const_iterator term1 = tmp_acdf.acdf_terms.begin();
    term1 != tmp_acdf.acdf_terms.end(); ++term1) {
        PropDNF p; p.dnf = term1->propDNF.get_modals(all_atoms);
        modals = modals.disjunction(p);
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

ACDF ACDF::ontic_prog(const OntiAction & ontic_action, const PropDNF & cstt) const {
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
            bool consis = !(acdf_term1->conjunction(*acdf_term2).unsatisfiable());
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
        new_acdf = new_acdf.disjunction(acdf_term->update(acdf, cstt));
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

ACDF ACDF::conjunction(const ACDF & acdf) const {
    ACDF new_acdf;
    for (list<ACDFTerm>::const_iterator term1 = acdf_terms.begin();
    term1 != acdf_terms.end(); ++term1) {
        for (list<ACDFTerm>::const_iterator term2 = acdf.acdf_terms.begin();
        term2 != acdf.acdf_terms.end(); ++term2) {
            new_acdf.acdf_terms.push_back(term1->conjunction(*term2));
        }
    }
    return new_acdf;
}

ACDF ACDF::disjunction(const ACDF & acdf) const {
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
        if (!term->objective()) return false;
    }
    return true;
}

bool ACDF::obj_consistent(const ACDF & acdf, const PropDNF & cstt) const {
    for (list<ACDFTerm>::const_iterator term1 = acdf_terms.begin();
    term1 != acdf_terms.end(); ++term1)
        for (list<ACDFTerm>::const_iterator term2 = acdf.acdf_terms.begin();
        term2 != acdf.acdf_terms.end(); ++term2)
            if (term1->propDNF.conjunction(term2->propDNF).isSatisfiable())
                return true;
    return false;
}

ACDF ACDF::negation_as_acdf(const PropDNF & cstt) const {
    ACDF new_acdf;
    for (list<ACDFTerm>::const_iterator term = acdf_terms.begin();
    term != acdf_terms.end(); ++term) {
        new_acdf = new_acdf.conjunction(term->negation_as_acdf(cstt));
    }
    return new_acdf.minimal(cstt);
}

/*
 * Author: Frank
 * minimal algos, remove the term that can be implied by other terms
 */
ACDF& ACDF::minimal(const PropDNF & cstt) {
    PropDNF empty_dnf;
    // cout << "before minimal =====================================" << endl;
    // print();
    // 1. remove inconsistent terms and minimal others
    for (list<ACDFTerm>::iterator term = acdf_terms.begin();
    term != acdf_terms.end(); ) {
        *term = term->minimal(empty_dnf);
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
        new_acdf = new_acdf.disjunction(*acdf);
    }
    return new_acdf;
}

ACDFList& ACDFList::minimal(const PropDNF & cstt) {
// cout << "before minimal =====================================" << endl;
// print();
    // 1. remove inconsistent acdfs and minimal others
    for (list<ACDF>::iterator acdf = acdfs.begin();
    acdf != acdfs.end(); ) {
        *acdf = acdf->minimal(cstt);
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
ACDFList ACDFList::conjunction(const ACDFList & acdflist) const {
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
            new_acdflist.acdfs.push_back(acdf->conjunction(acdflist.all_in_one()));
        }
    }
// cout << "half get ````````````````````" << endl;
// new_acdflist.print();
    if (all_in_one().valid()) new_acdflist = new_acdflist.disjunction(acdflist);
    else {
        // Set 2
// cout << "set 2 ````````````````````" << endl;
        for (list<ACDF>::const_iterator acdf = acdflist.acdfs.begin();
        acdf != acdflist.acdfs.end(); ++acdf) {
            new_acdflist.acdfs.push_back(acdf->conjunction(all_in_one()));
        }
    }
// cout << "get new ACDFList ````````````````````" << endl;
// new_acdflist.print();
    return new_acdflist;
}

ACDFList ACDFList::disjunction(const ACDFList & acdflist) const {
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

int ACDFTerm::kb_size() const {
    int s = propDNF.size(); for (auto& a: covers) s+= a.second.kb_size(); return s;
}

int ACDF::kb_size() const {
    int s = 0; for (auto& a: acdf_terms) s+= a.kb_size(); return s;
}

int ACDFList::kb_size() const {
    int s = 0; for (auto& a: acdfs) s+= a.kb_size(); return s;
}

