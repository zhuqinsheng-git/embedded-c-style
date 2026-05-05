## 9. Typedef 使用规范

> **速览**: 仅5种情况可用 typedef（不透明对象、整数抽象、sparse类型检查、标准C99类型、用户空间安全类型）；否则直接用 `struct`/`union` 关键字

**Linux 内核强烈反对滥用 typedef**。

### 9.1 不要使用的情况

```c
// ❌ 错误：对结构体和指针使用 typedef
typedef struct virtual_container {
        int field1;
        int field2;
} vps_t;

vps_t a;  // 这是什么？不知道！

// ✅ 正确：直接使用结构体
struct virtual_container *a;  // 清楚知道 a 是什么
```

### 9.2 可以使用 typedef 的情况

**仅在以下 5 种情况下使用 typedef**：

1. **完全不透明的对象**（主动隐藏实现细节）
   ```c
   typedef struct pte_struct pte_t;  // 只能通过访问函数操作
   ```

2. **清晰的整数类型抽象**（消除 int/long 混淆）
   ```c
   typedef unsigned int myflags_t;  // 有明确原因时才使用
   ```
   **注意**：u8/u16/u32/u64 更符合类别 4

3. **使用 sparse 做类型检查时创建新类型**

4. **与标准 C99 类型相同**
   ```c
   // Linux 特有的等同于标准类型
   typedef __u8 u8;
   typedef __u16 u16;
   typedef __u32 u32;
   typedef __u64 u64;
   ```

5. **用户空间安全使用的类型**
   ```c
   // 在与用户空间共享的结构体中
   struct user_api {
           __u32 field1;
           __u64 field2;
   };
   ```

### 9.3 基本原则

> **如果指针或结构体成员可以被直接访问，就不应该是 typedef**
