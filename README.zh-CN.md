<p align="right">
  <a href="README.md">English</a> | <a href="README.zh-CN.md">中文</a>
</p>

# embedded-c-style

一个 Claude Code Skill，定义基于 Linux Kernel Coding Style 的嵌入式 C 语言编码规范。

安装后，Claude Code 在编写或审查嵌入式系统 C 代码时会自动遵循这些规范。

## 章节索引

| 章节 | 内容 | 文件 |
|------|------|------|
| 1 | 文件头规范 | [references/01-file-header.md](references/01-file-header.md) |
| 2 | 命名规范 | [references/02-naming-conventions.md](references/02-naming-conventions.md) |
| 3 | 关键字修饰符 | [references/03-keyword-modifiers.md](references/03-keyword-modifiers.md) |
| 4 | 注释规范 | [references/04-comment-conventions.md](references/04-comment-conventions.md) |
| 5 | 代码格式规范 | [references/05-code-format.md](references/05-code-format.md) |
| 6 | 头文件保护 | [references/06-header-guards.md](references/06-header-guards.md) |
| 7 | 错误处理规范 | [references/07-error-handling.md](references/07-error-handling.md) |
| 8 | 集中的函数退出路径（goto 使用） | [references/08-goto-usage.md](references/08-goto-usage.md) |
| 9 | Typedef 使用规范 | [references/09-typedef-usage.md](references/09-typedef-usage.md) |
| 10 | 数据结构设计 | [references/10-data-structure-design.md](references/10-data-structure-design.md) |
| 11 | 函数设计规范 | [references/11-function-design.md](references/11-function-design.md) |
| 12 | 布尔类型使用 | [references/12-boolean-type-usage.md](references/12-boolean-type-usage.md) |
| 13 | 内存管理约定 | [references/13-memory-management.md](references/13-memory-management.md) |
| 14 | 条件编译规范 | [references/14-conditional-compilation.md](references/14-conditional-compilation.md) |
| 15 | 特殊宏定义 | [references/15-special-macros.md](references/15-special-macros.md) |
| 16 | 打印内核消息 | [references/16-printing-kernel-messages.md](references/16-printing-kernel-messages.md) |
| 17 | 代码组织原则 | [references/17-code-organization.md](references/17-code-organization.md) |
| A | 附录：快速参考表 | [references/18-appendix.md](references/18-appendix.md) |

## 使用方法

本仓库是一个 Claude Code Skill。将其放入 skills 目录即可使用：

```
# 全局安装（所有项目生效）
~/.claude/skills/embedded-c-style/

# 项目级安装（仅当前项目）
<项目根目录>/.claude/skills/embedded-c-style/
```

当任务匹配时，Claude Code 会自动加载这些规范。

## 文件结构

```
embedded-c-style/
├── SKILL.md            # Skill 入口文件（frontmatter + 索引）
├── references/         # 详细章节
│   ├── 01-file-header.md
│   └── ...
└── LICENSE             # MIT
```

## 许可证

MIT
