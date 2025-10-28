# 删除之前运行产生的日志文件，清理工作环境
exec sh -c "rm -f flex*.log"

# 打印脚本开始执行的时间信息，便于跟踪执行过程
puts "successful!!!  the start time is [clock format [clock seconds]]"

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
# 打开或创建HLS项目，项目名为vector_add_prj
open_project led_prj

# 设置顶层函数名为vector_add（即要综合的主函数）
set top_name led
set_top $top_name

# 添加设计源文件vector_add.cpp到项目中（从code目录）
add_files ../code/led.cpp

# 打开解决方案solution1，如果存在则重置（清空之前的结果）
open_solution -reset solution1

# 设置目标FPGA器件为Zynq-7020（xc7z020clg400-1封装）
set_part {xc7s50csga324-1}

# 创建时钟约束，设置时钟周期为10ns（即100MHz频率）
create_clock -period 10 -name default

# ============ HLS流程执行部分 ============
# 运行C仿真（CSIM），验证算法功能正确性
# csim_design -ldflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"

# 运行C综合（CSYNTH），将C++代码转换为RTL硬件描述
csynth_design

# # 运行C/RTL协同仿真（COSIM），验证综合后RTL与C++行为一致性
# cosim_design -ldflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"
# 导出IP核，便于在后续工程中复用
set export_dir "/home/fyt/A/teach_bili/led/ip"
set export_path [file join $export_dir $top_name]
file mkdir $export_path
export_design -format ip_catalog -output $export_path
# 将导出的压缩包重命名为与顶层函数一致
set export_zip [file join $export_path export.zip]
if {[file exists $export_zip]} {
    file rename -force $export_zip [file join $export_path "$top_name.zip"]
}
# 解压导出的IP，并删除原压缩包
set final_zip [file join $export_path "$top_name.zip"]
if {[file exists $final_zip]} {
    exec unzip -o $final_zip -d $export_path
    file delete -force $final_zip
}
# 退出Vitis HLS工具
exit
