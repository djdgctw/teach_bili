# RGB to Gray HLS Project

## 📁 项目目录结构

```
course_1/
├── code/                   # 源代码目录
│   ├── rgb2gray.cpp       # HLS主函数实现
│   ├── rgb2gray.h         # 头文件定义
│   └── main.cpp           # 测试文件
├── build/                  # 构建脚本目录
│   └── run_hls.tcl        # HLS运行脚本
├── images/                 # 图片资源目录
│   ├── ceshi_small.png    # 输入测试图片(48x48)
│   └── ceshi_gray_output_*.png  # 输出灰度图片
└── README.md              # 项目说明文档
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

## 📝 HLS流程说明

1. **CSIM** - C仿真：验证算法功能正确性
2. **CSYNTH** - C综合：将C++代码转换为RTL硬件描述  
3. **COSIM** - C/RTL协同仿真：验证综合后RTL与C++行为一致性

## 📊 设计参数

- **输入图片尺寸**: 48x48像素 (2304像素)
- **接口深度**: 4096 (足够处理输入数据)
- **时钟频率**: 100MHz (10ns周期)
- **目标器件**: Zynq-7020 (xc7z020clg400-1)

## 🔧 依赖环境

- Vitis HLS 2022.2
- OpenCV 4.x (conda环境: `/home/fyt/.conda/envs/opencv_env`)
- C++14标准

## 📈 性能结果

- **估计最大频率**: 136.99 MHz
- **流水线间隔**: II=1
- **延迟**: 根据图片尺寸动态调整 