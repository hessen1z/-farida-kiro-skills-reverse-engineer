# Reverse Engineering Cheatsheet

> Quick reference. Memorize the patterns. Master the keystrokes.

---

## x64 Registers Quick Reference

```
RAX  - return value, accumulator
RBX  - callee-saved general purpose
RCX  - arg1 / this pointer
RDX  - arg2
RSI  - callee-saved general purpose
RDI  - callee-saved general purpose
RBP  - frame pointer (optional in MSVC /O2)
RSP  - stack pointer (always points to return address on function entry)
R8   - arg3
R9   - arg4
R10  - volatile scratch
R11  - volatile scratch
R12  - callee-saved
R13  - callee-saved
R14  - callee-saved
R15  - callee-saved

XMM0-XMM3  - float args 1-4
XMM0       - float return value
XMM6-XMM15 - callee-saved float registers
```

---

## Common ASM Patterns

### Function Prologue Patterns (MSVC x64)

```asm
; Minimal (leaf function, no locals, no calls):
; (no prologue at all)

; Standard with shadow space:
sub  rsp, 28h         ; 32 bytes shadow + 8 for alignment

; With saved registers:
sub  rsp, 48h
mov  [rsp+20h], rbx
mov  [rsp+28h], rsi
mov  [rsp+30h], rdi

; With frame pointer:
push rbp
sub  rsp, 30h
lea  rbp, [rsp+20h]
```

### Virtual Call Pattern

```asm
; obj->method()   where obj is in RCX
mov  rax, [rcx]        ; load vptr
call qword ptr [rax]   ; slot 0

mov  rax, [rcx]
call qword ptr [rax+8] ; slot 1

mov  rax, [rcx]
call qword ptr [rax+N*8] ; slot N
```

### Object Construction Pattern

```asm
; new MyClass()
; Step 1: allocate
mov  ecx, SIZE_OF_OBJECT
call operator_new              ; returns ptr in rax
; Step 2: construct
mov  rcx, rax                  ; rcx = this
call MyClass__constructor      ; writes vptr, initializes fields
```

### Null Check Pattern

```asm
; if (ptr == nullptr) return;
test rcx, rcx
jz   short exit_label

; if (ptr != nullptr) { ... }
test rax, rax
jnz  not_null_branch
```

### Bounds Check Pattern

```asm
; if (index >= count) throw/exit
cmp  rax, rdx          ; compare index to count
jae  out_of_bounds     ; JAE = unsigned >=
```

### Struct Member Access

```asm
; obj->field at offset 0x18
mov  eax, dword ptr [rcx+18h]

; obj->nested->field
mov  rax, [rcx+10h]    ; load nested* from offset 0x10
mov  eax, [rax+24h]    ; load field from offset 0x24
```

### String Length (optimized)

```asm
; strlen-like: scan for null byte
xor  eax, eax
mov  rcx, string_ptr
repne scasb            ; scan while byte != al (0)
not  rcx               ; negate
lea  eax, [rcx-1]      ; subtract for null byte
```

### Array Indexed Access

```asm
; array[index] where elements are 8 bytes
mov  rax, [base + rcx*8]

; array[index] where elements are 4 bytes
mov  eax, [base + rcx*4]

; array[index] with variable stride
imul rcx, stride
add  rcx, base
mov  rax, [rcx]
```

---

## PE Structure Quick Reference

```
File start (offset 0)
  +0x00  IMAGE_DOS_HEADER
    .e_magic    = 4D 5A ("MZ")
    .e_lfanew   = offset to NT headers
  [DOS stub: mostly padding]

At e_lfanew offset:
  IMAGE_NT_HEADERS64
    +0x00  Signature = 50 45 00 00 ("PE\0\0")
    +0x04  IMAGE_FILE_HEADER
      .Machine         = 86 64 (x64) or 4C 01 (x86)
      .NumberOfSections
      .TimeDateStamp
      .SizeOfOptionalHeader
      .Characteristics
    +0x18  IMAGE_OPTIONAL_HEADER64
      .Magic           = 0B 02 (PE32+)
      .AddressOfEntryPoint  (RVA)
      .ImageBase            (usually 0x140000000 for x64 EXE)
      .SectionAlignment     (usually 0x1000)
      .FileAlignment        (usually 0x200)
      .SizeOfImage
      .DataDirectory[16]
        [0] = Export Table
        [1] = Import Table
        [2] = Resource
        [3] = Exception (.pdata)
        [5] = Base Relocation
        [6] = Debug
        [9] = TLS
        [12]= IAT

Section Headers (immediately after Optional Header):
  Each is 40 bytes
  .Name            (8 bytes, null-padded)
  .VirtualSize
  .VirtualAddress  (RVA in memory)
  .SizeOfRawData
  .PointerToRawData (file offset)
  .Characteristics
    0x20000000 = CODE
    0x40000000 = INITIALIZED_DATA
    0x80000000 = UNINITIALIZED_DATA
    0x20000000 = executable
    0x40000000 = readable
    0x80000000 = writable
    0xE0000020 = .text: CODE | READ | EXECUTE
    0xC0000040 = .rdata: INITIALIZED_DATA | READ
    0xC0000040 = .data: INITIALIZED_DATA | READ | WRITE (0xC0000040 | 0x80000000)
```

