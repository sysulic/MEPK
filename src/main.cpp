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
	// findAtomsByIndex[0] = "a";
	// findAtomsByIndex[1] = "b1";
	// findAtomsByIndex[2] = "b2";
	// PropTerm phi1(3), phi2(3), mu1(3), mu2(3);
	// phi1.literal[0] = TRUE;
	// phi1.literal[1] = FALSE;
	// phi2.literal[0] = FALSE;
	// phi2.literal[1] = FALSE;
	// // phi2.literal[2] = TRUE;

	// mu1.literal[0] = FALSE;
	// mu1.literal[1] = FALSE;
	// mu1.literal[2] = TRUE;
	// mu2.literal[0] = FALSE;
	// mu2.literal[1] = TRUE;
	// mu2.literal[2] = FALSE;
	// PropDNF phi, mu;
	// phi.dnf.push_back(phi1);// phi.dnf.push_back(phi2);
	// mu.dnf.push_back(mu1); mu.dnf.push_back(mu2);
	// PropDNF res_car = phi.update_cardinality(mu);
	// PropDNF res = phi.update(mu);

	// cout << "phi: ----------------" << endl;
	// phi.print();
	// cout << "update by mu: ----------------" << endl;
	// mu.print();
	// cout << "cardinality result: ----------------" << endl;
	// res_car.print();
	// cout << "result: ----------------" << endl;
	// res.print();


	if (argc < 2 || strlen(argv[1])<5) return 0;  // strlen() for filter empty line in test_cases

	int search_strategy = 0;  // bfs default
	if (argv[2]) search_strategy = atoi(argv[2]);
	else printf("Default: Heuristic search\n");

	Plan p(argv[1], search_strategy);

	if (!parsing_succeed) return 0;
	// initial full atom set
    for (int i = 0; i < atomNum; ++i) full_atom.insert(i);
    	
	p.exec_plan();

	if (argv[3] && atoi(argv[3])==1) p.latex_statistic();
	else p.show_statistic();

	return 0;
}