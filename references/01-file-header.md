## 1. 文件头规范

### 1.1 标准版权头

每个源文件必须包含标准的版权声明和许可信息：

```c
/*******************************************************************************
*                             zhuqinsheng
*                       ----------------------------
*                       embedded software development
*
* Copyright (c) 2026-present zhuqinsheng
* ALL rights reserved.
*******************************************************************************/
```

### 1.2 功能说明头（.c 文件）

实现文件需要添加功能说明和修改历史：

```c
/**
 * \file
 * \brief 串口通讯标准接口
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-30  orz, first implementation
 * - 1.00 15-06-20  deo, add ul_serdev_remove
 * -      18-10-15  hsg, add ul_serdev operate instead of ul_tydev operate
 * \endinternal
 */
```

### 1.3 简要说明头（.h 文件）

头文件可以简化为：

```c
/**
 * \file
 * \brief zhuqinsheng general data type defines
 *
 * \internal
 * \par modification history:
 * \endinternal
 */
```
