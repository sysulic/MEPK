#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "header.h"
#include "adnf.h"
#include "acdf.h"

using namespace std;

/* 
 * Definitions below are for ADNF
 */

enum ACTION_TYPE {
    ONTIC,
    OBSERVATION,
    COMMUNICATION,
    SENSING
};

// structure
struct SensingAction {
	string name;

    ACTION_TYPE category;  // category of this action

	KLDNF preCon;
	KLDNF posRes;
	KLDNF negRes;
};

struct ConditionalEffect {
	KLDNF condition;
	KLDNF effect;
};

struct OnticAction {
	string name;

    ACTION_TYPE category;  // category of this action

	KLDNF preCon;
	vector<ConditionalEffect> eff;
};

/* the node used in LAO* */
struct LAONode {  
	ACDF kb;
	double heuValue;
	bool isSolved;
	bool isDeadend;

	LAONode(ACDF _kb, double hv, bool iss, bool isd) : 
		kb(_kb), heuValue(hv), isSolved(iss), isDeadend(isd) {}
};

/* the edge used in LAO* */
struct LAOEdge {
    EdgeType et;
    int actionIndex;
    vector<int> childNode;

    LAOEdge() {};
    LAOEdge(EdgeType _et, int _actionIndex, vector<int> _childNode) : et(_et),
        actionIndex(_actionIndex), childNode(_childNode) {};

    bool operator == (const LAOEdge& r) const {
        return et==r.et && actionIndex==r.actionIndex;
    }
};

/* 
 * Definitions below are for ACDF
 */

//观察动作的描述
struct EpisAction
{
    string name; //动作的名称
    ACTION_TYPE category;  // category of this action
    ACDF pre_con; //动作执行的前置条件

    ACDF pos_res; //将所需要观察的“公式”化为ACDF形式， 为了好做演进 positive result
    ACDF neg_res; //将所需要观察的“公式”化为ACDF形式， 为了好做演进 negative result
};

//物理动作中的effect（效果三元组）
struct ConEffect
{
    ACDF condition; //效果中的条件
    ACDF effect;
};

//物理动作的描述
struct OntiAction
{
    string name; //动作的名称
    ACTION_TYPE category;  // category of this action
    ACDF pre_con; //动作执行的前置条件
    vector<ConEffect> con_eff; //效果二元组
};

enum STATE_TYPE {
    TOBEEXPLORED = 0,
    EXPLORED,
    DEAD,
    FINAL_GOAL
};

//搜索算法中的结点
struct Node
{
    ACDF kb; //结点的知识库
    int depth = 0;
    int ancestor_node_id = -1;
    int value = 0;  // for heuristic searching
    //下面两个变量分别是在搜索过程中所需要的两中标记
    STATE_TYPE flag;
    bool isolated;
    Node(){};
    Node(STATE_TYPE s, bool b, ACDF ed, int d, int an_id = 0) { flag = s; isolated = b; kb = ed; depth = d; ancestor_node_id = an_id; };
    ~Node(){};
};

struct Transition
{
    int front_state; //前一个结点
    int next_state;  //后一个结点
    bool is_observe_action; //是否为观察动作
    bool is_true; //是否为感知动作的+
    int action_number;  //动作的编号
};

enum SearchType {
    kHeuristic = 0,
    kDepthFirst = 1,
    kWidthFirst = 2,
};



#endif