#include "tester.h"
#include "header.h"

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

int main(int argc, char **argv) {
    Tester t(argv[1]);
    t.testing();
	return 0;
}
