#ifndef INITIAL_H
#define INITIAL_H

#include "define2.h"

extern list<string> agents;

extern map<int, string> atomsByIndex;
extern map<string, int> atomsByName;

extern vector<EpisAction> epis_actions;
extern vector<OnticAction> ontic_actions;


class Initial {
public:
    Initial() {}
    void exec(const char* dFile, const char* pFile);
    ~Initial() {}

    ACDF init;
    PropDNF constraint;
    ACDF goal;

public:
    // for atoms grounding and get all agents
    void atomsGrounding();
    // for epistemic action grounding
    void episActionsGrounding();
    PreEpistemicAction episActionParamGrouding(PreEpistemicAction & epistemicAction,
        const string param, const string obj);
    void replaceParamWithObj(Formula* f, const string param, const string obj);
    // for ontic action grounding
    void onticActionsGrounding();
    PreOnticAction onticActionParamGrouding(PreOnticAction & onticAction,
        const string param, const string obj);
    vector<ConEffect> getOnticEffect(EffectList effects);


    ACDF getACDFFromTree(Formula*, size_t, bool is_goal = false);
    ACDF getACDFTermsFromTree(Formula*, size_t, bool is_goal = false);
    PropDNF getPropDNFFromTree(Formula*);
    PropTerm getPropTermFromTree(Formula*);

    void printAtoms(ofstream &) const;
    void printAgents(ofstream &) const;
    void printInit(ofstream &) const;
    void printConstraint(ofstream &) const;
    void printGoal(ofstream &) const;
    void printEpisActions(ofstream &) const;
    void printOnticActions(ofstream &) const;
};

#endif
