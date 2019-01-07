#include "adnf.h"
#include "define.h"

using namespace std;

// for latex
std::string logicAnd = " & ";
std::string logicOr = " | ";
std::string logicNot = "~";

PropTerm::PropTerm(int _len, AtomType t) {
	len = _len;
	literal.resize(len);
	for (int i = 0; i < len; i++) {
		if (t==TRUE)
			literal[i] = TRUE;
		else if (t==FALSE)
			literal[i] = FALSE;
		else if (t==UNSAT)
			literal[i] = UNSAT;
		else
			literal[i] = UNDEFINED;
	}
}

PropTerm::~PropTerm() {
	literal.clear();
}

bool PropTerm::find(const string & atom) const {
    return literal[findAtomsByName[atom]]==TRUE || literal[findAtomsByName[atom]]==FALSE;
}

bool PropTerm::isSatisfiable() const {
	for (int i = 0; i < len; i++) {
		if (literal[i] == UNSAT) {
			return false;
		}
	}
	return true;
}

bool PropTerm::canEntail(const PropTerm& pt) const {
	assert(len == pt.len);
	if (!isSatisfiable()) return true;
	for (int i = 0; i < len; i++) {
		if (pt.literal[i] == TRUE || pt.literal[i] == FALSE) {
			if (pt.literal[i] != UNDEFINED &&
				literal[i] != pt.literal[i]) return false;
		}
	}
	return true;
}

PropTerm PropTerm::conjunction(const PropTerm& pt) const {
	assert(len == pt.len);
	PropTerm ans(len);
	for (int i = 0; i < len; i++) {
		if (literal[i] == UNSAT || pt.literal[i] == UNSAT
			|| (literal[i] == TRUE && pt.literal[i] == FALSE)
			|| (literal[i] == FALSE && pt.literal[i] == TRUE)) 
			ans.literal[i] = UNSAT;
		else if (literal[i] == UNDEFINED) ans.literal[i] = pt.literal[i];
		else if (pt.literal[i] == UNDEFINED) ans.literal[i] = literal[i];
		else ans.literal[i] = literal[i];
	}
	return ans;
}

PropTerm PropTerm::minimal() {
	return *this;
}

vector<PropTerm> PropTerm::negation() const {
	vector<PropTerm> ans;
	if (!isSatisfiable()) {
		ans.push_back(PropTerm(len));
	}
	else {
		for (int i = 0; i < len; i++) {
			if (literal[i] == UNDEFINED) continue;
			PropTerm tpt(len);
			tpt.literal[i] = (literal[i] == TRUE) ? FALSE : TRUE;
			ans.push_back(tpt);
		}
	}
	return ans;
}

PropDNF PropTerm::negation_as_dnf() const {
	PropDNF ans;
	if (!isSatisfiable()) {
		ans.dnf.push_back(PropTerm(len));
	}
	else {
		for (int i = 0; i < len; i++) {
			if (literal[i] == UNDEFINED) continue;
			PropTerm tpt(len);
			tpt.literal[i] = (literal[i] == TRUE) ? FALSE : TRUE;
			ans.dnf.push_back(tpt);
		}
	}
	return ans;

}

set<string> PropTerm::getTotalLiterals() const {
	set<string> ans;
	for (int i = 0; i < len; i++) {
		if (literal[i] == TRUE || literal[i] == FALSE) {
			ans.insert(findAtomsByIndex[i]);
		}
	}
	return ans;
}

bool PropTerm::operator==(const PropTerm& rhs) const {
	return literal==rhs.literal;
}

void PropTerm::print() const {
	if (!isSatisfiable()) cout << "False";
	else {
		bool flag = true;
		for (int i = 0; i < len; i++) {
			if (literal[i] == UNDEFINED) continue;
			cout << ((flag) ? "" : logicAnd)
				<< ((literal[i] == TRUE) ? "" : logicNot) << findAtomsByIndex[i];
			flag = false;
		}
		cout << ((flag) ? "True" : "");
	}
}

void PropTerm::show(ofstream& os) const {
	if (!isSatisfiable()) os << "(False)";
	else {
		bool flag = true;
		for (int i = 0; i < len; i++) {
			if (literal[i] == UNDEFINED) continue;
			os << ((flag) ? "(" : logicAnd)
				<< ((literal[i] == TRUE) ? "" : logicNot) << findAtomsByIndex[i];
			flag = false;
		}
		os << ((flag) ? "(True)" : ")");
	}
}

PropDNF::PropDNF(const PropDNF& pd) {
	for (auto ite = pd.dnf.begin(); ite != pd.dnf.end(); ite++) {
		dnf.push_back(*ite);
	}
}

PropDNF::~PropDNF() {
	dnf.clear();
}

bool PropDNF::isSatisfiable() const {
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		if (ite->isSatisfiable()) return true;
	}
	return false;
}

