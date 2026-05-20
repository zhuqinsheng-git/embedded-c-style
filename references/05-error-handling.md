## 5. Error Handling Conventions

> **Summary**: Action functions return error codes (0=success, negative=error); predicate functions return boolean (non-zero=true, 0=false); use standard errno values; multi-resource cleanup uses goto.

### 5.1 Return Value Convention

- **Action/command functions** → return `int` (0=success, -Exxx=failure)
- **Predicate functions** → return `bool` or `int` (non-zero=true, 0=false)
- **Mixing these two patterns is a source of bugs!**

```c
int work_queue_add(struct work_struct *p_work);  /* 0=success, -EBUSY=failure */
int pci_dev_present(struct pci_dev *p_dev);      /* 1=found, 0=not found */
```

### 5.2 Common Error Codes

| Error | Value | Meaning |
|-------|-------|---------|
| 0 | 0 | Success |
| -EPERM | -1 | Not permitted |
| -ENOENT | -2 | No such file |
| -EIO | -5 | I/O error |
| -ENOMEM | -12 | Out of memory |
| -EACCES | -13 | Permission denied |
| -EBUSY | -16 | Resource busy |
| -EINVAL | -22 | Invalid argument |

### 5.3 Goto Cleanup Pattern

For multiple resources, use goto for centralized cleanup. Labels should be descriptive (`err_free_buf`, not `err1`).

```c
static int __driver_init(driver_t *p_drv)
{
        int ret;

        p_drv->p_buf = malloc(BUF_SIZE);
        if (!p_drv->p_buf)
                return -ENOMEM;

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
        return -EINVAL;

if (p_dev->state != DEV_STATE_READY)
        return -EBUSY;
```
