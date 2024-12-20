-- 设置项目名称
set_project("mesh2sdf")

-- 设置语言为 C++
set_languages("c++17")

-- 添加依赖库
add_requires("cgal =5.5.2")
add_requires("polyscope >=1.3.0")
-- 如果需要 Boost 和其他库
add_requires("boost =1.78.0")

-- 添加构建规则
add_rules("mode.debug", "mode.release", "mode.releasedbg")

-- 定义目标
target("mesh_sdf_example")
    set_kind("binary")  -- 目标类型为可执行文件
    set_languages("c++17")

    -- 根据平台选择编译标志
    if is_plat("windows") then
        add_cxflags("/bigobj", "/openmp")  -- Windows 平台使用 /bigobj 和 /openmp
    end

    -- 添加源文件和头文件
    add_files("src/*.cpp")  -- 添加所有的 C++ 源文件
    add_headerfiles("src/*.h", "src/*.hpp")  -- 添加头文件
    add_includedirs(".", {public = true})  -- 当前目录下的头文件

    -- 添加依赖包
    add_packages("cgal", {public = true})
    add_packages("polyscope", {public = true})
    add_packages("boost", {public = true})  -- 如果使用 Boost，添加 Boost 库