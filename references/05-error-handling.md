## 5. Error Handling Conventions

> **Summary**: Action functions return error codes (0=success, non-zero=error); predicate functions return boolean (non-zero=true, 0=false); define semantic errors in a module-level enum; multi-resource cleanup uses goto.

### 5.1 Return Value Convention

- **Action/command functions** → return `int` (0=success, non-zero=error code)
- **Predicate functions** → return `bool` or `int` (non-zero=true, 0=false)
- **Mixing these two patterns is a source of bugs!**

```c
int work_queue_add(struct work_struct *p_work);  /* 0=success, >0=error code */
int pci_dev_present(struct pci_dev *p_dev);      /* 1=found, 0=not found */
```

### 5.2 Error Codes

Use a module-level enum for semantic errors. Use plain negative numbers for generic failures (invalid args, allocation failure).

```c
/* module.h — semantic errors for this module */
typedef enum
{
        XXX_OK           = 0,
        XXX_ERR_TIMEOUT  = 1,
        XXX_ERR_CRC      = 2,
        XXX_ERR_BUS      = 3,
} xxx_err_t;
```

| Return | Meaning |
|--------|---------|
| 0 | Success |
| 1+ | Module-specific error (see enum) |
| -1 | Invalid parameter |
| -2 | Allocation failure |

### 5.3 Goto Cleanup Pattern

For multiple resources, use goto for centralized cleanup. Labels should be descriptive (`err_free_buf`, not `err1`).

```c
static int __driver_init(driver_t *p_drv)
{
        int ret;

        p_drv->p_buf = malloc(BUF_SIZE);
        if (!p_drv->p_buf)
                return -2;

        ret = register_device(p_drv);
        if (ret != 0)
                goto err_free_buf;

        ret = request_irq(p_drv);
        if (ret != 0)
                goto err_unregister;

        return 0;

err_unregister:
        unregister_device(p_drv);
err_free_buf:
        free(p_drv->p_buf);
        return ret;
}
```

**Why goto**: unconditional jumps reduce nesting, are easy to trace, and prevent forgetting cleanup.

### 5.4 Parameter Validation

```c
if (!p_dev || !p_drvinfo)
        return -1;

if (p_dev->state != DEV_STATE_READY)
        return XXX_ERR_TIMEOUT;
```
