#include "initial.h"
#include "heuristicHelper.h"


void Initial::exec() {
cout << "start : ------------" << endl;
    mine_constraint = constraint;
    mine_init = kldnf_to_acdf(init, mine_constraint);
    mine_goal = kldnf_to_acdf(goal, mine_constraint);
// mine_pos_goal = kldnf_to_acdf(posGoal, mine_constraint);
// cout << "init : ------------" << endl;
// init.print();
// cout << "mine init : ------------" << endl;
// mine_init.print();
// cout << "goal init : ------------" << endl;
// mine_goal.print();
    for (auto& a : sActions) {
        EpisAction e_a;
        e_a.name = a.name;
        e_a.category = a.category;
        e_a.pre_con = kldnf_to_acdf(a.preCon, mine_constraint);
        e_a.pos_res = kldnf_to_acdf(a.posRes, mine_constraint);
        e_a.neg_res = kldnf_to_acdf(a.negRes, mine_constraint);
        mine_epis_actions.push_back(e_a);
    }

    for (auto& a : oActions) {
        OntiAction o_a;
        o_a.name = a.name;
        o_a.category = a.category;
        o_a.pre_con = kldnf_to_acdf(a.preCon, mine_constraint);
        for (auto& ce : a.eff) {
            ConEffect o_ce;
            o_ce.condition = kldnf_to_acdf(ce.condition, mine_constraint);
            o_ce.effect = kldnf_to_acdf(ce.effect, mine_constraint);
            o_a.con_eff.push_back(o_ce);
        }
        mine_ontic_actions.push_back(o_a);
    }

    // /* for printing compiled info */
    // string endFile = "../output/gossip3";
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

ACDF Initial::kldnf_to_acdf(const KLDNF & kldnf, const PropDNF & cstt) const {
    ACDF acdf;
// std::cout << endl << " ~~~~~---------+++++++++++++------~~~~~~" << std::endl;
// kldnf.print();
    for (auto& term : kldnf.dnf)
        acdf.acdf_terms.push_back(klterm_to_acdfterm(term, cstt));
    if (acdf.objective()) {
        ACDF obj_acdf;
        ACDFTerm obj_term;
        for (auto& term : acdf.acdf_terms)
            obj_term.propDNF = obj_term.propDNF.disjunction(term.propDNF);
        obj_acdf.acdf_terms.push_back(obj_term);
// std::cout << endl << " ~~~~~---------------------------~~~~~~" << std::endl;
// obj_acdf.print();
        return obj_acdf;
    }

// std::cout << endl << " ~~~~~---------------------------~~~~~~" << std::endl;
// acdf.print();
    return acdf;
}

ACDFTerm Initial::klterm_to_acdfterm(const KLTerm & klterm, const PropDNF & cstt) const {
    ACDFTerm acdf_term;
    acdf_term.propDNF = klterm.PPart;
// std::cout << " haha 41" << std::endl;
// std::cout << " ~~~~~---------+++++++++++++------~~~~~~" << std::endl;
// klterm.print();
    set<string> done_agents;
    for (auto& cover: klterm.KPart) {
        done_agents.insert(cover.first);
        if (klterm.LPart.find(cover.first) != klterm.LPart.end()) {
            // proposition 2.6 - 2
            for (auto& lterm : klterm.LPart.at(cover.first)) {

// std::cout << endl << " ~~~~~---------------------------~~~~~~" << std::endl;
// acdf_term.covers[cover.first].print();
                ACDFList new_list;
                ACDF k_part_cover = kldnf_to_acdf(cover.second, cstt);
                new_list.acdfs.push_back(k_part_cover);
                for (auto& lterm : klterm.LPart.at(cover.first))
                    new_list.acdfs.push_back(k_part_cover.conjunction(kldnf_to_acdf(lterm, cstt)));
// std::cout << endl << " conjunction with  --------------~~~~~~" << std::endl;
// new_list.print();
                acdf_term.covers[cover.first] = new_list;
 
// std::cout << endl << " got ============  --------------~~~~~~" << std::endl;
// acdf_term.print();
           }
        } else {
            acdf_term.covers[cover.first] = kpart_to_cover(cover.second, cstt);
        }
    }
    for (auto& lterm : klterm.LPart)
        if (done_agents.find(lterm.first) == done_agents.end()) {
            ACDFList cover;
            ACDF true_acdf(true);
            cover.acdfs.push_back(true_acdf);
            for (auto& lacdf : klterm.LPart.at(lterm.first))
                cover.acdfs.push_back(kldnf_to_acdf(lacdf, cstt));
            acdf_term.covers[lterm.first] = cover;
        }
    
// std::cout << endl << " ~~~~~-------------------------~~~~~~" << std::endl;
// acdf_term.print();
    return acdf_term;
}

ACDFList Initial::kpart_to_cover(const KLDNF & kpart, const PropDNF & cstt) const {
    ACDFList cover;
    cover.acdfs.push_back(kldnf_to_acdf(kpart, cstt));
    return cover;
}