bool PropDNF::canEntail(const PropDNF& pd) const {
	if(dnf.empty() && pd.dnf.empty()) return true;
	if(dnf.empty()) return false;
	if(pd.dnf.empty()) return true;
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		bool canEntail = false;
		for (auto ite2 = pd.dnf.begin(); ite2 != pd.dnf.end(); ite2++) {
			if (ite1->canEntail(*ite2)) {
				canEntail = true;
				break;
			}
		}
		if (!canEntail) return false;
	}
	return true;
}

bool PropDNF::isEqual(const PropDNF& pd) const {
	return this->canEntail(pd) && pd.canEntail(*this);
}

bool PropDNF::isEmpty() const {
	return dnf.empty();
}

PropDNF PropDNF::conjunction(const PropTerm& pt) const {
	if (dnf.empty()) {
		PropDNF res;
		res.dnf.push_back(pt);
		return res;
	}
	PropDNF res;
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		res.dnf.push_back(ite1->conjunction(pt));
	}
	return res.minimal();
}

PropDNF PropDNF::conjunction(const PropDNF& pd) const {
	if (dnf.empty()) return pd;
	if (pd.dnf.empty()) return *this;
	PropDNF ans;
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		for (auto ite2 = pd.dnf.begin(); ite2 != pd.dnf.end(); ite2++) {
			ans.dnf.push_back(ite1->conjunction(*ite2));
		}
	}
	return ans.minimal();
}

PropDNF PropDNF::disjunction(const PropDNF& pd) const {
	PropDNF ans(*this);
	ans.dnf.insert(ans.dnf.end(), pd.dnf.begin(), pd.dnf.end());
	return ans.minimal();
}

PropDNF PropDNF::minimal() {
	if(dnf.empty() || dnf.size() == 1) return *this;
	// remove the unsatisfiable term
	for (auto ite = dnf.begin(); ite != dnf.end();) {
		if (!ite->isSatisfiable()) ite = dnf.erase(ite);
		else ite++;
	}
	// Propositonal DNF is not satisifiable
	if(dnf.empty()) {
		PropTerm pt(atomNum);
		pt.literal[0] = UNSAT;
		dnf.push_back(pt);
	}
	// if pd1 entails pd2, remove pd1
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ) {
		bool flag = false;
		for (auto ite2 = dnf.begin(); ite2 != dnf.end(); ite2++) {
			if (ite1 == ite2) continue;
			if (ite1->canEntail(*ite2)) {
				flag = true;
				break;
			}
		}
		if (flag) ite1 = dnf.erase(ite1);
		else ite1++;
	}
	return *this;
}

PropDNF PropDNF::negation() const {
	PropDNF ans;
	vector<vector<PropTerm> > allTermNeg;
	// ~((p & q) | (p & r)) = ~(p & q) & ~(p & r)
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		allTermNeg.push_back(ite->negation());
	}
	// distribution
	for (size_t i = 0; i < allTermNeg.size(); i++) {
		if(allTermNeg[i].empty()) continue;
		if (ans.dnf.empty()) {
			for (size_t j = 0; j < allTermNeg[i].size(); j++) {
				ans.dnf.push_back(allTermNeg[i][j]);
			}
		}
		else {
			list<PropTerm>::iterator endIte = ans.dnf.end();
			endIte--;
			for (auto ite = ans.dnf.begin();; ite++) {
				for (size_t j = 1; j < allTermNeg[i].size(); j++) {
					PropTerm tpt = ite->conjunction(allTermNeg[i][j]);
					ans.dnf.push_back(tpt);
				}
				*ite = ite->conjunction(allTermNeg[i][0]);
				if (ite == endIte) break;
			}
		}
	}
	return ans.minimal();
}

PropDNF PropDNF::revision(const PropDNF& pd) {
// cout << "DNF 1:--------------------------------------" << endl;
// print();
// cout << "revised by DNF 2:--------------------------------------" << endl;
// pd.print();
	map<set<int>, PropDNF> min_wrt_revised;
	PropDNF result;
	bool exist_empty_min = false;
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		for (auto ite2 = pd.dnf.begin(); ite2 != pd.dnf.end(); ite2++) {
			PropTerm tpt(ite1->len);
			set<int> cur_diff = cover(*ite1, *ite2, tpt);
			if (*ite1 == *ite2) {
				exist_empty_min = true;
				result.dnf.push_back(tpt);
				continue;
			}
			if (min_wrt_revised.empty()) {
				PropDNF first_min_diff; first_min_diff.dnf.push_back(tpt);
				min_wrt_revised[cur_diff] = first_min_diff;
				continue;
			}
			bool new_min_added = true;  // new and update old
			bool new_diff_min = true;  // different new minimal
			int old_size = min_wrt_revised.size(), i = 0;
			for (map<set<int>, PropDNF>::iterator it = min_wrt_revised.begin(); i < old_size; i++) {
				set<int> min_diff = it->first;
				if (cur_diff == min_diff) {
					new_diff_min = false;
					min_wrt_revised[cur_diff].dnf.push_back(tpt);
					break;
				} else if (includes(min_diff.begin(), min_diff.end(), cur_diff.begin(), cur_diff.end())) {
					new_diff_min = false;
					// removing all supersets
					it = min_wrt_revised.erase(it);
					if (new_min_added) {	
						min_wrt_revised[cur_diff].dnf.clear();
						min_wrt_revised[cur_diff].dnf.push_back(tpt);
						new_min_added = false;
					}
				} else if (includes(cur_diff.begin(), cur_diff.end(), min_diff.begin(), min_diff.end())) {
					new_diff_min = false;
					break;
				} else {
					it++;
				}
			}
			if (new_diff_min) {
				PropDNF new_min_diff; new_min_diff.dnf.push_back(tpt);
				min_wrt_revised[cur_diff] = new_min_diff;
			}
		}
	}
	if (exist_empty_min) {
		return result;
	}
	// merge all min_wrt_revised
	for (auto & model : min_wrt_revised)
		result = result.disjunction(model.second);

