<p align="right">
  <a href="README.md">English</a> | <a href="README.zh-CN.md">中文</a>
</p>

# embedded-c-style

A Claude Code skill defining embedded C coding conventions based on the Linux Kernel Coding Style.

When installed, Claude Code will follow these conventions automatically when writing or reviewing C code for embedded systems.

## Contents

| # | Topic | File |
|---|-------|------|
| 1 | File Header | [references/01-file-header.md](references/01-file-header.md) |
| 2 | Naming Conventions | [references/02-naming-conventions.md](references/02-naming-conventions.md) |
| 3 | Keyword Modifiers | [references/03-keyword-modifiers.md](references/03-keyword-modifiers.md) |
| 4 | Comment Conventions | [references/04-comment-conventions.md](references/04-comment-conventions.md) |
| 5 | Code Format | [references/05-code-format.md](references/05-code-format.md) |
| 6 | Header Guards | [references/06-header-guards.md](references/06-header-guards.md) |
| 7 | Error Handling | [references/07-error-handling.md](references/07-error-handling.md) |
| 8 | Goto Usage | [references/08-goto-usage.md](references/08-goto-usage.md) |
| 9 | Typedef Usage | [references/09-typedef-usage.md](references/09-typedef-usage.md) |
| 10 | Data Structure Design | [references/10-data-structure-design.md](references/10-data-structure-design.md) |
| 11 | Function Design | [references/11-function-design.md](references/11-function-design.md) |
| 12 | Boolean Type Usage | [references/12-boolean-type-usage.md](references/12-boolean-type-usage.md) |
| 13 | Memory Management | [references/13-memory-management.md](references/13-memory-management.md) |
| 14 | Conditional Compilation | [references/14-conditional-compilation.md](references/14-conditional-compilation.md) |
| 15 | Special Macros | [references/15-special-macros.md](references/15-special-macros.md) |
| 16 | Printing Kernel Messages | [references/16-printing-kernel-messages.md](references/16-printing-kernel-messages.md) |
| 17 | Code Organization | [references/17-code-organization.md](references/17-code-organization.md) |
| A | Appendix | [references/18-appendix.md](references/18-appendix.md) |

## Usage

This repository is designed as a Claude Code skill. Place it in your skills directory:

```
# Global (all projects)
~/.claude/skills/embedded-c-style/

# Project-level (single project)
<project-root>/.claude/skills/embedded-c-style/
```

Claude Code will automatically load the rules when the skill matches your task.

## File Structure

```
embedded-c-style/
├── SKILL.md            # Skill entry point (frontmatter + index)
├── references/         # Detailed chapters
│   ├── 01-file-header.md
│   └── ...
└── LICENSE             # MIT
```

## License

MIT
