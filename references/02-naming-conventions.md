## 2. 命名规范

> **速览**: 类型 `xxx_t` 后缀；指针 `p_` 前缀；全局 `g_` 前缀；函数 `模块_功能` 格式；宏全大写+模块前缀；禁止匈牙利命名法

### 2.1 类型定义命名

使用 `typedef struct xxx xxx_t` 格式，结构体标签和 typedef 名称保持一致：

```c
typedef struct serial_dev serial_dev_t;
typedef struct serial_dcb serial_dcb_t;
```

### 2.2 变量命名

#### 指针变量
使用前缀 `p_` 表示指针：

```c
serial_dev_t *p_dev;
const char *p_drvname;
void *p_data;
```

#### 局部变量
使用小写字母 + 下划线分隔，保持简短：

```c
int ret = 0;
uint32_t cmd;
int i;              /* 循环计数器 */
char *tmp;          /* 临时变量 */
```

**Linux 风格建议**：本地变量名应该简短且能表达相关含义。如果怕混淆，说明函数太复杂了，应该拆分。

#### 全局变量
使用 `g_` 前缀：

```c
static int g_device_count;
static const char *g_default_path = "/dev/ttyS0";
```

#### 结构体成员
根据类型选择合适的前缀：

```c
struct serial_dev
{
        const char         *p_name;       /* 指针用 p_ */
        uint8_t             unit;         /* 普通变量小写 */
        int                 baudrate;
        void               *p_drv_data;   /* 指针用 p_ */
};
```

### 2.3 函数命名

#### 公开 API 函数
使用 `模块_功能` 格式，全小写 + 下划线：

```c
int serial_open(serial_dev_t *p_dev);
void serial_init(void);
int serial_register_driver(const serial_drv_t *p_drv);
```

#### 内部静态函数
使用前缀 `__`：

```c
static int __serial_ioctl(serial_dev_t *p_dev, int cmd, void *arg);
static int __serial_drain_buffer(serial_dev_t *p_dev);
```

#### 回调函数指针类型
使用 `pfn_` 前缀 + `_t` 后缀：

```c
typedef int (*pfn_serial_write_t)(serial_dev_t *p_dev,
        const void *p_buf, size_t len);
```

### 2.4 宏定义命名

#### 常量宏
全大写 + 下划线，带模块前缀：

```c
#define SERIAL_FLAG_NONBLOCK    (1 << 0)
#define SERIAL_MAX_PORTS        8
```

#### 功能性宏
全大写，带模块前缀：

```c
#define SERIAL_OFFSET(structure, member) \
        ((size_t)(&(((structure *)0)->member)))

#define SERIAL_CONTAINER_OF(ptr, type, member) \
        ((type *)((char *)(ptr) - SERIAL_OFFSET(type, member)))

#define ARRAY_SIZE(ar) (sizeof(ar) / sizeof((ar)[0]))
```

**Linux 风格建议**：优先使用已有的宏，不要重新发明。例如：
- 使用 `ARRAY_SIZE(x)` 而不是自己定义
- 使用 `min()` 和 `max()` 宏（带类型检查）

#### 配置宏
使用 `CONFIG_` 前缀：

```c
#if CONFIG_SERIAL_HAS_DMA
        /* DMA 相关代码 */
#endif
```

### 2.5 命名禁忌

- **禁止匈牙利命名法**：不要在变量名中包含类型信息（如 `iCount`, `pName`），编译器知道类型
- **全局变量必须有描述性名字**：不能叫 `foo`、`tmp` 等无意义名称
- **避免 master/slave、blacklist/whitelist**：
  - 推荐替换为：`primary/secondary`、`leader/follower`、`denylist/allowlist`
