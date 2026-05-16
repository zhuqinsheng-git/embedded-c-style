## 9. Miscellaneous

### 9.1 Memory Management

**Dynamic allocation**: use `sizeof(*p)` not type name:

```c
/* ✅ Adapts automatically if pointer type changes */
p = malloc(sizeof(*p));

/* ❌ May silently break if type changes */
p = malloc(sizeof(struct my_struct));
```

**Don't cast void pointer returns**:

```c
p = malloc(size);                    /* ✅ */
p = (struct my_struct *)malloc(size); /* ❌ unnecessary */
```

**Array allocation**:

```c
p = calloc(n, sizeof(*p));  /* zero-initialized, checks overflow */
```

### 9.2 Conditional Compilation

**Avoid `#ifdef` in .c files**; use stub functions in headers:

```c
/* header.h */
#ifdef CONFIG_FEATURE_X
void feature_func(void);
#else
static inline void feature_func(void) { }  /* stub */
#endif

/* source.c — unconditional call, compiler optimizes */
feature_func();
```

### 9.3 Branch Prediction

```c
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

if (unlikely(error))
{
        /* rarely executed path */
}
```

### 9.4 Alignment and Sections

```c
/* Memory alignment */
#define compiler_align(align) __attribute__((aligned(align)))

/* Place function in specific section */
#define section(x) __attribute__((section(x)))
```

### 9.5 Use Existing Macros

```c
#define ARRAY_SIZE(x)      (sizeof(x) / sizeof((x)[0]))
#define sizeof_field(t, f) (sizeof(((t *)0)->f))
min(a, b);
max(a, b);
```
