#include "header.h"
#include "plan.h"
#include <string.h>
#include <set>

using namespace std;

// global variable andfor compile
string domainName;
vector<string> atoms;
map<string, vector<string> > objects;
vector<string> agents;
map<int, string> findAtomsByIndex;
map<string, int> findAtomsByName;
map<string, int> findSensingActionByName;
map<string, int> findOnticActionByName;
vector<SensingAction> sActions;
vector<OnticAction> oActions;
KLDNF init;
KLDNF posGoal;
KLDNF goal;
PropDNF constraint;

bool parsing_succeed = true;
// search data
int atomNum, solNum, expNum, solDepth;
set<int> full_atom;

int main(int argc, char** argv) {
	
	if (argc < 2 || strlen(argv[1])<5) return 0;  // strlen() for filter empty line in test_cases

	int search_strategy = 2;  // bfs default
	if (argv[2]) search_strategy = atoi(argv[2]);
	else printf("Default: BFS searching\n");

	Plan p(argv[1], search_strategy);

	if (!parsing_succeed) return 0;
	// initial full atom set
    for (int i = 0; i < atomNum; ++i) full_atom.insert(i);
    	
	p.exec_plan();
	if (argv[3] && atoi(argv[3])==1) p.latex_statistic();
	else p.show_statistic();
	return 0;
}