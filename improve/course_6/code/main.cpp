#include "histogram_eq.h"
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
    
    std::string output_filename = "/home/fyt/teach_bili/improve/course_6/images/histogram_eq_output_" + timestamp.str() + ".png";
    
    // 读取测试图片并转换为灰度图
    cv::Mat img = cv::imread("/home/fyt/teach_bili/improve/course_6/images/images/test_input.png", cv::IMREAD_GRAYSCALE);
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
    
    // 计算原始图像的直方图统计
    int original_hist[256] = {0};
    for (int i = 0; i < size; i++) {
        original_hist[input[i]]++;
    }
    
    // 调用直方图均衡化函数
    histogram_eq(input, output, size);
    
    // 创建输出图片
    cv::Mat eq_img(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            eq_img.at<uchar>(i, j) = output[i * cols + j];
        }
    }
    
    // 保存均衡化结果
    cv::imwrite(output_filename, eq_img);
    
    // 计算均衡化后的直方图
    int equalized_hist[256] = {0};
    for (int i = 0; i < size; i++) {
        equalized_hist[output[i]]++;
    }
    
    // 输出直方图分析
    std::cout << "First 10 equalized values:" << std::endl;
    for (int i = 0; i < 10 && i < size; i++) {
        std::cout << "Input[" << i << "]=" << (int)input[i] 
                  << " -> Equalized[" << i << "]=" << (int)output[i] << std::endl;
    }
    
    // 分析图像对比度改善
    double original_mean = 0, original_std = 0;
    double equalized_mean = 0, equalized_std = 0;
    
    // 计算原始图像统计
    for (int i = 0; i < size; i++) {
        original_mean += input[i];
        equalized_mean += output[i];
    }
    original_mean /= size;
    equalized_mean /= size;
    
    for (int i = 0; i < size; i++) {
        original_std += (input[i] - original_mean) * (input[i] - original_mean);
        equalized_std += (output[i] - equalized_mean) * (output[i] - equalized_mean);
    }
    original_std = sqrt(original_std / size);
    equalized_std = sqrt(equalized_std / size);
    
    std::cout << "Histogram equalization completed!" << std::endl;
    std::cout << "Original image statistics:" << std::endl;
    std::cout << "  Mean: " << original_mean << ", Std: " << original_std << std::endl;
    std::cout << "Equalized image statistics:" << std::endl;
    std::cout << "  Mean: " << equalized_mean << ", Std: " << equalized_std << std::endl;
    std::cout << "Contrast improvement: " << (equalized_std / original_std) << "x" << std::endl;
    std::cout << "Enhanced image saved as: " << output_filename << std::endl;
    
    delete[] input;
    delete[] output;
    return 0;
} 