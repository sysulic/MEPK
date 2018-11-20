#ifndef INITIAL_H
#define INITIAL_H

#include "define.h"

extern vector<SensingAction> sActions;
extern vector<OnticAction> oActions;
extern KLDNF init;
extern KLDNF goal;
extern KLDNF posGoal;
extern PropDNF constraint;

class Initial {
public:
    Initial() {}
    void exec();
    ~Initial() {}

    ACDF mine_init;
    PropDNF mine_constraint;
    vector<EpisAction> mine_epis_actions;
    vector<OntiAction> mine_ontic_actions;
    ACDF mine_goal;
    ACDF mine_pos_goal;

public:

    ACDF kldnf_to_acdf(const KLDNF & kldnf, const PropDNF & cstt) const;

    ACDFTerm klterm_to_acdfterm(const KLTerm & klterm, const PropDNF & cstt) const;

    ACDFList kpart_to_cover(const KLDNF & kpart, const PropDNF & cstt) const;

    ACDFList lterm_to_cover(const KLDNF & lterm, const PropDNF & cstt) const;

};

#endif
