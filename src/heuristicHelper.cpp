#include "heuristicHelper.h"

extern KLDNF goal;

const double minHeuristicValue = 1.0f;
const double mMaxHeuristicValue = (double)INT_MAX;

double HeuristicHelper::getHeuristicValue(const KLDNF& kld) {
	//return minHeuristicValue;
	double ans = minHeuristicValue;
	ans += dist(kld, posGoal);
	return ans;
}

double HeuristicHelper::getHeuristicValue(const ACDF& kld, const ACDF& rld) {
	return getHeuristicValue(acdf_to_kldnf(kld));
	//return minHeuristicValue;
	double ans = minHeuristicValue;
	ans += dist(kld, rld);
	return ans;
}

double HeuristicHelper::dist(const KLDNF& lkld, const KLDNF& rkld) {
	double ans = mMaxHeuristicValue;
	if(lkld.dnf.empty() && rkld.dnf.empty()) return 0.0f;
	if(lkld.dnf.empty()) {
		for(list<KLTerm>::const_iterator ite2 = rkld.dnf.begin();
			ite2 != rkld.dnf.end();ite2++) {
			KLTerm klt;
			ans = min(ans, dist(klt, *ite2));
		}
		return (abs(ans-mMaxHeuristicValue) < 0.00001f ? 0 : ans);
	}
	if(rkld.dnf.empty()) return 0.0f;
	for(list<KLTerm>::const_iterator ite1 = lkld.dnf.begin();
		ite1 != lkld.dnf.end();ite1++) {
		for(list<KLTerm>::const_iterator ite2 = rkld.dnf.begin();
			ite2 != rkld.dnf.end();ite2++) {
			ans = min(ans, dist(*ite1, *ite2));
		}
	}
	return ((abs(ans-mMaxHeuristicValue) < 0.00001f) ? 0 : ans);
}

double HeuristicHelper::dist(const ACDF& lkld, const ACDF& rkld) {
	double ans = mMaxHeuristicValue;
	if(lkld.acdf_terms.empty() && rkld.acdf_terms.empty()) return 0.0f;
// lkld.print();
// cout << "haha.." << endl;
// rkld.print();
	if(lkld.acdf_terms.empty()) {
	// cout << "haha.." << endl;
		for(list<ACDFTerm>::const_iterator ite2 = rkld.acdf_terms.begin();
			ite2 != rkld.acdf_terms.end();ite2++) {
			ACDFTerm klt;
			ans = min(ans, dist(klt, *ite2));
		}
		return (abs(ans-mMaxHeuristicValue) < 0.00001f ? 0 : ans);
	}
	if(rkld.acdf_terms.empty()) return 0.0f;
	for(list<ACDFTerm>::const_iterator ite1 = lkld.acdf_terms.begin();
		ite1 != lkld.acdf_terms.end();ite1++) {
		for(list<ACDFTerm>::const_iterator ite2 = rkld.acdf_terms.begin();
			ite2 != rkld.acdf_terms.end();ite2++) {
			ans = min(ans, dist(*ite1, *ite2));
		}
	}
	return ((abs(ans-mMaxHeuristicValue) < 0.00001f) ? 0 : ans);
}

double HeuristicHelper::dist(const KLTerm& lklt, const KLTerm& rklt) {
	double pans = 0.0f, kans = 0.0f, lans = 0.0f, klen = 0.0f, kc = 0.0f;
	pans = dist(lklt.PPart, rklt.PPart);  // operand 1
	for(map<string, KLDNF>::const_iterator ite2 = rklt.KPart.begin();
		ite2 != rklt.KPart.end();ite2++) {
		if(lklt.KPart.find(ite2->first) == lklt.KPart.end()) {
			KLDNF kld;
			kans += dist(kld, ite2->second);  // operand 2
		}
		else {
			kans += dist(lklt.KPart.find(ite2->first)->second, ite2->second);  // operand 4
			klen += (lklt.KPart.find(ite2->first))->second.dnf.size();
			kc++;
		}
	}
	if(abs(kc-0.0f) > 0.00001f) kans += (klen/kc);
	for(map<string, list<KLDNF> >::const_iterator ite2 = rklt.LPart.begin();
		ite2 != rklt.LPart.end();ite2++) {
		if(lklt.LPart.find(ite2->first) == lklt.LPart.end()) {
			double tlans = (double)INT_MAX;
			KLDNF kld;
			for(list<KLDNF>::const_iterator ite3 = ite2->second.begin();
				ite3 != ite2->second.end();ite3++) {
				tlans = min(tlans, dist(kld, *ite3));  // operand 3
			}
			lans += tlans;
		}
		else {
			double tlans = (double)INT_MAX;
			for(list<KLDNF>::const_iterator ite3 = ite2->second.begin();
				ite3 != ite2->second.end();ite3++) {
				for(list<KLDNF>::const_iterator ite1 = lklt.LPart.find(ite2->first)->second.begin();
					ite1 != lklt.LPart.find(ite2->first)->second.end();ite1++) {
					tlans = min(tlans, dist(*ite1, *ite3));  // operand 5
				}
			}
			lans += tlans;
		}
	}
	return pans + kans + ((abs(lans-mMaxHeuristicValue) < 0.00001f) ? 0 : lans);
}

