## 7. 错误处理规范

### 7.1 错误码类型

使用 `aw_err_t` 类型返回错误码：

```c
aw_err_t awb_serial_open(awb_dev_t *p_dev);
aw_err_t awb_register_dev_driver(...);
```

### 7.2 返回值约定

- **成功**: 返回 AW_OK (通常为 0)
- **失败**: 返回负的错误码

```c
#define AW_OK           0
#define -AW_EACCES      // 权限拒绝
#define -AW_ENOTSUP     // 不支持的操作
#define -AW_EINVAL      // 无效参数
#define -AW_ENOMEM      // 内存不足
```

### 7.3 函数返回值命名规范

**Linux 风格重要规则**：

> 如果函数名是**动作或命令**，返回错误码整数（0=成功，-Exxx=失败）  
> 如果函数名是**判断**，返回布尔值（非0=成功/真，0=失败/假）

**示例**：

```c
// 命令型函数：返回错误码
aw_err_t add_work(struct work_struct *work);  // 0=成功，-EBUSY=失败

// 判断型函数：返回布尔值
int pci_dev_present(struct pci_dev *dev);     // 1=找到，0=未找到
```

**混合使用这两种方式是 bug 的来源！**

**例外**：返回实际计算结果的函数（如返回指针的函数用 NULL 或 ERR_PTR 表示错误）

### 7.4 错误处理模式

#### 立即返回

```c
static aw_err_t awb_serial_dev_drain_buffer_locked(struct awb_serial_dev *p_serdev)
{
        aw_err_t ret = AW_OK;
        
        if (p_serdev->has_write_buffer) {
                ret = AW_SEMB_TAKE(p_serdev->tx_complete_sem, AW_WAIT_FOREVER);
                if (AW_OK != ret) {
                        return ret;  // 立即返回错误
                }
        }
        
        return ret;
}
```

#### 清理后返回

```c
aw_local aw_err_t __aw_serial_ioctl(...)
{
        aw_err_t ret;
        
        ret = AW_MUTEX_LOCK(p_serdev->wr_mutex_sem, AW_WAIT_FOREVER);
        if (AW_OK != ret) {
                return ret;
        }
        
        switch (cmd) {
        case AW_IOCTL_SERIAL_DCB_SET:
                ret = p_serdev->p_serial_ops->serial_dcb_set(p_serdev, p_arg);
                break;
        default:
                ret = -AW_ENOTSUP;
                break;
        }
        
cleanup:
        AW_MUTEX_UNLOCK(p_serdev->wr_mutex_sem);
        return ret;
}
```

### 7.5 断言和检查

```c
// 参数检查
if (!p_dev || !p_drvinfo) {
        return -AW_EINVAL;
}

// 状态检查
if (p_dev->state != DEV_STATE_READY) {
        return -AW_EBUSY;
}
```