// cout << "DNF result:--------------------------------------" << endl;
// result.print();
	return result.minimal();
}

PropDNF PropDNF::revision_cardinality(const PropDNF& pd) {
	int minDiff = INT_MAX;
	PropDNF ans;
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		for (auto ite2 = pd.dnf.begin(); ite2 != pd.dnf.end(); ite2++) {
			PropTerm tpt(ite1->len);
			int curDiff = cover(*ite1, *ite2, tpt).size();
			if (curDiff < minDiff) {
				minDiff = curDiff;
				ans.dnf.clear();
			}
			if (curDiff == minDiff) ans.dnf.push_back(tpt);
		}
	}
	return ans.minimal();
}

PropDNF PropDNF::update(const PropDNF& pd) {
// cout << "DNF 1:--------------------------------------" << endl;
// print();
// cout << "update by DNF 2:--------------------------------------" << endl;
// pd.print();
	PropDNF result;
	for (auto phi_i = dnf.begin(); phi_i != dnf.end(); phi_i++) {
		for (auto mu_j = pd.dnf.begin(); mu_j != pd.dnf.end(); mu_j++) {
			PropTerm tpt(phi_i->len);
			cover(*phi_i, *mu_j, tpt);
			PropDNF patch;
			PropTerm tmp_term(phi_i->len);
			int tmp_term_size = 1;
			for (auto mu_k = pd.dnf.begin(); mu_k != pd.dnf.end(); mu_k++) {
				if (mu_k->canEntail(diff(*mu_j, *phi_i))) continue;
				tmp_term_size = minus(*mu_k, *phi_i, *mu_j, tmp_term);
				if (tmp_term_size == 0) {
					// cout << "haha "<< endl;
					break;
				}
				patch = patch.conjunction(tmp_term.negation_as_dnf());
			}
			if (tmp_term_size != 0)
				result = result.disjunction(patch.conjunction(tpt));
		}
	}

// cout << "DNF result:--------------------------------------" << endl;
// result.print();
	return result.minimal();
}

PropDNF PropDNF::update_cardinality(const PropDNF& pd) {
	PropDNF updated_partial_models;
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		int min_diff = INT_MAX;
		list<PropTerm> tptl;
		for (auto ite2 = pd.dnf.begin(); ite2 != pd.dnf.end(); ite2++) {
			PropTerm tpt(ite1->len);
			int cur_diff = cover(*ite1, *ite2, tpt).size();
			if (cur_diff < min_diff) {
				min_diff = cur_diff;
				tptl.clear();
			}
			if (cur_diff == min_diff) tptl.push_back(tpt);
		}
		updated_partial_models.dnf.insert(updated_partial_models.dnf.end(), tptl.begin(), tptl.end());
	}
	return updated_partial_models.minimal();
}

set<int> PropDNF::cover(const PropTerm& lpt, const PropTerm& rpt, PropTerm& apt) {
	set<int> prop_diff;  // return prop(Diff), apt is : rpt cover lpt
	for (int i = 0; i < lpt.len; i++) {
		if (lpt.literal[i] == UNDEFINED && rpt.literal[i] == UNDEFINED) continue;
		else if (lpt.literal[i] == UNDEFINED) {
			apt.literal[i] = rpt.literal[i];
		} else if (rpt.literal[i] == UNDEFINED) {
			apt.literal[i] = lpt.literal[i];
		} else {
			if (lpt.literal[i] != rpt.literal[i]) prop_diff.insert(i);
			apt.literal[i] = rpt.literal[i];
		}
	}
	return prop_diff;
}

PropTerm PropDNF::diff(const PropTerm& lpt, const PropTerm& rpt) {
	PropTerm diff(lpt.len);
	for (int i = 0; i < lpt.len; i++)
		if (lpt.literal[i] != UNDEFINED && rpt.literal[i] != UNDEFINED \
			&& lpt.literal[i] != rpt.literal[i])
			diff.literal[i] = lpt.literal[i];
	return diff;
}

int PropDNF::minus(const PropTerm& lpt, const PropTerm& rpt1, const PropTerm& rpt2, PropTerm& res) {
	// res = mu_k - (phi_i Union mu_j)
	res = lpt;
	int res_size = 0;
	for (int i = 0; i < lpt.len; i++)
		if (res.literal[i] != UNDEFINED) {
			if (lpt.literal[i] == rpt1.literal[i] || lpt.literal[i] == rpt2.literal[i] ) {
				res.literal[i] = UNDEFINED;
			} else {
				res_size++;
			}
		}
	return res_size;
}

void PropDNF::print(size_t indent) const {
    for (size_t i = 0; i < indent; ++i) cout << ' ';  // indent
	bool flag = true;
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		cout << ((flag) ? "(" : logicOr);
		ite->print();
		flag = false;
	}
	if(!flag) cout << ")";
	cout << endl;
}

void PropDNF::show(ofstream& os) const {
	bool flag = true;
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		os << ((flag) ? "(" : logicOr);
		ite->show(os);
		flag = false;
	}
	if(!flag) os << ")";
	os << endl;
}

set<string> PropDNF::get_total_literals() const {
    set<string> total_atoms;
    for (list<PropTerm>::const_iterator term = dnf.begin(); \
    term != dnf.end(); ++term) {
        set<string> part_atoms = term->getTotalLiterals();
        total_atoms.insert(part_atoms.begin(), part_atoms.end());
    }
    return total_atoms;
}

list<PropTerm> PropDNF::get_modals(const set<string> & total_atoms) const {
    list<PropTerm> modals = dnf;
    for (set<string>::const_iterator atom = total_atoms.begin(); \
        atom != total_atoms.end(); ++atom) {
        list<PropTerm>::const_iterator old_end = modals.end();
        // if prop_terms is empty at the beginning
        if (modals.empty()) {
            PropTerm tmp_term(findAtomsByIndex.size());  // initialize with length
            tmp_term.literal[findAtomsByName[*atom]] = TRUE;
            modals.push_back(tmp_term);
            tmp_term.literal[findAtomsByName[*atom]] = FALSE;
            modals.push_back(tmp_term);
            continue;
        }
        for (list<PropTerm>::iterator term = modals.begin(); \
            term != old_end; ++term) {
            if (!term->find(*atom)) {
                PropTerm new_term = *term;
                term->literal[findAtomsByName[*atom]] = TRUE;
                new_term.literal[findAtomsByName[*atom]] = FALSE;
                modals.push_back(new_term);
            }
        }
    }
    return modals;
}

KLTerm::KLTerm(const KLTerm& klt) {
	PPart = klt.PPart;
	KPart = klt.KPart;
	LPart = klt.LPart;
}

KLTerm::~KLTerm() {
	KPart.clear();
	LPart.clear();
}

bool KLTerm::isSatisfiable(const PropDNF& constraint) {
	// Prop part is satisfiable wrt constraint
	if (!PPart.conjunction(constraint).isSatisfiable()) return false;
	for (auto ite1 = KPart.begin(); ite1 != KPart.end(); ite1++) {
		// K part is satisfiable wrt constraint
		if (!(ite1->second).isSatisfiable(constraint)) return false;
		// L part does not exist
		if (LPart.find(ite1->first) == LPart.end()) continue;
		// L part is satisfiable wrt constraint
		for (auto ite2 = LPart[ite1->first].begin();
			ite2 != LPart[ite1->first].end(); ite2++) {
			if (!(ite1->second).conjunction(*ite2).isSatisfiable(constraint)) return false;
		}
	}
	return true;
}

bool KLTerm::isSatisfiable(KLTerm& klt, const PropDNF& constraint) {
	if(!klt.isSatisfiable(constraint)) return true;
	return this->conjunction(klt).isSatisfiable(constraint);
}

bool KLTerm::negEntail(KLTerm& klt, const PropDNF& constraint) {
	// Be careful! klt has been compiled into the negation form during compilation
	return !this->conjunction(klt).isSatisfiable(constraint);
}

