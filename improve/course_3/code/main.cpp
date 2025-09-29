#include "sobel_edge.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

int main() {
    // 生成时间戳用于区分CSIM和COSIM输出
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&time_t), "%H%M%S") << "_" << std::setfill('0') << std::setw(3) << ms.count();
    
    std::string output_filename = "/home/fyt/A/teach_bili/improve/course_3/images/sobel_edge_output_" + timestamp.str() + ".png";
    
    // 读取测试图片并转换为灰度图
    cv::Mat img = cv::imread("/home/fyt/A/teach_bili/improve/course_3/images/test_input.png", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Error: Could not load test_input.png from images directory" << std::endl;
        return -1;
    }
    
    int rows = img.rows;
    int cols = img.cols;
    int size = rows * cols;
    
    std::cout << "Loaded grayscale image: " << cols << "x" << rows << " = " << size << " pixels" << std::endl;
    std::cout << "Output will be saved as: " << output_filename << std::endl;
    
    // 分配内存
    ap_uint<8>* input = new ap_uint<8>[size];
    ap_uint<8>* output = new ap_uint<8>[size];
    
    // 将OpenCV图片数据转换为ap_uint数组
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input[i * cols + j] = img.at<uchar>(i, j);
        }
    }
    
    // 调用Sobel边缘检测函数
    sobel_edge(input, output, rows, cols);
    
    // 创建输出图片
    cv::Mat edge_img(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            edge_img.at<uchar>(i, j) = output[i * cols + j];
        }
    }
    
    // 保存边缘检测结果
    cv::imwrite(output_filename, edge_img);
    
    // 输出一些统计信息
    std::cout << "First 10 edge values:" << std::endl;
    for (int i = 0; i < 10 && i < size; i++) {
        std::cout << "Input[" << i << "]=" << (int)input[i] 
                  << " -> Edge[" << i << "]=" << (int)output[i] << std::endl;
    }
    
    // 计算边缘像素数量
    int edge_pixels = 0;
    for (int i = 0; i < size; i++) {
        if (output[i] > 30) {  // 阈值设为30
            edge_pixels++;
        }
    }
    
    std::cout << "Sobel edge detection completed!" << std::endl;
    std::cout << "Edge pixels (>30): " << edge_pixels << " out of " << size 
              << " (" << (edge_pixels * 100.0 / size) << "%)" << std::endl;
    std::cout << "Edge image saved as: " << output_filename << std::endl;
    
    delete[] input;
    delete[] output;
    return 0;
} 