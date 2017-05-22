#include "initial.h"
#include "reader.h"

Reader reader;

void Initial::exec(const char* dFile, const char* pFile) {
    reader.exec(dFile, pFile);

    atomsGrounding();
    // cout << "----- atomsGrounding done -----" << endl;
    constraint = getPropDNFFromTree(&reader.constraint).minimal();  // must get constraint first
    // cout << "----- constraint done -----" << endl;
    init = getACDFFromTree(&reader.init, 0).involve(constraint).minimal(constraint);
    // cout << "----- init done -----" << endl;
    PropDNF goal_cons;
    goal = getACDFFromTree(&reader.goal, 0, true).minimal(goal_cons);
    // cout << "----- goal done -----" << endl;
    episActionsGrounding();
    // cout << "----- episActionsGrounding done -----" << endl;
    onticActionsGrounding();
    // cout << "----- onticActionsGrounding done -----" << endl;
    // cout << "----- Preprocessing done -----" << endl;

    // string endFile = "../output/";
    // endFile += reader.domainName + "+" + reader.problemName + "_initial";
    // ofstream out_end(endFile.c_str());  // 打开要写入的文本文件
    // if(!out_end.is_open()) {
    //     cout << "cannot open " << endFile << endl;
    //     return;
    // }
    // printAtoms(out_end);
    // printAgents(out_end);
    // printInit(out_end);
    // printConstraint(out_end);
    // printGoal(out_end);
    // printEpisActions(out_end);
    // printOnticActions(out_end);
    // out_end.close();
}

void Initial::printInit(ofstream & out) const {
    // print init
    out << "---------------- init -------------------\n";
    init.show(out, 0);
    out << "---------------- done -------------------\n\n";
}

void Initial::printConstraint(ofstream & out) const {
    // print init
    out << "---------------- constraint -------------------\n";
    constraint.show(out, 0);
    out << "---------------- done -------------------\n\n";
}

void Initial::printGoal(ofstream & out) const {
    // print goal
    out << "---------------- goal -------------------\n";
    goal.show(out, 0);
    out << "---------------- done -------------------\n\n";
}

void Initial::atomsGrounding() {
    /* get atomic propositions from reader */

    // propositions table 
    size_t atomicCounter = 0;
    for (set<string>::iterator it = reader.atomicPropSet.begin();
            it != reader.atomicPropSet.end(); ++it) {
        // cout << *it << endl;
        atomsByName.insert( pair<string, int>(*it, atomicCounter) );
        atomsByIndex.insert( pair<int, string>((atomicCounter++), *it) );
    }

    // add agents to objects
    reader.objects.push_back( pair<string, StringList>("agent", reader.agents) );
    // pass agents to final data structure, put aside
    agents = reader.agents;
    // predicate grounding
    vector<queue<string> > atoms_vector;
    for (PredicateSet::const_iterator mul_type_pair = reader.predicates.begin();
            mul_type_pair != reader.predicates.end(); ++mul_type_pair) {
        queue<string> tmp_atoms;
        tmp_atoms.push((*mul_type_pair).first);  // grounding atomic proposition
        for (MultiTypeList::const_iterator sig_type_pair = (*mul_type_pair).second.begin();
                sig_type_pair != (*mul_type_pair).second.end(); ++sig_type_pair) {
            // find objects to the specific type
            for (MultiTypeList::const_iterator obj = reader.objects.begin();
                    obj != reader.objects.end(); ++obj) {
                if((*sig_type_pair).first == (*obj).first) {
                    for (size_t i = 0; i < (*sig_type_pair).second.size(); ++i) {
                        size_t tmp_atoms_size = tmp_atoms.size();
                        for (size_t i = 0; i < tmp_atoms_size; ++i) {
                            for (StringList::const_iterator ob = (*obj).second.begin();
                                ob != (*obj).second.end(); ++ob) {
                                if (tmp_atoms.front().find(" "+*ob) != string::npos) {
                                    continue;  // avoid repeat
                                }
                                // cout << tmp_atoms.front()+" "+*ob << " //test" << endl;
                                // construct an instance of predicate
                                tmp_atoms.push(tmp_atoms.front()+" "+*ob);
                            }
                            /// pop the atom at the front after finishing grounding a variable
                            tmp_atoms.pop();
                        }
                    }
                }
            }
        }
        atoms_vector.push_back(tmp_atoms);
    }

    for (vector<queue<string> > ::iterator atom_queue = atoms_vector.begin();
        atom_queue != atoms_vector.end(); ++atom_queue) {
        while (!(*atom_queue).empty()) {  // in case of repeat
            if (atomsByName.count((*atom_queue).front()) == 0) {
                atomsByName.insert( pair<string, int>((*atom_queue).front(), atomicCounter) );
                atomsByIndex.insert( pair<int, string>((atomicCounter++), (*atom_queue).front()) );
            }
            (*atom_queue).pop();
        }
    }
}

