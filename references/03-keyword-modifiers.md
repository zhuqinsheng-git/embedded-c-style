## 3. 关键字修饰符

AWorks 定义了一套统一的关键字别名，用于跨编译器兼容：

### 3.1 基本修饰符

```c
#define aw_local            static           // 本地静态
#define aw_const            const            // 常量
#define aw_import           extern           // 外部导入
#define aw_export           extern           // 外部导出
```

### 3.2 内联函数

```c
#define aw_inline           inline           // GCC/IAR 内联
#define aw_static_inline    static inline    // 静态内联

// 强制内联（GCC/ARM）
#define aw_static_always_inline \
    __attribute__((always_inline)) static inline
```

### 3.3 使用示例

```c
// 本地静态函数
aw_local aw_err_t __aw_serial_ioctl(...)
{
    // ...
}

// 常量数据
aw_const char *p_dev_name;
aw_const struct awb_devhcf g_awb_devhcf_list[] = { ... };

// 静态内联函数
aw_static_inline void awb_dev_set_drv_data(awb_dev_t *p_dev, void *p_drv_data)
{
    p_dev->p_drv_data = p_drv_data;
    aw_smp_wmb();
}

// 强制内联函数
aw_static_always_inline uint32_t get_value(void)
{
    return 42;
}
```
