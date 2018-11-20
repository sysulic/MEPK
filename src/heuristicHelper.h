#ifndef __HEURISTIC_HELPER__
#define __HEURISTIC_HELPER__

#include "parse.h"

extern KLDNF posGoal;

class HeuristicHelper {
public:
	HeuristicHelper() {};
	double getHeuristicValue(const KLDNF& kld);
	double dist(const KLDNF& lkld, const KLDNF& rkld);
	double dist(const KLTerm& lklt, const KLTerm& rklt);
	double dist(const PropDNF& lpd, const PropDNF& rpd);

	double getHeuristicValue(const ACDF& kld, const ACDF& pos_goal);
	double dist(const ACDF& lkld, const ACDF& rkld);
	double dist(const ACDFTerm& lklt, const ACDFTerm& rklt);

	KLDNF acdf_to_kldnf(const ACDF&);
	KLTerm acdfterm_to_klterm(const ACDFTerm& acdf_term);
	list<KLDNF> acdflist_to_kldnflist(const ACDFList& acdf_list);
};

#endif