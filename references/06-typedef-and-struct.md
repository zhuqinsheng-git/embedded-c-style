## 8. Typedef and Data Structure Design

> **Summary**: Avoid typedef for structs (use `struct xxx` directly); typedef only for opaque types, integer abstractions, or C99 standard types; opaque pointers hide implementation; function pointers enable OOP-style design

### 8.1 Typedef Rules

**Don't use typedef for structs**:

```c
/* ❌ Wrong: hides what a is */
typedef struct virtual_container
{
        int field1;
        int field2;
} vps_t;

vps_t a;

/* ✅ Clear: a is obviously a struct */
struct virtual_container a;
```

**Only use typedef in these cases**:

1. **Opaque objects** (hide implementation)
   ```c
   typedef struct pte_struct pte_t;  /* access only via functions */
   ```

2. **Integer type abstraction** (clarify intent)
   ```c
   typedef unsigned int myflags_t;
   ```

3. **Standard C99 types**
   ```c
   typedef unsigned char uint8_t;
   typedef unsigned int uint32_t;
   ```

### 8.2 Opaque Pointers

Use forward declarations to hide implementation:

```c
/* In header */
typedef struct serial_dev serial_dev_t;
struct serial_dev;  /* incomplete type */

/* Users can only use pointers */
int serial_dev_init(serial_dev_t *p_dev);
```

### 8.3 Function Pointer Encapsulation

```c
typedef struct serial_ops
{
        int (*open)(serial_dev_t *p_dev);
        int (*close)(serial_dev_t *p_dev);
        int (*write)(serial_dev_t *p_dev, const void *p_buf, size_t len);
} serial_ops_t;
```

### 8.4 Linked List Nodes

```c
typedef struct list_node
{
        struct list_node *next;
        struct list_node *prev;
} list_node_t;
```

### 8.5 Reference Counting

**If a structure is visible outside its creating thread, it must have reference counting.**

```c
struct my_data
{
        int refcount;
        /* ... */
};
```

### 8.6 One Declaration Per Line

```c
/* ✅ */
int timeout;      /**< \brief timeout in ms */
int retry_count;  /**< \brief retry count */

/* ❌ */
int timeout, retry_count;
```