void Initial::printAtoms(ofstream & out) const {
    out << "------------ print all atoms ----------------\n";
    for (size_t i = 0; i < atomsByIndex.size(); ++i)
    {
        out << i+1 << " : " << atomsByIndex[i] << endl;
    }
    out << "-------- end print all atoms ----------------\n\n";
}


void Initial::printAgents(ofstream & out) const {
    out << "------------ print all agents ---------------\n";
    size_t i = 1;
    for (list<string>::const_iterator agent = agents.begin();
        agent != agents.end(); ++agent)
    {
        out << i++ << " : " << *agent << endl;
    }
    out << "-------- end print all agents ---------------\n\n";
}

void Initial::episActionsGrounding() {
    for (PreEpistemicActionList::const_iterator epistemicAction = reader.epistemicActions.begin();
        epistemicAction != reader.epistemicActions.end(); ++epistemicAction) {

        queue<PreEpistemicAction> actions;
        actions.push(*epistemicAction);

        if ((*epistemicAction).paras.size() != 0) 
            actions.front().name += " ()";

        for(MultiTypeList::const_iterator param = (*epistemicAction).paras.begin();
            param != (*epistemicAction).paras.end(); ++param) {

            // find objects to the specific type of a parameter
            for (MultiTypeList::const_iterator obj = reader.objects.begin();
                    obj != reader.objects.end(); ++obj) {

                if((*param).first == (*obj).first) {
                    size_t tmp_actions_size = actions.size();  // cause size is changing!
                    for (size_t i = 0; i < tmp_actions_size; ++i) {

                        for (StringList::const_iterator ob = (*obj).second.begin();
                            ob != (*obj).second.end(); ++ob) {

                            // avoid adding redundant actions
                            string newParam = *ob+',';
                            if (actions.front().name.find(newParam) == string::npos)
                                actions.push(episActionParamGrouding(actions.front(),
                                            *(*param).second.begin(), *ob));
                        }
                        actions.pop();
                    }
                    break;
                }
            }
        }

        // PreEpistemicActions(reader) to EpisActions(dest structure)
        while (!actions.empty()) {
            EpisAction epis_action;
            epis_action.name = actions.front().name;
            epis_action.category = actions.front().category;
            if (epis_action.name[epis_action.name.length()-1] == ')')
                epis_action.name = epis_action.name.substr(0, epis_action.name.length()-3)+')';
            epis_action.pre_con = getACDFFromTree(&(actions.front().preCondition), 0).minimal(constraint);
            epis_action.pos_res = getACDFFromTree(&(actions.front().observe_pos), 0).minimal(constraint);
            epis_action.neg_res = getACDFFromTree(&(actions.front().observe_neg), 0).minimal(constraint);
            epis_actions.push_back(epis_action);
            actions.pop();
        }

    }
}

PreEpistemicAction Initial::episActionParamGrouding(PreEpistemicAction & epistemicAction,
    const string param, const string obj) {
    PreEpistemicAction action;
    action.name = epistemicAction.name;
    action.name.insert(action.name.length()-1, obj + ", ");
    action.category = epistemicAction.category;
    action.paras = epistemicAction.paras;
    action.preCondition = *(new Formula(epistemicAction.preCondition));
    action.observe_pos = *(new Formula(epistemicAction.observe_pos));
    action.observe_neg = *(new Formula(epistemicAction.observe_neg));
    // precondition
    replaceParamWithObj(&action.preCondition, param, obj);
    // observe_pos
    replaceParamWithObj(&action.observe_pos, param, obj);
    // observe_neg
    replaceParamWithObj(&action.observe_neg, param, obj);
    return action;
}

void Initial::replaceParamWithObj(Formula* f, const string param, const string obj) {
    // cout << param << " " << obj << endl;
    size_t found = f->label.find(param);
    // care the case: two similar parameters '?b' and 'bf' !
    while (found != string::npos &&
        ( (found+param.size() < f->label.size() && f->label[found+param.size()] == ' ')
        || (found+param.size() == f->label.size()) ) ) {
            f->label.replace(found, param.size(), obj);
            found = f->label.find(param);
    }
    if (f->left != NULL)
    {
        replaceParamWithObj(f->left, param, obj);
    }
    if (f->right != NULL)
    {
        replaceParamWithObj(f->right, param, obj);
    }
}

void Initial::printEpisActions(ofstream & out) const {
    out << "---------------- Epis Actions -------------------\n";
    size_t counter = 1;
    for(vector<EpisAction>::const_iterator epis_action = epis_actions.begin();
        epis_action != epis_actions.end(); ++epis_action) {
        if (epis_action != epis_actions.begin())
            out << "******************************************\n";
        out << ":action-" << counter++ << " "
            << (*epis_action).name << " --------------\n";
        out << ":category --------------\n";
        out << (*epis_action).category << endl;
        out << ":precondition --------------\n";
        (*epis_action).pre_con.show(out, 0);
        out << ":observe -------------------\n";
        (*epis_action).pos_res.show(out, 0);
        out << ":neg observe ---------------\n";
        (*epis_action).neg_res.show(out, 0);
    }
    out << "-------------------- done -----------------------\n\n";
}

void Initial::onticActionsGrounding() {
    for (PreOnticActionList::const_iterator onticAction = reader.onticActions.begin();
        onticAction != reader.onticActions.end(); ++onticAction) {

        // action(reader) to action_1 2 3...(reader)
        queue<PreOnticAction> actions;
        actions.push(*onticAction);

        if ((*onticAction).paras.size() != 0) 
            actions.front().name += " ()";

        for(MultiTypeList::const_iterator param = (*onticAction).paras.begin();
            param != (*onticAction).paras.end(); ++param) {

            // find objects to the specific type of a parameter
            for (MultiTypeList::const_iterator obj = reader.objects.begin();
                    obj != reader.objects.end(); ++obj) {

                if((*param).first == (*obj).first) {  // type is same
                    size_t tmp_actions_size = actions.size();  // cause size is increasing!
                    for (size_t i = 0; i < tmp_actions_size; ++i) {

                        for (StringList::const_iterator ob = (*obj).second.begin();
                            ob != (*obj).second.end(); ++ob) {

                            // avoid adding redundant actions
                            string newParam = *ob+',';
                            if (actions.front().name.find(newParam) == string::npos)
                                actions.push(onticActionParamGrouding(actions.front(),
                                            *(*param).second.begin(), *ob));
                        }
                        actions.pop();
                    }
                    break;
                }
            }
        }

        // PreOnticActions(reader) to OnticActions(dest structure)
        while (!actions.empty()) {
            OnticAction ontic_action;
            ontic_action.name = actions.front().name;
            ontic_action.category = actions.front().category;
            if (ontic_action.name[ontic_action.name.length()-1] == ')')
                ontic_action.name = ontic_action.name.substr(0, ontic_action.name.length()-3)+')';
            ontic_action.pre_con = getACDFFromTree(&(actions.front().preCondition), 0).minimal(constraint);
            ontic_action.con_eff = getOnticEffect(actions.front().effects);
            ontic_actions.push_back(ontic_action);
            actions.pop();
        }

    }
}

vector<ConEffect> Initial::getOnticEffect(EffectList effects) {
    vector<ConEffect> con_effs;
    for (EffectList::iterator eff = effects.begin();
        eff != effects.end(); ++eff) {
        ConEffect con_eff;
        // condition
        con_eff.condition = getACDFFromTree(&(eff->aft_condition), 0).minimal(constraint);
        // effect
        con_eff.effect = getACDFFromTree(&(eff->con_effect), 0).minimal(constraint);
        con_effs.push_back(con_eff);
    }
    return con_effs;
}

