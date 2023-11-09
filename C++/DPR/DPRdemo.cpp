#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>  // OpenCV for image manipulation

// Function to save a TIFF image
void save_tiff_img(const cv::Mat& img, const std::string& save_folder, const std::string& save_name) {
    cv::imwrite(save_folder + "/" + save_name + ".tif", img);
}

int main() {
    // Add path and directory of the images
    std::string data_folder = "Test_image";  // Folder where all the files are located.
    std::string filetype = "tif";  // Type of files to be processed

    // Load the image
    std::string file_name = "test_image";
    int n = 60;  // Frame number
    std::vector<cv::Mat> img(n);

    // Load images
    for (int i = 0; i < n; i++) {
        img[i] = cv::imread(data_folder + "/" + file_name + "." + filetype, i);
        if (img[i].empty()) {
            std::cerr << "Failed to load image: " << data_folder + "/" + file_name + "." + filetype << std::endl;
            return 1;  // Exit with an error code
        }
        // Convert image to double data type
        img[i].convertTo(img[i], CV_64F);
    }

    // Set DPR parameters
    double PSF = 4;
    // Gain: 2, Background: 10, Temporal: 'mean'
    cv::Mat I_DPR, raw_magnified;

    // Run DPR
    // Input image should have the CV_64F data type
    // Output the DPR-enhanced image and the magnified raw images for comparison
    // For single-frame image, use DPR_UpdateSingle function
    cv::Mat mean_img;
    for (int i = 0; i < n; i++) {
        cv::Mat single_I_DPR, single_raw_mag;
        // DPR_UpdateSingle function should be implemented here
        // Process the image and store results in single_I_DPR and single_raw_mag
        // ...

        if (i == 0) {
            I_DPR = single_I_DPR.clone();
            raw_magnified = single_raw_mag.clone();
            mean_img = single_raw_mag.clone();
        }
        else {
            cv::add(I_DPR, single_I_DPR, I_DPR);
            cv::add(raw_magnified, single_raw_mag, raw_magnified);
            cv::add(mean_img, single_raw_mag, mean_img);
        }
    }

    // Calculate the mean image
    mean_img /= n;

    // Save images
    std::string save_folder = "DPR_image";  // Folder where all the DPR-enhanced images are saved

    save_tiff_img(I_DPR, save_folder, "testimage_DPR2");
    save_tiff_img(mean_img, save_folder, "testiamge_magnified");

    return 0;  // Exit normally
}
