#include "geneSetConf.h"

// constractor
GeneSetConf::GeneSetConf(std::vector<int> orgRank1, std::vector<int> orgRank2) {

    N_ = orgRank1.size();

    orgRank1_ = new int[N_];
    orgRank2_ = new int[N_];
    curRank1_ = new int[N_];
    curRank2_ = new int[N_];

    W1_ = 0;
    W2_ = 0;
    W12_ = 0;
    S1_ = 0;
    S2_ = 0;
    orgS12_ = 0;
    for (int i = 0; i < N_; i++) {

        orgRank1_[i] = orgRank1[i];
        orgRank2_[i] = orgRank2[i];

        if (orgRank1_[i] == 1) {
            W1_ = W1_ + 1;
            S1_ = S1_ + (i + 1);
        } 

        if (orgRank2_[i] == 1) {
            W2_ = W2_ + 1;
            S2_ = S2_ + (i + 1);
        }
           
        if (orgRank1_[i] == 1 && orgRank2_[i] == 1) {
            W12_ = W12_ + 1;
            orgS12_ = orgS12_ + (i + 1);
        }
    }
              
    curRank1_ = orgRank1_;
    curRank2_ = orgRank2_;

    curS12_ = orgS12_;

    possibleAnchorList1_ = new int[W1_];
    possibleAnchorList2_ = new int[W2_];
    possiblePropStepList_ = new int[N_];

    rank1_or_rank2_ = 1;
 
}         


// print information
void GeneSetConf::printInfo() {

    std::cerr << "The number of genes: " << N_ << "\n";
    std::cerr << "The size of the gene set 1: " << W1_ << "\n";
    std::cerr << "The rank sum of the gene set 1: " << S1_ << "\n";
    std::cerr << "The size of the gene set 2: " << W2_ << "\n";
    std::cerr << "The rank sum of the gene set 2: " << S2_ << "\n";
    std::cerr << "The size of the common set: " << W12_ << "\n";
    std::cerr << "The rank sum of the common set: " << curS12_ << "\n";

}


void GeneSetConf::Update() {

    // **********
    // choose which configures of the gene sets 1 and 2 to be moved
    double u = gen_rand(1.0);
    if (u >= 0.5) {
        rank1_or_rank2_ = 1;
    } else {
        rank1_or_rank2_ = 2;
    }
    // **********

    setAnchors();
    selectPropAnchors();

    if (rank1_or_rank2_ == 1) {
        curRank1_[anchor1_] = 0;
        curRank1_[anchor2_] = 0;
        curRank1_[propAnchor1_] = 1;
        curRank1_[propAnchor2_] = 1;
        curS12_ = curS12_ - (curRank2_[anchor1_] == 1 ? (anchor1_ + 1) : 0) - (curRank2_[anchor2_] == 1 ? (anchor2_ + 1) : 0) + (curRank2_[propAnchor1_] == 1 ? (propAnchor1_ + 1) : 0) + (curRank2_[propAnchor2_] == 1 ? (propAnchor2_ + 1) : 0);
    } else {
        curRank2_[anchor1_] = 0;
        curRank2_[anchor2_] = 0;
        curRank2_[propAnchor1_] = 1;
        curRank2_[propAnchor2_] = 1;
        curS12_ = curS12_ - (curRank1_[anchor1_] == 1 ? (anchor1_ + 1) : 0) - (curRank1_[anchor2_] == 1 ? (anchor2_ + 1) : 0) + (curRank1_[propAnchor1_] == 1 ? (propAnchor1_ + 1) : 0) + (curRank1_[propAnchor2_] == 1 ? (propAnchor2_ + 1) : 0);
    } 

    // for debug
    // std::cout << curS12_ << "\n";
}


void GeneSetConf::setAnchors() {

    // **********
    // store the current rank list to the variables for rank 1 or 2 depending on the indicator 
    int rankNum = 0;
    if (rank1_or_rank2_ == 1) {

        for (int i = 0; i < N_; i++) {
            if (curRank1_[i] == 1) {
                possibleAnchorList1_[rankNum] = i;
                rankNum++;
            }
        }

    } else {

        for (int i = 0; i < N_; i++) {
            if (curRank2_[i] == 1) {
                possibleAnchorList2_[rankNum] = i;
                rankNum++;
            }
        }

    }
    // **********

    // **********
    // obtain two different random integers
    int u1 = 0;
    int u2 = 0;
    while(u1 == u2) {
        u1 = gen_rand(rankNum);
        u2 = gen_rand(rankNum);
    }
    // **********

    if (rank1_or_rank2_ == 1) {
        anchor1_ = possibleAnchorList1_[u1];
        anchor2_ = possibleAnchorList1_[u2];
    } else {
        anchor1_ = possibleAnchorList2_[u1];
        anchor2_ = possibleAnchorList2_[u2];
    }

}


