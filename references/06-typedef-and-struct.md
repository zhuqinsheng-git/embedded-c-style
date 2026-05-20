## 6. Typedef and Data Structure Design

> **Summary**: Don't typedef structs (use `struct xxx` directly); typedef only for opaque types, integer abstractions, or C99 standard types; opaque pointers hide implementation.

### 6.1 Typedef Rules

**Don't typedef structs**:

```c
/* Bad: hides what `a` is */
typedef struct virtual_container { ... } vps_t;
vps_t a;

/* Good: clearly a struct */
struct virtual_container a;
```

**Only use typedef for**:
1. **Opaque types** — hide implementation: `typedef struct pte_struct pte_t;`
2. **Integer abstraction** — clarify intent: `typedef unsigned int myflags_t;`
3. **C99 standard types** — `uint8_t`, `uint32_t`, etc.

### 6.2 Opaque Pointers

Forward declaration hides implementation — users can only use pointers:

```c
/* In header */
struct serial_dev;  /* incomplete type */

int serial_dev_init(struct serial_dev *p_dev);
```

### 6.3 Function Pointer Encapsulation

```c
struct serial_ops
{
        int (*open)(struct serial_dev *p_dev);
        int (*close)(struct serial_dev *p_dev);
        int (*write)(struct serial_dev *p_dev, const void *p_buf, size_t len);
};
```

### 6.4 Reference Counting

If a structure is visible outside its creating thread, it must have reference counting.

### 6.5 One Declaration Per Line

```c
/* Good */
int timeout;      /**< \brief timeout in ms */
int retry_count;  /**< \brief retry count */

/* Bad */
int timeout, retry_count;
```
