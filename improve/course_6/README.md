# Histogram Equalization HLS Project

## 📁 项目目录结构

```
course_6/
├── code/                              # 源代码目录
│   ├── histogram_eq.cpp              # 直方图均衡化HLS实现
│   ├── histogram_eq.h                # 头文件定义
│   └── main.cpp                      # 测试文件
├── build/                             # 构建脚本目录
│   └── run_hls.tcl                   # HLS运行脚本
├── images/                            # 图片资源目录
│   ├── test_input.png                # 输入测试图片(48x48灰度)
│   └── histogram_eq_output_*.png     # 输出均衡化图片
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

### 直方图均衡化原理
直方图均衡化是一种图像增强技术，通过重新分布像素强度来改善图像对比度。

**算法步骤:**

1. **计算直方图**: 统计每个灰度级的像素数量
```
histogram[i] = 像素值为i的像素数量
```

2. **计算累积分布函数(CDF)**:
```
cdf[i] = Σ(histogram[0] to histogram[i])
```

3. **生成映射表**:
```
new_value[i] = (cdf[i] - cdf_min) × 255 / (total_pixels - cdf_min)
```

4. **应用映射**: 使用查找表变换所有像素值

**效果**: 将图像的直方图均匀分布到整个灰度范围，增强对比度

## 📊 设计参数

- **输入图片**: 48x48像素灰度图 (2304像素)
- **直方图级数**: 256级 (0-255)
- **接口深度**: 4096 (足够处理输入数据)
- **时钟频率**: 100MHz (10ns周期)
- **目标器件**: Zynq-7020 (xc7z020clg400-1)

## 🔧 依赖环境

- Vitis HLS 2022.2
- OpenCV 4.x (conda环境: `/home/fyt/.conda/envs/opencv_env`)
- C++14标准

## 📈 HLS优化特性

- **流水线设计**: 所有循环使用 `#pragma HLS PIPELINE`
- **数组分割**: 使用 `#pragma HLS ARRAY_PARTITION complete` 优化查找表访问
- **内存接口**: AXI4 Master接口用于数据传输
- **并行化处理**: 直方图计算和CDF生成优化

## 🎯 应用场景

- **医学影像**: CT、X光片增强
- **卫星图像**: 遥感图像对比度改善
- **安防监控**: 低光照图像增强
- **数字摄影**: 自动曝光补偿
- **工业检测**: 低对比度缺陷检测

## 📊 性能指标

- **对比度改善**: 通过标准差比值衡量
- **计算复杂度**: O(n + 256) 时间复杂度
- **空间复杂度**: 需要256×3的额外存储空间
- **实时性**: 适合视频流实时处理

## 🔍 输出分析

程序会输出以下统计信息：
- 原始图像的均值和标准差
- 均衡化后图像的均值和标准差
- 对比度改善倍数
- 前10个像素的变换示例 