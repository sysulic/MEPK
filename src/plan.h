#ifndef PLAN_H
#define	PLAN_H

#include "initial.h"
#include "heuristicHelper.h"


// 启发式所用的优先队列存放的元素
class PlanHelper {
public:
    PlanHelper(int node_id, int heuristic_value) : node_id_(node_id), heuristic_value_(heuristic_value) {}
public:
    int node_id_;//节点下标，对应plan类里面的all_nodes
    int heuristic_value_;//该节点的评估值
};


// 为PlanHelper类提供比较功能
class PlanHelperComp {
public:
    bool operator()(const PlanHelper& lhs, const PlanHelper& rhs) const {
        return lhs.heuristic_value_ < rhs.heuristic_value_;
    }
};

class Plan{
public:
    Plan(const char *domain, int type = 2);
    void exec_plan();
    
    void explore(int);
    void expand(Transition, bool epis, bool new_node);
    void dead_propagation(int);
    void isolation_propagation(int);
    void reconnection_propagation(int);
    int get_tobeexplored_node();

    void goal_propagation(int, bool, int);
    bool is_exist_edge_from_node(int);
    bool sat_pre(Node, ACDF);
    int checknode(ACDF);
    bool check_zero_dead(ACDF);
    void BuildPlan();
    int show_build_result(int, const vector<Transition> &, int , set<int>, int );
    void show_statistic() const;
    void add_node(const Node& node);
    int calculate_node_heuristic_value(const Node& node);
    
    vector<Node> all_nodes;
private:
    Parse parser;
    
    Initial in;
    int explored_num;
    vector<Transition> all_edges;
    int hert_nodes;
    SearchType searchtype;
    // 统计信息，搜索的节点数就是all_nodes.size()
    int plan_tree_depth;//树的深度
    int plan_tree_node_num;//树的节点数
    float preprocess_time;//预处理时间
    float epis_progression_time;
    float ontic_progression_time;
    float search_time;//搜索时间
    HeuristicHelper helper_;
    // 优先队列，启发式使用
    priority_queue<PlanHelper, vector<PlanHelper>, PlanHelperComp> heuristic_que_;
    bool reset_key_ = false;
};

#endif
