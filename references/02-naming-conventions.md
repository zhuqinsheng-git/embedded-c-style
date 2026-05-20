## 2. Naming Conventions

> **Summary**: Types use `xxx_t` suffix; pointers use `p_` prefix; globals use `g_` prefix; functions use `module_action` format; macros are UPPER_CASE with module prefix; Hungarian notation is forbidden.

### 2.1 Struct Naming

Use `struct xxx` directly (no typedef). Exception: opaque types may use `typedef struct xxx xxx_t` to hide implementation.

```c
/* Normal: no typedef */
struct serial_dev dev;

/* Opaque: typedef allowed */
typedef struct pte_struct pte_t;  /* access only via functions */
```

### 2.2 Variable Naming

**Pointers** — prefix with `p_`:

```c
serial_dev_t *p_dev;
const char *p_drvname;
void *p_data;
```

**Locals** — lowercase + underscores, keep short:

```c
int ret = 0;
uint32_t cmd;
int i;              /* loop counter */
char *tmp;          /* temporary */
```

> **Linux style tip**: Local names should be short and descriptive. If you fear confusion, the function is too complex — split it.

**Globals** — prefix with `g_`:

```c
static int g_device_count;
static const char *g_default_path = "/dev/ttyS0";
```

**Struct members** — same rules (pointer prefix `p_`, others lowercase):

```c
struct serial_dev
{
        const char         *p_name;
        uint8_t             unit;
        int                 baudrate;
        void               *p_drv_data;
};
```

### 2.3 Function Naming

**Public API** — `module_action`, all lowercase + underscores:

```c
int serial_open(serial_dev_t *p_dev);
void serial_init(void);
int serial_register_driver(const serial_drv_t *p_drv);
```

**Internal static functions** — prefix with `__`:

```c
static int __serial_ioctl(serial_dev_t *p_dev, int cmd, void *arg);
```

**Callback function pointer types** — `pfn_` prefix + `_t` suffix:

```c
typedef int (*pfn_serial_write_t)(serial_dev_t *p_dev,
        const void *p_buf, size_t len);
```

### 2.4 Macro Naming

**Constants** — UPPER_CASE + underscores, with module prefix:

```c
#define SERIAL_FLAG_NONBLOCK    (1 << 0)
#define SERIAL_MAX_PORTS        8
```

**Utility macros** — UPPER_CASE, with module prefix:

```c
#define SERIAL_OFFSET(structure, member) \
        ((size_t)(&(((structure *)0)->member)))

#define ARRAY_SIZE(ar) (sizeof(ar) / sizeof((ar)[0]))
```

> **Linux style tip**: Prefer existing macros (`ARRAY_SIZE`, `min`, `max`) over reinventing them.

**Config macros** — `CONFIG_` prefix:

```c
#if CONFIG_SERIAL_HAS_DMA
        /* DMA related code */
#endif
```

### 2.5 Naming Don'ts

- **No Hungarian notation** — don't encode types in names (`iCount`, `pName`); the compiler knows the type.
- **Globals must be descriptive** — no `foo`, `tmp`, or other meaningless names.