bool KLTerm::strongEntail(KLTerm& klt, const PropDNF& constraint) {
	if(!this->isSatisfiable(constraint)) return true;
	if(!klt.isSatisfiable(constraint)) return false;
	// Prop part
	if (!PPart.conjunction(constraint).canEntail(klt.PPart)) return false;
	for (auto ite = klt.KPart.begin(); ite != klt.KPart.end(); ite++) {
		// Set of agents in klt is subset of that in *this
		if (KPart.find(ite->first) == KPart.end()) return false;
		// K part
		if (!KPart[ite->first].strongEntail(ite->second, constraint)) return false;
	}
	for (auto ite1 = klt.LPart.begin(); ite1 != klt.LPart.end(); ite1++) {
		// Set of agents in klt is subset of that in *this
		if (KPart.find(ite1->first) == KPart.end() &&
			LPart.find(ite1->first) == LPart.end()) return false;
		else if (KPart.find(ite1->first) == KPart.end()) {
			// K & L part
			for (auto ite2 = ite1->second.begin(); ite2 != ite1->second.end(); ite2++) {
				bool flag = false;
				for (auto ite3 = LPart[ite1->first].begin();
					ite3 != LPart[ite1->first].end(); ite3++) {
					if (ite3->strongEntail(*ite2, constraint)) {
						flag = true;
						break;
					}
				}
				if (!flag) return false;
			}
		}
		else if (LPart.find(ite1->first) == LPart.end()) {
			// K & L part
			for (auto ite2 = ite1->second.begin(); ite2 != ite1->second.end(); ite2++) {
				if (!KPart[ite1->first].strongEntail(*ite2, constraint)) return false;
			}
		}
		else {
			// K & L part
			for (auto ite2 = ite1->second.begin(); ite2 != ite1->second.end(); ite2++) {
				bool flag = false;
				for (auto ite3 = LPart[ite1->first].begin();
					ite3 != LPart[ite1->first].end(); ite3++) {
					if (KPart[ite1->first].conjunction(*ite3).strongEntail(*ite2, constraint)) {
						flag = true;
						break;
					}
				}
				if (!flag) return false;
			}
		}
	}
	return true;
}

bool KLTerm::strongEquivlent(KLTerm& klt, const PropDNF& constraint) {
	return this->strongEntail(klt, constraint) &&
		klt.strongEntail(*this, constraint);
}

bool KLTerm::isEmpty() {
	return PPart.isEmpty() && KPart.empty() && LPart.empty();
}

KLTerm KLTerm::minimal(const PropDNF& constraint) {
	PPart.minimal();
	for(auto ite = KPart.begin();ite != KPart.end();ite++) {
		ite->second.minimal(constraint);
	}
	for(auto ite1 = LPart.begin();ite1 != LPart.end();ite1++) {
		for(auto ite2 = ite1->second.begin();ite2 != ite1->second.end();ite2++) {
			ite2->minimal(constraint);
		}
		/*for(auto ite2 = ite1->second.begin();ite2 != ite1->second.end();) {
			bool eraseFlag = false;
			for(auto ite3 = ite1->second.begin();ite3 != ite1->second.end();ite3++) {
				if(ite2 == ite3) continue;
				if(ite3->strongEntail(*ite2, constraint)) {
					eraseFlag = true;
					break;
				}
			}
			if(eraseFlag) ite2 = ite1->second.erase(ite2);
			else ite2++;
		}*/
	}
	return *this;
}

KLTerm KLTerm::conjunction(KLTerm& klt) {
	KLTerm ans;
	// Prop part
	ans.PPart = PPart.conjunction(klt.PPart);
	// K part
	for (auto ite = KPart.begin(); ite != KPart.end(); ite++) {
		if (klt.KPart.find(ite->first) == klt.KPart.end()) {
			ans.KPart[ite->first] = ite->second;
		}
		else {
			ans.KPart[ite->first] = KPart[ite->first].conjunction(klt.KPart[ite->first]);
		}
	}
	for (auto ite = klt.KPart.begin(); ite != klt.KPart.end(); ite++) {
		if (KPart.find(ite->first) != KPart.end()) continue;
		ans.KPart[ite->first] = ite->second;
	}
	// L part
	for (auto ite = LPart.begin(); ite != LPart.end(); ite++) {
		ans.LPart[ite->first] = ite->second;
		if (klt.LPart.find(ite->first) == klt.LPart.end()) continue;
		else {
			ans.LPart[ite->first].insert(ans.LPart[ite->first].end(),
				klt.LPart[ite->first].begin(), klt.LPart[ite->first].end());
		}
	}
	for (auto ite = klt.LPart.begin(); ite != klt.LPart.end(); ite++) {
		if (LPart.find(ite->first) != LPart.end()) continue;
		ans.LPart[ite->first] = ite->second;
	}
	return ans;
}

vector<KLTerm> KLTerm::negation(const PropDNF& constraint) {
	vector<KLTerm> ans;
	// Propositional part: PPart => PPart
	PropDNF pPartNeg = PPart.negation();
	if(!pPartNeg.isEmpty()) {
		KLTerm ptklt;
		ptklt.PPart = pPartNeg;
		ans.push_back(ptklt);
	}
	// K part: KPart => LPart
	for (auto ite1 = KPart.begin(); ite1 != KPart.end(); ite1++) {
		KLDNF kPartNeg = ite1->second.negation(constraint);
		for (auto ite2 = kPartNeg.dnf.begin(); ite2 != kPartNeg.dnf.end(); ite2++) {
			KLTerm ltklt;
			ltklt.LPart[ite1->first].push_back(KLDNF(*ite2));
			ans.push_back(ltklt);
		}
	}
	// L part: LPart => KPart
	for (auto ite1 = LPart.begin(); ite1 != LPart.end(); ite1++) {
		for (auto ite2 = ite1->second.begin(); ite2 != ite1->second.end(); ite2++) {
			KLDNF lPartNeg = ite2->negation(constraint);
			KLTerm ktklt;
			ktklt.KPart[ite1->first] = lPartNeg;
			ans.push_back(ktklt);
		}
	}
	return ans;
}

