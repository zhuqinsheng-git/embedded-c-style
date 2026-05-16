---
name: embedded-c-style
description: Embedded C coding conventions based on Linux Kernel Coding Style. Use when writing, reviewing, or refactoring C code for embedded systems. Covers naming, formatting, comments, error handling, and data structures.
---

# Embedded C Coding Style

Based on Linux Kernel Coding Style. All rules in [references/](references/) directory.

## Core Rules

### Indentation & Braces

- **8-char tabs**, not 4 spaces
- **80 columns** max
- **Allman braces**: opening brace on its own line for all blocks (if/switch/for/while/functions)
- Single statements: no braces

```c
if (condition)
{
        do_something();
}

int function(int x)
{
        return x + 1;
}
```

### Naming

| Category | Rule | Example |
|----------|------|---------|
| Types | `xxx_t` suffix | `serial_dev_t` |
| Pointers | `p_` prefix | `p_dev`, `p_name` |
| Globals | `g_` prefix | `g_count` |
| Internal functions | `__` prefix | `__serial_ioctl` |
| Macros | ALL_CAPS | `SERIAL_MAX_PORTS` |

### Error Handling

- Action functions: return `int` (0=success, negative=error)
- Predicate functions: return `bool` or `int` (non-zero=true)
- Use standard errno: `-EINVAL`, `-ENOMEM`, `-EBUSY`
- Multi-resource cleanup: use goto with descriptive labels

```c
static int __driver_init(driver_t *p_drv)
{
        p_drv->p_buf = malloc(sizeof(*p_drv->p_buf));
        if (!p_drv->p_buf)
                return -ENOMEM;

        int ret = register_device(p_drv);
        if (ret != 0)
                goto err_free_buf;

        return 0;

err_free_buf:
        free(p_drv->p_buf);
        return ret;
}
```

### Comments

- Doxygen style: `\brief`, `\param[in]`, `\return`, `\retval`
- Struct members: `/**< \brief description */`
- Explain **what**, not **how**

### Typedef

Don't typedef structs. Use `struct xxx` directly. Only typedef for:
- Opaque types (hide implementation)
- Integer abstraction (`uint32_t`)

### Memory

- `malloc(sizeof(*p))` not `malloc(sizeof(struct my_struct))`
- Don't cast `void *` return

## Reference Files

| Chapter | Topic | File |
|---------|-------|------|
| 1 | File Header | [01-file-header.md](references/01-file-header.md) |
| 2 | Naming | [02-naming-conventions.md](references/02-naming-conventions.md) |
| 3 | Format | [03-code-format.md](references/03-code-format.md) |
| 4 | Comments | [04-comment-conventions.md](references/04-comment-conventions.md) |
| 5 | Error Handling | [05-error-handling.md](references/05-error-handling.md) |
| 6 | Typedef & Structs | [06-typedef-and-struct.md](references/06-typedef-and-struct.md) |
| 7 | Misc | [07-misc.md](references/07-misc.md) |
| A | Appendix | [A-appendix.md](references/A-appendix.md) |
