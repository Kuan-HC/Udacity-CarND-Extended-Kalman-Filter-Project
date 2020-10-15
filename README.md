# Udacity-CarND-Extended-Kalman-Filter-Project  
This is Udacity project Extended Kalman Filter, source code had been modified  
so it can run on local machines.

## Dependencies
* Here is a download [link](https://d17h27t6h515a5.cloudfront.net/topher/2017/March/58b7604e_eigen/eigen.zip) to the Eigen Library that is being used in the project.
* cmake

## Compile
``mkdir build && cd build``  
``cmake .. && make``  
``./ExtendedKF``  

## Result
Running the executive, it should look like this
```
99 times EKF runs
x_ =  20.3157
  11.524
0.482818
 4.42145
P_ = 0.00559509 -0.0033529  0.0117593  -0.010897
-0.0033529 0.00960715 -0.0119543  0.0244182
 0.0117593 -0.0119543  0.0755863  -0.053992
 -0.010897  0.0244182  -0.053992   0.135901
RMSE = 0.0891586
 0.103324
 0.799197
 0.620439
100 times EKF runs
x_ =  20.3799
  11.784
0.547429
 4.50323
P_ =  0.00495826 -0.00232721   0.0110373 -0.00731377
-0.00232721  0.00768668 -0.00798232   0.0195139
  0.0110373 -0.00798232   0.0849892  -0.0360491
-0.00731377   0.0195139  -0.0360491    0.126423
RMSE = 0.0895041
 0.102902
 0.795896
 0.618217

```
