# 删除之前运行产生的日志文件，清理工作环境
exec sh -c "rm -f flex*.log"

puts "开始综合basic版本..."
open_project cache_prj_basic
set_top cache_basic
add_files memory_opt.cpp
open_solution "solution1" -flow_target vivado
set_part {xcvu9p-flga2104-2-i}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp cache_prj_basic/solution1/syn/report/csynth.rpt result/basic_csynth.rpt"
close_project

puts "开始综合uram版本..."
open_project cache_prj_uram
set_top cache_uram
add_files memory_opt.cpp
open_solution "solution1" -flow_target vivado
set_part {xcvu9p-flga2104-2-i}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp cache_prj_uram/solution1/syn/report/csynth.rpt result/uram_csynth.rpt"
close_project

puts "开始综合double buffer版本..."
open_project cache_prj_double
set_top cache_double_buffer
add_files memory_opt.cpp
open_solution "solution1" -flow_target vivado
set_part {xcvu9p-flga2104-2-i}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp cache_prj_double/solution1/syn/report/csynth.rpt result/double_buffer_csynth.rpt"
close_project

puts "开始综合hybrid版本..."
open_project cache_prj_hybrid
set_top cache_hybrid
add_files memory_opt.cpp
open_solution "solution1" -flow_target vivado
set_part {xcvu9p-flga2104-2-i}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp cache_prj_hybrid/solution1/syn/report/csynth.rpt result/hybrid_csynth.rpt"
close_project

puts "所有版本综合完成！"