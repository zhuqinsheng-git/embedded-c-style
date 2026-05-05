## 7. 错误处理规范

### 7.1 错误码类型

使用 `ul_err_t` 类型返回错误码：

```c
ul_err_t ulb_serial_open(ulb_dev_t *p_dev);
ul_err_t ulb_register_dev_driver(...);
```

### 7.2 返回值约定

- **成功**: 返回 UL_OK (通常为 0)
- **失败**: 返回负的错误码

```c
#define UL_OK           0
#define -UL_EACCES      // 权限拒绝
#define -UL_ENOTSUP     // 不支持的操作
#define -UL_EINVAL      // 无效参数
#define -UL_ENOMEM      // 内存不足
```

### 7.3 函数返回值命名规范

**Linux 风格重要规则**：

> 如果函数名是**动作或命令**，返回错误码整数（0=成功，-Exxx=失败）  
> 如果函数名是**判断**，返回布尔值（非0=成功/真，0=失败/假）

**示例**：

```c
// 命令型函数：返回错误码
ul_err_t add_work(struct work_struct *work);  // 0=成功，-EBUSY=失败

// 判断型函数：返回布尔值
int pci_dev_present(struct pci_dev *dev);     // 1=找到，0=未找到
```

**混合使用这两种方式是 bug 的来源！**

**例外**：返回实际计算结果的函数（如返回指针的函数用 NULL 或 ERR_PTR 表示错误）

### 7.4 错误处理模式

#### 立即返回

```c
static ul_err_t ulb_serial_dev_drain_buffer_locked(struct ulb_serial_dev *p_serdev)
{
        ul_err_t ret = UL_OK;
        
        if (p_serdev->has_write_buffer) {
                ret = UL_SEMB_TAKE(p_serdev->tx_complete_sem, UL_WAIT_FOREVER);
                if (UL_OK != ret) {
                        return ret;  // 立即返回错误
                }
        }
        
        return ret;
}
```

#### 清理后返回

```c
ul_local ul_err_t __ul_serial_ioctl(...)
{
        ul_err_t ret;
        
        ret = UL_MUTEX_LOCK(p_serdev->wr_mutex_sem, UL_WAIT_FOREVER);
        if (UL_OK != ret) {
                return ret;
        }
        
        switch (cmd) {
        case UL_IOCTL_SERIAL_DCB_SET:
                ret = p_serdev->p_serial_ops->serial_dcb_set(p_serdev, p_arg);
                break;
        default:
                ret = -UL_ENOTSUP;
                break;
        }
        
cleanup:
        UL_MUTEX_UNLOCK(p_serdev->wr_mutex_sem);
        return ret;
}
```

### 7.5 断言和检查

```c
// 参数检查
if (!p_dev || !p_drvinfo) {
        return -UL_EINVAL;
}

// 状态检查
if (p_dev->state != DEV_STATE_READY) {
        return -UL_EBUSY;
}
```
