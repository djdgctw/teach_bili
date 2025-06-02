# Sobel Edge Detection HLS Project

## 📁 项目目录结构

```
course_3/
├── code/                           # 源代码目录
│   ├── sobel_edge.cpp             # Sobel边缘检测HLS实现
│   ├── sobel_edge.h               # 头文件定义
│   └── main.cpp                   # 测试文件
├── build/                          # 构建脚本目录
│   └── run_hls.tcl                # HLS运行脚本
├── images/                         # 图片资源目录
│   ├── test_input.png             # 输入测试图片(48x48灰度)
│   └── sobel_edge_output_*.png    # 输出边缘检测图片
└── README.md                      # 项目说明文档
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

### Sobel边缘检测原理
Sobel算子是一种离散微分算子，用于计算图像灰度函数的梯度近似值。它使用两个3×3的卷积核：

**水平边缘检测核 Gx:**
```
-1  0  1
-2  0  2  
-1  0  1
```

**垂直边缘检测核 Gy:**
```
-1 -2 -1
 0  0  0
 1  2  1
```

**边缘强度计算:**
```
Edge = |Gx| + |Gy|
```

## 📊 设计参数

- **输入图片**: 48x48像素灰度图 (2304像素)
- **接口深度**: 4096 (足够处理输入数据)
- **时钟频率**: 100MHz (10ns周期)
- **目标器件**: Zynq-7020 (xc7z020clg400-1)
- **边缘阈值**: 30 (用于统计边缘像素)

## 🔧 依赖环境

- Vitis HLS 2022.2
- OpenCV 4.x (conda环境: `/home/fyt/.conda/envs/opencv_env`)
- C++14标准

## 📈 HLS优化特性

- **流水线设计**: 内层循环使用 `#pragma HLS PIPELINE`
- **内存接口**: AXI4 Master接口用于数据传输
- **边界处理**: 自动处理图像边界像素
- **资源共享**: 卷积核操作优化

## 🎯 应用场景

- 图像预处理
- 目标检测前的边缘提取
- 计算机视觉算法的前端处理
- FPGA加速图像处理系统 