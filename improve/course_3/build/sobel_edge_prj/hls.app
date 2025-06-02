<AutoPilot:project xmlns:AutoPilot="com.autoesl.autopilot.project" projectType="C/C++" name="sobel_edge_prj" top="sobel_edge">
    <files>
        <file name="../../../code/main.cpp" sc="0" tb="1" cflags=" -I/home/fyt/.conda/envs/opencv_env/include/opencv4  -std=c++14 -L/home/fyt/.conda/envs/opencv_env/lib -Wl,-rpath,/home/fyt/.conda/envs/opencv_env/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -Wno-unknown-pragmas" csimflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="../code/sobel_edge.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="../code/sobel_edge.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
    </files>
    <solutions>
        <solution name="solution1" status=""/>
    </solutions>
    <Simulation argv="">
        <SimFlow name="csim" setup="false" optimizeCompile="false" clean="false" ldflags="-L/home/fyt/.conda/envs/opencv_env/lib -Wl,-rpath,/home/fyt/.conda/envs/opencv_env/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs" mflags=""/>
    </Simulation>
</AutoPilot:project>

