# Zygisk Next Module Sample

## 中文版本

该仓库包含一个可构建的 Zygisk Next 模块示例项目。

您可以运行 gradle task `zipDebug` 生成 debug 版本的 zip 或运行 `installMagisk|KsuDebug` 以安装模块。

输出将位于 module/release 。

### 模块声明

一个 Zygisk Next 模块是一个合法的 [Magisk 模块](https://topjohnwu.github.io/Magisk/guides.html#magisk-modules)，
且具有 Zygisk Next 特有的声明文件，该文件必须被放置在 `$MODDIR/zn_modules.txt` 文件中， 其中 `$MODDIR` 是模块的目录。

文件的每一行是一个 Zygisk Next 模块库和作用域声明，如下所示：

```txt
path=/path/of/program/to/inject path/to/znmodule_lib.so
name=name_of_program_to_inject path/to/znmodule_lib.so
```

其中，path 表示绝对路径与之相等的程序将被注入；name 表示可执行程序名字与之相等的程序将被注入，被注入的程序会被加载由路径 
path/to/znmodule_lib.so 指向的动态链接库，如果该路径是一个相对路径，则会被相对模块目录寻找，如果该路径是一个绝对路径，
则根据绝对路径寻找，最终路径必须是模块目录下的文件，否则不会被加载。

### 模块作用范围

由 init 进程产生(fork-execve)的服务进程，并且满足程序是 ELF 格式的动态链接的可执行程序  

### 模块 API （草案）

参见 [zygisk_next_api.h](module/src/main/cpp/zygisk_next_api.h)

当前 API 版本为 1 ，提供 plt hook 和 inline hook 能力。

请注意：如需使用 inline hook ，请确保目标进程的 SELinux 域拥有 execmem 权限。
可以借助 Magisk 模块的 sepolicy 修改功能来允许该权限。

## English version

TODO
