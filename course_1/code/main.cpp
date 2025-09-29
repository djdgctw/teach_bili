#include "vector_add.h"
#include <iostream>
#include <opencv2/opencv.hpp>

#define SIZE 256

int main() {
    
    std::cout << "Vector Subtract-1 Test Started" << std::endl;
    std::cout << "Vector size: " << SIZE << " elements" << std::endl;
    
    // 动态分配内存
    ap_uint<32>* a = new ap_uint<32>[SIZE];
    ap_uint<32>* c = new ap_uint<32>[SIZE];
    
    // 生成测试数据
    for (int i = 0; i < SIZE; i++) {
        a[i] = i + 10;           // 10, 11, 12, ..., 10+SIZE-1
        c[i] = 0;                // 初始化输出数组
    }
    
    std::cout << "调用vector_add函数（现在是减1功能）" << std::endl;
    vector_add(a, c, SIZE);
    
    // 验证结果
    int errors = 0;
    for (int i = 0; i < SIZE; i++) {
        if (c[i] != a[i] - 1) {
            errors++;
            std::cout << "Error at index " << i << ": a=" << a[i] << ", c=" << c[i] << std::endl;
        }
    }
    if (errors == 0) {
        std::cout << "All results correct!" << std::endl;
    } else {
        std::cout << errors << " errors found." << std::endl;
    }

    // 释放动态分配的内存
    delete[] a;
    delete[] c;
    return (errors == 0) ? 0 : 1;
} 