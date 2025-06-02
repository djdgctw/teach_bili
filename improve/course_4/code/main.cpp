#include "gaussian_blur.h"
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
    
    std::string output_filename = "/home/fyt/teach_bili/improve/course_4/images/gaussian_blur_output_" + timestamp.str() + ".png";
    
    // 读取测试图片并转换为灰度图
    cv::Mat img = cv::imread("/home/fyt/teach_bili/improve/course_4/images/test_input.png", cv::IMREAD_GRAYSCALE);
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
    
    // 调用高斯模糊函数
    gaussian_blur(input, output, rows, cols);
    
    // 创建输出图片
    cv::Mat blur_img(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            blur_img.at<uchar>(i, j) = output[i * cols + j];
        }
    }
    
    // 保存模糊结果
    cv::imwrite(output_filename, blur_img);
    
    // 输出一些统计信息
    std::cout << "First 10 blur values:" << std::endl;
    for (int i = 0; i < 10 && i < size; i++) {
        std::cout << "Input[" << i << "]=" << (int)input[i] 
                  << " -> Blur[" << i << "]=" << (int)output[i] << std::endl;
    }
    
    // 计算图像平滑度指标（标准差）
    double sum = 0, sum_sq = 0;
    for (int i = 0; i < size; i++) {
        sum += output[i];
        sum_sq += output[i] * output[i];
    }
    double mean = sum / size;
    double variance = (sum_sq / size) - (mean * mean);
    double std_dev = sqrt(variance);
    
    std::cout << "Gaussian blur completed!" << std::endl;
    std::cout << "Output image statistics:" << std::endl;
    std::cout << "  Mean: " << mean << std::endl;
    std::cout << "  Standard deviation: " << std_dev << std::endl;
    std::cout << "Blurred image saved as: " << output_filename << std::endl;
    
    delete[] input;
    delete[] output;
    return 0;
} 