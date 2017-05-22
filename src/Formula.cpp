#include "Formula.h"

Formula::Formula() { label = ""; left = NULL; right = NULL; }

Formula::Formula(string la) {
    label = la;
    left = NULL;
    right = NULL;
}

Formula::Formula(string la, Formula* l, Formula* r) {
    label = la;
    left = l;
    right = r;
}

Formula::Formula(const Formula & f)
    : label(f.label), left(NULL), right(NULL) {
    if (f.left) left = new Formula(*f.left);
    if (f.right) right = new Formula(*f.right);
}

Formula::~Formula() {
    if (left) { delete left; left = NULL; }
    if (right) { delete right; right = NULL; }
}

void Formula::set_complement() {
    if (label == "True") {
        label = "False";
        return;
    } else if (label == "False") {
        label = "True";
        return;
    }
    Formula* tmp = new Formula(label, left, right);
    label = "!";
    left = tmp;
    right = NULL;
}

void Formula::set_neg_observe() {
    if (label == "True") {
        label = "False";
        return;
    } else if (label == "False") {
        label = "True";
        return;
    }
    Formula* tmp = new Formula("!", left, NULL);
    left = tmp;
}

void Formula::show(ofstream & file, size_t deep) const {
    for (size_t i = 0; i < deep; i++) file << " ";
    file << label << endl;
    // file << &label << endl;  // check label's address
    if (left) left->show(file, deep+1);
    if (right) right->show(file, deep+1);
}

void Formula::print(size_t deep) const {
    for (size_t i = 0; i < deep; i++) cout << " ";
    cout << label << endl;
    // cout << &label << endl;  // check label's address
    if (left) left->print(deep+1);
    if (right) right->print(deep+1);
}

/*
 * The function is to replace all "->"s in
 * binary tree with "|" and "!".
 *
 * E.g:
 *             A -> B <=> ¬A V B
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | imply (A) |       ->      |       |      |
 * |       (B) |     /   \     |     /   \    |
 * |           |    A    B     |    !    B    |
 * |           |               |    A         |
 *  ------------------------------------------
 */
void Formula::removeImply() {
    if (label != "->") return;
    Formula* leftF = new Formula("!", left, NULL);
    label = "|";
    left = leftF;
    if (left) left->removeImply();
    if (right) right->removeImply();
}

/*
 * The function is to replace all "oneof"s in binary tree
 * with "&", "|" and "!".
 *
 * E.g:
 *  oneof (A) (B) (C) <=> (A^¬B^¬C) V (¬A^B^¬C) V (¬A^¬B^C)
 *  -----------------------------------------------------
 * | epddl-doc | before b-tree |       after b-tree      |
 *  -----------------------------------------------------
 * | oneof (A) |     oneof     |                |        |
 * |       (B) |     /   \     |           /          \  |
 * |       (C) |    /    C     |          |           &  |
 * |           |   / \         |       /     \      /  \ |
 * |           |  A  B         |      &      &     &   C |
 * |           |               |    /   \  /   \  / \    |
 * |           |               |   &    ! &    ! !  !    |
 * |           |               |  / \  / / \  / /  /     |
 * |           |               | A  ! C !  B ! A  B      |
 * |           |               |   /   /    /            |
 * |           |               |  B   A    C             |
 *  -----------------------------------------------------
 */
void Formula::removeOneof() {
    if (label != "oneof") return;
    // cout << "In function removeOneof, root: " f->label << "" << endl;
    label = "|";
    vector<Formula*> clause_vec;  // points to each prop in the leaf
    vector<string> prop_vec;  // props in the leaf
    if (right == NULL) {
        cout << "Warning: at least two atomic propositions with oneof!" << endl;
        return;
    }
    clause_vec.push_back(right);
    prop_vec.push_back(right->label);
    Formula* pf = left;
    bool only_oneof = false;
    while (pf->label == "oneof") {
        pf->label = "|";
        clause_vec.push_back(pf->right);
        prop_vec.push_back(pf->right->label);
        pf = pf->left;
        only_oneof = true;
    }
    if (only_oneof) { 
        clause_vec.push_back(pf);  // leftest leaf of oneof
        prop_vec.push_back(pf->label);
    } else {
        clause_vec.push_back(pf);
        prop_vec.push_back(pf->label);  
    }
    const size_t prop_size = prop_vec.size();
    vector<Formula*>::iterator clause_it = clause_vec.begin();
    // neg_counter - a tag for locating which literal should be the negative
    for (size_t neg_counter = 0; clause_it != clause_vec.end(); clause_it++, neg_counter++)
    {
        // generate a CNF in place of the prop in every leaf
        size_t i;
        for (i = 0; i < prop_size-1; i++)
        {
            (*clause_it)->label = "&";
            (*clause_it)->left = new Formula();
            if (i != neg_counter) {
                (*clause_it)->right = new Formula("!");
                (*clause_it)->right->left = new Formula(prop_vec.at(i));
            } else {
                (*clause_it)->right = new Formula(prop_vec.at(i));
            }
            *clause_it = (*clause_it)->left;
        }
        // process the leftest leaf
        if (i != neg_counter) {
            (*clause_it)->label = "!";
            (*clause_it)->left = new Formula(prop_vec.at(i));
        } else {
            (*clause_it)->label = prop_vec.at(i);
        }
    }
    if (left) left->removeOneof();
    if (right) right->removeOneof();
    // cout << "In function removeOneof, root: " f->label << " doen" << endl;
}

