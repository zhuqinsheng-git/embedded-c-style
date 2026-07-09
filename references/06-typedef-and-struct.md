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

### 6.6 Header File Design

A header is the module's public contract. Someone who has never seen your `.c` should be able to read the `.h` and know how to use the module.

**Self-contained** — the header must compile on its own. Include everything it needs to compile:

```c
/* sensor.h — reads a temperature sensor over I2C */

#include <stdint.h>       /* uint8_t, int16_t — this header needs them */
#include <stdbool.h>      /* bool — this header uses it */

struct i2c_bus;           /* forward declare — we only use pointers */

/* public types */
typedef enum {
        SENSOR_OK          = 0,
        SENSOR_ERR_TIMEOUT = 1,
        SENSOR_ERR_CRC     = 2,
} sensor_err_t;

/* public API */
int  sensor_init(struct i2c_bus *bus, uint8_t addr);
int  sensor_read_temp(struct i2c_bus *bus, int16_t *temp_out);
bool sensor_is_ready(struct i2c_bus *bus);
```

**Minimal includes** — only include what the *header itself* needs. If the `.c` needs `<string.h>`, include it in the `.c`, not the header.

**Forward declare** — if you only use a pointer to a type, don't include its full header:

```c
struct i2c_bus;  /* enough — no need to #include "i2c.h" */
```

**Structure** — types and enums at the top, function declarations below, no implementation details:
