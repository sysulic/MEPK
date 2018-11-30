#include "plan.h"
#include <algorithm>

Plan::Plan(const char *domain, int type) {
    // printf("================================================================\n");
    // printf("domain_file(%s)\n     p_file(%s)\n", domain, p);
    // if (type == 0)
    //     cout << "search_type(Heur first)\n" << endl;
    // if (type == 1)
    //     cout << "search_type(Deap first)\n" << endl;
    // if (type == 2)
    //     cout << "search_type(Bread first)\n" << endl;
    all_nodes.clear();
    all_edges.clear();
    explored_num = -1;
    searchtype = type == 0 ? kHeuristic : (type == 1 ? kDepthFirst : kWidthFirst);
    plan_tree_depth = 0;
    plan_tree_node_num = 0;
    clock_t t_start = clock();
    printf("Preprocessing...\n");
    if (!parser.exec(domain, false)) return;
    in.exec();

    // //print actions
    // int i = 0;
    // cout << "======= epis actions : ============" << endl;
    // for (std::vector<EpisAction>::const_iterator v = in.mine_epis_actions.begin();
    //     v != in.mine_epis_actions.end(); ++v) {
    //     cout << ++i << ": " << (*v).name << endl;
    // }
    // cout << "======= ontic actions : ===========" << endl;
    // i = 0;
    // for (std::vector<OnticAction>::const_iterator v = in.mine_ontic_actions.begin();
    //     v != in.mine_ontic_actions.end(); ++v) {
    //     cout << ++i << ": " << (*v).name << endl;
    // }
    // cout << "===================================" << endl;

    clock_t t_end = clock();
    preprocess_time = difftime(t_end, t_start) / 1000000.0;
}

// Algorithm 6
void Plan::exec_plan() {
    printf("Planning...\n");
    if (in.mine_init.neg_entails(in.mine_goal, in.mine_constraint)) {
        printf("init neg_entails goal!\n");
        return;
    }

    clock_t t_start = clock();
    Node init_node;
    init_node.flag = TOBEEXPLORED;
    init_node.isolated = false;
    init_node.kb = in.mine_init;
    init_node.depth = 0;
    add_node(init_node);
    hert_nodes = 0; //for deep search
    while(true) {
        int node_pos = get_tobeexplored_node();//heuristic
        if (node_pos == -1) {
            return ;
        }
         
        explore(node_pos); 
        if (all_nodes[0].flag == FINAL_GOAL) {
            clock_t t_end = clock();
            search_time = difftime(t_end, t_start) / 1000000.0;
            BuildPlan();  // 之后再调用BuildPlan，原算法中的Tree
            return ;
        }
        if (all_nodes[0].flag == DEAD) {
            return ;
        }
    }
}