KLTerm KLTerm::revision(KLTerm& klt, const PropDNF& constraint) {
	if (this->isSatisfiable(klt, constraint)) return this->conjunction(klt);
	KLTerm ans;
	// Proposition part
	ans.PPart = this->PPart.revision(klt.PPart.conjunction(constraint));
	// pre-process
	map<string, list<KLDNF> > subFormulas;
	for(auto ite1 = klt.LPart.begin();ite1 != klt.LPart.end();ite1++) {
		if(klt.KPart.find(ite1->first) == klt.KPart.end()) {
			subFormulas[ite1->first] = ite1->second;
		}
		else {
			for(auto ite2 = ite1->second.begin();ite2 != ite1->second.end();ite2++) {
				subFormulas[ite1->first].push_back(
					klt.KPart[ite1->first].conjunction(*ite2));
			}
		}
	}
	// K part
	for(auto ite1 = KPart.begin();ite1 != KPart.end();ite1++) {
		if(klt.KPart.find(ite1->first) == klt.KPart.end() &&
			klt.LPart.find(ite1->first) == klt.LPart.end()) {
			ans.KPart[ite1->first] = ite1->second;
		}
		else {
			KLDNF kkld;
			if(klt.KPart.find(ite1->first) != klt.KPart.end()) {
				kkld = ite1->second.revision(klt.KPart[ite1->first], constraint);
			}
			if(subFormulas.find(ite1->first) != subFormulas.end()) {
				for(auto ite2 = subFormulas[ite1->first].begin();
					ite2 != subFormulas[ite1->first].end();ite2++) {
					KLDNF tkld = ite1->second.revision(*ite2, constraint);
					kkld = kkld.disjunction(tkld);
				}
			}
			ans.KPart[ite1->first] = kkld;
		}
	}
	for(auto ite1 = klt.KPart.begin();ite1 != klt.KPart.end();ite1++) {
		if(KPart.find(ite1->first) == KPart.end()) {
			ans.KPart[ite1->first] = ite1->second;
		}
	}
	// L part
	for(auto ite1 = LPart.begin();ite1 != LPart.end();ite1++) {
		if(klt.KPart.find(ite1->first) == klt.KPart.end() &&
			klt.LPart.find(ite1->first) == klt.LPart.end()) {
			ans.LPart[ite1->first].insert(ans.LPart[ite1->first].end(), 
				ite1->second.begin(), ite1->second.end());
		}
		else {
			list<KLDNF> lkld, satPair;
			if(klt.LPart.find(ite1->first) != klt.LPart.end()) {
				lkld = klt.LPart[ite1->first];
			}
			if(ans.KPart.find(ite1->first) != ans.KPart.end()) {
				KLDNF phiK = ans.KPart[ite1->first];
				for(auto ite2 = ite1->second.begin();
					ite2 != ite1->second.end();ite2++) {
					if(ite2->isSatisfiable(phiK, constraint)) {
						satPair.push_back(ite2->conjunction(phiK));
					}
				}
				if(satPair.empty()) {
					for(auto ite2 = ite1->second.begin();
						ite2 != ite1->second.end();ite2++) {
							satPair.push_back(ite2->revision(phiK, constraint));
					}
				}
				lkld.insert(lkld.end(), satPair.begin(), satPair.end());
			}
			else {
				lkld.insert(lkld.end(), 
					ite1->second.begin(), ite1->second.end());
			}
			ans.LPart[ite1->first] = satPair;
		}
	}
	for(auto ite1 = klt.LPart.begin();ite1 != klt.LPart.end();ite1++) {
		if(LPart.find(ite1->first) == LPart.end()) {
			ans.LPart[ite1->first] = ite1->second;
		}
	}
	return ans;
}

