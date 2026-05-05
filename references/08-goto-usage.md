## 8. 集中的函数退出路径（goto 使用）

> **速览**: 需要资源清理时推荐用 goto；标签名用有含义的名称（`out_free_buffer`、`err_free_foo`）；避免单一 `err` 标签；不需要清理时直接 return

**Linux 内核强烈推荐在需要清理时使用 goto**。

### 8.1 为什么使用 goto

- 无条件语句容易理解和跟踪
- 减少嵌套深度
- 避免忘记更新个别退出点导致的错误
- 让编译器优化冗余代码

### 8.2 使用模式

```c
int fun(int a)
{
        int result = 0;
        char *buffer;

        buffer = kmalloc(SIZE, GFP_KERNEL);
        if (!buffer)
                return -ENOMEM;

        if (condition1) {
                while (loop1) {
                        ...
                }
                result = 1;
                goto out_free_buffer;
        }
        ...
out_free_buffer:
        kfree(buffer);
        return result;
}
```

### 8.3 标签命名

**选择能说明行为的标签名**：

```c
// ✅ 好的命名
out_free_buffer:
err_free_bar:
err_free_foo:

// ❌ 坏的命名
err1:
err2:
```

### 8.4 避免单一 err 标签的错误

```c
// ❌ 错误：某些路径上 foo 可能为 NULL
err:
        kfree(foo->bar);
        kfree(foo);
        return ret;

// ✅ 正确：分离错误标签
err_free_bar:
        kfree(foo->bar);
err_free_foo:
        kfree(foo);
        return ret;
```

### 8.5 不需要清理时直接 return

```c
if (error_condition)
        return -EINVAL;
```
