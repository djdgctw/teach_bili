# teach_bili —— HLS图像处理课程项目集

本仓库包含多个基于 Xilinx Vitis HLS 的图像处理与基础算法硬件加速设计示例，适合FPGA开发、HLS学习和数字图像处理课程实验。

## 📁 目录结构

```
teach_bili/
├── course_1/         # 基础算法示例（如向量加法）
├── base/             # 预留基础模块（当前为空）
└── improve/          # 进阶图像处理算法
    ├── course_2/     # RGB转灰度
    ├── course_3/     # Sobel边缘检测
    ├── course_4/     # 高斯模糊
    ├── course_5/     # 阈值二值化
    ├── course_6/     # 直方图均衡化
    ├── course_7/     # 图像旋转
    └── course_8/     # 图像缩放
```

## 📦 子项目内容说明

- `code/`：HLS主算法、头文件、测试代码
- `build/`：HLS流程脚本（如`run_hls.tcl`）
- `images/`：测试图片及输出结果
- `README.md`：子项目详细说明

## 🚀 快速开始

以 `course_1` 为例，其他子项目流程类似：

```bash
cd course_1/build/
source /opt/Xilinx/Vitis_HLS/2022.2/settings64.sh
vitis_hls -f run_hls.tcl
```

## 🛠 依赖环境

- Vitis HLS 2022.2
- C++14 标准
- OpenCV 4.x（部分图像处理项目需要，建议用系统包或conda环境）
- 推荐平台：Ubuntu 20.04 + Xilinx官方开发板

## 📚 项目功能简介

- **course_1**：向量加法（基础并行计算）
- **improve/course_2**：RGB转灰度图像
- **improve/course_3**：Sobel边缘检测
- **improve/course_4**：高斯模糊
- **improve/course_5**：阈值二值化
- **improve/course_6**：直方图均衡化
- **improve/course_7**：图像90度旋转
- **improve/course_8**：图像2:1缩放

每个子项目均包含详细的算法说明、HLS优化点、测试数据和应用场景，详见各自目录下的 `README.md`。

## 💡 适用人群

- FPGA/HLS初学者
- 数字图像处理课程实验
- 需要硬件加速的图像处理开发者

## 📄 参考与致谢

- Xilinx官方文档与课程
- OpenCV官方文档
- 相关开源社区 