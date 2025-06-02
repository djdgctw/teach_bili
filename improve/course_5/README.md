# Threshold Binarization HLS Project

## 📁 项目目录结构

```
course_5/
├── code/                          # 源代码目录
│   ├── threshold.cpp             # 阈值二值化HLS实现
│   ├── threshold.h               # 头文件定义
│   └── main.cpp                  # 测试文件
├── build/                         # 构建脚本目录
│   └── run_hls.tcl               # HLS运行脚本
├── images/                        # 图片资源目录
│   ├── test_input.png            # 输入测试图片(48x48灰度)
│   └── threshold_output_*.png    # 输出二值化图片
└── README.md                     # 项目说明文档
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

### 阈值二值化原理
阈值二值化是将灰度图像转换为二值图像的基本操作：

**阈值化公式:**
```
if pixel > threshold:
    output = 255 (白色)
else:
    output = 0 (黑色)
```

**默认阈值**: 128 (可调整)

## 📊 设计参数

- **输入**: 48x48像素灰度图
- **阈值**: 128 (可配置)
- **输出**: 二值图像 (0或255)
- **时钟**: 100MHz
- **器件**: Zynq-7020

## 🔧 依赖环境

- Vitis HLS 2022.2
- OpenCV 4.x
- C++14标准

## 🎯 应用场景

- 图像分割
- 目标检测预处理
- 文档图像处理
- 工业视觉检测 