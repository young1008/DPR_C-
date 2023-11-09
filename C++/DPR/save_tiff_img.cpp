#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <tiffio.h>

// Function to save a TIFF image
void save_tiff_img(const std::vector<std::vector<std::vector<double>>& img, const std::string& save_folder, const std::string& save_name) {
    uint32_t a = img.size();  // Image length
    uint32_t b = img[0].size();  // Image width
    uint32_t c = img[0][0].size();  // Number of slices

    TIFF* tiff = nullptr;

    // Check if the input image is a 3D array
    if (c > 1) {
        for (uint32_t j = 0; j < c; ++j) {
            // Create or append to the TIFF file
            if (j == 0) {
                tiff = TIFFOpen((save_folder + "/" + save_name + ".tif").c_str(), "w");
            } else {
                tiff = TIFFOpen((save_folder + "/" + save_name + ".tif").c_str(), "a");
            }

            // Set TIFF tags
            TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, a);
            TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, b);
            TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
            TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
            TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, 64);
            TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, 1);
            TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

            // Write the image data for the current slice
            for (uint32_t i = 0; i < a; ++i) {
                TIFFWriteScanline(tiff, &img[i][0][j], i, 0);
            }

            TIFFClose(tiff);
        }
    } else {
        // Create a single slice TIFF file for a 2D image
        tiff = TIFFOpen((save_folder + "/" + save_name + ".tif").c_str(), "w");

        // Set TIFF tags
        TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, a);
        TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, b);
        TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
        TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
        TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, 64);
        TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

        // Write the entire 2D image
        for (uint32_t i = 0; i < a; ++i) {
            TIFFWriteScanline(tiff, &img[i][0][0], i, 0);
        }

        TIFFClose(tiff);
    }
}

int main() {
    // Example usage of the save_tiff_img function
    std::vector<std::vector<std::vector<double>>> img;
    // Populate img with your image data

    std::string save_folder = "your_save_folder";
    std::string save_name = "your_save_name";

    save_tiff_img(img, save_folder, save_name);

    return 0;
}