// Algorithm 7
void Plan::explore(int node_pos) {
// cout << "@explore: " << node_pos << endl;
// if (node_pos == 802)
//     all_nodes[802].kb.print();
    bool execed = false;  // deep search find new node
    // 进行感知演进
    for (size_t i = 0; i < in.mine_epis_actions.size(); ++i) {
// cout << "node " << node_pos << " to test epis action: " << in.mine_epis_actions[i].name << endl;
        if (all_nodes[node_pos].kb.neg_entails(in.mine_epis_actions[i].pre_con, in.mine_constraint)) {
// if (node_pos == 802)
//     cout <<  "node " << node_pos << "doing... epis action: " << in.mine_epis_actions[i].name << endl;
            // clock_t epis_start = clock();
            vector<ACDF> res = all_nodes[node_pos].kb.epistemic_prog(in.mine_epis_actions[i], in.mine_constraint);
            // clock_t epis_end = clock();
            // epis_progression_time += difftime(epis_end, epis_start) / 1000000.0;

            if (check_zero_dead(res[0]) || check_zero_dead(res[1]))
                continue;
            // cout << node_pos << " after action : " << in.mine_epis_actions[i].name << " pos :" << endl;
            int res_pos = checknode(res[0]);  // find if old node; if it is old node, then return node number            
            if (res_pos == node_pos) continue;
            bool new_node = false;
            if (res_pos == -1) {
                Node newNode(TOBEEXPLORED, false, res[0], all_nodes[node_pos].depth+1);
                add_node(newNode);
                res_pos = all_nodes.size()-1;
                new_node = true;
            }
            all_nodes[res_pos].depth = min(all_nodes[res_pos].depth, all_nodes[node_pos].depth+1);
            Transition tbs;
            tbs.front_state = node_pos;
            tbs.next_state = res_pos;
            tbs.is_observe_action = true;
            tbs.action_number = i;
            tbs.is_true = true;
            expand(tbs, true, new_node);
           
            // cout << "from node:" << node_pos << "epis action pos done: " << in.mine_epis_actions[i].name << " ================= " << endl;
            // for (size_t xx = 0; xx < all_nodes.size(); ++xx)
            // {
            //     cout <<"node " << xx << ": " << all_nodes[xx].flag << " " << (all_nodes[xx].isolated ? " isolated" : " connected") << endl;
            // }
            // cout << " ================================================================= " << endl;

            // cout <<  node_pos << " after action : " << in.mine_epis_actions[i].name << " neg :" << endl;
            int res_pos1 = checknode(res[1]);
            if (res_pos1 == node_pos) continue;
            new_node = false;
            if (res_pos1 == -1) {
                Node newNode(TOBEEXPLORED, false, res[1], all_nodes[node_pos].depth+1);
                add_node(newNode);
                res_pos1 = all_nodes.size()-1;
                new_node = true;
            }
            all_nodes[res_pos].depth = min(all_nodes[res_pos].depth, all_nodes[node_pos].depth+1);
            Transition tbs1;
            tbs1.front_state = node_pos;
            tbs1.next_state = res_pos1;
            tbs1.is_observe_action = true;
            tbs1.action_number = i;
            tbs1.is_true = false;
            expand(tbs1, true, new_node);
            
            if (all_nodes[res_pos1].flag == FINAL_GOAL && all_nodes[res_pos].flag == FINAL_GOAL) {
                goal_propagation(node_pos, true, i);
                return;
            }
            if (searchtype == 1 && !execed) {
                hert_nodes = res_pos;
                execed = true;
            }

            // cout << "from node:" << node_pos << "epis action neg done: " << in.mine_epis_actions[i].name << " ================= " << endl;
            // for (size_t xx = 0; xx < all_nodes.size(); ++xx)
            // {
            //     cout <<"node " << xx << ": " << all_nodes[xx].flag << " " << (all_nodes[xx].isolated ? " isolated" : " connected") << endl;
            // }
            // cout << " ================================================================= " << endl;
        }
    }
    // 进行物理演进
    for (size_t i = 0; i < in.mine_ontic_actions.size(); ++i) {
// cout << "node " << node_pos << " to test ontic action: " << in.mine_ontic_actions[i].name << endl;
        if (all_nodes[node_pos].kb.neg_entails(in.mine_ontic_actions[i].pre_con, in.mine_constraint)) {
// if (node_pos == 802)
//     cout << "node " << node_pos << " doing... ontic action: " << in.mine_ontic_actions[i].name << endl;
            // clock_t ontic_start = clock();
            ACDF res = all_nodes[node_pos].kb.ontic_prog(in.mine_ontic_actions[i], in.mine_constraint);
            // clock_t ontic_end = clock();
            // ontic_progression_time += difftime(ontic_end, ontic_start) / 1000000.0;
            if (check_zero_dead(res)) continue;
            
            int res_pos = checknode(res);
// if (node_pos == 802)
//     cout << "res pos: " << res_pos << endl;
            if (res_pos == node_pos) continue;
            bool new_node = false;
            if (res_pos == -1) {
                Node newNode(TOBEEXPLORED, false, res, all_nodes[node_pos].depth+1);
                add_node(newNode);
                // cout << all_nodes.size() << endl;
                res_pos = all_nodes.size()-1;
                new_node = true;
            }
            all_nodes[res_pos].depth = min(all_nodes[res_pos].depth, all_nodes[node_pos].depth+1);
            Transition tbs;
            tbs.front_state = node_pos;
            tbs.next_state = res_pos;
            tbs.is_observe_action = false;
            tbs.action_number = i;
            expand(tbs, false, new_node);

            if (all_nodes[res_pos].flag == FINAL_GOAL) {
// if (node_pos == 802)
//     cout << "goal" << endl;
                goal_propagation(node_pos, false, i);
                return;
            }

            if (searchtype == 1 && !execed) {
                hert_nodes = res_pos;
                execed = true;
            }

            // cout <<  "from node:" << node_pos << "ontic action done: " << in.mine_ontic_actions[i].name << " ================= " << endl;
            // for (size_t xx = 0; xx < all_nodes.size(); ++xx)
            // {
            //     cout <<"node " << xx << ": " << all_nodes[i].flag << " " << (all_nodes[xx].isolated ? " isolated" : " connected") << endl;
            // }
            // cout << " ================================================================= " << endl;
        }
    }

    if (is_exist_edge_from_node(node_pos)) {
        all_nodes[node_pos].flag = EXPLORED;
    } else {
        all_nodes[node_pos].flag = DEAD;
        dead_propagation(node_pos);
    }

    // cout << " ------------------------------- " << endl;
    // for (vector<Transition>::const_iterator e = all_edges.begin();
    // e != all_edges.end(); ++e) {
    //     cout << e->front_state << " - "
    //         << (e->is_observe_action ? in.mine_epis_actions[e->action_number].name : in.mine_ontic_actions[e->action_number].name)
    //         << " - " << e->next_state << endl;
    //     // all_nodes[e->next_state].kb.print();
    // }

}

