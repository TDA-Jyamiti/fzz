from setuptools import setup, Extension
import os.path as pth
import os



__module_file_dir = pth.dirname(pth.realpath(__file__))
__cpp_src_dir = pth.join(__module_file_dir, 'pyfzz')
src_files = []
src_files.append(pth.join(__cpp_src_dir, 'fzz.cpp'))
setup(name='pyfzz',
      version='0.0.0',
      author='Soham Mukherjee',
      description="A simple Python wrapper for Fast Zigzag originally written by Tao Hou in C++",
      author_email='soham.juetce@gmail.com',
      python_requires='>=3.9',
      classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: BSD License',
        'Operating System :: MacOS :: MacOS X',
    ],
      ext_modules=[Extension('fzz',include_dirs=[os.path.join(__cpp_src_dir,'phat-include')],
                             sources=src_files, language='c++17', extra_compile_args=['-std=c++17'])],
                             )