PreOnticAction Initial::onticActionParamGrouding(PreOnticAction & onticAction,
        const string param, const string obj) {
    PreOnticAction action;
    action.name = onticAction.name;
    action.name.insert(action.name.length()-1, obj + ", ");
    action.category = onticAction.category;
    action.paras = onticAction.paras;
    action.preCondition = *(new Formula(onticAction.preCondition));
    replaceParamWithObj(&action.preCondition, param, obj);
    for (EffectList::const_iterator eff = onticAction.effects.begin();
        eff != onticAction.effects.end(); ++eff) {
        Effect effect;
        effect.aft_condition = *(new Formula(eff->aft_condition));
        replaceParamWithObj(&effect.aft_condition, param, obj);
        effect.con_effect = *(new Formula(eff->con_effect));
        replaceParamWithObj(&effect.con_effect, param, obj);
        action.effects.push_back(effect);
    }
    return action;
}

void Initial::printOnticActions(ofstream & out) const {
    out << "---------------- Ontic Actions -------------------\n";
    size_t counter = 1;
    for(vector<OnticAction>::const_iterator ontic_action = ontic_actions.begin();
        ontic_action != ontic_actions.end(); ++ontic_action) {

        if (ontic_action != ontic_actions.begin())
            out << "******************************************\n";
        out << ":action-" << counter++ << " "
            << ontic_action->name << " --------------\n";
        out << ":category --------------\n";
        out << (*ontic_action).category << endl;
        out << ":precondition --------------\n";
        (*ontic_action).pre_con.show(out, 0);
        out << ":effects -------------------\n";
        size_t counter = 1;
        for (vector<ConEffect>::const_iterator eff = ontic_action->con_eff.begin();
            eff != ontic_action->con_eff.end(); ++eff) {
            out << "effect " << counter++ << " --------\n";
            eff->condition.show(out, 0);
            out << endl;
            eff->effect.show(out, 0);
            out << endl;
        }

    }
    out << "-------------------- done -----------------------\n\n";
}

ACDF Initial::getACDFFromTree(Formula* f, size_t depth, bool is_goal) {
                    // cout << "haha 0" << endl;
    // cout << "++++++++++++++++++++++++++++++++++" << endl;
    // f->print(0);
    ACDF acdf;
    // check whether ƒ is epistemic Formula
    if (f->is_objective()) {
        // cout << "1 ......................." << endl;
        // f->print(0);
        // cout << "2 ......................." << endl;
        acdf.print();
        ACDFTerm term;
        term.propDNF = getPropDNFFromTree(f).minimal();
        PropDNF p;
        acdf.acdf_terms.push_back(term);
        // cout << "3 ......................." << endl;
        // acdf.print();
        // cout << " ......................." << endl;
        return acdf;
    }

    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "|") {
                acdf = acdf.merge(getACDFTermsFromTree(f, depth, is_goal));
                // acdf.print();
                // cout << "======================---" << endl;
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    // cout << "get ++++++++++++++++++++++++++++++++++" << endl;
    // acdf.print();
    return acdf;
}