void GeneSetConf::selectPropAnchors() {

    // **********
    // check the region in which the anchors can move
    int ubound1 = std::min(anchor1_, N_ - anchor2_ - 1);
    int ubound2 = std::min(anchor2_, N_ - anchor1_ - 1);
    // **********

    // **********
    // for each step , check whether the anchors can move
    int possibleProbNum = 0;
    for (int i = ubound1; i >= - ubound2; i--) {

        if (rank1_or_rank2_ == 1) {

            if ((curRank1_[anchor1_ - i] == 0 and curRank1_[anchor2_ + i] == 0) or i == 0 or anchor1_ - anchor2_ == i) {

                if ((anchor1_ - anchor2_ != 2 * i) and (curRank2_[anchor1_] + curRank2_[anchor2_] == curRank2_[anchor1_ - i] + curRank2_[anchor2_ + i])) {

                    possiblePropStepList_[possibleProbNum] = i;
                    possibleProbNum++;
                }

            }

        } else {

            if ((curRank2_[anchor1_ - i] == 0 and curRank2_[anchor2_ + i] == 0) or i == 0 or anchor1_ - anchor2_ == i) {

                if ((anchor1_ - anchor2_ != 2 * i) and (curRank1_[anchor1_] + curRank1_[anchor2_] == curRank1_[anchor1_ - i] + curRank1_[anchor2_ + i])) {

                    possiblePropStepList_[possibleProbNum] = i;
                    possibleProbNum++;
                }

            }

        }
    }

    // **********
    // for debug
    // std::cout << possibleProbNum << "\n";

    int u = gen_rand(possibleProbNum);
    propAnchor1_ = anchor1_ - possiblePropStepList_[u];
    propAnchor2_ = anchor2_ + possiblePropStepList_[u];

}


void GeneSetConf::checkConsistency() {

    int tempW1 = 0;
    int tempW2 = 0;
    int tempW12 = 0;
    long unsigned int tempS1 = 0;
    long unsigned int tempS2 = 0;

    for (int i = 0; i < N_; i++) {

        if (curRank1_[i] == 1) {
            tempW1 = tempW1 + 1;
            tempS1 = tempS1 + (i + 1);
        }

        if (curRank2_[i] == 1) {
            tempW2 = tempW2 + 1;
            tempS2 = tempS2 + (i + 1);
        }

        if (curRank1_[i] == 1 && curRank2_[i] == 1) {
            tempW12 = tempW12 + 1;
        }
    }

    int inconsistencyFlag = 0;

    if (tempW1 != W1_) {
        std::cerr << "The size of the gene set 1 is inconsistent. This should have been " << W1_ << " while the current value is " << tempW1 << ".\n";
        inconsistencyFlag = 1;
    }

    if (tempW2 != W2_) {
        std::cerr << "The size of the gene set 2 is inconsistent. This should have been " << W2_ << " while the current value is " << tempW2 << ".\n";
        inconsistencyFlag = 1;
    }

    if (tempW12 != W12_) {
        std::cerr << "The size of the common set is inconsistent. This should have been " << W12_ << " while the current value is " << tempW12 << ".\n";
        inconsistencyFlag = 1;
    }

    if (tempS1 != S1_) {
        std::cerr << "The rank sum of the gene set 1 is inconsistent. This should have been " << S1_ << " while the current value is " << tempS1 << ".\n";
        inconsistencyFlag = 1;
    }

    if (tempS2 != S2_) {
        std::cerr << "The rank sum of the gene set 2 is inconsistent. This should have been " << S2_ << " while the current value is " << tempS2 << ".\n";
        inconsistencyFlag = 1;
    }

    if (inconsistencyFlag == 1) {
        std::cout << "rank1 or rank2: " << rank1_or_rank2_ << "\n";
        std::cout << "anchor1: " << anchor1_ << "\n";
        std::cout << "anchor2: " << anchor2_ << "\n";
        std::cout << "propAnchor1: " << propAnchor1_ << "\n";
        std::cout << "propAnchor2: " << propAnchor2_ << "\n";
    }


    if (inconsistencyFlag == 1) {
        exit(8);
    }

}


