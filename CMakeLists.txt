cmake_minimum_required(VERSION 3.27)
project(Ordina)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 收集所有源文件
file(GLOB SOURCES "src/*.c")

# 添加可执行文件和库
add_executable(Ordina ${SOURCES})

# 添加库
foreach(source_file ${SOURCES})
    get_filename_component(file_name ${source_file} NAME_WE)
    add_library(o_${file_name} ${source_file})
    target_link_libraries(Ordina o_${file_name})
endforeach()

include_directories(${CMAKE_SOURCE_DIR}/src)

# 添加生成汇编文件的命令
set(ASM_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/asm_output)
file(MAKE_DIRECTORY ${ASM_OUTPUT_DIR})

# 添加生成汇编文件的命令（针对所有源文件）
foreach(source_file ${SOURCES})
    get_filename_component(file_name ${source_file} NAME_WE)
    add_custom_command(TARGET Ordina POST_BUILD
        COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -S ${source_file} -o ${ASM_OUTPUT_DIR}/${file_name}.s
        COMMENT "Generating assembly output for ${file_name}.c"
    )
endforeach()

# 创建一个自定义目标来显示汇编文件
add_custom_target(show_asm
    COMMAND cat ${ASM_OUTPUT_DIR}/*.s
    DEPENDS Ordina
    COMMENT "Displaying assembly output for all source files"
)

# 将显示汇编文件的操作与构建目标关联
add_dependencies(show_asm Ordina)
