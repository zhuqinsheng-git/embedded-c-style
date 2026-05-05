## 14. 条件编译规范

> **速览**: 避免在 .c 文件中使用 `#ifdef`，改为头文件桩函数；用 `IS_ENABLED()` 宏替代；未使用代码用 `__maybe_unused` 标记

### 14.1 避免在 .c 文件中使用 #ifdef

**Linux 风格建议**：

```c
// ❌ 避免：在 .c 文件中使用预处理条件
#ifdef CONFIG_FEATURE_X
        do_something();
#endif

// ✅ 推荐：在头文件中提供桩函数
// header.h
#ifdef CONFIG_FEATURE_X
void feature_func(void);
#else
static inline void feature_func(void) { }  // 空桩
#endif

// source.c
feature_func();  // 无条件调用，编译器优化
```

### 14.2 使用 IS_ENABLED 宏

```c
// ✅ 推荐：转化为 C 布尔表达式
if (IS_ENABLED(CONFIG_SOMETHING)) {
        ...
}

// 编译器会做常量折叠，无运行时开销
// 但允许 C 编译器检查块内代码的正确性
```

**注意**：如果块内引用了不存在的符号，仍需使用 `#ifdef`。

### 14.3 标记未使用的代码

```c
// 使用 __maybe_unused 而不是 #ifdef
static __maybe_unused void unused_func(void)
{
        ...
}

// 如果总是未使用，直接删除
```

### 14.4 长条件块的注释

```c
#ifdef CONFIG_SOMETHING
...
#endif /* CONFIG_SOMETHING */
```
