#include "pyfzz.h"
#include "../fzz.h"



#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
namespace py = pybind11;

namespace FZZ { 
// std::vector<std::tuple<Integer, Integer, Integer>> FastZigzag::compute_zigzag(const std::vector<std::tuple<char, std::vector<int>>> &filt_simp);


std::vector<std::tuple<Integer, Integer, Integer>> PyFastZigzag::compute_zigzag(const std::vector<std::tuple<char, std::vector<int>>> &filt_simp) {
    std::vector<Simplex> filt_simp_lin;
    std::vector<bool> filt_op;
    
    // filt_simp_lin.emplace_back();
    
    for (auto i = 0; i < filt_simp.size(); i++) {
        auto op = std::get<0>(filt_simp[i]);
        auto simp = std::get<1>(filt_simp[i]);
        // filt_simp_lin.emplace_back();
       
        FZZ::Simplex s;
        if (op == 'i') {
            filt_op.push_back(true);
        } else {
            assert(op == 'd');
            filt_op.push_back(false);
        }
        
        for(auto k = 0; k < simp.size(); k++){
            s.push_back(simp[k]);
            
        }
        // std::cout << std::endl;

        filt_simp_lin.push_back(s);
        
    }
    std::vector< std::tuple<FZZ::Integer, FZZ::Integer, FZZ::Integer> > persistence;
    FZZ::FastZigzag fzz;
    fzz.compute(filt_simp_lin, filt_op, &persistence);
    return persistence;
}
} // namespace FZZ {

PYBIND11_MODULE(fzz, m) {
    py::class_<FZZ::PyFastZigzag>(m, "fzz")
        .def(py::init<>())
        .def("compute_zigzag", &FZZ::PyFastZigzag::compute_zigzag);
}


