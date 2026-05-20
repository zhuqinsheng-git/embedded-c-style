## 3. Code Format

> **Summary**: Tab=8 chars; line width ≤80; Allman braces (all on new line); space after keywords, not after sizeof; `*` near variable name; case aligned with switch.

### 3.1 Indentation

**8-character tabs** (Linux standard, not 4 spaces). Large indentation makes block hierarchy easier to see.

### 3.2 Line Width

**80 columns, hard limit.** Break long statements at logical points. Exception: user-visible strings (don't break, hard to grep).

```c
int serial_register_driver(
        const serial_drv_t *p_drv,
        const char *p_name)
{
        ...
}
```

### 3.3 Braces

**Allman style**: opening brace on its own line for all blocks (functions, if, switch, for, while, do).

```c
int function(int x)
{
        return x + 1;
}

if (condition)
{
        do_something();
}
else
{
        do_other();
}

switch (action)
{
case KOBJ_ADD:
        return "add";
default:
        return NULL;
}
```

**Single statements don't need braces.** If one branch has multiple statements, use braces on all branches.

### 3.4 Spacing

- **Space after**: `if`, `switch`, `case`, `for`, `do`, `while`
- **No space after**: `sizeof`, `typeof`, `alignof`, `__attribute__`
- **Pointer `*`**: near variable name (`char *p` not `char* p`)
- **Binary operators**: space on both sides (`a + b`, `x == y`)
- **Unary operators**: no space (`&x`, `*p`, `!flag`, `++i`)
- **Member operators**: no space (`ptr->member`, `obj.member`)

### 3.5 Switch Case

`case` labels aligned with `switch`, no extra indent:

```c
switch (suffix)
{
case 'G':
case 'g':
        mem <<= 30;
        break;
default:
        break;
}
```

### 3.6 Header Guards & C++ Compatibility

```c
#ifndef __SERIAL_H__
#define __SERIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* declarations */

#ifdef __cplusplus
}
#endif

#endif /* __SERIAL_H__ */
```

### 3.7 Function Design

- Short functions, one purpose each
- Max ~24 visible lines (80x24 terminal)
- Local variables: ≤10
- Prefer inline functions over macros (only if ≤3 lines)