ACDF Initial::getACDFTermsFromTree(Formula* f, size_t depth, bool is_goal) {
// cout << "==================================" << endl;
// f->print(0);
    PropDNF p; if (!is_goal) p = constraint;
    ACDF new_acdf;
    stack<Formula*> s;
// cout << "haha 0" << endl;
    do {
        while(f->label != "NULL") {
            if (f->label[0] == 'K' || f->label.substr(0, 2) == "DK") {
                bool is_DK =  f->label[0] == 'K' ? false : true;
// cout << "haha 1" << endl;
// new_acdf.print();
// cout << "------------------------------" << endl;
                string agent = f->label.substr(f->label.find_first_of('_')+1);
                ACDF agent_cover = getACDFFromTree(f->left, depth+1, is_goal);
                ACDFList agent_covers;
                agent_covers.acdfs.push_back(agent_cover);
// cout << "haha 2" << endl;
// cout << agent << ": " << endl;
// cout << " ——+——+——++——+——+——+——+——+——+——+——+————+——+——" << endl;
// new_acdf.print();
// cout << " ——+——+——++——+——+——+——+——+——+——+——+————+——+——" << endl;
                // if empty, then initialize with the first term
                if (new_acdf.empty()) {
                    ACDFTerm tmp_term;
                    if (!is_DK) {
                        tmp_term.covers[agent] = agent_covers;
                        new_acdf.acdf_terms.push_back(tmp_term);
                    } else {
                        // add Term : Cover_a {T, ACDF}
                        ACDFList tmp_acdflist;
                        tmp_acdflist.acdfs.push_back(agent_cover);
                        ACDF true_term(true);
                        tmp_acdflist.acdfs.push_back(true_term);
                        tmp_term.covers[agent] = tmp_acdflist;
                        new_acdf.acdf_terms.push_back(tmp_term);
                    }
                    f->label = "NULL";
// cout << "------------------------------" << endl;
// new_acdf.print();
// cout << "------------------------------" << endl;
                    continue;
                }
// cout << "haha 4" << endl;
                ACDF tmp_acdf;  // not use new_acdf directly here, becase it's increasing
                for (list<ACDFTerm>::iterator acdf_term = new_acdf.acdf_terms.begin();
                acdf_term != new_acdf.acdf_terms.end(); ++acdf_term) {
// cout << "haha 5" << endl;
                    bool existed = (acdf_term->covers.find(agent) != acdf_term->covers.end());

                    ACDFTerm tmp_term = *acdf_term;
                    if (!is_DK) {
                        // Kø : each term's same agent Coverø ^ Coverø
                        tmp_term.covers[agent] =
                            existed ? tmp_term.covers[agent].group(agent_covers).minimal(p, true, true) : agent_covers;
                        tmp_acdf.acdf_terms.push_back(tmp_term);
                    } else {
                        // DKø : each term's same agent Coverø ^ Cover{T, ø})
                        // add Term : Cover_a {T, ACDF}
                        ACDFList new_acdflist;  // include two terms, true term and a cover
                        new_acdflist.acdfs.push_back(agent_cover);
                        ACDF true_term(true);
                        new_acdflist.acdfs.push_back(true_term);
// cout << "new_acdflist ++++++++++++++++++++++++++" << endl;  
// new_acdflist.print();
// cout << "++++++++++++++++++++++++++" << endl;
// agent_covers.print();
// cout << "++++++++++++++++++++++++++" << endl;
// cout << "exist? :" << existed << endl;
                        tmp_term.covers[agent] = 
                            existed ? tmp_term.covers[agent].group(new_acdflist).minimal(p, true, true) : new_acdflist;
                        tmp_acdf.acdf_terms.push_back(tmp_term);
// cout << "tmp_acdf ++++++++++++++++++++++++++" << endl;  
// tmp_acdf.print();
// cout << "++++++++++++++++++++++++++" << endl;  
                    }
                }
//                 tmp_acdf.print();
// cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;  
                // cout << "after minimal " << endl;
                // tmp_acdf.minimal(p).print();
                new_acdf = tmp_acdf.minimal(p, true, true);
// new_acdf.print();
// cout << "*&*&*&*&*&*&*&*&" << endl;      
// cout << "haha 1" << endl;
                f->label = "NULL";
            } else if (f->label != "&" || f->label == "True" || f->label == "False") {
        //    cout << " * *****************************" << endl;
                if (new_acdf.empty()) {
                    ACDFTerm term;
                    term.propDNF = getPropDNFFromTree(f);
                    new_acdf.acdf_terms.push_back(term);
                } else {
                    for (list<ACDFTerm>::iterator acdf_term = new_acdf.acdf_terms.begin();
                    acdf_term != new_acdf.acdf_terms.end(); ++acdf_term) {
                        acdf_term->propDNF = acdf_term->propDNF.group(getPropDNFFromTree(f));
                    }
                }
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    // cout << "get ==================================" << endl;
    // new_acdf.print();
    return new_acdf;
}

PropDNF Initial::getPropDNFFromTree(Formula* f) {
    PropDNF p_dnf;
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "K" && f->label != "DK"
                && f->label != "|") {
                p_dnf.prop_terms.push_back(getPropTermFromTree(f));
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }

    } while(f->label != "NULL" || !s.empty());
    // p_dnf.print();
    // cout << "……………………………………………………" << endl;
    return p_dnf;
}

PropTerm Initial::getPropTermFromTree(Formula* f) {
    PropTerm p_term(atomsByIndex.size()*2);
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "&") {
                if (f->label == "True") return p_term;
                if (f->label == "False") {
                    p_term.literals.set();
                    return p_term;
                }
                if (f->label == "!") {
                    if (atomsByName.find(f->left->label) != atomsByName.end()) {
                        p_term.literals[atomsByName[f->left->label]*2+1] = 1;
                    }
                } else {
                    if (atomsByName.find(f->label) != atomsByName.end()) {
                        p_term.literals[atomsByName[f->label]*2] = 1;
                    }
                }
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    return p_term;
}
