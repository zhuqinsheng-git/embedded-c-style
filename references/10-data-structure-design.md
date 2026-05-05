## 10. 数据结构设计

### 10.1 不透明指针

使用前向声明隐藏实现细节：

```c
// 头文件中
typedef struct awb_dev awb_dev_t;  // 前向声明
struct awb_dev;                     // 不完整类型

// 使用者只能操作指针，无法访问内部成员
aw_err_t awb_dev_init(awb_dev_t *p_dev);
```

### 10.2 函数指针封装

将操作封装到结构体中，实现面向对象的设计：

```c
typedef struct awb_dev_drvinfo {
        uint8_t     awb_ver;
        uint8_t     bus_type_id;
        char       *p_drvname;
        
        // 函数指针
        aw_err_t (*probe) (awb_dev_t *p_dev);
        aw_err_t (*remove) (awb_dev_t *p_dev);
        awb_dev_pm_ops_t pm_ops;
} awb_dev_drvinfo_t;
```

### 10.3 链表节点

使用标准的链表结构：

```c
typedef struct _rtk_list_node {
        struct _rtk_list_node *next;
        struct _rtk_list_node *prev;
} rtk_list_node_t;

struct awb_dev {
        struct aw_list_head bus_dev_list_node;  // 链表节点
        struct awb_dev *p_parent;               // 父设备
        // ...
};
```

### 10.4 引用计数

**如果一个数据结构在创建和销毁它的单线执行环境之外可见，必须有引用计数**。

```c
struct my_data {
        atomic_t refcount;  // 引用计数
        // ... 其他字段
};
```

**注意**：
- 上锁不能取代引用计数
- 上锁是为了保持一致性，引用计数是内存管理技巧
- 很多结构有 2 级引用计数（如 `mm_users` 和 `mm_count`）

### 10.5 数据声明

**每行只声明一个数据**，方便添加注释：

```c
// ✅ 正确
int timeout;      /**< \brief 超时时间（毫秒） */
int retry_count;  /**< \brief 重试次数 */

// ❌ 错误
int timeout, retry_count;
```