### Address Conversion Formula

```
RVA to File Offset:
  file_offset = RVA - section.VirtualAddress + section.PointerToRawData

File Offset to RVA:
  RVA = file_offset - section.PointerToRawData + section.VirtualAddress

VA to RVA:
  RVA = VA - ImageBase

RVA to VA:
  VA = RVA + ImageBase
```

---

## RTTI Structure Quick Reference (MSVC x64)

```
vtable layout:
  vtable[-1]  -> _RTTICompleteObjectLocator* (COL)
  vtable[0]   -> virtual function slot 0
  vtable[N]   -> virtual function slot N

COL (at offset from image base):
  +0x00  DWORD signature     (1 = x64)
  +0x04  DWORD offset        (object base to vtable owner, usually 0)
  +0x08  DWORD cdOffset
  +0x0C  INT   pTypeDescriptor   (RVA to TypeDescriptor)
  +0x10  INT   pClassDescriptor  (RVA to ClassHierarchyDescriptor)
  +0x14  INT   pSelf             (RVA to this COL -- self-referential)

TypeDescriptor (in .data):
  +0x00  QWORD pVFTable   (points to type_info's vtable)
  +0x08  QWORD spare      (0)
  +0x10  CHAR  name[]     (".?AVMyClass@@")

Mangled name patterns:
  .?AV  = class
  .?AU  = struct
  .?AW  = union
  @@    = end of scope

ClassHierarchyDescriptor:
  +0x00  DWORD signature    (0)
  +0x04  DWORD attributes   (bit0=MI, bit1=virtual inh.)
  +0x08  DWORD numBaseClasses
  +0x0C  INT   pBaseClassArray  (RVA to array of RVAs)
```

---

## x64dbg Keyboard Shortcuts

```
F2        - Toggle software breakpoint
F4        - Run to cursor
F7        - Step into
F8        - Step over
F9        - Run
Ctrl+F9   - Run until return (execute until ret)
F12       - Pause execution
Alt+M     - Memory map
Ctrl+G    - Go to address
X         - Cross references (on highlighted item)
;         - Comment
:         - Rename label

Breakpoints:
  Right-click address -> Breakpoint -> Hardware, Execute
  Right-click memory  -> Hardware Breakpoint -> Read/Write

Memory dump:
  Ctrl+G in dump pane -> enter address
  Right-click in dump -> Data type -> various
  Right-click in dump -> Follow in disassembler

Search:
  Ctrl+F  - Find pattern in current module
  Ctrl+B  - Find pattern in all memory
```

---

## IDA Pro Keyboard Shortcuts

```
G         - Jump to address
X         - Cross references
N         - Rename
Y         - Set type (function signature, variable type)
T         - Apply struct type to operand
K         - Stack variable
H         - Convert to hex
A         - Convert to ASCII string
D         - Convert to data
C         - Convert to code
U         - Undefine
P         - Create function
;         - Comment (regular)
Shift+;   - Repeatable comment (shows in callers)
/         - Comment (pseudocode)
Ctrl+F    - Find text
Alt+T     - Find text (in Names window)
Space     - Toggle graph / linear view
Esc       - Navigate back
Enter     - Follow jump/call
Ctrl+Enter- Open in new window
Tab       - Switch between decompiler and disassembly
Ctrl+Alt+B- Breakpoints list
```

---

## WinDbg Commands