/*
 * The function is to move all "!"s to the
 * front of atomic propositions
 *
 * E.g:
 *           ¬(A ^ B) <=> ¬A V ¬B
 *           ¬(A V B) <=> ¬A ^ ¬B
 *  ------------------------------------------
 * | epddl-doc | before b-tree | After b-tree |
 *  ------------------------------------------
 * | not(and   |        !      |        |     |
 * |       (A) |       /       |      /   \   |
 * |       (B) |      &        |     !    !   |
 * |    )      |     / \       |    /    /    |
 * |           |    A  B       |   A    B     |
 *  ------------------------------------------
 * | not(or    |        !      |        &     |
 * |       (A) |       /       |      /   \   |
 * |       (B) |      |        |     !    !   |
 * |    )      |     / \       |    /    /    |
 * |           |    A  B       |   A    B     |
 *  ------------------------------------------
 */
void Formula::inwardMoveNot() {
    if (label == "!") {
        // cout << "In function inwardMoveNot, root: " << f->label << "" << endl;
        if (left->label == "&" || left->label == "|") {
            left->label == "&" ? label = "|" : label = "&";
            Formula* r = new Formula("!", left->right, NULL);
            right = r;
            left->right = NULL;
            left->label = "!";
        }
    }
    if (left) left->inwardMoveNot();
    if (right) right->inwardMoveNot();
    // cout << "In function inwardMoveNot, root: " << f->label << " doen" << endl;
    return;
}

/*
 * The function is to merge all "K"s to one "K" for the same agent.
 *
 * E.g:
 *           K(A) ^ K(B) <=> K(A^B)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | and(K(A)) |        &      |       K      |
 * |    (K(B)) |       / \     |      /       |
 * |           |      K  K     |     &        |
 * |           |     /  /      |    / \       |
 * |           |    A  B       |   A  B       |
 *  ------------------------------------------
 */
void Formula::mergeK() {
    // cout << "In function mergeK, root: " << f->label << "" << endl;
    left->right = right->left;
    right->left = NULL;  // avoid deleting B
    delete right; right = NULL;
    label = left->label;
    left->label = "&";
    // cout << "In function mergeK, root: " << f->label << " doen" << endl;
    return;
}

/*
 * The function is to merge all "DK"s to one "DK" for the same agent.
 *
 * E.g:
 *           DK(A) V DK(B) <=> DK(AVB)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | or(DK(A)) |        |      |       DK     |
 * |   (DK(B)) |      /   \    |       /      |
 * |           |     DK   DK   |      |       |
 * |           |    /    /     |     / \      |
 * |           |   A    B      |    A  B      |
 *  ------------------------------------------
 */
void Formula::mergeDK() {
    // cout << "In function mergeDK, root: " << f->label << "" << endl;
    left->right = right->left;
    right->left = NULL;
    delete right; right = NULL;
    label = left->label;
    left->label = "|";
    // cout << "In function mergeDK, root: " << f->label << " doen" << endl;
    return;
}

/*
 * The function is to move all "&"s to the
 * underneath of all "|"s by distributive law.
 *
 * E.g:
 *        (AVB) ^ C <=> A^C V B^C
 *        A ^ (BVC) <=> A^B V A^C
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | and(or    |       &       |       |      |
 * |       (A) |      / \      |     /   \    |
 * |       (B) |     |  C      |    &    &    |
 * |    )      |    / \        |   / \  / \   |
 * |    (C)    |   A  B        |  A  C B  C   |
 *  ------------------------------------------
 * | and(A)    |       &       |       |      |
 * |    (or    |      / \      |     /   \    |
 * |       (B) |     A  |      |    &    &    |
 * |       (C) |       / \     |   / \  / \   |
 * |    )      |      B  C     |  A  B A  C   |
 *  ------------------------------------------
 */
void Formula::inwardMoveAnd() {
    // cout << "In function inwardMoveAnd, root: " << f->label << "" << endl;
    if (left->label == "|") {
        Formula* rr = new Formula(*right);  // "rr" meas right subtree of right subtree of f
        Formula* r = new Formula("&", left->right, rr);
        left->right = right;
        left->label = "&";
        right = r;
        label = "|";
    // cout << "left label is | : doen" << endl;
    } else {
        Formula* ll = new Formula(*left);  // "ll" meas left subtree of left subtree of f
        Formula* l = new Formula("&", ll, right->left);
        right->left = left;
        right->label = "&";
        left = l;
        label = "|";
    // cout << "left label is & : doen" << endl;
    }
    // cout << "In function inwardMoveAnd, root: " << f->label << " doen" << endl;
    return;
}

