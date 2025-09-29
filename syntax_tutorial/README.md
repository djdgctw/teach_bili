# HLS优化指令教程

本目录包含了一系列HLS优化指令的实例教程，每个课程都专注于特定的优化技巧。

## 课程列表

1. lesson1_loop_opt: 循环优化
   - 循环展开（unroll）
   - 循环流水线（pipeline）
   - 循环计数约束（loop_tripcount）

2. lesson2_array_opt: 数组优化
   - 数组分割（array_partition）
   - 数组重构（array_reshape）
   - 存储器映射策略

3. lesson3_dataflow: 数据流优化
   - dataflow指令
   - stream深度配置
   - 任务级并行化

4. lesson4_memory: 存储器优化
   - URAM绑定
   - BRAM优化策略
   - 存储器接口配置

5. lesson5_interface: 接口优化
   - 接口协议选择
   - AXI接口配置
   - 端口聚合/分离

## 优化原则

1. 资源利用
   - BRAM最小容量为18Kbits
   - 合理选择分块策略
   - 避免资源浪费

2. 性能优化
   - 关注关键路径
   - 平衡并行度
   - 注意资源约束

3. 最佳实践
   - 选择合适维度进行分块
   - 注意数据依赖关系
   - 考虑访问模式

## 项目结构

每个课程都包含：
- 源代码示例
- TCL构建脚本
- 详细的说明文档
- 性能对比数据