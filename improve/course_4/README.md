# Gaussian Blur HLS Project

## 📁 项目目录结构

```
course_4/
├── code/                              # 源代码目录
│   ├── gaussian_blur.cpp             # 高斯模糊HLS实现
│   ├── gaussian_blur.h               # 头文件定义
│   └── main.cpp                      # 测试文件
├── build/                             # 构建脚本目录
│   └── run_hls.tcl                   # HLS运行脚本
├── images/                            # 图片资源目录
│   ├── test_input.png                # 输入测试图片(48x48灰度)
│   └── gaussian_blur_output_*.png    # 输出模糊图片
└── README.md                         # 项目说明文档
```

## 🚀 如何运行

### 1. 进入构建目录
```bash
cd build/
```

### 2. 运行HLS流程
```bash
source /opt/Xilinx/Vitis_HLS/2022.2/settings64.sh
vitis_hls -f run_hls.tcl
```

## 📝 算法说明

### 高斯模糊原理
高斯模糊使用5×5高斯卷积核对图像进行平滑处理，减少噪声和细节。

**5×5高斯核:**
```
 1   4   6   4  1
 4  16  24  16  4
 6  24  36  24  6
 4  16  24  16  4
 1   4   6   4  1
```

**归一化**: 除以256 (核系数之和)

## 📊 设计参数

- **输入**: 48x48像素灰度图
- **卷积核**: 5×5高斯核
- **时钟**: 100MHz
- **器件**: Zynq-7020

## 🔧 依赖环境

- Vitis HLS 2022.2
- OpenCV 4.x
- C++14标准 