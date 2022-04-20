#include "utils.h"
#include <string>
#include <sstream>
#include <boost/functional/hash.hpp>

size_t IntVecHash::operator()(const vector<int> &v) const {
    std::size_t seed = 0;
    for (auto i = 0; i < v.size(); i ++) {
        boost::hash_combine(seed, v[i]);
    }

    return seed;
}

bool operator==(const vector<int> &v1, const vector<int> &v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for (auto i = 0; i < v1.size(); i ++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }

    return true;
}

ostream& operator<<(ostream& os, const array<int,3>& a) {
    if (a.size() == 0) {
        os << "()";
        return os;
    }

    os << '(' << a[0];
    for (auto i = 1; i < a.size(); i ++) {
        os << ',' << a[i];
    }
    os << ')';

    return os;
}

ostream& operator<<(ostream& os, const array<int,4>& a) {
    if (a.size() == 0) {
        os << "()";
        return os;
    }

    os << '(' << a[0];
    for (auto i = 1; i < a.size(); i ++) {
        os << ',' << a[i];
    }
    os << ')';

    return os;
}

void splitStrLast(
    const std::string& str, const std::string splitter, 
    std::string* before, std::string* after) {

    auto pos = str.find_last_of(splitter);

    if (before != NULL) {
        *before = str.substr(0, pos);
    }

    if (after != NULL) {
        if (pos != std::string::npos) {
            *after = str.substr(pos + 1);
        } else {
            *after = "";
        }
    }
}

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

void printPers(const std::string outfname,
    const std::vector< std::tuple<Integer, Integer, Integer> > &pers) {

    std::ofstream fout(outfname);
    if (!fout) {
        ERR() << "open '" << outfname << "' for write failed!" << std::endl;
        exit(-1);
    }

    for (auto& e : pers) {
        fout << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e) << std::endl;    
    }
}