KLTerm KLTerm::update(KLTerm& klt, const PropDNF& constraint) {
	KLTerm ans;
	// Proposition part
	ans.PPart = this->PPart.update(klt.PPart.conjunction(constraint));
	// pre-process
	map<string, list<KLDNF> > subFormulas;
	for(auto ite1 = klt.LPart.begin();ite1 != klt.LPart.end();ite1++) {
		if(klt.KPart.find(ite1->first) == klt.KPart.end()) {
			subFormulas[ite1->first] = ite1->second;
		}
		else {
			for(auto ite2 = ite1->second.begin();ite2 != ite1->second.end();ite2++) {
				subFormulas[ite1->first].push_back(
					klt.KPart[ite1->first].conjunction(*ite2));
			}
		}
	}
	// K part
	for(auto ite1 = KPart.begin();ite1 != KPart.end();ite1++) {
		if(klt.KPart.find(ite1->first) == klt.KPart.end() &&
			klt.LPart.find(ite1->first) == klt.LPart.end()) {
			ans.KPart[ite1->first] = ite1->second;
		}
		else {
			KLDNF kkld;
			if(klt.KPart.find(ite1->first) != klt.KPart.end()) {
				kkld = ite1->second.update(klt.KPart[ite1->first], constraint);
			}
			if(subFormulas.find(ite1->first) != subFormulas.end()) {
				for(auto ite2 = subFormulas[ite1->first].begin();
					ite2 != subFormulas[ite1->first].end();ite2++) {
					KLDNF tkld = ite1->second.update(*ite2, constraint);
					kkld = kkld.disjunction(tkld);
				}
			}
			ans.KPart[ite1->first] = kkld;
		}
	}
	for(auto ite1 = klt.KPart.begin();ite1 != klt.KPart.end();ite1++) {
		if(KPart.find(ite1->first) == KPart.end()) {
			ans.KPart[ite1->first] = ite1->second;
		}
	}
	// L part
	for(auto ite1 = LPart.begin();ite1 != LPart.end();ite1++) {
		if(klt.KPart.find(ite1->first) == klt.KPart.end() &&
			klt.LPart.find(ite1->first) == klt.LPart.end()) {
			ans.LPart[ite1->first].insert(ans.LPart[ite1->first].end(), 
				ite1->second.begin(), ite1->second.end());
		}
		else {
			list<KLDNF> lkld, satPair;
			if(klt.LPart.find(ite1->first) != klt.LPart.end()) {
				lkld = klt.LPart[ite1->first];
			}
			if(ans.KPart.find(ite1->first) != ans.KPart.end()) {
				KLDNF phiK = ans.KPart[ite1->first];
				for(auto ite2 = ite1->second.begin();ite2 != ite1->second.end();ite2++) {
					satPair.push_back(ite2->update(phiK, constraint));
				}
				lkld.insert(lkld.end(), satPair.begin(), satPair.end());
			}
			else {
				lkld.insert(lkld.end(), 
					ite1->second.begin(), ite1->second.end());
			}
			ans.LPart[ite1->first] = satPair;
		}
	}
	for(auto ite1 = klt.LPart.begin();ite1 != klt.LPart.end();ite1++) {
		if(LPart.find(ite1->first) == LPart.end()) {
			ans.LPart[ite1->first] = ite1->second;
		}
	}
	return ans;
}

void KLTerm::print() const {
	PPart.print();
	for (auto ite = KPart.begin(); ite != KPart.end(); ite++) {
		cout << logicAnd << "K_" << ite->first << "(";
		ite->second.print();
		cout << ")";
	}
	for (auto ite1 = LPart.begin(); ite1 != LPart.end(); ite1++) {
		for (auto ite2 = ite1->second.begin(); ite2 != ite1->second.end(); ite2++) {
			cout << logicAnd << "L_" << ite1->first << "(";
			ite2->print();
			cout << ")";
		}
	}
}

void KLTerm::show(ofstream& os) const {
	PPart.show(os);
	for (auto ite = KPart.begin(); ite != KPart.end(); ite++) {
		os << logicAnd << "K_" << ite->first << "(";
		ite->second.show(os);
		os << ")";
	}
	for (auto ite1 = LPart.begin(); ite1 != LPart.end(); ite1++) {
		for (auto ite2 = ite1->second.begin(); ite2 != ite1->second.end(); ite2++) {
			os << logicAnd << "L_" << ite1->first << "(";
			ite2->show(os);
			os << ")";
		}
	}
}

KLDNF::KLDNF(const KLTerm& klt) {
	dnf.push_back(klt);
}

KLDNF::KLDNF(const KLDNF& kld) {
	dnf = kld.dnf;
}

KLDNF::~KLDNF() {
	dnf.clear();
}

bool KLDNF::isSatisfiable(const PropDNF& constraint) {
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		if (ite->isSatisfiable(constraint)) return true;
	}
	return false;
}

bool KLDNF::isSatisfiable(KLDNF& kld, const PropDNF& constraint) {
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		for (auto ite2 = kld.dnf.begin(); ite2 != kld.dnf.end(); ite2++) {
			if (ite1->isSatisfiable(*ite2, constraint)) return true;
		}
	}
	return false;
}

bool KLDNF::negEntail(KLDNF& kld, const PropDNF& constraint) {
	return !this->conjunction(kld).isSatisfiable(constraint);
}

bool KLDNF::strongEntail(KLDNF& kld, const PropDNF& constraint) {
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		bool flag = false;
		for (auto ite2 = kld.dnf.begin(); ite2 != kld.dnf.end(); ite2++) {
			if (ite1->strongEntail(*ite2, constraint)) {
				flag = true;
				break;
			}
		}
		if (!flag) return false;
	}
	return true;
}

