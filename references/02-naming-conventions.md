## 2. 命名规范

> **速览**: 类型 `xxx_t` 后缀；指针 `p_` 前缀；全局 `__g_` 前缀；函数 `模块_功能` 格式；宏全大写+模块前缀；禁止匈牙利命名法

### 2.1 类型定义命名

使用 `typedef struct xxx xxx_t` 格式，结构体标签和 typedef 名称保持一致：

```c
typedef struct ulb_dev ulb_dev_t;
typedef struct ulb_bus_type_info ulb_bus_type_info_t;
typedef struct ul_serial_dcb ul_serial_dcb_t;
```

**注意**：避免使用类似 `vps_t` 这样不透明的 typedef，除非符合[第 9 章 Typedef 使用规范](09-typedef-usage.md)的规则。

### 2.2 变量命名

#### 指针变量
使用前缀 `p_` 表示指针：

```c
ulb_dev_t *p_dev;
const char *p_drvname;
void *p_drv_data;
struct ulb_dev *p_parent;
```

#### 局部变量
使用小写字母 + 下划线分隔，保持简短：

```c
ul_err_t ret = UL_OK;
uint32_t cmd;
ul_oflag_t oflag;
int i;              // 循环计数器
char *tmp;          // 临时变量
```

**Linux 风格建议**：本地变量名应该简短且能表达相关含义。如果怕混淆，说明函数太复杂了，应该拆分。

#### 全局变量
使用 `__g_` 前缀：

```c
ul_local ul_const struct ulb_ep24cxx_devinfo __g_eeprom_0_devinfo;
ul_local struct ulb_ep24cxx_dev __g_eeprom_0_dev;
```

#### 结构体成员
根据类型选择合适的前缀：

```c
struct ulb_devhcf {
    const char         *p_driver_name;     // 指针用 p_
    uint8_t             unit;              // 普通变量小写
    uint8_t             bus_type_id;
    struct ulb_dev     *p_dev;             // 指针用 p_
    ul_const void      *p_devinfo;
};
```

### 2.3 函数命名

#### 公开 API 函数
使用 `模块_功能` 格式，全小写 + 下划线：

```c
ul_err_t ulb_serial_open(ulb_dev_t *p_dev);
void ulb_plb_init(void);
ul_err_t ulb_register_dev_driver(...);
uint32_t ulb_devhcf_list_count_get(void);
```

#### 内部静态函数
使用前缀 `__` 或完整的模块前缀：

```c
static ul_err_t __ul_serial_ioctl(...);
static ul_err_t ulb_serial_dev_drain_locked(...);
static ul_err_t ulb_serial_dev_drain_buffer_locked(...);
```

#### 回调函数指针类型
使用 `pfn_` 前缀 + `_t` 后缀：

```c
typedef ul_bool_t (*pfn_driver_match_t)(
        const ulb_bus_type_info_t *p_bustype,
        const ulb_dev_drvinfo_t *p_drv,
        struct ulb_dev *p_dev);
```

### 2.4 宏定义命名

#### 常量宏
全大写 + 下划线，带模块前缀：

```c
#define ULB_DEV_FLAGS_IS_BUS            (1 << 0)
#define ULB_BUS_TYPE_ID_PLB             1
#define ULB_BUS_TYPE_ID_I2C             20
#define ULB_BUS_TYPE_ID_SPI             21
#define UL_LITTLE_ENDIAN                1234
#define UL_BIG_ENDIAN                   3412
```

#### 功能性宏
使用 `UL_` 前缀的大写形式：

```c
#define UL_OFFSET(structure, member) \
    ((ul_cpu_uint_t)(&(((structure *)0)->member)))

#define UL_CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - UL_OFFSET(type, member)))

#define UL_NELEMENTS(ar) (sizeof(ar) / sizeof((ar)[0]))
#define UL_MEMBER_SIZE(structure, member) (sizeof(((structure *)0)->member))
```

**Linux 风格建议**：优先使用内核已有的宏，不要重新发明。例如：
- 使用 `ARRAY_SIZE(x)` 而不是自己定义
- 使用 `min()` 和 `max()` 宏（带类型检查）
- 使用 `sizeof_field(t, f)` 计算结构体成员大小

#### 配置宏
使用 `CONFIG_` 前缀：

```c
#if CONFIG_ULB_SERIAL_HAS_WRITE_BUF
    // 代码
#endif

#if CONFIG_ULBUS_DEV_REF_CHILD_EN
    struct ul_list_head ref_child_head;
#endif
```

### 2.5 命名禁忌

- **禁止匈牙利命名法**：不要在变量名中包含类型信息（如 `iCount`, `pName`），编译器知道类型
- **全局变量必须有描述性名字**：不能叫 `foo`、`tmp` 等无意义名称
- **避免 master/slave、blacklist/whitelist**：
  - 推荐替换为：`primary/secondary`、`leader/follower`、`denylist/allowlist`
  - **注意**：以上规则不适用于中文文档
