## 3. Code Format

> **Summary**: Tab=8 chars; line width ≤80; Allman braces (all braces on new line); space after keywords, not after sizeof; `*` near variable name; case aligned with switch

### 3.1 Indentation

**Use 8-character tabs (Linux standard, not 4 spaces).**

Reason: Indentation exists to define block boundaries. Large indentation makes hierarchy easier to see after hours of reading.

### 3.2 Line Width

**80 columns. Hard limit.**

Break long statements into meaningful pieces:

```c
int serial_register_driver(
        const serial_drv_t *p_drv,
        const char *p_name)
{
        ...
}
```

Exceptions: user-visible strings (don't break, hard to grep).

### 3.3 Braces

**Allman style: opening brace on its own line for all blocks.**

```c
/* Functions */
int function(int x)
{
        body of function
}

/* Control statements */
if (condition)
{
        do_something();
}

switch (action)
{
case KOBJ_ADD:
        return "add";
case KOBJ_REMOVE:
        return "remove";
default:
        return NULL;
}

do
{
        body of do-loop
} while (condition);

/* else on its own line */
if (x == y)
{
        ...
}
else
{
        ...
}
```

**Single statements don't need braces**:

```c
if (condition)
        action();

if (condition)
        do_this();
else
        do_that();
```

**Multi-branch with one branch having multiple statements: use braces on all branches**:

```c
if (condition)
{
        do_this();
        do_that();
}
else
{
        otherwise();
}
```

### 3.4 Spacing

**Space after keywords**: `if`, `switch`, `case`, `for`, `do`, `while`

**No space after**: `sizeof`, `typeof`, `alignof`, `__attribute__`

**Pointer declaration**: `*` near variable name

```c
char *linux_banner;              /* ✅ */
char* wrong_style;               /* ❌ */
```

**Binary operators**: space on both sides

```c
=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :
```

**Unary operators**: no space

```c
&  *  +  -  ~  !  ++  --
```

**Struct member operators**: no space

```c
ptr->member
obj.member
```

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

### 3.6 Header Guards

```c
#ifndef __SERIAL_H__
#define __SERIAL_H__

/* header content */

#endif /* __SERIAL_H__ */
```

### 3.7 C++ Compatibility

All headers must support C++ callers:

```c
#ifndef __SERIAL_H__
#define __SERIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* C declarations */

#ifdef __cplusplus
}
#endif

#endif /* __SERIAL_H__ */
```

### 3.8 Function Design

- Functions should be short and do one thing
- Max 1-2 screens (80x24 terminal)
- Local variables: ≤5-10
- Inline only if ≤3 lines
- Prefer inline functions over macros
