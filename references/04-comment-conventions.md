## 4. Comment Conventions

> **Summary**: Doxygen style; multi-line comments use Linux kernel `/* ... */` style; struct members use `/**< \brief */`; function comments include `\param`, `\return`, `\retval`; comments explain what not how

### 4.1 Doxygen Style

Use Doxygen-style comments for documentation generation.

### 4.2 Multi-line Comment Style

**Use Linux kernel style**:

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

Or Doxygen style:

```c
/**
 * \brief Add a reference child device
 *
 * \param[in] p_parent  parent device
 * \param[in] p_dev     child device
 * \param[out] p_desc   reference child descriptor
 * \return error code
 * \retval 0    success
 * \retval -1   invalid parameter
 *
 * \par Example
 * \code
 * serial_dev_t *p_parent = ...;
 * serial_dev_t *p_child = ...;
 * int ret = dev_add_ref_child(p_parent, p_child, NULL);
 * \endcode
 */
```

### 4.3 Struct Member Comments

Use `/**< \brief description */` format:

```c
struct serial_dev
{
        const char         *p_name;       /**< \brief device name */
        uint8_t             unit;         /**< \brief device unit number */
        int                 baudrate;     /**< \brief baud rate */
        void               *p_drv_data;   /**< \brief driver private data */
};
```

### 4.4 Function Comments

#### Full Function Documentation

```c
/**
 * \brief Open a serial device
 *
 * \param[in] p_dev  device handle
 * \param[in] flags  open flags
 * \return error code
 * \retval 0    success
 * \retval -1   device busy
 * \retval -2   invalid parameter
 */
int serial_open(serial_dev_t *p_dev, int flags);
```

#### Simplified Function Documentation

```c
/**
 * \brief Initialize list node
 *
 * A list node must be initialized before adding to a list.
 * \param[in] p_node  node to initialize
 */
static inline void list_init(struct list_node *p_node)
{
        p_node->next = p_node;
        p_node->prev = p_node;
}
```

### 4.5 Comment Principles

**Linux style emphasizes**:
- Comments should explain **what** (not **how**)
- Don't comment obvious code
- If a function is complex enough to need internal comments, it's too long — split it
- Comment the function's purpose and reason at its head
- Comment data declarations, one per line
