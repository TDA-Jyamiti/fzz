# include "../fzz.h"


namespace FZZ { 
class PyFastZigzag: public FastZigzag
{
		
	public:
        std::vector<std::tuple<Integer, Integer, Integer>> compute_zigzag(const std::vector<std::tuple<char, std::vector<int>>> &filt_simp);

			
};
} // namespace FZZ {