## 5. 代码格式规范

### 5.1 缩进（重要）

**⚠️ 采用 Linux 内核标准：使用 8 字符制表符（Tab）**

```
制表符是 8 个字符，所以缩进也是 8 个字符。
```

**理由**：
- 缩进的全部意义在于清楚定义控制块的起止
- 大缩进使代码在长时间阅读后更容易分辨层次
- 如果超过 3 级缩进，说明代码已经有问题了

**配置编辑器**：
- Emacs: 设置 `c-basic-offset` 为 8，`indent-tabs-mode` 为 t
- Vim: 设置 `tabstop=8`, `shiftwidth=8`, `expandtab` 或不设置
- VSCode: 设置 `"editor.tabSize": 8`, `"editor.insertSpaces": false`

**Switch 语句的特殊缩进**：

```c
switch (suffix) {
case 'G':
case 'g':
        mem <<= 30;
        break;
case 'M':
case 'm':
        mem <<= 20;
        break;
case 'K':
case 'k':
        mem <<= 10;
        fallthrough;
default:
        break;
}
```

**注意**：`case` 标签与 `switch` 对齐，不要二次缩进。

### 5.2 行长限制

**每一行的长度限制是 80 列，强烈建议遵守。**

长于 80 列的语句要打散成有意义的片段：

```c
// ✅ 正确：参数换行对齐
aw_err_t awb_register_dev_driver(
        awb_dev_driver_registration_t *p_dev_driver_regist,
        const awb_dev_drvinfo_t *p_drvinfo)
{
    // ...
}

// ✅ 正确：长表达式换行
if (very_long_condition_variable_name == SOME_VALUE &&
    another_important_check(result) == TRUE) {
    do_something();
}
```

**例外**：
- 用户可见的字符串（如 printk 信息）不要打散，否则难以 grep
- 超过 80 列能显著增加可读性且不隐藏信息时

### 5.3 大括号和空格

#### 大括号放置规则

**采用 K&R 风格，但函数有特殊规则**：

1. **非函数语句块**（if, switch, for, while, do）：起始大括号在行尾

```c
if (x is true) {
        we do y
}

switch (action) {
case KOBJ_ADD:
        return "add";
case KOBJ_REMOVE:
        return "remove";
default:
        return NULL;
}
```

2. **函数定义**：起始大括号在**下一行开头**

```c
int function(int x)
{
        body of function
}
```

3. **do-while 和 else**：结束大括号后跟剩余部分

```c
do {
        body of do-loop
} while (condition);

if (x == y) {
        ..
} else if (x > y) {
        ...
} else {
        ....
}
```

4. **单语句不需要大括号**：

```c
if (condition)
        action();

if (condition)
        do_this();
else
        do_that();
```

5. **多分支中有一个是多语句，全部用大括号**：

```c
if (condition) {
        do_this();
        do_that();
} else {
        otherwise();
}
```

#### 空格使用规则

**关键字后加空格**：
```c
if, switch, case, for, do, while
```

**关键字后不加空格**：
```c
sizeof, typeof, alignof, __attribute__
```

**示例**：
```c
if (condition) { }          // ✅ if 后有空格
s = sizeof(struct file);    // ✅ sizeof 后无空格
s = sizeof( struct file );  // ❌ 错误
```

**指针声明**：`*` 靠近变量名

```c
char *linux_banner;                      // ✅ 正确
unsigned long long memparse(char *ptr, char **retptr);  // ✅ 正确
char* wrong_style;                       // ❌ 错误
```

**运算符两侧加空格**：
```c
=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :
```

**一元操作符不加空格**：
```c
&  *  +  -  ~  !  sizeof  typeof  alignof  __attribute__  defined
++  --  (前后都不加)
```

**结构体成员操作符不加空格**：
```c
ptr->member
obj.member
```

**禁止事项**：
- 不要在行尾留空格
- 不要把多个语句放在一行（除非有特殊原因）
- 不要用逗号避免大括号：`if (cond) do_a(), do_b();` ❌
- 不要在一行里放多个赋值语句

### 5.4 函数定义格式

**函数原型应包含参数名**：

```c
// ✅ 正确：包含参数名
aw_err_t awb_serial_open(awb_dev_t *p_dev);

// ❌ 错误：缺少参数名
aw_err_t awb_serial_open(awb_dev_t *);
```

**不要在函数声明中使用 `extern`**（多余且使行变长）

**函数原型元素顺序**（Linux 风格）：

```c
__init void * __must_check action(enum magic value, size_t size, u8 count,
                                  char *fmt, ...) __printf(4, 5) __malloc;
```

顺序：
1. 存储类型（`static __always_inline`）
2. 存储类型属性（`__init`）
3. 返回类型（`void *`）
4. 返回类型属性（`__must_check`）
5. 函数名（`action`）
6. 函数参数（必须写参数名）
7. 函数参数属性（`__printf(4, 5)`）
8. 函数行为属性（`__malloc`）

**函数定义时**，参数属性要移到存储类型属性之后：

```c
static __always_inline __init __printf(4, 5) void * __must_check action(
        enum magic value, size_t size, u8 count, char *fmt, ...) __malloc
{
        ...
}
```

**函数之间用空行隔开**，EXPORT 宏紧跟在结束大括号后：

```c
int system_is_up(void)
{
        return system_state == SYSTEM_RUNNING;
}
EXPORT_SYMBOL(system_is_up);
```
