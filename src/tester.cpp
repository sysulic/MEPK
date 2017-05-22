#include "tester.h"

Tester::Tester(const char *domain, const char *p) {
    i.exec(domain, p);
    kb = init = i.init;
    constraint = i.constraint;
    add(kb);
    goal = i.goal;
}

void Tester::reset() {
    kb = init;
    action_sequnce.clear();
    kbs.clear();
    print_KB();
    print_actions(true);
}

void Tester::testing() {
    print_KB();
    print_actions(true);
    print_help();
    // testing
    while (true) {
        cout << ">> ";
        string command = get_command();
        if (command[0] == 'h') {
            print_help();
        } else if (command[0] == 'r') {
            reset();
        } else if (command.find("==") != string::npos) {
            equivalent(stoi(command.substr(command.find_first_of('k')+1, command.find_first_of('='))),
                stoi(command.substr(command.find_last_of('k')+1)));
        } else if (command == "ks") {
            print_all_KBs();
        } else if (command[0] == 'k') {
            print_KB();
        } else if (command[0] == 'g') {
            print_goal();
        } else if (command == "aa") {
            print_actions(true);
        } else if (command[0] == 'a') {
            print_actions();
        } else if (command[0] == 's') {
            print_action_sequnce();
        } else if (command[0] == 'e' || command[0] == 'E') {
        	try_epis_prog(stoi(command.substr(1, command.length()-2)),
        		command[command.length()-1]);
        } else if (command[0] == 'o' || command[0] == 'O') {
        	try_ontic_prog(stoi(command.substr(1)));
        }
    }
}

void Tester::add(const ACDF & kb) {
    string kb_name = to_string(action_sequnce.size()) + ". ";
    if (kbs.size() == 0) kb_name += "*init*  ";
    for (list<string>::const_iterator action = action_sequnce.begin();
        action != action_sequnce.end(); ++action)
        kb_name += *action + ", ";
    kb_name = kb_name.substr(0, kb_name.length()-2);
    kbs[kb_name] = kb;
}

void Tester::try_epis_prog(size_t action_no, char symbol) {
    size_t index = 0;
    for (vector<EpisAction>::const_iterator epis_action = epis_actions.begin();
        epis_action != epis_actions.end(); ++epis_action) {
        if (index++ != action_no) continue;
	    if (!kb.neg_entails(epis_action->pre_con, constraint)) {
	        cout << "KB can't entail " << epis_action->name << " :" << endl;
	        print_KB();
	        cout << "precondition :" << endl;
	        epis_action->pre_con.print();
		    cout << "----------------------------------------------------------------------------" << endl;
	        continue;
	    } else {
	        cout << "KB entails precondition of action \""
	            << epis_action->name << "\" :" << endl;
    		if (symbol == '+') {
	        	kb = kb.epistemic_prog(*epis_action, constraint).front();
	        	action_sequnce.push_back(epis_action->name+"+");
                add(kb);  // must after action_sequnce increased
	        }
    		else if (symbol == '-') {
	        	kb = kb.epistemic_prog(*epis_action, constraint).back();
	        	action_sequnce.push_back(epis_action->name+"-");
                add(kb);
	        }
	        print_KB();
	        print_actions(true);
	    }
    	return;
    }
}

void Tester::try_ontic_prog(size_t action_no) {
    size_t index = 0;
    OnticAction taken_action;
    for (vector<OnticAction>::const_iterator ontic_action = ontic_actions.begin();
        ontic_action != ontic_actions.end(); ++ontic_action) {
        if (index++ != action_no) continue;
        taken_action = *ontic_action;
        break;
    }
    if (!kb.neg_entails(taken_action.pre_con, constraint)) {
        cout << "KB can't entail " << taken_action.name << " :" << endl;
        print_KB();
        cout << "precondition :" << endl;
        taken_action.pre_con.print();
	    cout << "----------------------------------------------------------------------------" << endl;
        return;
    } else {
        cout << "KB entails precondition of action \""
            << taken_action.name << "\" :" << endl;
        kb = kb.ontic_prog(taken_action, constraint);
	    action_sequnce.push_back(taken_action.name);
        add(kb);
        print_KB();
        print_actions(true);
    }
}

string Tester::get_command() const {
    // get the command
    string command = "";
    do {
    	if (command != "") {
    		cout << ">> Command not found! (input \"h\" for help)" << endl;
    		cout << ">> ";
    	}
        cin >> command;
    } while (command[0] != 'h' && command[0] != 'k' && command[0] != 'a'
        && command[0] != 'e' && command[0] != 'o' && command[0] != 's'
        && command[0] != 'r' && command[0] != 'g' && command[0] != 'n');
    return command;
}

void Tester::print_KB() const {
    cout << "Current Knowledge Base: ----------------------------------------------------" << endl;
    kb.print();
    cout << "----------------------------------------------------------------------------" << endl;
}

void Tester::print_all_KBs() const {
    cout << "All Knowledge Base: --------------------------------------------------------" << endl;
    for (map<string, ACDF>::const_iterator kb = kbs.begin();
        kb != kbs.end(); ++kb) {
        cout << kb->first << endl;
    }
    cout << "----------------------------------------------------------------------------" << endl;
}

