## 16. 打印内核消息

**Linux 内核强调打印信息的规范性**。

### 16.1 拼写和格式

- 使用正确的拼写：`do not` 而不是 `dont`
- 信息简单明了、无歧义
- **不必以英文句号结束**
- 避免在小括号里打印数字：`printk("value (%d)\n", val);` ❌

### 16.2 使用适当的打印宏

```c
// 驱动模型诊断宏（推荐）
dev_err(dev, "error message\n");
dev_warn(dev, "warning message\n");
dev_info(dev, "info message\n");

// 通用打印宏
pr_notice("notice message\n");
pr_info("info message\n");
pr_warn("warning message\n");
pr_err("error message\n");
pr_debug("debug message\n");  // 仅当 DEBUG 定义时编译
```

### 16.3 调试信息

- `pr_debug()` 默认不编译，需定义 `DEBUG` 或 `CONFIG_DYNAMIC_DEBUG`
- 使用 `VERBOSE_DEBUG` 开启 `dev_vdbg()`
- 调试信息应该有助于远程除错
