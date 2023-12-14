## CMake

### CMake介绍

CMake是一个开源的跨平台构建工具，用于自动生成用于构建软件的构建脚本（Makefile、Visual Studio项目等）。
它使用一种称为CMakeLists.txt的简单文本配置文件来描述构建过程，并基于此生成适用于各种构建系统的构建文件。

CMake的设计目标是使跨平台软件的构建过程更加简化和统一。通过提供一个高级的构建系统抽象层，
CMake允许开发者在一个平台上定义构建过程，然后可以生成适用于多个平台和构建工具的构建文件。
这使得开发者可以在不同的操作系统和开发环境中更轻松地构建和管理项目。

使用CMake，开发者可以使用一致的语法和命令来描述项目的构建过程，包括源代码文件、编译选项、链接库、目标输出等。
CMake会根据CMakeLists.txt文件生成相应的构建文件，如Makefile（用于Unix-like系统）、Ninja文件、Visual Studio项目文件等。
然后，开发者可以使用生成的构建文件来执行实际的构建过程，如编译、链接和生成最终的可执行文件或库。

CMake支持多种主流的编译器和构建系统，如GNU Make、Ninja、Visual Studio、Xcode等。它广泛应用于各种开源项目和商业项目中，
为开发者提供了便捷的构建和跨平台开发的能力。

总结来说，CMake是一个跨平台的构建工具，用于自动生成适用于多个构建系统的构建文件。
它简化了项目构建过程的管理，提高了跨平台开发的效率。

### 例子

```cpp
cmake_minimum_required(VERSION 3.12)  # 指定所需的CMake版本

project(MyProject)  # 设置项目名称

# 添加源文件
set(SOURCES
    src/main.cpp
    src/foo.cpp
    src/bar.cpp
)

# 添加可执行文件
add_executable(myapp ${SOURCES})

# 添加头文件搜索路径
target_include_directories(myapp PUBLIC include)

# 添加链接的库
target_link_libraries(myapp
    PRIVATE
        foo_library
        bar_library
)

# 设置编译选项
target_compile_options(myapp PRIVATE -Wall -Wextra)

# 设置安装规则
install(TARGETS myapp DESTINATION bin)
install(FILES README.md DESTINATION doc)
```

这个示例CMakeLists.txt文件包含了以下几个常用命令的使用：

+ cmake_minimum_required：指定所需的CMake版本。
+ project：设置项目名称。
+ set：设置变量，这里用于指定源文件列表。
+ add_executable：添加可执行文件，指定源文件列表生成可执行文件。
+ target_include_directories：添加头文件搜索路径。
+ target_link_libraries：添加链接的库。
+ target_compile_options：设置编译选项。
+ install：设置安装规则，指定将可执行文件和其他文件安装到指定位置。

