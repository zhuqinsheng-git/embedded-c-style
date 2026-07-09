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

### 7.5 Portability

**Use `stdint.h` types — never bare `int` or `long` when size matters.**

```c
/* bad — size varies across platforms */
int count;          /* 16-bit on AVR, 32-bit on ARM, who knows */
long timestamp;     /* 32-bit on Windows x64, 64-bit on Linux x64 */

/* good — size is explicit */
int32_t count;      /* always 32 bits */
uint64_t timestamp; /* always 64 bits, unsigned */
uint8_t  addr;      /* always 8 bits — common for Modbus/register values */
```

**Don't cast pointer to int.**

```c
/* bad — breaks on 64-bit systems where pointer is 8 bytes, int is 4 */
int addr = (int)ptr;

/* good */
uintptr_t addr = (uintptr_t)ptr;  /* uintptr_t is guaranteed to hold a pointer */
```

`int` is fine for loop counters, return codes, and small ranges where size doesn't matter. Use sized types for everything that touches memory layout, protocols, or hardware registers.
