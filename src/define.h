#ifndef DEFINE_H
#define DEFINE_H


#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <set>
#include <list>
#include <map>
#include <queue>
#include <vector>
#include <stack>
#include "Formula.h"

//#include <algorithm>
//#include <sys/time.h>
//#include <sys/resource.h>
//#include <math.h>
//#include <cstdio>

using namespace std;

struct PreEpistemicAction;
struct ConEffect;
struct PreOnticAction;
struct Effect;

typedef list<Effect> EffectList;
typedef set<string> StringSet;
typedef list<string> StringList;
typedef pair<string, StringList> SingleTypePair;
typedef list<SingleTypePair> MultiTypeList;
typedef pair<string, MultiTypeList> MultiTypePair;
typedef set<MultiTypePair> PredicateSet;
typedef list<PreEpistemicAction> PreEpistemicActionList;
typedef list<PreOnticAction> PreOnticActionList;

enum ACTION_TYPE {
    ONTIC,
    OBSERVATION,
    COMMUNICATION,
    SENSING
};

//观察动作的描述 - for preprocessing
struct PreEpistemicAction
{
    string name; // action name
    ACTION_TYPE category; // sense or ontic
    MultiTypeList paras; // parameters
    Formula preCondition;
    Formula observe_pos;
    Formula observe_neg;
};

//动作中的effect（效果二元组）- for preprocessing
struct Effect
{
    Formula aft_condition; //效果中的条件
    Formula con_effect;
};

//物理动作的描述 - for preprocessing
struct PreOnticAction
{
    string name; //动作的名称
    ACTION_TYPE category; // sense or ontic
    MultiTypeList paras;
    Formula preCondition;
    EffectList effects; //效果二元组
};


#endif
