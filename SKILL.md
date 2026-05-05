---
name: c-code-style
description: zhuqinsheng C 语言编码规范 - 基于 Linux Kernel Coding Style 的嵌入式 C 编码规范，覆盖文件头、命名、注释、格式、内存管理等完整编码约定
---

# zhuqinsheng C 语言编码规范

> **版本**: 0.1  
> **适用框架**: zhuqinsheng Embedded Framework  
> **最后更新**: 2026-05-05  
> **参考标准**: Linux Kernel Coding Style + zhuqinsheng 框架特性

本规范分为以下章节，可根据需要查阅对应文件：

## 章节索引

| 章节 | 内容 | 文件 |
|------|------|------|
| 1. 文件头规范 | 版权头、功能说明头、简要说明头 | [references/01-file-header.md](references/01-file-header.md) |
| 2. 命名规范 | 类型、变量、函数、宏的命名规则 | [references/02-naming-conventions.md](references/02-naming-conventions.md) |
| 3. 关键字修饰符 | ul_local、ul_const、ul_inline 等 | [references/03-keyword-modifiers.md](references/03-keyword-modifiers.md) |
| 4. 注释规范 | Doxygen 风格、函数/结构体注释 | [references/04-comment-conventions.md](references/04-comment-conventions.md) |
| 5. 代码格式规范 | 缩进、行长、大括号、空格 | [references/05-code-format.md](references/05-code-format.md) |
| 6. 头文件保护 | #ifndef / #define / #endif 格式 | [references/06-header-guards.md](references/06-header-guards.md) |
| 7. 错误处理规范 | 错误码、返回值约定、断言 | [references/07-error-handling.md](references/07-error-handling.md) |
| 8. 集中的函数退出路径（goto 使用） | goto 使用模式与标签命名 | [references/08-goto-usage.md](references/08-goto-usage.md) |
| 9. Typedef 使用规范 | typedef 允许/禁止的情形 | [references/09-typedef-usage.md](references/09-typedef-usage.md) |
| 10. 数据结构设计 | 不透明指针、链表、引用计数 | [references/10-data-structure-design.md](references/10-data-structure-design.md) |
| 11. 函数设计规范 | 函数长度、内联、返回值 | [references/11-function-design.md](references/11-function-design.md) |
| 12. 布尔类型使用 | bool 使用规则与优化 | [references/12-boolean-type-usage.md](references/12-boolean-type-usage.md) |
| 13. 内存管理约定 | 静态分配、动态分配 | [references/13-memory-management.md](references/13-memory-management.md) |
| 14. 条件编译规范 | #ifdef 替代方案、IS_ENABLED | [references/14-conditional-compilation.md](references/14-conditional-compilation.md) |
| 15. 特殊宏定义 | 段属性、分支预测、废弃警告 | [references/15-special-macros.md](references/15-special-macros.md) |
| 16. 打印内核消息 | printk、dev_err、pr_debug | [references/16-printing-kernel-messages.md](references/16-printing-kernel-messages.md) |
| 17. 代码组织原则 | 目录结构、分层架构、设备树 | [references/17-code-organization.md](references/17-code-organization.md) |
| A. 附录：快速参考表 | 命名/修饰符/注释/错误码要点速查 | [references/18-appendix.md](references/18-appendix.md) |

---

## 参考资料

- [Linux Kernel Coding Style](https://www.kernel.org/doc/html/latest/process/coding-style.html)
- zhuqinsheng Embedded Framework Documentation
- Doxygen Manual: https://www.doxygen.nl/manual/
- MISRA C Guidelines (参考)

---

## 修订历史

| 版本 | 日期 | 作者 | 说明 |
|------|------|------|------|
| 0.1 | 2026-05-05 | zhuqinsheng | 初始版本 |

---

**© 2026-present zhuqinsheng. All rights reserved.**
