## 1. File Header Specification

> **Summary**: Each source file should contain a copyright header; .c files add a function description header (with modification history); .h files can use a brief description header

### 1.1 Standard Copyright Header

Each source file should contain a copyright notice and license:

```c
/**
 * Copyright (c) 2026 Your Name
 * SPDX-License-Identifier: MIT
 */
```

Or a more complete format:

```c
/*
 * Copyright (c) 2026 Your Name
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the MIT License.
 */
```

### 1.2 Function Description Header (.c files)

Implementation files should add function description and modification history:

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

Header files can be simplified:

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