bool KLDNF::strongEquivlent(KLDNF& kld, const PropDNF& constraint) {
	return this->strongEntail(kld, constraint) &&
		kld.strongEntail(*this, constraint);
}

KLDNF KLDNF::conjunction(KLDNF& kld) {
	KLDNF ans;
	if (dnf.empty()) return kld;
	if (kld.dnf.empty()) return *this;
	for (auto ite1 = dnf.begin(); ite1 != dnf.end(); ite1++) {
		for (auto ite2 = kld.dnf.begin(); ite2 != kld.dnf.end(); ite2++) {
			if(ite1->isEmpty() || ite2->isEmpty()) continue;
			ans.dnf.push_back(ite1->conjunction(*ite2));
		}
	}
	return ans;
}

KLDNF KLDNF::disjunction(KLDNF& kld) {
	if (dnf.empty()) return kld;
	if (kld.dnf.empty()) return *this;
	KLDNF ans(*this);
	ans.dnf.insert(ans.dnf.end(), kld.dnf.begin(), kld.dnf.end());
	return ans;
}

KLDNF KLDNF::minimal(const PropDNF& constraint) {
	if(dnf.size() <= 0) return *this;
	// remove the unsatisfiable term
	for (auto ite = dnf.begin(); ite != dnf.end();) {
		if (!ite->isSatisfiable(constraint)) ite = dnf.erase(ite);
		else ite++;
	}
	for(auto ite = dnf.begin();ite != dnf.end();ite++) {
		ite->minimal(constraint);
	}
	// if kld1 entails kld2, remove kld1
	/*for (auto ite1 = dnf.begin(); ite1 != dnf.end();) {
		bool flag = false;
		for (auto ite2 = dnf.begin(); ite2 != dnf.end(); ite2++) {
			if (ite1 == ite2) continue;
			if (ite1->strongEntail(*ite2, constraint)) {
				flag = true;
				break;
			}
		}
		if (flag) ite1 = dnf.erase(ite1);
		else ite1++;
	}*/
	return *this;
}

KLDNF KLDNF::negation(const PropDNF& constraint) {
	KLDNF ans;
	vector<vector<KLTerm> > allTermNeg;
	// ~(formula1 | formula2) = ~formula1 & ~formula2
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		allTermNeg.push_back(ite->negation(constraint));
	}
	// distribution
	for (size_t i = 0; i < allTermNeg.size(); i++) {
		if(allTermNeg[i].empty()) continue;
		if (ans.dnf.empty()) {
			for (size_t j = 0; j < allTermNeg[i].size(); j++) {
				ans.dnf.push_back(allTermNeg[i][j]);
			}
		}
		else {
			auto endIte = ans.dnf.end();
			endIte--;
			for (auto ite = ans.dnf.begin();; ite++) {
				for (size_t j = 1; j < allTermNeg[i].size(); j++) {
					KLTerm tpt = ite->conjunction(allTermNeg[i][j]);
					ans.dnf.push_back(tpt);
				}
				*ite = ite->conjunction(allTermNeg[i][0]);
				if (ite == endIte) break;
			}
		}
	}
	return ans;
}

KLDNF KLDNF::revision(KLDNF& kld, const PropDNF& constraint) {
	KLDNF ans;
	list<KLTerm> satPair;
	for(auto ite1 = dnf.begin();ite1 != dnf.end();ite1++) {
		for(auto ite2 = kld.dnf.begin();ite2 != kld.dnf.end();ite2++) {
			if(ite1->isSatisfiable(*ite2, constraint)) {
				satPair.push_back(ite1->conjunction(*ite2));
			}
		}
	}
	if(satPair.empty()) {
		for(auto ite1 = dnf.begin();ite1 != dnf.end();ite1++) {
			for(auto ite2 = kld.dnf.begin();ite2 != kld.dnf.end();ite2++) {
				satPair.push_back(ite1->revision(*ite2, constraint));
			}
		}
	}
	ans.dnf = satPair;
	return ans;
}

KLDNF KLDNF::update(KLDNF& kld, const PropDNF& constraint) {
	KLDNF ans;
	for(auto ite1 = dnf.begin();ite1 != dnf.end();ite1++) {
		for(auto ite2 = kld.dnf.begin();ite2 != kld.dnf.end();ite2++) {
			ans.dnf.push_back(ite1->update(*ite2, constraint));
		}
	}
	return ans;
}

void KLDNF::print() const {
	bool flag = true;
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		cout << ((flag) ? "" : logicOr) << "(";
		ite->print();
		cout << ")";
		flag = false;
	}
}

void KLDNF::show(ofstream& os) const {
	bool flag = true;
	for (auto ite = dnf.begin(); ite != dnf.end(); ite++) {
		os << ((flag) ? "" : logicOr) << "(";
		ite->show(os);
		os << ")";
		flag = false;
	}
}
