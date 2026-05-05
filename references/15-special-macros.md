## 15. 特殊宏定义

> **速览**: `ul_section()` 段属性；`ul_ram_code_section()` RAM执行；`likely()/unlikely()` 分支预测；`ul_compiler_deprecated()` 废弃警告；`ul_compiler_align()` 内存对齐

### 15.1 段属性

```c
// 将函数放置到特定段
#define ul_section(x) __attribute__((section(x)))

// 将代码放置到 RAM 中执行（提高性能）
#define ul_ram_code_section(func) \
        __attribute__((section(".ram_code"), used, noinline))

// 使用示例
ul_ram_code_section(critical_func)
void critical_func(void)
{
        // 高性能要求的代码
}
```

### 15.2 分支预测优化

```c
#if defined(__GNUC__)
# define likely(x)   __builtin_expect(!!(x), 1)
# define unlikely(x) __builtin_expect(!!(x), 0)
#else
# define likely(x)   (x)
# define unlikely(x) (x)
#endif

// 使用示例
if (likely(ret == UL_OK)) {
        // 经常执行的路径
}

if (unlikely(error)) {
        //  rarely 执行的路径
}
```

### 15.3 废弃警告

```c
#define ul_compiler_deprecated(msg) \
        __attribute__ ((deprecated(msg)))

// 使用示例
ul_compiler_deprecated("Use ulb_new_function instead")
void old_function(void);
```

### 15.4 内存对齐

```c
#define ul_compiler_align(align) __attribute__((aligned(align)))

// 使用示例
struct ul_compiler_align(16) aligned_struct {
        uint8_t data[16];
};
```

### 15.5 使用内核已有宏

**不要重新发明**：

```c
// 使用 ARRAY_SIZE 而不是自己定义
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

// 使用 min/max（带类型检查）
min(a, b);
max(a, b);

// 计算结构体成员大小
#define sizeof_field(t, f) (sizeof(((t*)0)->f))
```