/*
 * The function is to move all "|"s to the
 * underneath of all "&"s by distributive law.
 *
 * E.g:
 *        A^B V C <=> (AVC) ^ (BVC)
 *        A V B^C <=> (AVB) ^ (AVC)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | or(and    |       |       |       &      |
 * |       (A) |      / \      |     /   \    |
 * |       (B) |     &  C      |    |    |    |
 * |   )       |    / \        |   / \  / \   |
 * |   (C)     |   A  B        |  A  C B  C   |
 *  ------------------------------------------
 * | or (A)    |       |       |       &      |
 * |    (and   |      / \      |     /   \    |
 * |       (B) |     A  &      |    |    |    |
 * |       (C) |       / \     |   / \  / \   |
 * |    )      |      B  C     |  A  B A  C   |
 *  ------------------------------------------
 */
void Formula::inwardMoveOr() {
    // cout << "In function inwardMoveAnd, root: " << f->label << "" << endl;
    if (left->label == "&") {
        Formula* rr = new Formula(*right);  // "rr" meas right subtree of right subtree of f
        Formula* r = new Formula("|",left->right, rr);
        left->right =right;
        left->label = "|";
        right = r;
        label = "&";
    // cout << "left label is | : doen" << endl;
    } else {
        Formula* ll = new Formula(*left);  // "ll" meas left subtree of left subtree of f
        Formula* l = new Formula("|", ll,right->left);
        right->left =left;
        right->label = "|";
        left = l;
        label = "&";
    // cout << "left label is & : doen" << endl;
    }
    // cout << "In function inwardMoveAnd, root: " << f->label << " doen" << endl;
}

/*
 * The function is to remove continuous "not" operator.
 *
 * E.g:
 *               ¬(¬A) <=> A
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | not(not   |       !       |       A      |
 * |       (A) |      /        |              |
 * |    )      |     !         |              |
 * |           |    /          |              |
 * |           |   A           |              |
 *  ------------------------------------------
 */
void Formula::removeDoubleNot() {
    if (left && left->label == "!" &&
        left->left && left->left->label == "!") {
        Formula * tmp = left;
        left = left->left->left;
        tmp->left->left = NULL;  // avoid deleting the nodes below double not
        delete tmp; tmp = NULL;
    }
    if (right && right->label == "!" &&
        right->left && right->left->label == "!") {
        Formula * tmp = right;
        right = right->left->left;
        tmp->left->left = NULL;
        delete tmp; tmp = NULL;
    }
    if (left) left->removeDoubleNot();
    if (right) right->removeDoubleNot();
}

/*
 * The function is to convert "¬K" to "DK¬".
 *
 * E.g:
 *               ¬K(A) <=> DK(¬A)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | not(K     |       !       |      DK      |
 * |       (A) |      /        |      /       |
 * |    )      |     K         |     !        |
 * |           |    /          |    /         |
 * |           |   A           |   A          |
 *  ------------------------------------------
 */
void Formula::convertKtoDK() {
    if (label == "!" && left->label[0] == 'K') {
        label = "D" + left->label;
        left->label = "!";
    }
    if (left) left->convertKtoDK();
    if (right) right->convertKtoDK();
}

/*
 * The function is to convert "¬DK" to "K¬".
 *
 * E.g:
 *               ¬DK(A) <=> K(¬A)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | not(DK    |         !     |       K      |
 * |       (A) |        /      |      /       |
 * |   )       |       DK      |     !        |
 * |           |      /        |    /         |
 * |           |     A         |   A          |
 *  ------------------------------------------
 */
void Formula::convertDKtoK() {
    if (label == "!" && left->label.substr(0,2) == "DK") {
        label = left->label.substr(1, left->label.length()-1);
        left->label = "!";
    }
    if (left) left->convertDKtoK();
    if (right) right->convertDKtoK();
}

/* this is only used once */
void Formula::removeSameLabel() {
    if (left && left->label == "same")
        left->label = label;
    if (right && right->label == "same")
        right->label = label;
    if (left) left->removeSameLabel();
    if (right) right->removeSameLabel();
}

void Formula::convertToCDFTree() {
    removeSameLabel();
    // removeImply();
    // removeOneof();
    inwardMoveNot();
    removeDoubleNot();
    convertKtoDK();
    removeDoubleNot();
    convertDKtoK();
    inwardMoveNot();
    removeDoubleNot();
    transformToCDFTree();
    convertDKtoK();
    removeDoubleNot();
}

void Formula::transformToCDFTree() {
    /*
    if (label == "|" && left && left->label.substr(0, 2) == "DK"
        && right && right->label == left->label)
            mergeDK();
            */
    if (label == "&") {
        /* several cases to make algorithm complete */
        if (left->label == "&")
            left->transformToCDFTree();
        if (left->label[0] == 'K' &&
            right && right->label == left->label)
            mergeK();
        if (left->label == "|" || (right && right->label == "|"))
            inwardMoveAnd();
    }
    if (left != NULL) left->transformToCDFTree();
    if (right != NULL) right->transformToCDFTree();
}

bool Formula::is_objective() {
    if (left && !left->is_objective()) return false;
    if (right && !right->is_objective()) return false;
    return label[0] != 'K' && label.substr(0, 2) != "DK";
}
