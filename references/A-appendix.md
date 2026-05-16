## Appendix: Quick Reference

### A. Naming Conventions

| Category | Convention | Example |
|----------|-----------|---------|
| **Type definitions** | `xxx_t` suffix | `serial_dev_t`, `int32_t` |
| **Pointer variables** | `p_` prefix | `p_dev`, `p_name`, `p_data` |
| **Global variables** | `g_` prefix | `g_device_count` |
| **Local variables** | lowercase + underscore, short | `ret`, `cmd`, `i` |
| **Public functions** | `module_action` | `serial_open` |
| **Internal functions** | `__` prefix | `__serial_ioctl` |
| **Function pointer types** | `pfn_xxx_t` | `pfn_write_t` |
| **Constant macros** | ALL_CAPS + module prefix | `SERIAL_MAX_PORTS` |
| **Config macros** | `CONFIG_XXX` | `CONFIG_HAS_DMA` |

### B. Comment Tags

| Tag | Usage |
|-----|-------|
| `\brief` | Brief description |
| `\param[in]` | Input parameter |
| `\param[out]` | Output parameter |
| `\return` | Return value |
| `\retval` | Specific return value |
| `\par` | Paragraph title |
| `\code` / `\endcode` | Code block |
| `\internal` | Internal notes |

### C. Common Error Codes

| Error | Value | Meaning |
|-------|-------|---------|
| 0 | 0 | Success |
| `-EPERM` | -1 | Not permitted |
| `-ENOENT` | -2 | No such file |
| `-EIO` | -5 | I/O error |
| `-ENOMEM` | -12 | Out of memory |
| `-EACCES` | -13 | Permission denied |
| `-EBUSY` | -16 | Resource busy |
| `-EINVAL` | -22 | Invalid argument |

### D. Code Format Quick Reference

| Item | Rule |
|------|------|
| **Indentation** | 8-char tab |
| **Line width** | 80 columns |
| **All braces** | New line (Allman) |
| **Single statement** | No braces |
| **Switch case** | Aligned with switch |
| **Pointer `*`** | Near variable name |
| **Keywords** | Space after if/for/while |
| **sizeof** | No space after |

### E. Keywords

Use standard C keywords directly. **Do not define alias macros** (like `#define ul_local static`).

| Use | Not |
|-----|-----|
| `static` | `ul_local` |
| `const` | `ul_const` |
| `inline` | `ul_inline` |
| `extern` | `ul_import` / `ul_export` |

### F. Boolean Type

Use `bool` from `<stdbool.h>`, not `int`:

```c
bool is_ready = true;   /* ✅ */
int is_ready = 1;       /* ❌ */
```

### G. Typedef Rules

**Don't** typedef structs. **Do** typedef for:
- Opaque types (hide implementation)
- Integer abstraction (`uint32_t`)
- C99 standard types
