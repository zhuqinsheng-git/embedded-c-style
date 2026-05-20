## 4. Comment Conventions

> **Summary**: Doxygen style; multi-line `/* ... */` kernel style; struct members use `/**< \brief */`; function comments include `\param`, `\return`, `\retval`; explain **what** not **how**.

### 4.1 Multi-line Comment Style

Linux kernel style:

```c
/*
 * This is the preferred style for multi-line
 * comments in the Linux kernel source code.
 */
```

### 4.2 Function Comments

Doxygen style with full parameter documentation:

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

### 4.3 Struct Member Comments

Use `/**< \brief description */` inline:

```c
struct serial_dev
{
        const char         *p_name;       /**< \brief device name */
        uint8_t             unit;         /**< \brief device unit number */
        int                 baudrate;     /**< \brief baud rate */
        void               *p_drv_data;   /**< \brief driver private data */
};
```

### 4.4 Comment Principles

- Explain **what**, not **how**
- Don't comment obvious code
- If a function needs internal comments, it's too long — split it
- Comment data declarations, one per line
