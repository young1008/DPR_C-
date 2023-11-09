#include <vector>
#include <string>
#include <opencv2/opencv.hpp>  // OpenCV for image manipulation

void DPRStack(const std::vector<cv::Mat>& I_in, double PSF, const Options& options, cv::Mat& I_DPR, cv::Mat& raw_magnified) {
    int n = I_in.size();
    I_DPR = cv::Mat::zeros(I_in[0].size(), I_in[0].type());
    raw_magnified = cv::Mat::zeros(I_in[0].size(), I_in[0].type());

#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        cv::Mat single_I_DPR, single_raw_mag;
        DPR_UpdateSingle(I_in[i], PSF, options, single_I_DPR, single_raw_mag);
        single_I_DPR.copyTo(I_DPR.col(i));  // Assuming the third dimension is the channel dimension
        single_raw_mag.copyTo(raw_magnified.col(i));
    }

    // Temporal process
    std::string temporal = options.temporal;
    std::vector<std::string> tp = { "mean", "var" };

    if (!temporal.empty()) {
        auto it = std::find(tp.begin(), tp.end(), temporal);
        if (it != tp.end()) {
            int index = std::distance(tp.begin(), it);
            if (index == 0) {
                cv::reduce(I_DPR, I_DPR, 2, cv::REDUCE_MEAN);
            }
            else if (index == 1) {
                cv::reduce(I_DPR, I_DPR, 2, cv::REDUCE_VAR);
            }
        }
    }
}
