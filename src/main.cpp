#include "plan.h"

list<string> agents;

map<int, string> atomsByIndex;
map<string, int> atomsByName;

vector<EpisAction> epis_actions;
vector<OnticAction> ontic_actions;

int main(int argc, char **argv) {

	if (argc < 3) return 0;
    if (argc != 3 && argc != 4) {
        printf("Usage:\n%s domain_file p_file (search_type)\n", argv[0]);
        return 0;
    }
    int search_type = 0;
    if (argc == 4) {
        search_type = atoi(argv[3]);
    }
    Plan p = Plan(argv[1], argv[2], search_type);

    // print info of problem
    // cout << atomsByIndex.size() << " " << epis_actions.size() << " " << ontic_actions.size() << endl;

    p.exec_plan();
    p.show_statistic();

    return 0;
}