void Tester::equivalent(size_t k1, size_t k2) const {
    ACDF kb1, kb2;
    for (map<string, ACDF>::const_iterator kb = kbs.begin();
        kb != kbs.end(); ++kb) {
        string kb_name = kb->first;
        if (kb_name.substr(0, kb_name.find_first_of('.')) == to_string(k1))
            kb1 = kb->second;
        if (kb_name.substr(0, kb_name.find_first_of('.')) == to_string(k2))
            kb2 = kb->second;
    }

    cout << "----------------------------------------------------------------------------" << endl;
    if (kb1.strong_entails(kb2, constraint)) cout << "  KB " << k1 << " |-> KB " << k2 << ", ";
    else  cout << "KB " << k1 << " ->| KB " << k2 << ", ";
    if (kb2.strong_entails(kb1, constraint)) cout << "KB " << k2 << " |-> KB " << k1 << endl;
    else  cout << "KB " << k2 << " ->| KB " << k1 << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "KB " << k1 << ":" << endl;
    kb1.print();
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "KB " << k2 << ":" << endl;
    kb2.print();
    cout << "----------------------------------------------------------------------------" << endl;
}

void Tester::print_goal() const {
    if (kb.neg_entails(goal, constraint))
    	cout << "Init can entail goal: ----------------------------------------------------------" << endl;
    else
    	cout << "Init can't entail goal: --------------------------------------------------------" << endl;
    goal.print();
    cout << "----------------------------------------------------------------------------" << endl;
}

void Tester::print_actions(bool print_entailed_action) const {
	if (print_entailed_action)
	    cout << "All epistemic actions that can be taken: -----------------------------------" << endl;
    else
    	cout << "All epistemic actions: -----------------------------------------------------" << endl;
    size_t epis_no = 0;
    bool epis_none = true;
    for (vector<EpisAction>::const_iterator epis_action = epis_actions.begin();
        epis_action != epis_actions.end(); ++epis_action) {
    	if (kb.neg_entails(epis_action->pre_con, constraint)) {
    		epis_none = false;
	        cout << "  " << epis_no << "\t==>\t" << epis_action->name << endl;
	    }
	    else
	    	if (!print_entailed_action)
		        cout << "  " << epis_no << "\t-/-\t" << epis_action->name << endl;
		epis_no++;
    }
    if (epis_none) cout << "**** No avaliable epistemic actions ****" << endl;

    if (print_entailed_action)
	    cout << "All ontic actions that can be taken: ---------------------------------------" << endl;
    else
    	cout << "All ontic actions: ---------------------------------------------------------" << endl;
    size_t ontic_no = 0;
    bool ontic_none = true;
    for (vector<OnticAction>::const_iterator ontic_action = ontic_actions.begin();
        ontic_action != ontic_actions.end(); ++ontic_action) {
    	if (kb.neg_entails(ontic_action->pre_con, constraint)) {
    		ontic_none = false;
        	cout << "  " << ontic_no << "\t==>\t" << ontic_action->name << endl;
        }
	    else
	    	if (!print_entailed_action)
	        	cout << "  " << ontic_no << "\t-/-\t" << ontic_action->name << endl;
    	ontic_no++;
    }
    if (ontic_none) cout << "**** No avaliable ontic actions ****" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
}

void Tester::print_action_sequnce() const {
    cout << "Action Sequnce: ------------------------------------------------------------" << endl;
    if (action_sequnce.empty()) {
    	cout << "**** None ****" << endl;
    	return;
    }
    size_t counter = 1;
    for (list<string>::const_iterator action = action_sequnce.begin();
    	action != action_sequnce.end(); ++action)
    	cout << counter++ << ". " << *action << endl;
    cout << "----------------------------------------------------------------------------" << endl;
}

void Tester::print_help() {
    cout << "--------------------  Input the command ------------------------------------" << endl;
    cout << "                 h - this help info" << endl;
    cout << "                 r - back to initial state" << endl;
    cout << "                 k - print current KB" << endl;
    cout << "                ks - print all KBs" << endl;
    cout << "      k[no]==k[no] - tell if KB k1 equals KB k2" << endl;
    cout <<"      (e.g. \"k1==k3\" is to determine if KB k1 equals KB k2" << endl;
    cout << "                 n - print negation of current KB" << endl;
    cout << "                 g - print goal" << endl;
    cout << "                aa - only print actions that can be done" << endl;
    cout << "                 a - print all actions" << endl;
    cout << "                 s - print action sequnce" << endl;
    cout << "      e+[no]+[+|-] - take epis action" << endl;
    cout <<"      (e.g. \"e3+\" means taking the third epistemic action's positive observe" << endl;
    cout <<"            \"e5-\" means taking the fifth epistemic action's negative observe)" << endl;
    cout << "            o+[no] - take epis action" << endl;
    cout <<"      (e.g. \"o12\" means taking the twelfth ontic action)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
}
