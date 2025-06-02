#include "rgb2gray.h"
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
    
    std::string output_filename = "/home/fyt/teach_bili/improve/course_2/images/ceshi_gray_output_" + timestamp.str() + ".png";
    
    // 读取测试图片 - 使用相对路径从images目录读取
    cv::Mat img = cv::imread("/home/fyt/teach_bili/improve/course_2/images/ceshi_small.png", cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Could not load ceshi_small.png from images directory" << std::endl;
        return -1;
    }
    
    int rows = img.rows;
    int cols = img.cols;
    int size = rows * cols;
    
    std::cout << "Loaded image: " << cols << "x" << rows << " = " << size << " pixels" << std::endl;
    std::cout << "Output will be saved as: " << output_filename << std::endl;
    
    // 分配内存 - 使用动态内存以支持任意尺寸
    ap_uint<24>* rgb = new ap_uint<24>[size];
    ap_uint<8>* gray = new ap_uint<8>[size];
    
    // 将OpenCV图片数据转换为ap_uint数组
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            // OpenCV格式是BGR，转换为RGB
            ap_uint<8> r = pixel[2];  // Red
            ap_uint<8> g = pixel[1];  // Green
            ap_uint<8> b = pixel[0];  // Blue
            rgb[i * cols + j] = (r << 16) | (g << 8) | b;
        }
    }
    
    // 调用硬件函数
    rgb2gray(rgb, gray, size);
    
    // 创建输出图片
    cv::Mat gray_img(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gray_img.at<uchar>(i, j) = gray[i * cols + j];
        }
    }
    
    // 保存灰度图片到images目录
    cv::imwrite(output_filename, gray_img);
    
    // 输出一些统计信息
    std::cout << "First 10 pixels:" << std::endl;
    for (int i = 0; i < 10 && i < size; i++) {
        ap_uint<8> r = rgb[i].range(23, 16);
        ap_uint<8> g = rgb[i].range(15, 8);
        ap_uint<8> b = rgb[i].range(7, 0);
        std::cout << "RGB(" << (int)r << "," << (int)g << "," << (int)b 
                  << ") -> Gray=" << (int)gray[i] << std::endl;
    }
    
    // 验证结果
    int errors = 0;
    for (int i = 0; i < size; i++) {
        ap_uint<8> r = rgb[i].range(23, 16);
        ap_uint<8> g = rgb[i].range(15, 8);
        ap_uint<8> b = rgb[i].range(7, 0);
        ap_uint<8> expected = (r * 30 + g * 59 + b * 11) / 100;
        
        if (gray[i] != expected) errors++;
    }
    
    if (errors == 0) {
        std::cout << "Test PASSED! All " << size << " pixels processed correctly." << std::endl;
        std::cout << "Gray image saved as: " << output_filename << std::endl;
    } else {
        std::cout << "Test FAILED: " << errors << " errors out of " << size << " pixels." << std::endl;
    }
    
    delete[] rgb;
    delete[] gray;
    return 0;
} 