double HeuristicHelper::dist(const ACDFTerm& lklt, const ACDFTerm& rklt) {
	double pans = 0.0f, kans = 0.0f, lans = 0.0f, klen = 0.0f, kc = 0.0f;
	pans = dist(lklt.propDNF, rklt.propDNF);  // operand 1
	for(map<string, ACDFList>::const_iterator ite2 = rklt.covers.begin();
		ite2 != rklt.covers.end();ite2++) {
		if(lklt.covers.find(ite2->first) == lklt.covers.end()) {
			double tlans = (double)INT_MAX;
			ACDF kld;
			for(list<ACDF>::const_iterator ite3 = ite2->second.acdfs.begin();
				ite3 != ite2->second.acdfs.end();ite3++) {
				tlans = min(tlans, dist(kld, *ite3));  // operand 3
			}
			lans += tlans;
		}
		else {
			double tlans = (double)INT_MAX;
			for(list<ACDF>::const_iterator ite3 = ite2->second.acdfs.begin();
				ite3 != ite2->second.acdfs.end();ite3++) {
				for(list<ACDF>::const_iterator ite1 = lklt.covers.find(ite2->first)->second.acdfs.begin();
					ite1 != lklt.covers.find(ite2->first)->second.acdfs.end();ite1++) {
					tlans = dist(*ite1, *ite3);  // operand 5
					// tlans = min(tlans, dist(*ite1, *ite3));  // operand 5
				}
			}
			lans += tlans;
		}
	}
	return pans + kans + ((abs(lans-mMaxHeuristicValue) < 0.00001f) ? 0 : lans);
}

double HeuristicHelper::dist(const PropDNF& lpd, const PropDNF& rpd) {
	double ans = (double)INT_MAX;
	for(list<PropTerm>::const_iterator ite2 = rpd.dnf.begin();
		ite2 != rpd.dnf.end();ite2++) {
		double tans = 0.0f;
		for(size_t i = 0;i < (ite2->literal).size();i++) {
			if(ite2->literal[i] == TRUE ||
				ite2->literal[i] == FALSE) {
				bool isConsisitent = true;
				for(list<PropTerm>::const_iterator ite1 = lpd.dnf.begin();
					ite1 != lpd.dnf.end();ite1++) {
					if(!ite1->isSatisfiable()) continue;
					isConsisitent &= (ite1->literal[i] == ite2->literal[i]);
					if(!isConsisitent) break;
				}
				tans += ((isConsisitent) ? 0.0f : 1.0f);
			}
		}
		ans = min(ans, tans);
	}
	return ((abs(ans-mMaxHeuristicValue) < 0.00001f) ? 0 : ans);
}

KLDNF HeuristicHelper::acdf_to_kldnf(const ACDF& acdf) {
    KLDNF kldnf;
    for (auto& term : acdf.acdf_terms)
        kldnf.dnf.push_back(acdfterm_to_klterm(term));
    return kldnf;
}

KLTerm HeuristicHelper::acdfterm_to_klterm(const ACDFTerm& acdf_term) {
    KLTerm klterm;
    klterm.PPart = acdf_term.propDNF;

    for (auto& cover: acdf_term.covers) {
    	klterm.KPart[cover.first] = acdf_to_kldnf(cover.second.all_in_one());
    	klterm.LPart[cover.first] = acdflist_to_kldnflist(cover.second);
    }

    return klterm;
}

list<KLDNF> HeuristicHelper::acdflist_to_kldnflist(const ACDFList& acdf_list) {
	list<KLDNF> kldnf_list;
	for (auto& acdf: acdf_list.acdfs)
		kldnf_list.push_back(acdf_to_kldnf(acdf));
	return kldnf_list;
}
