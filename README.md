# EchoEar Core

EchoEar 喵伴公共模块。由 [echoear 固件](https://github.com/xiaolonghuster/echoear)复用，面向微雪、VIEWE 和未来的新板型。

## 边界

- `include/`：不依赖小智的游戏、宠物、计时、导航、音频处理模型、状态共享及主机接口。图标声明需要 LVGL。
- `src/`：原版 LVGL 图标资源，作为独立 ESP-IDF 组件编译。
- `adapters/xiaozhi/`：完整的现有界面、猫眼、设置和应用显示，以及小智服务连接代码。它有意依赖小智的 Application、Display、Settings 和网络 API，是可选适配层，不是平台无关核心。
- `cmake/xiaozhi.cmake`：向固件导出适配层源码。它们在固件 main 中编译；独立组件不反向依赖 main，避免循环依赖。
- `tests/`：无需开发板即可执行的模型及导航测试。

界面与应用只在此仓库维护。固件仓库保留硬件驱动、引脚、语音框架、主机接口实现和打包发布。

## 使用

ESP-IDF 工程把此目录加入 `EXTRA_COMPONENT_DIRS`，依赖组件 `echoear-core`。要求 ESP-IDF >=6.0.1、LVGL ~9.5.0。小智项目还需引入 `cmake/xiaozhi.cmake`，将导出的适配源码加入 main，并实现 `echoear::GetHost()`。

纯逻辑测试：

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

主机接口定义在 `include/echoear_platform.h`。音量/亮度写入应在主机应用任务执行；界面通过 `Host::Schedule` 调度。板型能力、旋转和 SD 接线由固件提供，核心不包含厂商 GPIO 常量。

## 新板接入

在固件仓库新增板型驱动和构建配置，提供屏幕、触摸、音频、按键以及能力描述，选择共享适配层即可。先禁用未经验证的能力；单麦不能启用当前声源方向估计，无参考输入不能直接启用设备端 AEC。原版 ESP-VoCat 尚未在此拆分中完成驱动接入或实机验收。

不同语音固件可复用独立模型和资源，但需要另写界面服务适配，不能直接把 Xiaozhi 适配层当成通用后端。

## 版本与来源

初始版本 0.1.0，来自 EchoEar 统一固件。MIT 代码许可证见 LICENSE；Espressif ESP-Brookesia 图标采用 Apache-2.0，完整声明见 ORIGINAL_UI_LICENSE.md。保留源项目版权说明。

固件通过 Git submodule 固定具体提交。升级时先发布核心提交，再更新固件指针并对全部板型构建验收；不自动跟随 main。
