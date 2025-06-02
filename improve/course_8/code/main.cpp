#include "resize.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

int main() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&time_t), "%H%M%S") << "_" << std::setfill('0') << std::setw(3) << ms.count();
    
    std::string output_filename = "/home/fyt/teach_bili/improve/course_8/images/resize_output_" + timestamp.str() + ".png";
    
    cv::Mat img = cv::imread("/home/fyt/teach_bili/improve/course_8/images/test_input.png", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Error: Could not load test_input.png" << std::endl;
        return -1;
    }
    
    int rows = img.rows;
    int cols = img.cols;
    int size = rows * cols;
    int new_rows = rows / 2;
    int new_cols = cols / 2;
    int new_size = new_rows * new_cols;
    
    std::cout << "Original image: " << cols << "x" << rows << " = " << size << " pixels" << std::endl;
    std::cout << "Resized image: " << new_cols << "x" << new_rows << " = " << new_size << " pixels" << std::endl;
    
    ap_uint<8>* input = new ap_uint<8>[size];
    ap_uint<8>* output = new ap_uint<8>[new_size];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input[i * cols + j] = img.at<uchar>(i, j);
        }
    }
    
    resize_half(input, output, rows, cols);
    
    cv::Mat resized_img(new_rows, new_cols, CV_8UC1);
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            resized_img.at<uchar>(i, j) = output[i * new_cols + j];
        }
    }
    
    cv::imwrite(output_filename, resized_img);
    
    std::cout << "Image resize (50%) completed!" << std::endl;
    std::cout << "Compression ratio: " << (new_size * 100.0 / size) << "%" << std::endl;
    std::cout << "Resized image saved as: " << output_filename << std::endl;
    
    delete[] input;
    delete[] output;
    return 0;
} 