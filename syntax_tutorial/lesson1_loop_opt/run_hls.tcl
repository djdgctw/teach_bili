# 删除之前运行产生的日志文件，清理工作环境
exec sh -c "rm -f flex*.log"

puts "开始综合basic版本..."
open_project vector_add_prj_basic
set_top vector_add_basic
add_files vector_add.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp vector_add_prj_basic/solution1/syn/report/csynth.rpt result/basic_csynth.rpt"
close_project

puts "开始综合unroll版本..."
open_project vector_add_prj_unroll
set_top vector_add_unroll
add_files vector_add.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp vector_add_prj_unroll/solution1/syn/report/csynth.rpt result/unroll_csynth.rpt"
close_project

puts "开始综合pipeline版本..."
open_project vector_add_prj_pipeline
set_top vector_add_pipeline
add_files vector_add.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp vector_add_prj_pipeline/solution1/syn/report/csynth.rpt result/pipeline_csynth.rpt"
close_project



puts "所有版本综合完成！"