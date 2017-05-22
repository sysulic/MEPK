#ifndef FORMULA_H
#define FORMULA_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Formula
{
public:
    string label;
    Formula* left;
    Formula* right;
public:
    Formula();
    Formula(string la);
    Formula(string la, Formula* l, Formula* r);
    Formula(const Formula & f);
    ~Formula();
    void set_complement();
    void set_neg_observe();  // set the observe to neg
    void show(ofstream & file, size_t deep) const;
    void print(size_t deep) const;

    // intermediate structure
    void removeSameLabel();
    void removeImply();
    void removeOneof();
    void removeDoubleNot();
    void inwardMoveNot() ;
    void mergeK();
    void mergeDK();
    void inwardMoveAnd();
    void inwardMoveOr();
    void convertKtoDK();
    void convertDKtoK();
    /*
     * Data: Sep 07, 2016
     * Author: Frank
     * Changelog: DNFTree -> AHDNFTree, and cancel the CNFTree.
     */
    void convertToCDFTree();  // do some preprocessings here
    void transformToCDFTree();  // mainly for transforming

    bool is_objective();
};

#endif
