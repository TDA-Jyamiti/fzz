#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "fzz.h"

void getFilePurename(const std::string& filename, std::string *purename) {
    auto pos = filename.find_last_of("/\\");
    if (pos != std::string::npos) {
        *purename = filename.substr(pos + 1);
    } else {
        *purename = filename;
    }
    
    pos = purename->find_last_of(".");
    *purename = purename->substr(0, pos);
}

void parseSimplex(const std::string& str, char &op, FZZ::Simplex &simp) {
    std::istringstream iss(str);
    iss >> op;

    FZZ::Integer index;
    while (iss >> index) { simp.push_back(index); }
}

int main(const int argc, const char *argv[]) {
    if (argc < 2) 
    { std::cerr << "Err: no enough input" << std::endl; return -1; }

    const std::string infilename(argv[1]);
    std::ifstream filt_fin(infilename);

    if (!filt_fin)
    { std::cerr << "Err: input file open failed" << std::endl; return -1; }

    std::string line;
    char op;
    std::vector<FZZ::Simplex> filt_simp;
    std::vector<bool> filt_op;

    while (filt_fin) {
        std::getline(filt_fin, line);
        if (line.size() == 0) { continue; }

        filt_simp.emplace_back();
        parseSimplex(line, op, filt_simp.back());

        if (op == 'i') {
            filt_op.emplace_back(true);
        } else {
            assert(op == 'd');
            filt_op.emplace_back(false);
        }
    }

    filt_fin.close();

    std::vector< std::tuple<FZZ::Integer, FZZ::Integer, FZZ::Integer> > persistence;
    FZZ::FastZigzag fzz;
    fzz.compute(filt_simp, filt_op, &persistence);

    std::string purename;
    getFilePurename(infilename, &purename);
    std::ofstream pers_fout(purename + "_pers");

    for (const auto& e : persistence) {
        pers_fout << std::get<2>(e) << " " << std::get<0>(e) 
            << " " << std::get<1>(e) << std::endl;    
    }

    return 0;
}
