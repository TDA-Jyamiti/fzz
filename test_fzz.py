
from pyfzz import pyfzz

if __name__ == '__main__':
    fzz = pyfzz()
    data = fzz.read_file('sample_filt')
    bars = fzz.compute_zigzag(data)
    fzz.write_file('sample_filt_pers', bars)
    # bars = fzz.compute_zigzag([('i', [0]), ('i', [1]), ('i', [0, 1])])

    print(bars)