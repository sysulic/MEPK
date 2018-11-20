#include "header.h"
#include "plan.h"

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

// search data
int atomNum, solNum, expNum, solDepth;
double preTime, searchTime;

int main(int argc, char** argv) {

	if (argc < 2) return 0;

	Plan p(argv[1], atoi(argv[2]));
	p.exec_plan();
	p.show_statistic();

	return 0;
}