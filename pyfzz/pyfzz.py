import fzz
from typing import List, Tuple

class pyfzz:
    def __init__(self):
        self.fzz = fzz.fzz()
    
    def compute_zigzag(self, data: List[Tuple[str, List[int]]]) -> List[Tuple[int, int, int]]:
        return self.fzz.compute_zigzag(data)
    
    def read_file(self, filename) -> List[Tuple[str, List[int]]]:
        filtration = []
        with open(filename, 'r') as f:
            for line in f:
                line_split = line.strip('\n').split()
                op = line_split[0]
                filtration.append((op, [int(x) for x in line_split[1:]]))
        return filtration
    
    def write_file(self, filename, data: List[Tuple[int, int, int]]):
        with open(filename, 'w') as f:
            for bar in data:
                f.write(f'{bar[2]} {bar[0]} {bar[1]}\n')