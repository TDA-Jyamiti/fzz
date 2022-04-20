#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <utility>
#include <iterator>
#include <unordered_map>
#include <boost/functional/hash.hpp>

typedef int Integer;
typedef std::vector<Integer> Simplex;

using std::vector;
using std::array;
using std::cout;
using std::endl;
using std::ostream;

inline char pathSeparator() {
#if defined _WIN32 || defined __CYGWIN__
    return '\\';
#else
    return '/';
#endif
}

inline std::ostream& ERR() {
    return std::cerr << "ERR: ";
}

struct IntVecHash { 
    size_t operator()(const vector<int> &v) const; 
};

bool operator==(const vector<int> &v1, const vector<int> &v2);

// inline ostream& operator<<(ostream& os, const Vector3d& v) {
//     os << '(' << v[0] << "," << v[1] << "," << v[2] << ")";
//     return os;
// }

// inline ostream& operator<<(ostream& os, const Vector4d& v) {
//     os << '(' << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << ")";
//     return os;
// }

template <class ElemT>
std::string containerToStr(std::vector<ElemT> C, const char *delim) {
    std::ostringstream oss;

    if (!C.empty()) {
        // Convert all but the last element to avoid a trailing ","
        std::copy(C.begin(), C.end()-1,
            std::ostream_iterator<ElemT>(oss, delim));

        // Now add the last element with no delimiter
        oss << C.back();
    }

    return oss.str();
}

template <class T1, class T2> inline
ostream& operator<<(ostream& os, const std::pair<T1, T2>& p) {
    os << '<' << p.first << ',' << p.second << '>';
    return os;
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& a) {
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

ostream& operator<<(ostream& os, const array<int,3>& a);
ostream& operator<<(ostream& os, const array<int,4>& a);

inline int mod(int a, int b) {
    if (a >= 0) {
        return a % b;
    }

    return ((-a/b+1)*b+a) % b;
}

template <class T> inline
bool vecIntersect(const vector<T>& v1, const vector<T>& v2) {
    for (auto e : v1) {
        if (std::find(v2.begin(), v2.end(), e) != v2.end()) {
            return true;
        }
    }

    return false;
}

template<class HashMapType> inline 
void printHashMapLoad(const HashMapType &map) {
    cout << "load_factor=" << map.load_factor()
        << ",max_load_factor=" << map.max_load_factor() 
        << ",bucket_count=" << map.bucket_count() 
        << ",size=" << map.size() << endl;
}

void splitStrLast(
    const std::string& str, const std::string splitter, 
    std::string* before, std::string* after);

void getFilePurename(const std::string& filename, std::string *purename);

template <int L>
struct IntArrayHash { 
    size_t operator()(const array<int,L> &a) const; 
};

template <int L>
size_t IntArrayHash<L>::operator()(const array<int,L> &a) const {
    // cout << "IntArrayHash" << endl;
    // cout << a << endl;

    std::size_t seed = 0;
    for (auto i = 0; i < a.size(); i ++) {
        boost::hash_combine(seed, a[i]);
        // cout << "seed" << i << ": " << seed << endl;
    }

    return seed;
}

template <int L>
struct IntArrayEqual { 
    bool operator()(const array<int,L> &a1, const array<int,L> &a2) const; 
};

template <int L>
bool IntArrayEqual<L>::operator()(const array<int,L> &a1, const array<int,L> &a2) const {
    // cout << "IntArrayEqual" << endl;
    // cout << a1 << endl;
    // cout << a2 << endl;

    for (auto i = 0; i < a1.size(); i ++) {
        if (a1[i] != a2[i]) {
            return false;
        }
    }

    return true;
}

inline void unpackDimId(
    int id, int dim1_cnt, int dim2_cnt, int dim3_cnt,
    int* dim1_id, int* dim2_id, int* dim3_id) {

    *dim3_id = id / (dim2_cnt*dim1_cnt);
    auto left = id % (dim2_cnt*dim1_cnt);
    *dim2_id = left / dim1_cnt;
    *dim1_id = left % dim1_cnt;
}

inline void packDimId(
    int dim1_id, int dim2_id, int dim3_id,
    int dim1_cnt, int dim2_cnt, int dim3_cnt,
    int* id) {

    *id = dim3_id*dim2_cnt*dim1_cnt + dim2_id*dim1_cnt + dim1_id;
}

void printPers(const std::string outfname,
    const std::vector< std::tuple<Integer, Integer, Integer> > &pers);

template <class ElemType>
class VecHash { 
public:
    size_t operator()(const std::vector<ElemType>& v) const; 
};

template <class ElemType>
size_t VecHash<ElemType>
    ::operator()(const std::vector<ElemType>& v) const {

    std::size_t seed = 0;

    for (auto e : v) { boost::hash_combine(seed, e); }

    return seed;
}

template <class ElemType>
class VecEqual { 
public:
    bool operator()(const std::vector<ElemType>& v1, 
        const std::vector<ElemType>& v2) const; 
};

template <class ElemType>
bool VecEqual<ElemType>
    ::operator()(const std::vector<ElemType>& v1, 
        const std::vector<ElemType>& v2) const {

    if (v1.size() != v2.size()) { return false; }

    for (auto i = 0; i < v1.size(); i ++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }

    return true;
}

typedef std::unordered_map< Simplex, Integer,
    VecHash<Integer>, VecEqual<Integer> > SimplexIdMap;

#endif
