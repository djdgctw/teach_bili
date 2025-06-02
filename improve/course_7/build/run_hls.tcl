# 删除之前的日志文件
exec sh -c "rm -f flex*.log"
puts "Image Rotation HLS Project - Start time: [clock format [clock seconds]]"

set opencv_path "/home/fyt/.conda/envs/opencv_env"
set opencv_include "$opencv_path/include/opencv4"
set opencv_lib "$opencv_path/lib"
set ::env(LD_LIBRARY_PATH) "$opencv_lib:$::env(LD_LIBRARY_PATH)"

open_project rotate_prj
set_top rotate_90
add_files ../code/rotate.cpp
add_files ../code/rotate.h
add_files -tb ../code/main.cpp -cflags "-I$opencv_include -std=c++14" -csimflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"
open_solution -reset solution1
set_part {xc7z020clg400-1}
create_clock -period 10 -name default

csim_design -ldflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"
csynth_design
cosim_design -ldflags "-L$opencv_lib -Wl,-rpath,$opencv_lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs"
exit 