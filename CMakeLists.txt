cmake_minimum_required(VERSION 3.10)

# 项目名称和使用的C++标准
project(MyRedis VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加源文件目录
file(GLOB SOURCES
	"main.cpp"
	"src/*.cpp"
)

# 添加可执行文件
add_executable(MyRedis ${SOURCES})

# 设置输出目录
set_target_properties(MyRedis PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# 如果有第三方库需要链接，可以在这里添加
# target_link_libraries(MyRedis your_library_name)