// Algorithm 8
void Plan::expand(Transition ts, bool epis, bool new_node) {
// if (ts.front_state == 802) {
// cout << "expand..." << endl;
// cout << ts.front_state << " - "
//     << (ts.is_observe_action ? in.mine_epis_actions[ts.action_number].name : in.mine_ontic_actions[ts.action_number].name)
//     << " - " << ts.next_state << endl;
// }
    bool edge_exist = false;
    for (size_t i = 0; i < all_edges.size(); ++i)
        if (all_edges[i].front_state == ts.front_state && all_edges[i].next_state == ts.next_state)
            edge_exist = true;
    if (!edge_exist) {
        all_edges.push_back(ts);
    }
    if (!new_node) {
        reconnection_propagation(ts.next_state);
    } else {
        all_nodes[ts.next_state].isolated = false;
        if (all_nodes[ts.next_state].kb.neg_entails(in.mine_goal, in.mine_constraint, true, &(all_nodes[ts.next_state].value))) {
        // impossible case:: || (epis && !all_nodes[ts.next_state].kb.obj_consistent(all_nodes[ts.front_state].kb, in.mine_constraint)) )
            all_nodes[ts.next_state].flag = FINAL_GOAL;
        } else {
            all_nodes[ts.next_state].flag = TOBEEXPLORED;
        }
    }
    // cout << "---------------------------" << endl;
    // cout << ts.front_state << " - "
    //     << (ts.is_observe_action ? in.mine_epis_actions[ts.action_number].name : in.mine_ontic_actions[ts.action_number].name)
    //     << " - " << ts.next_state << endl;
    // cout << "-------------------------------------------------------" << endl << endl;
}

// Algorithm 12
void Plan::dead_propagation(int node_num) {
    //cout << "dead propagation..." << endl;
    for (size_t i = 0; i < all_edges.size(); ) {
        if (all_edges[i].next_state == node_num) {
            int front = all_edges[i].front_state;
            if (!all_edges[i].is_observe_action)
                all_edges.erase(all_edges.begin()+i);
            else{
                for (size_t j = 0; j < all_edges.size(); j++) {
                    if ((all_edges[i].front_state == all_edges[j].front_state) && (all_edges[i].action_number == all_edges[j].action_number)) {
                        if (j!=i) {
                            isolation_propagation(all_edges[j].next_state);
                            if (i > j) {
                                all_edges.erase(all_edges.begin()+i);
                                all_edges.erase(all_edges.begin()+j);
                                --i;
                            }
                            else{
                                all_edges.erase(all_edges.begin()+j);
                                all_edges.erase(all_edges.begin()+i);
                                --i;
                            }
                        }
                    }
                }
            }
            bool is_front_dead = true;
            for (size_t k = 0; k < all_edges.size(); k++) {
                if (front == all_edges[k].front_state)
                    is_front_dead = false;
            }
            //may change num of all_edges
            if (is_front_dead)
                dead_propagation(front);
        }
        else
            ++i;
    }
}

// Algorithm 11
void Plan::isolation_propagation(int node_num) {
    //cout << "isolation_propagation..." << endl;
    bool in_coming_edge = false;
    for (size_t i = 0; i < all_edges.size(); ++i)
        if (all_edges[i].next_state == node_num
        && all_nodes[all_edges[i].front_state].isolated == false) {
            in_coming_edge = true;
            break;
        }
    if (!all_nodes[node_num].isolated && !in_coming_edge) {
        all_nodes[node_num].isolated = true;
        for (size_t i = 0; i < all_edges.size(); ++i)
            if (all_edges[i].front_state == node_num)
                isolation_propagation(all_edges[i].next_state);
    }    
}

// Algorithm 9
void Plan::reconnection_propagation(int node_num) {
    //cout << "reconnection_propagation..." << endl;
    if (all_nodes[node_num].isolated) {
        all_nodes[node_num].isolated = false;
        for (size_t i = 0; i < all_edges.size(); ++i)
            if (all_edges[i].front_state == node_num) {
                reconnection_propagation(all_edges[i].next_state);
            }
    }    
}

