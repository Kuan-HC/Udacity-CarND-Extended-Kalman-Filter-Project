#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <Eigen/Dense>

#include "measurement_package.h"
#include "FusionEKF.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

int i = 0;

int main()
{
  // Create a Kalman Filter instance
  FusionEKF fusionEKF;
  // used to compute the RMSE later
  Tools tools;
  vector<VectorXd> estimations;
  vector<VectorXd> ground_truth;

  // hardcoded input file with laser and radar measurements
  string in_file_name_ = "../data/obj_pose-laser-radar-synthetic-input.txt";
  ifstream in_file(in_file_name_.c_str(), ifstream::in);

  if (!in_file.is_open())
  {
    cout << "Cannot open input file: " << in_file_name_ << endl;
  }
  
  string sensor_measurement;
  while (getline(in_file, sensor_measurement) && (i <= 100))
  {
    //cout << sensor_measurement << endl;
    MeasurementPackage meas_package;
    std::istringstream iss(sensor_measurement);

    long long timestamp;

    // reads first element from the current line
    string sensor_type;
    iss >> sensor_type;

    if (sensor_type.compare("L") == 0)
    {
      meas_package.sensor_type_ = MeasurementPackage::LASER;
      meas_package.raw_measurements_ = VectorXd(2);
      float px;
      float py;
      iss >> px;
      iss >> py;
      meas_package.raw_measurements_ << px, py;
      iss >> timestamp;
      meas_package.timestamp_ = timestamp;
    }
    else if (sensor_type.compare("R") == 0)
    {
      meas_package.sensor_type_ = MeasurementPackage::RADAR;
      meas_package.raw_measurements_ = VectorXd(3);
      float ro;
      float theta;
      float ro_dot;
      iss >> ro;
      iss >> theta;
      iss >> ro_dot;
      meas_package.raw_measurements_ << ro, theta, ro_dot;
      iss >> timestamp;
      meas_package.timestamp_ = timestamp;
    }

    /* For evluate EKF performance */
    float x_gt;
    float y_gt;
    float vx_gt;
    float vy_gt;
    iss >> x_gt;
    iss >> y_gt;
    iss >> vx_gt;
    iss >> vy_gt;

    VectorXd gt_values(4);
    gt_values(0) = x_gt;
    gt_values(1) = y_gt;
    gt_values(2) = vx_gt;
    gt_values(3) = vy_gt;
    ground_truth.push_back(gt_values);

    // Call ProcessMeasurement(meas_package) for Kalman filter
    fusionEKF.ProcessMeasurement(meas_package);

    // Push the current estimated x,y positon from the Kalman filter's
    //   state vector

    VectorXd estimate(4);

    double p_x = fusionEKF.ekf_.x_(0);
    double p_y = fusionEKF.ekf_.x_(1);
    double v1 = fusionEKF.ekf_.x_(2);
    double v2 = fusionEKF.ekf_.x_(3);

    estimate(0) = p_x;
    estimate(1) = p_y;
    estimate(2) = v1;
    estimate(3) = v2;

    estimations.push_back(estimate);

    VectorXd RMSE = tools.CalculateRMSE(estimations, ground_truth);
    cout << "RMSE = " << RMSE << endl;

    i++;
  }

  

  if (in_file.is_open())
  {
    in_file.close();
  }

  return 0;
}