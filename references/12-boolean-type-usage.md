## 12. 布尔类型使用

> **速览**: 用 `bool` 而非 `int`；用 `true`/`false` 而非 1/0；多个布尔值考虑位域或标志位

**Linux 内核推荐使用布尔类型提高可读性**。

### 12.1 基本规则

```c
#include <stdbool.h>  // 或使用框架提供的 bool 类型

bool is_ready;        // ✅ 使用 bool
int is_ready;         // ❌ 避免使用 int 表示布尔

is_ready = true;      // ✅ 使用 true/false
is_ready = 1;         // ❌ 避免使用 1/0
```

### 12.2 何时使用布尔

**适合使用**：
- 函数返回类型（判断型函数）
- 栈变量
- 提高可读性的场景

**不适合使用**：
- 缓存行布局重要的结构体（bool 大小和对齐因架构而异）
- 大小重要的场景
- 多个 true/false 值应考虑位域或 u8

### 12.3 多个布尔值的优化

```c
// 如果有多个布尔值，考虑位域
struct flags {
        u8 is_ready : 1;
        is_enabled : 1;
        is_busy : 1;
};

// 或者作为函数参数的标志
void func(u32 flags);  // 调用时：func(FLAG_READY | FLAG_ENABLED);
```
