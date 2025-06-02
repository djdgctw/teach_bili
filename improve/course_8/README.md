# Image Resize HLS Project

## 📁 项目目录结构

```
course_8/
├── code/                      # 源代码目录
│   ├── resize.cpp            # 2:1缩放HLS实现
│   ├── resize.h              # 头文件定义
│   └── main.cpp              # 测试文件
├── build/                     # 构建脚本目录
│   └── run_hls.tcl           # HLS运行脚本
└── images/                    # 图片资源目录
    ├── test_input.png        # 输入测试图片
    └── resize_output_*.png   # 输出缩放图片
```

## 🚀 如何运行

```bash
cd build/
source /opt/Xilinx/Vitis_HLS/2022.2/settings64.sh
vitis_hls -f run_hls.tcl
```

## 📝 算法说明

**2:1降采样算法:**
- 取每隔一个像素进行采样
- 输出尺寸为原图的50%
- 简单高效的下采样方法

**输出维度:** 输入MxN -> 输出(M/2)x(N/2)

## 🎯 应用场景

- 图像压缩
- 多尺度处理
- 金字塔构建
- 数据降维 