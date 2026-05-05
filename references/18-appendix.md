## 附录：快速参考表

### A. 命名规范速查

| 类别 | 规范 | 示例 |
|------|------|------|
| **类型定义** | `xxx_t` 后缀 | awb_dev_t, `aw_err_t` |
| **指针变量** | `p_` 前缀 | p_dev, p_drvname, p_devinfo |
| **全局变量** | `__g_` 前缀 | `__g_eeprom_0_dev` |
| **局部变量** | 小写+下划线，简短 | `ret`, `cmd`, `i`, `tmp` |
| **公开函数** | `模块_功能` | `awb_serial_open`, `awb_plb_init` |
| **内部函数** | `__` 或完整前缀 | `__aw_serial_ioctl` |
| **函数指针类型** | `pfn_xxx_t` | `pfn_driver_match_t` |
| **宏常量** | 全大写+模块前缀 | AWB_BUS_TYPE_ID_I2C, AW_OK |
| **配置宏** | `CONFIG_XXX` | `CONFIG_AWB_SERIAL_HAS_WRITE_BUF` |

### B. 关键字修饰符速查

| 关键字 | 含义 | 等价于 | 使用场景 |
|--------|------|--------|----------|
| aw_local | 本地静态 | `static` | 内部函数、静态变量 |
| aw_const | 常量 | `const` | 只读数据、常量指针 |
| aw_inline | 内联 | `inline` | 小函数优化（≤3行） |
| `aw_static_inline` | 静态内联 | `static inline` | 头文件中的辅助函数 |
| `aw_static_always_inline` | 强制内联 | `__attribute__((always_inline))` | 性能关键代码 |
| aw_import | 外部导入 | `extern` | 声明外部变量 |
| aw_export | 外部导出 | `extern` | 导出全局符号 |

### C. 注释标签速查

| 标签 | 用途 | 示例 |
|------|------|------|
| `\brief` | 简要说明 | `\brief 初始化设备` |
| `\param[in]` | 输入参数 | `\param[in] p_dev 设备指针` |
| `\param[out]` | 输出参数 | `\param[out] p_result 结果` |
| `\param[in,out]` | 输入输出参数 | `\param[in,out] p_buf 缓冲区` |
| `\return` | 返回值说明 | `\return 错误码` |
| `\retval` | 具体返回值 | `\retval AW_OK 成功` |
| `\par` | 段落标题 | `\par 示例` |
| `\code` | 代码块开始 | `\code ... \endcode` |
| `\endcode` | 代码块结束 | - |
| `\internal` | 内部说明 | 修改历史等 |
| `\file` | 文件说明 | `\file awb_serial.c` |

### D. 常见错误码

| 错误码 | 值 | 含义 |
|--------|-----|------|
| AW_OK | 0 | 成功 |
| `-AW_EPERM` | -1 | 不允许的操作 |
| `-AW_ENOENT` | -2 | 没有这样的文件或目录 |
| `-AW_EINTR` | -4 | 中断的系统调用 |
| `-AW_EIO` | -5 | I/O 错误 |
| `-AW_EAGAIN` | -11 | 资源暂时不可用 |
| `-AW_ENOMEM` | -12 | 内存不足 |
| `-AW_EACCES` | -13 | 权限拒绝 |
| `-AW_EFAULT` | -14 | 错误的地址 |
| `-AW_EBUSY` | -16 | 设备或资源忙 |
| `-AW_EEXIST` | -17 | 文件已存在 |
| `-AW_ENODEV` | -19 | 没有这样的设备 |
| `-AW_EINVAL` | -22 | 无效参数 |
| `-AW_ENOTSUP` | -95 | 不支持的操作 |

### E. 总线类型 ID

| 总线类型 | ID | 说明 |
|----------|-----|------|
| AWB_BUS_TYPE_ID_PLB | 1 | 处理器本地总线 |
| AWB_BUS_TYPE_ID_I2C | 20 | I2C 总线 |
| AWB_BUS_TYPE_ID_SPI | 21 | SPI 总线 |
| AWB_BUS_TYPE_ID_SDIO | 22 | SDIO 总线 |
| AWB_BUS_TYPE_ID_MII | 23 | MII 总线 |
| AWB_BUS_TYPE_ID_USBH | 24 | USB Host 总线 |
| AWB_BUS_TYPE_ID_DISPLAY | 26 | 显示器总线 |
| AWB_BUS_TYPE_ID_FLASH | 27 | Flash 总线 |
| AWB_BUS_TYPE_ID_CAM | 29 | Camera 总线 |
| AWB_BUS_TYPE_ID_HWTIMER | 30 | 硬件定时器总线 |

### F. 代码格式要点速查

| 项目 | 规范 | 说明 |
|------|------|------|
| **缩进** | 8 字符制表符 | ⚠️ Linux 标准，非 4 空格 |
| **行长** | 80 列 | 超过需换行 |
| **函数大括号** | 另起一行 | `int func()\n{` |
| **其他大括号** | 行尾 | `if (cond) {` |
| **单语句** | 不用大括号 | `if (cond) action();` |
| **Switch case** | 与 switch 对齐 | 不二次缩进 |
| **指针声明** | `*` 靠近变量 | `char *p` |
| **关键字空格** | if/for 后加 | sizeof 后不加 |
| **运算符空格** | 二元运算符两侧 | 一元运算符不加 |
| **行尾空格** | 禁止 | 配置编辑器自动删除 |
