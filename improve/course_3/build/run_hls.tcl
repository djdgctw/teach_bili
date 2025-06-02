# 删除之前运行产生的日志文件，清理工作环境
exec sh -c "rm -f flex*.log"

# 打印脚本开始执行的时间信息，便于跟踪执行过程
puts "Sobel Edge Detection HLS Project - Start time: [clock format [clock seconds]]"

# ============ OpenCV环境配置部分 ============
# 设置OpenCV安装路径（conda环境中的OpenCV）
set opencv_path "/home/fyt/.conda/envs/opencv_env"

# 设置OpenCV头文件路径（包含opencv2等头文件）
set opencv_include "$opencv_path/include/opencv4"

# 设置OpenCV库文件路径（包含.so动态库文件）
set opencv_lib "$opencv_path/lib"

# 设置环境变量LD_LIBRARY_PATH，确保运行时能找到OpenCV动态库
set ::env(LD_LIBRARY_PATH) "$opencv_lib:$::env(LD_LIBRARY_PATH)"

# ============ HLS项目配置部分 ============
# 打开或创建HLS项目，项目名为sobel_edge_prj
open_project sobel_edge_prj

# 设置顶层函数名为sobel_edge（即要综合的主函数）
set_top sobel_edge

# 添加设计源文件sobel_edge.cpp到项目中（从code目录）
add_files ../code/sobel_edge.cpp

# 添加头文件sobel_edge.h到项目中（从code目录）
add_files ../code/sobel_edge.h

# 添加测试文件main.cpp，并设置编译和链接选项：
# -cflags: C++编译选项，包含OpenCV头文件路径和C++14标准
# -csimflags: C仿真链接选项，链接OpenCV库文件
add_files -tb ../code/main.cpp -cflags "-I$opencv_include -std=c++14" -csimflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"

# 打开解决方案solution1，如果存在则重置（清空之前的结果）
open_solution -reset solution1

# 设置目标FPGA器件为Zynq-7020（xc7z020clg400-1封装）
set_part {xc7z020clg400-1}

# 创建时钟约束，设置时钟周期为10ns（即100MHz频率）
create_clock -period 10 -name default

# ============ HLS流程执行部分 ============
# 运行C仿真（CSIM），验证算法功能正确性
# -ldflags: 链接OpenCV库文件，确保测试程序能正常运行
csim_design -ldflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"

# 运行C综合（CSYNTH），将C++代码转换为RTL硬件描述
csynth_design

# 运行C/RTL协同仿真（COSIM），验证综合后RTL与C++行为一致性
# -ldflags: 同样需要链接OpenCV库以支持测试文件的执行
cosim_design -ldflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"

# 退出Vitis HLS工具
exit 