## 2. 命名规范

### 2.1 类型定义命名

使用 `typedef struct xxx xxx_t` 格式，结构体标签和 typedef 名称保持一致：

```c
typedef struct awb_dev awb_dev_t;
typedef struct awb_bus_type_info awb_bus_type_info_t;
typedef struct aw_serial_dcb aw_serial_dcb_t;
```

**注意**：避免使用类似 `vps_t` 这样不透明的 typedef，除非符合第 9 章的规则。

### 2.2 变量命名

#### 指针变量
使用前缀 `p_` 表示指针：

```c
awb_dev_t *p_dev;
const char *p_drvname;
void *p_drv_data;
struct awb_dev *p_parent;
```

#### 局部变量
使用小写字母 + 下划线分隔，保持简短：

```c
aw_err_t ret = AW_OK;
uint32_t cmd;
aw_oflag_t oflag;
int i;              // 循环计数器
char *tmp;          // 临时变量
```

**Linux 风格建议**：本地变量名应该简短且能表达相关含义。如果怕混淆，说明函数太复杂了，应该拆分。

#### 全局变量
使用 `__g_` 前缀：

```c
aw_local aw_const struct awb_ep24cxx_devinfo __g_eeprom_0_devinfo;
aw_local struct awb_ep24cxx_dev __g_eeprom_0_dev;
```

#### 结构体成员
根据类型选择合适的前缀：

```c
struct awb_devhcf {
    const char         *p_driver_name;     // 指针用 p_
    uint8_t             unit;              // 普通变量小写
    uint8_t             bus_type_id;
    struct awb_dev     *p_dev;             // 指针用 p_
    aw_const void      *p_devinfo;
};
```

### 2.3 函数命名

#### 公开 API 函数
使用 `模块_功能` 格式，全小写 + 下划线：

```c
aw_err_t awb_serial_open(awb_dev_t *p_dev);
void awb_plb_init(void);
aw_err_t awb_register_dev_driver(...);
uint32_t awb_devhcf_list_count_get(void);
```

#### 内部静态函数
使用前缀 `__` 或完整的模块前缀：

```c
static aw_err_t __aw_serial_ioctl(...);
static aw_err_t awb_serial_dev_drain_locked(...);
static aw_err_t awb_serial_dev_drain_buffer_locked(...);
```

#### 回调函数指针类型
使用 `pfn_` 前缀 + `_t` 后缀：

```c
typedef aw_bool_t (*pfn_driver_match_t)(
        const awb_bus_type_info_t *p_bustype,
        const awb_dev_drvinfo_t *p_drv,
        struct awb_dev *p_dev);
```

### 2.4 宏定义命名

#### 常量宏
全大写 + 下划线，带模块前缀：

```c
#define AWB_DEV_FLAGS_IS_BUS            (1 << 0)
#define AWB_BUS_TYPE_ID_PLB             1
#define AWB_BUS_TYPE_ID_I2C             20
#define AWB_BUS_TYPE_ID_SPI             21
#define AW_LITTLE_ENDIAN                1234
#define AW_BIG_ENDIAN                   3412
```

#### 功能性宏
使用 `AW_` 前缀的大写形式：

```c
#define AW_OFFSET(structure, member) \
    ((aw_cpu_uint_t)(&(((structure *)0)->member)))

#define AW_CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - AW_OFFSET(type, member)))

#define AW_NELEMENTS(ar) (sizeof(ar) / sizeof((ar)[0]))
#define AW_MEMBER_SIZE(structure, member) (sizeof(((structure *)0)->member))
```

**Linux 风格建议**：优先使用内核已有的宏，不要重新发明。例如：
- 使用 `ARRAY_SIZE(x)` 而不是自己定义
- 使用 `min()` 和 `max()` 宏（带类型检查）
- 使用 `sizeof_field(t, f)` 计算结构体成员大小

#### 配置宏
使用 `CONFIG_` 前缀：

```c
#if CONFIG_AWB_SERIAL_HAS_WRITE_BUF
    // 代码
#endif

#if CONFIG_AWBUS_DEV_REF_CHILD_EN
    struct aw_list_head ref_child_head;
#endif
```

### 2.5 命名禁忌

- **禁止匈牙利命名法**：不要在变量名中包含类型信息（如 `iCount`, `pName`），编译器知道类型
- **全局变量必须有描述性名字**：不能叫 `foo`、`tmp` 等无意义名称
- **避免 master/slave、blacklist/whitelist**：
  - 推荐替换为：`primary/secondary`、`leader/follower`、`denylist/allowlist`
  - **注意**：以上规则不适用于中文文档