int Plan::get_tobeexplored_node() {
    if (searchtype == kWidthFirst || searchtype == kDepthFirst) {
        if (searchtype == kDepthFirst) {
            if (all_nodes[hert_nodes].flag == TOBEEXPLORED && !all_nodes[hert_nodes].isolated) {
                return hert_nodes;
            } else {
                /*
                // find available father node
                int father_node = hert_nodes;
                for (size_t i = 0; i < all_edges.size() && father_node != 0; ++i) {
                    if (all_edges[i].next_state == father_node) {
                        for (size_t j = 0; j < all_edges.size(); ++j) {
                            if (all_edges[j].front_state == all_edges[i].front_state
                                && all_nodes[all_edges[j].next_state].flag == TOBEEXPLORED
                                && !all_nodes[all_edges[j].next_state].isolated) {
                                return all_edges[j].next_state;
                            }
                        }
                    }
                    father_node = all_edges[i].next_state;
                    i = 0;
                }
                //*/
            }
        }
        for (size_t i = explored_num + 1; i < all_nodes.size(); ++i) {
            if (all_nodes[i].flag == TOBEEXPLORED && !all_nodes[i].isolated) {
                return i;
            }
        }
        return -1;    
    } else {
        if (heuristic_que_.empty())
            return -1;
        int ret = -1;
        vector<PlanHelper> phv;
        while (! heuristic_que_.empty()) {
            PlanHelper ph = heuristic_que_.top();
            heuristic_que_.pop();
            if (all_nodes[ph.node_id_].flag == TOBEEXPLORED && !all_nodes[ph.node_id_].isolated) {
                ret = ph.node_id_;
                break;
            } else {
                phv.push_back(ph);
            }
        }
        for (size_t i = 0; i < phv.size(); ++ i) {
            heuristic_que_.push(phv[i]);
        }
        return ret;
    }
}
    

// Algorithm 10
void Plan::goal_propagation(int start_node_num, bool is_observe_action, int act_num) {
// cout << "goal_propagation..." << endl;
// cout << start_node_num << ": " << all_nodes[start_node_num].flag << endl;
    all_nodes[start_node_num].flag = FINAL_GOAL;
    // all_nodes[start_node_num].value *= 10;
    for (size_t i = 0; i < all_edges.size(); ) {
        if (all_edges[i].front_state == start_node_num) {
            if (all_edges[i].action_number != act_num || is_observe_action != all_edges[i].is_observe_action) {
                isolation_propagation(all_edges[i].next_state);
                all_edges.erase(all_edges.begin()+i);
            }
            else
                ++i;
        }
        else
            ++i;            
    }

    for (size_t i = 0; i < all_edges.size(); ++i) {
        if (all_edges[i].next_state == start_node_num) {
            if (!all_edges[i].is_observe_action) {
                goal_propagation(all_edges[i].front_state, false, all_edges[i].action_number);
            } else {
                for (size_t j = 0; j < all_edges.size(); ++j)
                    if (j != i) {
                        if (all_edges[j].is_observe_action && all_edges[j].front_state \
                        == all_edges[i].front_state && all_edges[j].action_number == all_edges[i].action_number) {
                            if (all_nodes[all_edges[j].next_state].flag == FINAL_GOAL)
                                goal_propagation(all_edges[i].front_state, true, all_edges[i].action_number);
                            break;
                        }
                    }
            }
        }
    }
    // cout << start_node_num << all_nodes[start_node_num].flag << endl;
    return;
}

bool Plan::is_exist_edge_from_node(int n) {
    for (size_t i = 0; i < all_edges.size(); ++i) {
        if (all_edges[i].front_state == n)
            return true;
    }
    return false;    
}

int Plan::checknode(ACDF ed) {
    // return -1;
    for (size_t i = 0; i < all_nodes.size(); ++i)
        if ( all_nodes[i].kb.equals(ed, in.mine_constraint)) {
            // ed.print();
            // cout << "equals with node " << i <<  " : ------------------- " << endl;
            // all_nodes[i].kb.print();
            // cout << "-------------------------" << endl;
            return i;
        }
    return -1;   
}

bool Plan::check_zero_dead(ACDF ed) {
    return ed.acdf_terms.size() == 0;
   
}

