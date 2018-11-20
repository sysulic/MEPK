#ifndef __PARSE_H__
#define __PARSE_H__

#include "header.h"
#include "define.h"

class Parse {
public:
	Parse() {};
	void exec(const char* path, bool showCompileResult = false);
};

#endif