```
# Execution
g           - go (run)
p           - step over
t           - step into
gu          - go up (run until return)
pa addr     - go to address
ta addr     - trace to address

# Breakpoints
bp addr     - software breakpoint
ba e1 addr  - hardware execute breakpoint (1 byte)
ba r4 addr  - hardware read/write breakpoint (4 bytes)
bl          - list breakpoints
bc *        - clear all breakpoints

# Memory
dd addr     - dump DWORDs
dq addr     - dump QWORDs
db addr     - dump bytes
da addr     - dump ASCII string
du addr     - dump Unicode string
dp addr     - dump pointers
dv          - display local variables

# Symbols
x module!pattern    - find symbol matching pattern
x ntdll!*Create*    - find all ntdll exports with "Create"
ln addr     - nearest symbol to address
.reload     - reload symbols

# Stack
k           - call stack
kb          - call stack with parameters
kp          - call stack with full params

# Modules
lm          - list modules
lmf m name  - find module by name

# Process
!peb        - dump PEB
!teb        - dump TEB
!heap -a    - analyze heaps
!handle     - list handles

# Analysis
!analyze -v - crash analysis (verbose)
.exr -1     - last exception record
.cxr addr   - set context to crash context record
```

---

## Pattern Signature Format Reference

```
IDA Hex-Rays YARA (for signature matching):
  48 89 5C 24 08   = literal bytes
  ??               = wildcard byte

x64dbg pattern:
  48 89 5C 24 08 ?? ?? ?? ??   (same format)

Common instruction encodings to wildcard:

CALL rel32:
  E8 ?? ?? ?? ??

JMP rel32:
  E9 ?? ?? ?? ??

JMP SHORT rel8:
  EB ??

LEA reg, [rip+disp32]:
  48 8D ?? ?? ?? ?? ??
  (REX prefix + 8D + ModRM + 4-byte displacement)

MOV reg, [rip+disp32]:
  48 8B ?? ?? ?? ?? ??

MOV rax, imm64:
  48 B8 ?? ?? ?? ?? ?? ?? ?? ??

CALL [rip+disp32] (indirect, through IAT):
  FF 15 ?? ?? ?? ??
```

---

## Memory Protection Constants

```
PAGE_NOACCESS          = 0x01
PAGE_READONLY          = 0x02
PAGE_READWRITE         = 0x04
PAGE_WRITECOPY         = 0x08
PAGE_EXECUTE           = 0x10
PAGE_EXECUTE_READ      = 0x20
PAGE_EXECUTE_READWRITE = 0x40
PAGE_EXECUTE_WRITECOPY = 0x80
PAGE_GUARD             = 0x100  (modifier)
PAGE_NOCACHE           = 0x200  (modifier)

State flags:
MEM_COMMIT   = 0x1000
MEM_RESERVE  = 0x2000
MEM_FREE     = 0x10000

Type flags:
MEM_IMAGE    = 0x1000000  (PE mapped)
MEM_MAPPED   = 0x40000    (file mapped)
MEM_PRIVATE  = 0x20000    (anonymous / private)
```

---

## PEB / TEB Key Offsets (x64)

```
PEB (Process Environment Block):
  +0x000  BYTE   InheritedAddressSpace
  +0x001  BYTE   ReadImageFileExecOptions
  +0x002  BYTE   BeingDebugged          <- IsDebuggerPresent reads this
  +0x003  BYTE   BitField
  +0x008  PVOID  Mutant
  +0x010  PVOID  ImageBaseAddress
  +0x018  PPEB_LDR_DATA Ldr             <- module list
  +0x020  PRTL_USER_PROCESS_PARAMETERS ProcessParameters
  +0x058  PVOID  Reserved4[3]
  +0x068  ULONG  NtGlobalFlag           <- debug heap flags (x86)
  +0x0BC  ULONG  NtGlobalFlag           <- debug heap flags (x64)
  +0x0B0  ULONGLONG HeapBase            <- first heap address area

TEB (Thread Environment Block):
  +0x000  NT_TIB  NtTib
    +0x000  PVOID ExceptionList  (x86 SEH chain)
    +0x008  PVOID StackBase
    +0x010  PVOID StackLimit
  +0x030  PVOID  Self             <- TEB self-pointer (GS:[0x30])
  +0x040  PVOID  EnvironmentPointer
  +0x048  CLIENT_ID ClientId
    +0x048  PVOID UniqueProcess
    +0x050  PVOID UniqueThread
  +0x060  PVOID  ActiveRpcHandle
  +0x100  PVOID  TlsSlots[64]
  +0x1480 PVOID  TlsExpansionSlots

Access in assembly:
  gs:[0x30]  -> TEB.Self (pointer to TEB itself)
  gs:[0x60]  -> TEB.ProcessEnvironmentBlock (pointer to PEB)
  gs:[0x48]  -> TEB.ClientId.UniqueProcess (current process ID)
  gs:[0x50]  -> TEB.ClientId.UniqueThread  (current thread ID)
```

