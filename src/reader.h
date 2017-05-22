#ifndef READER_H
#define READER_H

#include "define.h"

using namespace std;

class Reader
{
 public:
  /****** common part ******/
  StringSet atomicPropSet;

  /****** domain part ******/
  string domainName;
  StringSet types;
  // list<谓词, 多对<类型, list<变量> > >
  PredicateSet predicates;
  PreEpistemicActionList epistemicActions;
  PreOnticActionList onticActions;

  /****** problem part ******/
  string problemName;
  MultiTypeList objects;
  StringList agents;
  Formula init;
  Formula constraint;
  Formula goal;

 public:
  Reader() {}
  ~Reader() {}

  void exec(const char* dFile, const char* pFile);

  void printInit(ofstream & out_begin, ofstream & out_end);
  void printConstraint(ofstream & out_begin, ofstream & out_end);
  void printGoal(ofstream & out_begin, ofstream & out_end);
  /*
   * Data: Jul 23, 2016
   * Author: Frank
   * Changlog: add para bool, to determine if edit those actions before,
   *           mainly for the operation get_complement.
   */
  void printEpistemicActions(ofstream & out_file, bool);
  void printOnticActions(ofstream & out_file, bool);

};

#endif