void Plan::BuildPlan() {
    if (all_nodes[0].flag != FINAL_GOAL) {
        cout<<"no plan"<<endl;
        return;
    }
    vector<Transition> goal_edges;
    for (size_t i = 0; i < all_edges.size(); ++i)
        if (all_nodes[all_edges[i].front_state].flag == FINAL_GOAL && all_nodes[all_edges[i].next_state].flag == FINAL_GOAL)
            goal_edges.push_back(all_edges[i]);
    set<int> nodes;  // 标记节点是否在树里面
    printf("\nPlan tree:\n");
    // cout << goal_edges.size() << endl;  // print the size of goal_edges
    plan_tree_node_num = 0;
    plan_tree_depth = show_build_result(0, goal_edges, 0, nodes, -1);
}

void Plan::show_statistic() {
    if (search_time < 0.01) search_time = 0.01;
    printf("\nStatistic:\n");
    // printf("  preprocess time: %.4fs\n", preprocess_time);
    // printf("  epis progression time: %.4fs\n", epis_progression_time);
    // printf("  ontic progression time: %.4fs\n", ontic_progression_time);
    printf("  search time:\t  %.2fs\n", search_time);
    printf("  total time:\t  %.2fs\n", preprocess_time+search_time);
    printf("  solution depth: %d\n", plan_tree_depth);
    printf("  solution size:  %d\n", plan_tree_node_num);
    printf("  search size:\t  %lu\n", all_nodes.size());
}

void Plan::latex_statistic() {
    if (search_time < 0.01) search_time = 0.01;
    printf(" & %lu & %lu+%lu & %lu & 1 & %.2f-%.2f(%d/%d/%lu) \\\\\n", agents.size(), in.mine_epis_actions.size(), \
        in.mine_ontic_actions.size(), findAtomsByIndex.size(), preprocess_time+search_time, \
        search_time, plan_tree_depth, plan_tree_node_num, all_nodes.size());
}

int Plan::show_build_result(int node_num, const vector<Transition> &goal_edges, int tab_num, set<int> nodes, int oldnode) {
    int depth = 0;
    ++plan_tree_node_num;
    ++tab_num;
    vector<Transition> next_trans;  // all edges from the same node node_num
    if (oldnode != -1)
        nodes.insert(oldnode);
    
    for (size_t i = 0; i < goal_edges.size(); ++i)
        if (goal_edges[i].front_state == node_num)
            next_trans.push_back(goal_edges[i]);

    // cout << next_trans.size() << endl;
    for (size_t i = 0; i < next_trans.size(); ++i)
        if (nodes.find(next_trans[i].next_state) == nodes.end()) {
            for (int k = 0; k < tab_num; k++) 
                cout << " ";
            if (next_trans[i].is_observe_action) {
                if (next_trans[i].is_true) {                   
                    cout << in.mine_epis_actions[next_trans[i].action_number].name << " +:" << endl;
                    depth = max(depth, show_build_result(next_trans[i].next_state, goal_edges, tab_num, nodes, node_num) + 1);
                } else {
                    cout << in.mine_epis_actions[next_trans[i].action_number].name << " -:" << endl;
                    depth = max(depth, show_build_result(next_trans[i].next_state, goal_edges, tab_num, nodes, node_num) + 1);
                    
                }
            } else {
                cout << in.mine_ontic_actions[next_trans[i].action_number].name << endl;
                depth = max(depth, show_build_result(next_trans[i].next_state, goal_edges, tab_num, nodes, node_num) + 1);
            }   
        }
    return depth;
}


void Plan::add_node(const Node& node) {
    all_nodes.push_back(node);
    int node_id = all_nodes.size() - 1;
    int heuristic_value = calculate_node_heuristic_value(node);
    heuristic_que_.push(PlanHelper(node_id, heuristic_value));
}

int Plan::calculate_node_heuristic_value(const Node& node) {
    // assert(!in.mine_goal.acdf_terms.empty());
    // if (search_time > 20.0 && !reset_key_) {
    //     // reset heuristic queue
    //     cout << "runout of time" << endl;
    //     vector<PlanHelper> phv; 
    //     while (! heuristic_que_.empty()) {
    //         PlanHelper ph = heuristic_que_.top();
    //         ph.heuristic_value_ = 0;
    //         phv.push_back(ph);
    //     }
    //     for (size_t i = 0; i < phv.size(); ++ i) {
    //         heuristic_que_.push(phv[i]);
    //     }
    //     reset_key_ = true;
    //     return 0;
    // }
    int node_value = 0;
    node.kb.neg_entails(in.mine_goal, in.mine_constraint, true, &node_value);
    // node_value = node.value;//a -- *search_difficulty/10;
    // node_value = node.value;//b -- *search_difficulty/10;
    // cout << node_value << endl;
    // if(node.depth>6) value -= 100;
    return node_value;//-node.kb.kb_size();
}
