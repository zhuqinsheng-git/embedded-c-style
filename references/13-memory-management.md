## 13. 内存管理约定

> **速览**: 静态变量用 `ul_local` 标记；动态分配用 `sizeof(*p)` 而非类型名；不要强制转换 `void` 指针返回值

### 13.1 静态分配

使用 ul_local 标记本地静态变量：

```c
// 设备实例静态分配
ul_local struct ulb_ep24cxx_dev __g_eeprom_0_dev;

// 设备信息常量
ul_local ul_const struct ulb_ep24cxx_devinfo __g_eeprom_0_devinfo = {
        0x50,           /* I2C从机地址 */
        EP24C02,        /* 芯片型号 */
};
```

### 13.2 动态内存分配

**Linux 内核推荐的分配方式**：

```c
// ✅ 推荐：传递指针解引用的大小
p = kmalloc(sizeof(*p), GFP_KERNEL);

// ❌ 避免：传递类型名
p = kmalloc(struct my_struct, GFP_KERNEL);
```

**理由**：当指针类型改变时，第一种方式自动适应，第二种可能出错。

**数组分配**：
```c
// 普通数组
p = kmalloc_array(n, sizeof(*p), GFP_KERNEL);

// 零初始化数组
p = kcalloc(n, sizeof(*p), GFP_KERNEL);
```

**优点**：
- 检查 n * sizeof(...) 溢出
- 溢出时返回 NULL
- 失败时自动发起堆栈转储，无需额外错误消息

**不要强制转换 void 指针**：
```c
// ✅ 正确
p = kmalloc(size, GFP_KERNEL);

// ❌ 错误（多余）
p = (struct my_struct *)kmalloc(size, GFP_KERNEL);
```
