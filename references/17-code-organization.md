## 17. 代码组织原则

### 17.1 目录结构

每个子系统独立目录，遵循统一结构：

```
subsys/ul_subsys_driver_serial/
├── Kconfig.opts          # 配置选项
├── component.json        # 组件描述
├── doc/                  # 文档
│   ├── serial_api.md
│   └── examples/
├── include/              # 公开头文件
│   └── ulb_serial.h
└── source/               # 源代码
    └── ulb_serial.c
```

### 17.2 分层架构

```
应用层 (Application)
    ↓
服务层 (Service)
    ↓
驱动层 (Driver)
    ↓
硬件抽象层 (HAL)
    ↓
硬件 (Hardware)
```

### 17.3 模块化设计

- **高内聚**: 相关功能放在同一模块
- **低耦合**: 模块间通过明确定义的接口通信
- **单一职责**: 每个模块只负责一个功能领域

### 17.4 接口统一

通过 ioctl 提供统一的控制接口：

```c
// 串口 ioctl 命令
#define UL_IOCTL_SERIAL_DCB_GET         0x01
#define UL_IOCTL_SERIAL_DCB_SET         0x02
#define UL_IOCTL_SERIAL_TIMEOUT_GET     0x03
#define UL_IOCTL_SERIAL_TIMEOUT_SET     0x04
#define UL_IOCTL_SERIAL_FLUSH           0x05
#define UL_IOCTL_SERIAL_DRAIN           0x06

// 统一调用方式
ul_err_t ret = ioctl(fd, UL_IOCTL_SERIAL_DCB_SET, &dcb);
```

### 17.5 设备树集成

驱动通过 YAML 绑定文件描述，自动生成配置代码：

```yaml
# ulb_spidev.yaml
title: ULBus-Lite SPI Bus Device
inherits:
    !include ulb_device.yaml

parent:
    bus: spi

properties:
    compatible:
        constraint: "vendor,spi-device"
    reg:
        type: int
```

### 17.6 编辑器配置

**不要在源代码中包含编辑器模式行**：

```c
// ❌ 禁止：Emacs 模式行
/* -*- mode: c -*- */

// ❌ 禁止：Vim 模式行
/* vim:set sw=8 noet */
```

每个人都有他自己的编辑器配置，源文件不应该覆盖别人的配置。
