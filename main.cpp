#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "geneSetConf.h"
#include "random.h"

int ReadRankFile(const std::string& rank_file, std::vector<int>& orgRank, std::size_t& N) {

    std::ifstream ifs(rank_file.c_str());
    if (ifs.fail()) {
        std::cerr << "Error: Could not open the input file.\n";
        exit(8);
    }

    std::string line;

    // Get feature size
    while(std::getline(ifs, line)) {

        std::istringstream is(line);

        int temp = -1;
        is >> temp;
        N = N + 1;

        if (temp == -1) {
            std::cerr << "parse error" << "\n";
            return -1;
        }

        orgRank.push_back(temp);
    }

    return(0);

}


int main(int argc, char** argv) {

    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " rank_file1 rank_file2 output_file " << std::endl;
        return -1;
    }

    std::string rank_file1 = argv[1];
    std::string rank_file2 = argv[2];
    std::string outfile = argv[3];
    
    long unsigned int MCMCNum = 10000000;
    long unsigned int burnInNum = 10000;

    if (argc >= 5) {
        MCMCNum = atoi(argv[4]);
    }                 
    if (argc >= 6) {
        burnInNum = atoi(argv[5]);
    }

    // **********
    // reading input rank files
    std::vector<int> orgRank1;
    std::vector<int> orgRank2;

    std::size_t N1 = 0;
    std::size_t N2 = 0;

    if (ReadRankFile(rank_file1, orgRank1, N1) != 0) {
        std::cerr << "Cannot read" << std::endl;
        return(-1);
    }

    if (ReadRankFile(rank_file2, orgRank2, N2) != 0) {
        std::cerr << "Cannot read" << std::endl;
        return(-1);
    }

    if (N1 != N2) {
        std::cerr << "The sizes of " << rank_file1 << " and " << rank_file2 << " are inconsistent." << "\n";
    }
    // **********
    
    
    GeneSetConf gsConf(orgRank1, orgRank2);
    gsConf.printInfo();
    gsConf.checkConsistency();

    std::cerr << "The number of burn-in cycles is : " << burnInNum << "\n";
    std::cerr << "The number of MCMC cycles is : " << MCMCNum << "\n";


    std::size_t belowOrgRankSum = 0;

    // **********
    // burn in step
    for (long unsigned int i = 1; i <= burnInNum; i++) {
        gsConf.Update();
    }
    std::cerr << "The burn-in cycles are finished.\n";
    // **********

    for (long unsigned int i = 1; i <= MCMCNum; i++) {

        gsConf.Update();
        belowOrgRankSum = belowOrgRankSum + gsConf.checkRankSum();

        if (i % 100000 == 0) {
            std::cerr << i << " times finished. current rank_sum: " << gsConf.getRankSum() << ". #{MCMC samples: rank_sums <= the target rank_sum}: " << belowOrgRankSum << "\n";
            gsConf.checkConsistency();
        }
    }


    std::ofstream ofs(outfile.c_str());
    if (ofs.fail()) {
        std::cerr << "Error: Could not open the output file.\n";
        exit(8);
    }
    ofs << "MCMC cycle: " << MCMCNum << "\n";
    ofs << "p-value: " << static_cast<double>(belowOrgRankSum) / static_cast<double>(MCMCNum) << "\n";
    ofs.close();

    return(0);
}
