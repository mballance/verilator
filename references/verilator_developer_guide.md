# Verilator Developer Guide and Best Practices

**Purpose:** This document provides a comprehensive reference for developers adding significant code to Verilator, ensuring adherence to current practices and best practices.

**Date Created:** 2026-02-07

---

## Table of Contents

1. [Overview](#overview)
2. [Code Architecture](#code-architecture)
3. [Coding Conventions](#coding-conventions)
4. [AST and Visitor Pattern](#ast-and-visitor-pattern)
5. [Creating New Passes](#creating-new-passes)
6. [Testing](#testing)
7. [Debugging](#debugging)
8. [Build System](#build-system)
9. [Common Patterns](#common-patterns)
10. [Code Review Checklist](#code-review-checklist)

---

## Overview

### Verilator Architecture

Verilator is a cycle-accurate HDL compiler that transforms Verilog/SystemVerilog into optimized C++ or SystemC code. The compilation flow consists of:

1. **Parsing** - Flex/Bison lexer and parser create AST from HDL source
2. **Linking** - Connect references to definitions, resolve parameters
3. **Elaboration** - Expand hierarchy, optimize
4. **Pseudo-flattening** - Create scopes for each module instance
5. **Optimization** - Multiple passes refine and optimize AST
6. **Ordering** - Create evaluation order for combinational logic
7. **Code Generation** - Emit optimized C++/SystemC

### Key Source Files

- **src/Verilator.cpp** - Main entry point, `process()` function orchestrates passes
- **src/V3Ast*.h/cpp** - AST node definitions
- **src/V3*.h/cpp** - Individual compiler passes (e.g., V3Width, V3Gate, V3Order)
- **src/verilog.y** - Bison grammar for parsing
- **src/verilog.l** - Flex lexer specification
- **test_regress/t/** - Regression test cases

### Documentation References

- **docs/internals.rst** - Comprehensive internal documentation (2655 lines)
- **docs/CONTRIBUTING.rst** - Contribution guidelines
- **docs/guide/** - User documentation

---

## Code Architecture

### Core Classes

#### `AstNode` - Abstract Syntax Tree Base Class

All AST nodes derive from `AstNode`. Key properties:

- **Type Hierarchy Rules:**
  - All non-final subclasses MUST be abstract and named `AstNode*`
  - Only leaf classes can be concrete (not `AstNode*` prefixed)
  - `astgen` script enforces this structure

- **Child Pointers:**
  - Up to 4 children via `op1p()` through `op4p()` methods
  - Abstracted by specific accessor names (e.g., `thensp()`, `elsesp()`)
  - Use `@astgen` directives to define child nodes

- **Navigation:**
  - `back()` - Previous sibling in statement list
  - `next()` - Next sibling
  - `nextp()` - Next item in list (for list-type operands)

- **User Attributes:**
  - 5 user fields per node: `user1()` through `user4()` (integer or pointer), plus `userp()`
  - Must be cleared before use: `AstNode::user#ClearTree()`
  - Document usage at top of each visitor class

**Example AstNode Child Definition:**
```cpp
// @astgen op1 := lhsp : AstNodeExpr        // Required, single node
// @astgen op2 := rhsp : Optional[AstNodeExpr]  // Optional single node
// @astgen op3 := stmtsp : List[AstNodeStmt]    // List of nodes
// @astgen alias op1 := condp                   // Alias for existing operand

class AstIf final : public AstNodeIf {
    // ... implementation
    ASTGEN_MEMBERS_AstIf;  // MUST include this macro
};
```

#### `VNVisitor` - Base Visitor Class

All compiler passes implement visitors derived from `VNVisitor`:

```cpp
class MyPassVisitor final : public VNVisitor {
    // NODE STATE - Document user() field usage
    //  AstNode::user1()  -> int. Count of references
    //  AstNode::user2p() -> AstNode*. Pointer to definition
    const VNUser1InUse m_inuser1;  // Mark user1 as in-use
    const VNUser2InUse m_inuser2;

    // STATE - Member variables for passing context
    AstNodeModule* m_modp = nullptr;  // Current module
    AstNodeFTask* m_ftaskp = nullptr;  // Current function/task

    // METHODS
    void visit(AstModule* nodep) override {
        VL_RESTORER(m_modp);  // Save/restore for nested contexts
        m_modp = nodep;
        iterateChildren(nodep);
    }

    void visit(AstVar* nodep) override {
        // Access current context via m_modp
        // Process variable...
    }

    void visit(AstNode* nodep) override {
        // Default handler - iterate children
        iterateChildren(nodep);
    }

public:
    MyPassVisitor(AstNetlist* nodep) {
        iterate(nodep);
    }
};
```

#### `V3Graph` - Graph Algorithms

Used for ordering, scheduling, and dependency analysis:

```cpp
class V3Graph;           // Base graph class
class V3GraphVertex;     // Vertex base
class V3GraphEdge;       // Edge base
class V3GraphAlg;        // Algorithm base

// Iterating edges:
for (V3GraphEdge* edgep = vertexp->inBeginp();
     edgep;
     edgep = edgep->inNextp()) {
    // Process incoming edge
}
```

---

## Coding Conventions

### Language Standards

- **Required:** C++14
- **Compatible:** C++17/C++20 (code maintained to build successfully)
- **Avoid:** C++20+ features unless essential

### Naming Conventions

```cpp
// mixedCapsSymbols (NOT underlined_symbols)
class MyClassName { };
void myFunctionName() { }

// Pointer suffix "p"
AstNode* nodep;          // Single pointer
AstNode** nodepp;        // Pointer to pointer

// Member variable prefix "m_"
class MyClass {
    int m_count;         // Member variable
    bool m_enabled;
};

// Iterator variables
for (AstNode* nodep = ...; nodep; nodep = nodep->nextp()) { }
```

### Indentation and Style

**C++ Code:**
- 4 spaces per level, NO tabs
- 2 spaces between code and inline comments
- 1 space after `if`/`for`/`switch`/`while`
- NO space before semicolons
- NO space between function name and `(`
- Automatically formatted with `make format` (clang-format 18)

```cpp
// Good
if (condition) {
    doSomething();  // Comment
    value = compute(param1, param2);
}

// Bad
if(condition){
    doSomething() ;
    value=compute( param1 , param2 ) ;
}
```

**Verilog Code:**
- 2 spaces per level, NO tabs
- `begin` on same line as statement
- `end` on separate line, same indent as starting statement

```verilog
always @(posedge clk) begin
  if (enable) begin
    data <= next_data;
  end
end
```

### Comments

```cpp
class MyClass {
    int m_counter;        // REQUIRED: Comment every member variable
    bool m_initialized;   // Tracks initialization state

    /// Triple-slash for user-facing API (include directory)
    void publicFunction();

    // Double-slash for internal code
    void internalFunction();
};
```

### Header Guards

```cpp
#ifndef VERILATOR_V3MYPASS_H_
#define VERILATOR_V3MYPASS_H_

// ... content ...

#endif  // Guard
```

### File Headers

```cpp
// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: [Brief description]
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2003-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************
```

---

## AST and Visitor Pattern

### Type Checking and Casting

```cpp
// VN_IS - Check node type (like instanceof)
if (VN_IS(nodep, If)) {
    // nodep is AstIf or derived
}

// VN_CAST - Dynamic cast (returns nullptr if wrong type)
if (AstIf* ifp = VN_CAST(nodep, If)) {
    // Safe to use ifp
}

// VN_AS - Assert-cast (asserts type in debug, undefined if wrong)
AstIf* ifp = VN_AS(nodep, If);  // Use when type is known

// VN_DBG_AS - Assert-cast in debug only (faster in release)
AstIf* ifp = VN_DBG_AS(nodep, If);  // Use in child getters
```

### Visitor Pattern Implementation

**Method Resolution Order:**
```cpp
void visit(AstIf* nodep)        // Most specific
void visit(AstNodeIf* nodep)
void visit(AstNodeStmt* nodep)
void visit(AstNode* nodep)      // Most general (fallback)
```

**Iteration Patterns:**

```cpp
// Iterate children (all 4 operands)
iterateChildren(nodep);

// Iterate specific operand
iterate(nodep->lhsp());

// Iterate list with edits
for (AstNode* itemp = listp; itemp; ) {
    AstNode* nextp = itemp->nextp();  // Save before potential deletion
    iterate(itemp);
    itemp = nextp;
}

// Accept with potential node replacement
AstNode* newp = nodep->acceptSubtreeReturnEdits(visitor);
```

### Data Passing Between Visitors

**1. Member Variables (Parent  Child):**
```cpp
class MyVisitor final : public VNVisitor {
    AstNodeModule* m_modp = nullptr;

    void visit(AstModule* nodep) override {
        VL_RESTORER(m_modp);  // Auto save/restore
        m_modp = nodep;
        iterateChildren(nodep);  // Children see m_modp set
    }
};
```

**2. User Attributes (Child  Parent or Annotations):**
```cpp
// At top of visitor - document usage!
// NODE STATE
//  AstNode::user1()  -> int. Reference count
//  AstNode::user2p() -> AstNode*. Pointer to definition
const VNUser1InUse m_inuser1;

// Usage
AstNode::user1ClearTree();  // Clear before use
nodep->user1(42);           // Set value
int count = nodep->user1(); // Get value
```

**3. Return Values (Limited use):**
```cpp
// Some helpers return values directly
AstNode* newp = V3Width::widthSelNoIterEdit(nodep);
```

### Modifying the AST

```cpp
// Unlink node from tree
VNRelinker relinkHandle;
nodep->unlinkFrBack(&relinkHandle);

// Replace with new node
AstNode* newp = new AstNewNode(...);
relinkHandle.relink(newp);

// Delete node
VL_DO_DANGLING(nodep->deleteTree(), nodep);

// Insert before/after
nodep->addNextHere(newNode);
nodep->addHereThisAsNext(newNode);
```

---

## Creating New Passes

### Pass Template

**Header (V3MyPass.h):**
```cpp
// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: [Description of pass]
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// [License header as shown above]
//
//*************************************************************************

#ifndef VERILATOR_V3MYPASS_H_
#define VERILATOR_V3MYPASS_H_

#include "config_build.h"
#include "verilatedos.h"

class AstNetlist;

//============================================================================

class V3MyPass final {
public:
    static void mypass(AstNetlist* nodep) VL_MT_DISABLED;
};

#endif  // Guard
```

**Implementation (V3MyPass.cpp):**
```cpp
// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: [Description]
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// [License header]
//
//*************************************************************************
// V3MyPass's Transformations:
//
// At module level:
//      [Document transformations performed]
//
//*************************************************************************

#include "V3PchAstNoMT.h"  // VL_MT_DISABLED_CODE_UNIT

#include "V3MyPass.h"

VL_DEFINE_DEBUG_FUNCTIONS;

//######################################################################
// MyPass state, as a visitor of each AstNode

class MyPassVisitor final : public VNVisitor {
    // NODE STATE
    //  AstNode::user1()  -> [document usage]
    const VNUser1InUse m_inuser1;

    // STATE
    AstNodeModule* m_modp = nullptr;

    // METHODS

    // Visitors
    void visit(AstModule* nodep) override {
        UINFO(4, " MOD   " << nodep);
        VL_RESTORER(m_modp);
        m_modp = nodep;
        iterateChildren(nodep);
    }

    void visit(AstNode* nodep) override {
        iterateChildren(nodep);
    }

public:
    // CONSTRUCTORS
    explicit MyPassVisitor(AstNetlist* nodep) {
        iterate(nodep);
    }
    ~MyPassVisitor() override = default;
};

//######################################################################
// MyPass class functions

void V3MyPass::mypass(AstNetlist* nodep) {
    UINFO(2, __FUNCTION__ << ": " << endl);
    {
        MyPassVisitor visitor{nodep};
    }
    V3Global::dumpCheckGlobalTree("mypass", 0, dumpTree() >= 3);
}
```

### Integrating a New Pass

1. **Add to src/Makefile_obj.in:**
   ```makefile
   VM_CLASSES += V3MyPass
   ```

2. **Call from Verilator.cpp `process()`:**
   ```cpp
   V3MyPass::mypass(netlistp);
   ```

3. **Reconfigure:**
   ```bash
   cd $VERILATOR_ROOT
   ./configure
   make -j$(nproc)
   ```

---

## Testing

### Test File Structure

**Python Driver (test_regress/t/t_example.py):**
```python
#!/usr/bin/env python3
# DESCRIPTION: Verilator: Verilog Test driver/expect definition
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of either the GNU Lesser General Public License Version 3
# or the Perl Artistic License Version 2.0.
# SPDX-FileCopyrightText: 2024 Wilson Snyder
# SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0

import vltest_bootstrap

# Specify scenarios (simulator, vlt, vltmt)
test.scenarios('simulator')

# Compilation
test.compile(
    v_flags2=["--trace", "--coverage"],
    verilator_flags2=["--debug"]
)

# Execution
test.execute()

# Checks
if test.vlt_all:
    test.file_grep(test.trace_filename, r"expected_signal")
    test.file_grep("obj_dir/output.txt", r"Expected.*pattern")

test.passes()
```

**Verilog Test (test_regress/t/t_example.v):**
```verilog
// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2024 Author Name
// SPDX-License-Identifier: CC0-1.0

module t(clk);
  input clk;

  integer cyc; initial cyc = 0;

  always @(posedge clk) begin
    cyc <= cyc + 1;

    if (cyc == 10) begin
      $write("*-* All Finished *-*\n");
      $finish;
    end
  end
endmodule
```

### Test for Expected Failures

**Bad test naming:** Use `_bad` suffix
```python
# t_example_bad.py
test.compile(fails=1)  # Expect compilation to fail
# OR
test.execute(fails=1)  # Expect execution to fail
```

### Running Tests

```bash
# Single test
test_regress/t/t_example.py

# With debugging
test_regress/t/t_example.py --debug

# Parallel regression
make test -j$(nproc)

# Specific tests
cd test_regress
./driver.py t/t_example*.py -j 8
```

### Test Best Practices

1. **Minimal test cases** - Test one feature per test
2. **Self-checking** - Tests should verify their own output
3. **CC0 license** - Tests are public domain unless otherwise specified
4. **Documentation** - Comment the purpose of each test
5. **Reproducible** - Should pass consistently

---

## Debugging

### Debug Macros

```cpp
// Information messages (level-based)
UINFO(2, "Starting pass");           // Level 2 message
UINFO(4, " Processing " << nodep);   // Level 4 (more detailed)

// Assertions
UASSERT(condition, "Message");
UASSERT_OBJ(condition, nodep, "Message with node context");

// Fatal errors (should never happen)
VL_UNREACHABLE;
nodep->v3fatalSrc("Internal error message");

// Conditional code in debug builds
#ifdef VL_DEBUG
    // Debug-only code
#endif
```

### Debug Levels

- `--debug` - Enable level 3 and below globally
- `--debugi <level>` - Set global debug level
- `--debugi-<srcfile> <level>` - Set per-file level
  - Example: `--debug --debugi 5 --debugi-V3Width 9`

### Debug Output Files

**Created with --debug:**

1. **{prefix}__inputs.vpp** - All input files preprocessed
   ```bash
   verilator -f prefix__inputs.vpp prefix__inputs.vpp
   ```

2. **{prefix}*.tree** - AST dumps in human-readable format
   - Created after each major pass
   - Shows AST structure with node types, pointers, attributes

3. **{prefix}*.tree.json** - AST in JSON format
   - Machine-readable
   - Can be analyzed with external tools

4. **{prefix}*.dot** - GraphViz dot files
   - Graph visualizations
   - Printed with command to render:
     ```bash
     dot -Tps -o output.ps obj_dir/Vtop_foo.dot
     ```

### GDB Debugging

**Start test under GDB:**
```bash
test_regress/t/t_example.py --debug --gdb
```

**GDB Utilities (src/.gdbinit, src/.gdbinit.py):**
```gdb
# Print node
pn nodep

# Print node tree
pnt nodep

# JSON AST dump
jstash nodep
jtree nodep
jtree $1

# Break on edit number
watch AstNode::s_editCntGbl=1234

# Track specific node changes
watch m_editCount
```

### Common Debug Workflows

**1. Find where node is modified:**
```bash
# Run with --debug, find <e#num> in .tree file
# In GDB:
watch AstNode::s_editCntGbl==<num>
```

**2. Dump AST at specific pass:**
```cpp
V3Global::dumpCheckGlobalTree("mypass", 0, dumpTree() >= 3);
```

**3. Enable tracing for specific module:**
```bash
verilator --trace --trace-depth 99 top.v
```

---

## Build System

### Source Organization

```
verilator/
 src/                  # Main source
    V3*.cpp/h        # Compiler passes
    Verilator.cpp    # Main entry point
    verilog.y        # Parser grammar
    verilog.l        # Lexer
    astgen           # AST code generator
 include/             # Runtime library headers
 test_regress/        # Regression tests
    t/              # Test cases
    driver.py       # Test driver
 docs/               # Documentation
 examples/           # Example designs
 ci/                 # CI configuration
```

### Build Process

```bash
# Configure
./configure --enable-longtests --enable-ccwarn

# Build
make -j$(nproc)

# Install
make install

# Format code
make format

# Run tests
make test
```

### Generated Files

- **astgen** generates:
  - `V3Ast__gen_*.cpp/h` - AST node members
  - `V3*__gen.cpp` - Preprocessed source files

- **Build directories:**
  - `obj_opt/` - Optimized build
  - `obj_dbg/` - Debug build
  - `obj_dir/` - Test outputs

---

## Common Patterns

### Error and Warning Messages

```cpp
// Error (stops compilation)
nodep->v3error("Message explaining the issue");

// Warning (allows compilation to continue)
nodep->v3warn(WARNINGTYPE, "Message explaining the issue");

// Information
nodep->v3info("Informational message");

// With file/line context
fileline()->v3error("Error with location");
```

### Tree Modifications

**Pattern 1: Replace Node**
```cpp
VNRelinker handle;
oldp->unlinkFrBack(&handle);
AstNode* newp = new AstNewNode(...);
handle.relink(newp);
VL_DO_DANGLING(oldp->deleteTree(), oldp);
```

**Pattern 2: Insert Statement**
```cpp
// Insert before
nodep->addHereThisAsNext(new AstStmt(...));

// Insert after
nodep->addNextHere(new AstStmt(...));
```

**Pattern 3: Replace and Keep Old**
```cpp
// Keep oldp for reference but remove from tree
VNRelinker handle;
oldp->unlinkFrBack(&handle);
AstNode* newp = makeReplacement(oldp);  // Uses oldp
handle.relink(newp);
// Don't delete oldp yet, it's referenced
```

### Safe Iteration During Modification

```cpp
// List iteration with edits
for (AstNode* nodep = listp; nodep; ) {
    AstNode* const nextp = nodep->nextp();  // Save next

    // May delete/modify nodep
    processNode(nodep);

    nodep = nextp;  // Continue with saved pointer
}
```

### Creating Temporary Variables

```cpp
// Create variable in module scope
AstVar* const varp = new AstVar{
    nodep->fileline(),
    VFlagChildDType{},  // Has child dtype
    "temp_var",
    VVarType::BLOCKTEMP  // Temporary variable
};
varp->dtypep(nodep->dtypep());
m_modp->addStmtsp(varp);

// Reference the variable
AstVarRef* const refp = new AstVarRef{
    nodep->fileline(),
    varp,
    VAccess::WRITE  // or READ
};
```

### Width and Type Handling

```cpp
// Get/set width
int width = nodep->width();
nodep->dtypeChgWidth(newWidth, newWidthMin);

// Type from another node
newNodep->dtypeFrom(existingNodep);

// Create specific type
AstNodeDType* dtypep = new AstBasicDType{
    fl, VBasicDTypeKwd::UINT32
};
```

---

## Code Review Checklist

### Before Submitting

- [ ] **Code formatted** with `make format`
- [ ] **All tests pass** with `make test`
- [ ] **New test added** for new functionality
- [ ] **Documentation updated** (if user-visible change)
- [ ] **Commit message follows convention**:
  ```
  Add/Fix/Improve/Optimize <description> (#issue)
  ```
- [ ] **CONTRIBUTORS file updated** (first contribution)
- [ ] **No compiler warnings** with `--enable-ccwarn`

### Code Quality

- [ ] **Naming conventions** followed (mixedCaps, pointer suffix)
- [ ] **Member variables commented**
- [ ] **NODE STATE documented** in visitor classes
- [ ] **User fields cleared** before use (`AstNode::user#ClearTree()`)
- [ ] **No memory leaks** (nodes properly deleted)
- [ ] **Thread safety** considered (`VL_MT_DISABLED` annotations)
- [ ] **Error messages** clear and actionable

### AST Modifications

- [ ] **VNRelinker** used for safe unlinking
- [ ] **Pointers saved** before modifying lists
- [ ] **Dangling pointers** properly marked (`VL_DO_DANGLING`)
- [ ] **Type checking** uses `VN_IS/VN_CAST/VN_AS`
- [ ] **Children properly linked** (parent/child pointers correct)

### Testing

- [ ] **Test is minimal** and focused
- [ ] **Test is self-checking** (doesn't require manual verification)
- [ ] **Test has CC0 license** header
- [ ] **Failure tests** have `_bad` suffix and `fails=1`
- [ ] **Test documented** with description comment

### Performance

- [ ] **No unnecessary tree walks**
- [ ] **User fields** used instead of hash maps when possible
- [ ] **String operations** minimized
- [ ] **Graph algorithms** appropriate for problem

---

## Additional Resources

### Key Documentation

- **docs/internals.rst** - Comprehensive internal documentation
- **docs/CONTRIBUTING.rst** - Contribution guidelines
- **Verilator Manual** - User documentation at https://verilator.org/verilator_doc.html
- **Verilator Website** - https://verilator.org
- **Verilator Forum** - https://verilator.org/forum

### Source Code References

Study these passes as examples:
- **V3Clean.cpp** - Simple cleanup pass
- **V3Width.cpp** - Complex width resolution
- **V3Gate.cpp** - Graph-based optimization
- **V3Order.cpp** - Dependency ordering
- **V3Timing.cpp** - Coroutine/timing support

### Development Tools

- **clang-format 18** - C++ code formatting
- **yapf** - Python code formatting
- **gcov** - Code coverage analysis
- **gdb** - Debugging with custom scripts
- **GraphViz** - Visualizing AST and graphs
- **SystemC** - For SystemC output testing

### IEEE References

- **IEEE 1800-2023** - SystemVerilog Language Standard
- Verilator aims for close compliance with supported features

---

## Revision History

| Date       | Changes                                      |
|------------|----------------------------------------------|
| 2026-02-07 | Initial version - comprehensive developer guide |

---

## Notes

- This document based on Verilator source code and documentation as of 2026-02-07
- See docs/internals.rst for additional details on specific subsystems
- Coding standards are automatically enforced by CI/CD actions
- When in doubt, follow existing code patterns in similar passes
