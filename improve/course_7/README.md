# Image Rotation HLS Project

## 📁 项目目录结构

```
course_7/
├── code/                      # 源代码目录
│   ├── rotate.cpp            # 90度旋转HLS实现
│   ├── rotate.h              # 头文件定义
│   └── main.cpp              # 测试文件
├── build/                     # 构建脚本目录
│   └── run_hls.tcl           # HLS运行脚本
└── images/                    # 图片资源目录
    ├── test_input.png        # 输入测试图片
    └── rotate_output_*.png   # 输出旋转图片
```

## 🚀 如何运行

```bash
cd build/
source /opt/Xilinx/Vitis_HLS/2022.2/settings64.sh
vitis_hls -f run_hls.tcl
```

## 📝 算法说明

**90度顺时针旋转变换:**
```
(x, y) -> (y, rows-1-x)
```

**输出维度:** 输入为MxN，输出为NxM

## 🎯 应用场景

- 图像预处理
- 显示方向调整
- 数据增强 