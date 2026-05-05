## 3. 关键字修饰符

> **速览**: `ul_local`(static)、`ul_const`(const)、`ul_inline`(inline)、`ul_import`(extern)、`ul_export`(extern) — 统一关键字别名用于跨编译器兼容

zhuqinsheng 定义了一套统一的关键字别名，用于跨编译器兼容：

### 3.1 基本修饰符

```c
#define ul_local            static           // 本地静态
#define ul_const            const            // 常量
#define ul_import           extern           // 外部导入
#define ul_export           extern           // 外部导出
```

### 3.2 内联函数

```c
#define ul_inline           inline           // GCC/IAR 内联
#define ul_static_inline    static inline    // 静态内联

// 强制内联（GCC/ARM）
#define ul_static_always_inline \
    __attribute__((always_inline)) static inline
```

### 3.3 使用示例

```c
// 本地静态函数
ul_local ul_err_t __ul_serial_ioctl(...)
{
    // ...
}

// 常量数据
ul_const char *p_dev_name;
ul_const struct ulb_devhcf g_ulb_devhcf_list[] = { ... };

// 静态内联函数
ul_static_inline void ulb_dev_set_drv_data(ulb_dev_t *p_dev, void *p_drv_data)
{
    p_dev->p_drv_data = p_drv_data;
    ul_smp_wmb();
}

// 强制内联函数
ul_static_always_inline uint32_t get_value(void)
{
    return 42;
}
```
