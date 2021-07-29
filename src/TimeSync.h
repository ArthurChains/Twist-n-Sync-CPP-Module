//
// Created by achains on 18.07.2021.
//

#ifndef TWIST_N_SYNC_CPP_MODULE_TIMESYNC_H
#define TWIST_N_SYNC_CPP_MODULE_TIMESYNC_H

#include "Eigen/Core"
#include "util/TSUtil.h"
#include <vector>

class TimeSync {
 public:
    explicit TimeSync(std::vector<std::vector<double>> & gyro_first,
                      std::vector<std::vector<double>> & gyro_second,
                      std::vector<double> & ts_first,
                      std::vector<double> & ts_second,
                      bool const & do_resample = true);

    void obtainDelay();

    void resample(double const & accuracy);

    double getTimeDelay() const;

 private:

    static Eigen::MatrixX3d interpolateGyro(Eigen::VectorXd const & ts_old, Eigen::MatrixX3d const & gyro_old,
                                            Eigen::VectorXd const & ts_new);

    TSUtil::CorrData getInitialIndex() const;

    // 3D angular velocities from devices' gyros
    Eigen::MatrixX3d gyro_first_;
    Eigen::MatrixX3d gyro_second_;

    // Gyros' timestamps
    Eigen::VectorXd ts_first_;
    Eigen::VectorXd ts_second_;

    // Flag to do resampling of angular velocities
    bool do_resample_;
    double time_delay_ = 0.0;
};


#endif //TWIST_N_SYNC_CPP_MODULE_TIMESYNC_H
