#include "rotate.h"
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

    std::string output_filename = "/home/fyt/teach_bili/improve/course_7/images/rotate_output_" + timestamp.str() + ".png";
    
    cv::Mat img = cv::imread("/home/fyt/teach_bili/improve/course_7/images/test_input.png", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Error: Could not load test_input.png" << std::endl;
        return -1;
    }
    
    int rows = img.rows;
    int cols = img.cols;
    int size = rows * cols;
    
    std::cout << "Loaded image: " << cols << "x" << rows << " = " << size << " pixels" << std::endl;
    std::cout << "After rotation: " << rows << "x" << cols << std::endl;
    
    ap_uint<8>* input = new ap_uint<8>[size];
    ap_uint<8>* output = new ap_uint<8>[size];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input[i * cols + j] = img.at<uchar>(i, j);
        }
    }
    
    rotate_90(input, output, rows, cols);
    
    // Create rotated image (dimensions swapped)
    cv::Mat rotated_img(cols, rows, CV_8UC1);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            rotated_img.at<uchar>(i, j) = output[i * rows + j];
        }
    }
    
    cv::imwrite(output_filename, rotated_img);
    
    std::cout << "90-degree rotation completed!" << std::endl;
    std::cout << "Rotated image saved as: " << output_filename << std::endl;
    
    delete[] input;
    delete[] output;
    return 0;
} 