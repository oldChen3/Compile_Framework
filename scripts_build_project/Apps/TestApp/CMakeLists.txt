#要求CMAKE的最低版本
cmake_minimum_required(VERSION 2.8)

#制定工程名称
project(Test-App)

#set(CMAKE_CXX_COMPILER "g++")

#为项目的编译 以及 代码的编译 添加 宏开关
#参数：宏开关名称， 宏用途描述， 宏默认值
option(MY_DEBUG "enable debug message" OFF)

#设置一个变量，用于保存最终生成物存放的位置
#EXECUTABLE_OPTPUT_PATH:默认变量，表示生成的可执行文件存放的位置
#PROJECT_SOURCE_DIR:cmake自带的变量,表示工程的根目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#添加可执行程序
#APP_Demo 是最终生成的可执行程序
#AppMain.c 是参与编译的源文件
#add_executable(App_Demo AppMain.c)

#将指定的目录下的所有源文件列表存放到变量 SRC__LIST 中
#这种方法优势是可以一次性添加多文件，但是也会全部无选择性进行添加
#aux_source_directory(. SRC_LIST)

#增加编译选项
add_compile_options(-Wall)

#使用set命令，创建变量
#set(SRC_LIST ./AppMain.c ./MwCamera.c)

#设置动态库和静态存放库路径的变量
#set(STATIC_LIB_PATH ${PROJECT_SOURCE_DIR}/lib)
#set(STATIC_LIB_PATH ${PROJECT_SOURCE_DIR}/lib)

#正常来说源代码会存在多个目录，并且会将头文件 库文件 源文件 进行分目录存放
#这时候就需要指定链接时需要的头文件路径
#set(INC_LIST src/Mw/include src/DevDri/include src/Sys/include src/Common/include)
#include_directories(${INC_LIST}) #用来向工程添加多个指定的头文件的搜索路径，路径之间用空格隔开

aux_source_directory(src/App SRC_LIST_APP)
#aux_source_directory(src/Mw/Camera SRC_LIST_MW)
#aux_source_directory(src/Mw/NetComm SRC_LIST_MW_NETCOMM)
#aux_source_directory(src/Mw/CV SRC_LIST_MW_CV)
#aux_source_directory(src/DevDri SRC_LIST_DD)
#aux_source_directory(src/Sys/system SRC_LIST_SYS)

#寻找系统需要的库,并自动将库信息存放到指定变量中
#参数分别为 库信息变量，库名称，HINTS，库所在路径
#find_library(SYSTEM_API_LIB libsysApi_d.so HINTS ${STATIC_LIB_PATH})

if(MY_DEBUG)
	add_compile_options(-DMY_DEBUG)
	message(STATUS "Enable Debug Message Output")
else()
	message(STATUS "Disable Debug Message")
endif()

#add_executable(App_Main ${SRC_LIST_APP} ${SRC_LIST_MW} ${SRC_LIST_DD} ${SRC_LIST_SYS} ${SRC_LIST_MW_NETCOMM} ${SRC_LIST_MW_CV})
add_executable(TestApp ${SRC_LIST_APP})

#将库和目标进行链接
#target_link_libraries(App_Main pthread)

