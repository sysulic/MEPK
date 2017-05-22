#include "tester.h"

list<string> agents;

map<int, string> atomsByIndex;
map<string, int> atomsByName;

vector<EpisAction> epis_actions;
vector<OnticAction> ontic_actions;

int main(int argc, char **argv) {
    Tester t(argv[1], argv[2]);
    t.testing();
	return 0;
}
