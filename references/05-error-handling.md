## 7. Error Handling Conventions

> **Summary**: Action functions return error codes (0=success, negative=error); predicate functions return boolean (non-zero=true, 0=false); use standard errno values

### 7.1 Return Value Convention

**Linux style important rule**:

> If the function name is an **action or command**, return an error code integer (0=success, -Exxx=failure)
> If the function name is a **predicate**, return a boolean (non-zero=true, 0=false)

**Examples**:

```c
/* Command function: returns error code */
int work_queue_add(struct work_struct *p_work);  /* 0=success, -EBUSY=failure */

/* Predicate function: returns boolean */
int pci_dev_present(struct pci_dev *p_dev);      /* 1=found, 0=not found */
```

**Mixing these two patterns is a source of bugs!**

### 7.2 Common Error Codes

Use standard errno values:

| Error Code | Value | Meaning |
|------------|-------|---------|
| 0 | 0 | Success |
| -EPERM | -1 | Operation not permitted |
| -ENOENT | -2 | No such file or directory |
| -EIO | -5 | I/O error |
| -EAGAIN | -11 | Resource temporarily unavailable |
| -ENOMEM | -12 | Out of memory |
| -EACCES | -13 | Permission denied |
| -EBUSY | -16 | Device or resource busy |
| -EEXIST | -17 | File already exists |
| -EINVAL | -22 | Invalid argument |
| -ENOSYS | -38 | Function not implemented |

### 7.3 Error Handling Patterns

#### Immediate Return

```c
static int __serial_drain_buffer(serial_dev_t *p_dev)
{
        int ret;

        if (p_dev->has_write_buf)
        {
                ret = sem_wait(&p_dev->tx_sem);
                if (ret != 0)
                        return ret;
        }

        return 0;
}
```

#### Cleanup Before Return (goto pattern)

```c
static int __serial_ioctl(serial_dev_t *p_dev, int cmd, void *p_arg)
{
        int ret;

        ret = mutex_lock(&p_dev->lock);
        if (ret != 0)
                return ret;

        switch (cmd)
        {
        case IOCTL_SET_BAUDRATE:
                ret = __set_baudrate(p_dev, *(int *)p_arg);
                break;
        default:
                ret = -ENOTSUP;
                break;
        }

        mutex_unlock(&p_dev->lock);
        return ret;
}
```

When there are multiple resources to release, use goto for centralized cleanup.

**Why goto**: unconditional jumps are easy to trace, reduce nesting, and prevent forgetting cleanup on error paths.

**Label naming**: use descriptive names (`err_free_buf`, `out_release`), not `err1`/`err2`.

```c
static int __driver_init(driver_t *p_drv)
{
        int ret;

        p_drv->p_buf = malloc(BUF_SIZE);
        if (!p_drv->p_buf)
        {
                ret = -ENOMEM;
                goto err_out;
        }

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
err_out:
        return ret;
}
```

### 7.4 Assertions and Checks

```c
/* Parameter validation */
if (!p_dev || !p_drvinfo)
        return -EINVAL;

/* State check */
if (p_dev->state != DEV_STATE_READY)
        return -EBUSY;
```
