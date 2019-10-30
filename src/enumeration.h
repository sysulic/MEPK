#ifndef __ENUMERATE_H__
#define __ENUMERATE_H__

// enumeration
enum AtomType {
	TRUE, FALSE, UNDEFINED, UNSAT
};

/* different type of actions */
enum ActionType {  
    UNDEFINE = 0,
    ONTICACTION = 1,
    SENSEACTION = 2,
    TERMINATE = 3,
};

/* different type of the edges in LAO* */
enum EdgeType {
    ONTICEDGE = 0,
    EPISEDGE = 1,
};

#endif