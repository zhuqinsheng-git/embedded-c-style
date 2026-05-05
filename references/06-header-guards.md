## 6. 头文件保护

### 6.1 标准格式

使用双重下划线 + 全大写文件名：

```c
#ifndef __AWBUS_DEV_H__
#define __AWBUS_DEV_H__

// 头文件内容

#endif /* __AWBUS_DEV_H__ */
```

### 6.2 简化格式

也可以使用单重下划线：

```c
#ifndef __AW_COMMON_H
#define __AW_COMMON_H

// 头文件内容

#endif
```

### 6.3 C++ 兼容性

所有头文件必须支持 C++ 调用：

```c
#ifndef __AW_COMMON_H
#define __AW_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

// C 代码

#ifdef __cplusplus
}
#endif

#endif /* __AW_COMMON_H */
```
