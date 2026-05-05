## 4. 注释规范

> **速览**: Doxygen 风格；多行注释用 Linux 内核 `/* ... */` 风格；结构体成员用 `/**< \brief */`；函数注释含 `\param`、`\return`、`\retval`；注释解释 what 而非 how

### 4.1 Doxygen 风格

zhuqinsheng 使用 Doxygen 风格的注释，支持自动生成文档。

### 4.2 多行注释首选风格

**采用 Linux 内核风格**：

```c
/*
 * This is the preferred style for multi-line
 * comments in the Linux kernel source code.
 * Please use it consistently.
 *
 * Description:  A column of asterisks on the left side,
 * with beginning and ending almost-blank lines.
 */
```

或者也可以使用：

```c
/**
 * \brief 添加引用子设备
 *
 * \param[in] p_ref_parent_dev  引用父设备
 * \param[in] p_dev             子设备
 * \param[out] p_ref_child_des  引用子设备描述
 * \return 错误码
 * \retval UL_OK 成功
 * \retval -UL_EINVAL 参数无效
 *
 * \par 示例
 * \code
 * ulb_dev_t *parent_dev = ...;
 * ulb_dev_t *child_dev = ...;
 * ul_err_t ret = ulb_dev_add_ref_child(parent_dev, child_dev, NULL);
 * \endcode
 */
```

### 4.3 结构体成员注释

使用 `/**< \brief 说明 */` 格式：

```c
struct ulb_devhcf {
    const char         *p_driver_name;     /**< \brief 设备驱动名 */
    uint8_t             unit;              /**< \brief 设备单元号 */
    uint8_t             bus_type_id;       /**< \brief 设备所处总线的类型 */
    
    /**< \brief 这个设备是否创建总线
     *
     * 需要注意的是，不是所有设备都依赖这个标志，例如USB host就始终会创建总线
     * 而串口是否创建总线就依赖于这个标志
     */
    uint8_t             is_create_bus;
    
    struct ulb_dev     *p_dev;             /**< \brief 指向设备实例内存 */
    ul_const void      *p_devinfo;         /**< \brief 指向设备信息(常量) */
};
```

### 4.4 函数注释

#### 完整函数文档

```c
/**
 * \brief 添加引用子设备
 *
 * \param[in] p_ref_parent_dev  引用父设备
 * \param[in] p_dev             子设备
 * \param[out] p_ref_child_des  引用子设备描述
 * \return 错误码
 * \retval UL_OK 成功
 * \retval -UL_EINVAL 参数无效
 *
 * \par 示例
 * \code
 * ulb_dev_t *parent_dev = ...;
 * ulb_dev_t *child_dev = ...;
 * ul_err_t ret = ulb_dev_add_ref_child(parent_dev, child_dev, NULL);
 * \endcode
 */
ul_err_t ulb_dev_add_ref_child(
        ulb_dev_t *p_ref_parent_dev,
        ulb_dev_t *p_dev,
        struct ulb_dev_ref_child_des *p_ref_child_des);
```

#### 简化函数文档

```c
/**
 * \brief 初始化链表节点
 *
 * an list node must init before add it to a list
 * \param[in] list_node     a node to init
 * \retval 无
 */
static ul_inline void rtk_list_node_init(rtk_list_node_t *list_node)
{
    list_node->next = list_node;
    list_node->prev = list_node;
}
```

### 4.5 注释原则

**Linux 风格强调**：
- 注释应该解释**做什么**（what），而不是**怎么做**（how）
- 不要注释显而易见的代码
- 如果函数复杂到需要内部注释，说明函数太长，应该拆分
- 在函数头部注释其功能和原因
- 注释数据声明，每行只声明一个数据
