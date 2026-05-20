## 7. Miscellaneous

### 7.1 Memory Management

Use `sizeof(*p)`, not `sizeof(struct my_struct)` — adapts if pointer type changes. Don't cast `void *` returns from malloc/calloc.

```c
p = malloc(sizeof(*p));
p = calloc(n, sizeof(*p));    /* zero-initialized */
```

### 7.2 Conditional Compilation

Avoid `#ifdef` in `.c` files. Use stub functions in headers instead — compiler optimizes away the empty call:

```c
/* header.h */
#ifdef CONFIG_FEATURE_X
void feature_func(void);
#else
static inline void feature_func(void) { }  /* stub */
#endif
```

### 7.3 Branch Prediction

```c
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

if (unlikely(error)) { /* rarely executed path */ }
```

### 7.4 Alignment and Sections

```c
#define compiler_align(align) __attribute__((aligned(align)))
#define section(x)            __attribute__((section(x)))
```
