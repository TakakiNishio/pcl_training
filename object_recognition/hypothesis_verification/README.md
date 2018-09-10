### Tutorial: Hypothesis Verification for 3D Object Recognition

[tutorial]( http://www.pointclouds.org/documentation/tutorials/global_hypothesis_verification.php#global-hypothesis-verification )
```
$ sudo cp -r ../3rdparty/metslib /usr/include/pcl-1.7/pcl/recognition/hv/.
$ mkdir build
$ cd build
$ cmake ..
$ make
```
```
$ cp ../../pcd_files/milk* .
$ ./global_hypothesis_verification milk.pcd milk_cartoon_all_small_clorox.pcd --cg_size 0.02
```
