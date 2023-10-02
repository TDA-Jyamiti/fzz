
from pyfzz import pyfzz

if __name__ == '__main__':
    fzz = pyfzz()

    # You can use the following code to test the function directly with a list of insertion and deletion operations.
    bars = fzz.compute_zigzag([('i', [0]), ('i', [1]), ('i', [0, 1]), ('d', [0, 1]), ('d', [1])])
    print(bars)

    # Alternatively you can read the filtration from a file
    # and then write the barcodes into a file.
    data = fzz.read_file('sample_filt')
    bars = fzz.compute_zigzag(data)
    print(f'Bars from file {bars}')
    fzz.write_file('sample_filt_pers', bars)