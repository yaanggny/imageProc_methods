# Introduction

This repository contains the code for the paper **Efficient Coarse-to-Fine PatchMatch for Large Displacement Optical Flow**. [Yinlin Hu](http://yinlinhu.github.io), Rui Song, and Yunsong Li. CVPR. 2016. [[Paper]](https://zpascal.net/cvpr2016/Hu_Efficient_Coarse-To-Fine_PatchMatch_CVPR_2016_paper.pdf)

## ChangeLog
Based on [the latest version](https://github.com/YinlinHu/CPM/commit/bc15a129b49539bcefd3c5ac26f2e0b2a4b4cc7c).

- removed the redundencies
- changed code style
- fixed README

# How to Use
- Linux
  
It is assumed that the OpenCV has been installed correctly.

```
$ cmake .
$ make
```

Then, you can play with the examples:

```
$ bash demo.sh
```

- Windows
  - try `demo.bat` with the Windows executables.
  - change `OpenCV_DIR` in `CMakeLists.txt` and build.

# Citing

```
@inproceedings{hu2016cpm,
  title={Efficient Coarse-to-Fine PatchMatch for Large Displacement Optical Flow},
  author={Yinlin Hu and Rui Song and Yunsong Li},
  booktitle={CVPR},
  year={2016}
}
```