---

## Crypto Magic Constants

```
MD5:
  Init: A=0x67452301  B=0xEFCDAB89  C=0x98BADCFE  D=0x10325476

SHA-1:
  K[0..19]  = 0x5A827999
  K[20..39] = 0x6ED9EBA1
  K[40..59] = 0x8F1BBCDC
  K[60..79] = 0xCA62C1D6
  H0=0x67452301 H1=0xEFCDAB89 H2=0x98BADCFE H3=0x10325476 H4=0xC3D2E1F0

SHA-256:
  H0=0x6A09E667  H1=0xBB67AE85  H2=0x3C6EF372  H3=0xA54FF53A
  K[0]=0x428A2F98  K[1]=0x71374491  K[2]=0xB5C0FBCF

AES S-Box first bytes:
  63 7C 77 7B F2 6B 6F C5 30 01 67 2B FE D7 AB 76

RC4: No constants; state = 256-byte array initialized 0..255, then KSA loop

ChaCha20 constant ("expand 32-byte k"):
  65 78 70 61 6E 64 20 33 32 2D 62 79 74 65 20 6B
  (as DWORDs: 0x61707865 0x3320646E 0x79622D32 0x6B206574)

CRC32 polynomial: 0xEDB88320 (reversed)
```

---

## Common Anti-Debug Checks and Bypasses

```
Check                        Location          Patch/Bypass
---------------------------------------------------------------------------
IsDebuggerPresent            PEB+0x002         patch byte to 0
NtGlobalFlag check           PEB+0x0BC (x64)   patch DWORD to 0
Heap ForceFlags              Heap+0x74 (x64)   patch DWORD to 0
Heap Flags                   Heap+0x70 (x64)   AND out debug bits
NtQueryInformationProcess    ProcessDebugPort  hook: return 0
  (class 7, 30, 31)
CheckRemoteDebuggerPresent   wraps NtQIP       same hook
Timing: RDTSC                code              don't single-step
Timing: GetTickCount         code              run at full speed
OutputDebugString            exception         ignore DBG_PRINTEXCEPTION_C
TLS callbacks                PE TLS dir        set x64dbg TLS pause
INT3 scan (self-check)       reads own .text   use hardware BPs only
DR register check            GetThreadContext  ScyllaHide patch
SetUnhandledExceptionFilter  exception flow    let ScyllaHide handle
```

---

## MSVC DLL Characteristics Flags

```
IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA  = 0x0020  (64-bit ASLR)
IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE     = 0x0040  (ASLR enabled)
IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY  = 0x0080  (signature check)
IMAGE_DLLCHARACTERISTICS_NX_COMPAT        = 0x0100  (DEP enabled)
IMAGE_DLLCHARACTERISTICS_NO_ISOLATION     = 0x0200
IMAGE_DLLCHARACTERISTICS_NO_SEH           = 0x0400  (no SEH)
IMAGE_DLLCHARACTERISTICS_NO_BIND          = 0x0800
IMAGE_DLLCHARACTERISTICS_APPCONTAINER     = 0x1000
IMAGE_DLLCHARACTERISTICS_WDM_DRIVER       = 0x2000
IMAGE_DLLCHARACTERISTICS_GUARD_CF         = 0x4000  (CFG enabled)
IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE = 0x8000
```

---

## Vtable Mangled Name Patterns (MSVC)

```
Vtable symbol:   ??_7ClassName@@6B@
                 ??_7ClassName@Namespace@@6B@

RTTI COL symbol: ??_R4ClassName@@6B@
TypeDescriptor:  ??_R0?AVClassName@@@8

Demangle with:
  undname.exe "??_7MyClass@@6B@"    -> "const MyClass::`vftable'"
  WinAPI: UnDecorateSymbolName()
  IDA: Edit -> Demangle Name (Ctrl+Shift+D)
```

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

