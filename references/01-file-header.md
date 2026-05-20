## 1. File Header Specification

> **Summary**: Each source file needs a copyright header; .c files add a function description header with modification history; .h files use a brief version.

### 1.1 Copyright Header

```c
/**
 * Copyright (c) 2026 Your Name
 * SPDX-License-Identifier: MIT
 */
```

### 1.2 Function Description Header (.c files)

```c
/**
 * \file
 * \brief Serial communication standard interface
 *
 * \internal
 * \par modification history
 * - 1.00 26-05-16  zqs, first implementation
 * - 1.01 26-06-01  zqs, add DMA support
 * \endinternal
 */
```

### 1.3 Brief Description Header (.h files)

Same format, empty modification history:

```c
/**
 * \file
 * \brief Common data type definitions
 *
 * \internal
 * \par modification history:
 * \endinternal
 */
```
