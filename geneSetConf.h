#include <iostream>
#include <vector>
#include <algorithm>
#include "random.h"

class GeneSetConf {

    private:
        int* orgRank1_; // the original configuration for the gene set 1
        int* orgRank2_; // the original configuration for the gene set 2

        int* curRank1_; // the current configuration for the gene set 1
        int* curRank2_; // the current configuration for the gene set 2

        int W1_; // the size of the gene set 1
        int W2_; // the size of the gene set 2
        int W12_; // the size of the common set
        
        long unsigned int S1_; // the rank sum of the gene set 1
        long unsigned int S2_; // the rank sum of the gene set 2
        long unsigned int orgS12_; // the original rank sum of the common set
        long unsigned int curS12_; // the current rank sum of the common set

        int N_; // the number of genes


        int anchor1_; // position of the first gene to be moved
        int anchor2_; // position of the second gene to be moved 
        int propAnchor1_; // proposed position for the anchor1
        int propAnchor2_; // proposed position for the anchor2
        int rank1_or_rank2_; // indicating which configuration is moved

        int* possibleAnchorList1_; // the set of anchors that can be moved for the gene set 1
        int* possibleAnchorList2_; // the set of anchors that can be moved for the gene set 2

        int*possiblePropStepList_; // the set of possible step size;
    public:
        GeneSetConf(std::vector<int> orgRank1, std::vector<int>orgRank2);
        void printInfo(); 
        void Update();
        void setAnchors();
        void selectPropAnchors();
        void checkConsistency();
        int checkRankSum();
        long unsigned int getRankSum();
};

inline int GeneSetConf::checkRankSum() {

    if (curS12_ <= orgS12_) {
        return(1);
    } else {
        return(0);
    }

}   

inline long unsigned int GeneSetConf::getRankSum() {

    return(curS12_);

}

