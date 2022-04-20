#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#include "utils.h"

// phat headers
// wrapper algorithm that computes the persistence pairs of a given boundary matrix using a specified algorithm
#include <phat/compute_persistence_pairs.h>

// main data structure (choice affects performance)
#include <phat/representations/vector_vector.h>
#include <phat/representations/bit_tree_pivot_column.h>

// algorithm (choice affects performance)
#include <phat/algorithms/standard_reduction.h>
#include <phat/algorithms/chunk_reduction.h>
#include <phat/algorithms/row_reduction.h>
#include <phat/algorithms/twist_reduction.h>


// 'orig_f_add_id' and 'orig_f_del_id' form a mapping 
// from the up-down filtration to the original filtration
std::vector<Integer> orig_f_add_id;
std::vector<Integer> orig_f_del_id;

Integer simp_num;

void parseSimplex(const std::string& str, char &op, Simplex &simp) {
    std::istringstream iss(str);
    iss >> op;

    Integer index;
    while (iss >> index) { simp.push_back(index); }
}

void getBoundaryChainPhat(const SimplexIdMap &id_map, 
    const Simplex &simp, std::vector<phat::index> &bound_c) {

    bound_c.clear();

    if (simp.size() <= 1) { return; }

    bound_c.reserve(simp.size());

    Simplex bound_simp(simp.begin()+1, simp.end());
    bound_c.push_back(id_map.at(bound_simp));
    // std::cout << "  " << bound_simp << endl;

    for (Integer i = 0; i < simp.size()-1; ++i) {
        bound_simp[i] = simp[i];
        // std::cout << "  " << bound_simp << endl;
        bound_c.push_back(id_map.at(bound_simp));
    }

    std::sort(bound_c.begin(), bound_c.end());
}

inline Integer getDim(const std::vector<phat::index> &bound_c) {
    if (bound_c.size() == 0) { return 0; }
    return bound_c.size() - 1;
}

inline void mapOrdIntv(Integer &b, Integer &d) {
    // assert(b-1 > 0);
    // assert(d < orig_f_add_id.size());

    // Up-down interval is same, 
    // so directly map to interval of input filtration
    b = orig_f_add_id[b-1] + 1;
    d = orig_f_add_id[d];
}

inline void mapRelExtIntv(Integer &p, Integer &b, Integer &d) {
    // assert(d >= simp_num);

    if (b > simp_num) { // Open-closed
        // Map to up-down interval
        std::swap(b, d);
        b = 3*simp_num - b;
        d = 3*simp_num - d;
        p --;

        // Map to interval of input filtration
        b = orig_f_del_id[b-1-simp_num] + 1;
        d = orig_f_del_id[d-simp_num];
    } else { // Closed-closed
        // Map to up-down interval
        d = 3*simp_num - d-1;
        
        // Map to interval of input filtration
        b = orig_f_add_id[b-1];
        d = orig_f_del_id[d-simp_num];

        if (b < d) {
            b = b+1;
        } else {
            std::swap(b, d);
            b = b+1;
            p = p-1;
        }
    }
}

int main(const int argc, const char *argv[]) {
    // std::cout << "fzz starts" << std::endl;

    if (argc < 2) 
    { std::cerr << "Err: no enough input" << std::endl; return -1; }

    const std::string infilename(argv[1]);
    std::ifstream filt_fin(infilename);

    if (filt_fin) 
    { ; /* std::cout << "input: " << infilename << std::endl; */ } 
    else 
    { std::cerr << "Err: input file open failed" << std::endl; return -1; }

    Integer filt_len;
    filt_fin >> filt_len;

    std::string purename;
    getFilePurename(infilename, &purename);
    std::ofstream pers_fout(purename + "_fzz_pers");

    std::vector<phat::index> bound_c;
    // phat::boundary_matrix< phat::vector_vector > bound_chains;
    phat::boundary_matrix< phat::bit_tree_pivot_column > bound_chains;
    bound_chains.set_num_cols(filt_len + 1);

    // Add the Omega vertex for the coning
    bound_chains.set_col(0, bound_c);
    bound_chains.set_dim(0, 0);

    std::vector<Integer> del_ids;

    SimplexIdMap *p_id_map = new SimplexIdMap();
    SimplexIdMap &id_map = *p_id_map;

    Integer orig_f_id = 0;
    std::string line;
    char op;
    Simplex simp;
    Integer s_id = 1;

    while (filt_fin) {
        std::getline(filt_fin, line);
        if (line.size() == 0) { continue; }

        simp.clear();
        parseSimplex(line, op, simp);

        if (op == 'i') {
            getBoundaryChainPhat(id_map, simp, bound_c);
            bound_chains.set_col(s_id, bound_c);
            bound_chains.set_dim(s_id, getDim(bound_c));

            // assert(s_id == bound_chains.size()-1);
            id_map[simp] = s_id;
            orig_f_add_id.push_back(orig_f_id);
            s_id ++;

        } else {
            del_ids.push_back(id_map[simp]);
            orig_f_del_id.push_back(orig_f_id);
        }

        orig_f_id ++;
    }

    filt_fin.close();
    // assert(del_ids.size() == s_id-1);
    delete p_id_map;

    simp_num = del_ids.size();
    // assert(simp_num*2 == filt_len);

    std::vector<Integer> cone_sid(simp_num+1);
    Integer dim;

    for (auto del_id_it = del_ids.rbegin(); del_id_it != del_ids.rend(); ++del_id_it) {
        bound_c.clear();
        bound_c.push_back(*del_id_it);

        std::vector<phat::index> orig_bound_c;
        bound_chains.get_col(*del_id_it, orig_bound_c);

        if (orig_bound_c.size() == 0) {
            bound_c.push_back(0);
        } else {
            for (auto bsimp : orig_bound_c) {
                // assert(cone_sid[bsimp] >= 0);
                bound_c.push_back(cone_sid[bsimp]);
            }
        }

        std::sort(bound_c.begin(), bound_c.end());

        bound_chains.set_col(s_id, bound_c);
        bound_chains.set_dim(s_id, getDim(bound_c));

        cone_sid[*del_id_it] = s_id;

        s_id ++;
    }

    phat::persistence_pairs pairs;
    phat::compute_persistence_pairs< phat::twist_reduction >( pairs, bound_chains );

    for (phat::index idx = 0; idx < pairs.get_num_pairs(); idx++) {
            Integer b = pairs.get_pair(idx).first;
            Integer d = pairs.get_pair(idx).second - 1;
            Integer p = bound_chains.get_dim(b);

            if (d < simp_num) { mapOrdIntv(b, d); } 
            else { mapRelExtIntv(p, b, d); }

            pers_fout << p << " " << b << " " << d << std::endl;
    }

    // std::cout << "fzz ends" << std::endl;

    return 0;
}
