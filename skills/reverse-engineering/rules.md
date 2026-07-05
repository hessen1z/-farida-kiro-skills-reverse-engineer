# Reverse Engineering — Operating Rules

> Strict operating rules for the Reverse Engineering Expert skill.
> These rules govern every analysis decision. Follow them without exception.

---

## Assembly & Decompilation

1. Always verify pseudocode against raw disassembly before drawing conclusions.
2. Never trust decompiler-assigned types without cross-checking the disassembly.
3. When decompiler and disassembly disagree, disassembly is correct.
4. Always read the actual MOV/LEA instructions when struct field types are unclear.
5. Distinguish between byte, word, dword, and qword accesses — they change meaning.
6. Never assume a `jmp` at function end is a loop — check if it is a tail call.
7. Verify tail calls by confirming the stack frame was cleaned before the jump.
8. Identify function boundaries before analyzing function internals.
9. Treat every indirect call (`call rax`, `call [rax+N]`) as unresolved until confirmed.
10. Always resolve indirect calls dynamically before finalizing static analysis.
11. Recognize compiler idioms: `xor eax, eax` = zero, `test rax, rax` = null check.
12. Identify loop patterns: counter in ECX/RCX, REPE/REPNE prefixes, conditional jump at bottom.
13. Never rename a function based on a single instruction or string reference.
14. A function called from only one place may be inlined in other builds — search for it.
15. Distinguish user code from compiler-generated code (CRT init, EH frames, RTTI glue).
16. Mark compiler-generated functions clearly — do not waste time analyzing them deeply.
17. Identify `__purecall` stubs in vtables — they mark abstract base classes.
18. Recognize COMDAT folding: multiple logical functions may share one address.
19. Always check for function padding (INT3, NOP, align bytes) between functions.
20. Never assume a sequence of bytes is code without verifying it is in an executable section.

## Memory & Addresses

21. Never hardcode virtual addresses — they change with ASLR every load.
22. Always work with RVAs relative to module base, not absolute VAs.
23. Always identify the module base before computing any address.
24. Compute RVA as: `RVA = VA - ImageBase`.
25. Compute file offset as: `FileOffset = RVA - SectionVA + SectionRawOffset`.
26. Never confuse file offsets with RVAs — sections align differently on disk vs memory.
27. Validate every pointer before dereferencing: check MEM_COMMIT, not PAGE_GUARD, readable.
28. Check for null pointers at every dereference level in a pointer chain.
29. Validate that intermediate pointers in a chain are non-zero before continuing.
30. Verify pointer chain stability across multiple restarts before using it in production.
31. Do not scan the entire virtual address space — restrict to MEM_COMMIT + executable regions.
32. When scanning cross-process, use VirtualQueryEx before ReadProcessMemory on each region.
33. Prefer scanning MEM_IMAGE regions when looking for code in a known module.
34. Always document the base address and version of the binary that offsets were found in.
35. Record offsets as RVAs, not VAs, in all documentation.
36. Always identify the module an address belongs to before analyzing it.
37. Distinguish between MEM_IMAGE (PE-mapped), MEM_PRIVATE (heap/stack), and MEM_MAPPED (file-backed).
38. Never assume a non-null pointer is valid — validate protection flags and commit state.
39. Check for PAGE_GUARD before reading any memory region.
40. When a pointer chain breaks after a game update, re-verify each level individually.

## PE Format

41. Always inspect the PE header before opening a binary in a disassembler.
42. Read the import table before analyzing any function — it reveals what the binary does.
43. Read the export table before assuming a DLL is opaque.
44. Check the debug directory for PDB path and symbol age before doing any analysis.
45. Inspect DLL Characteristics flags: ASLR, DEP, CFG, High-Entropy VA.
46. Check the TLS directory for callbacks that run before the entry point.
47. Always set debugger to pause at TLS callbacks, not just the entry point.
48. Check the exception directory (.pdata) for all registered function ranges.
49. Verify section entropy before doing any static analysis — high entropy means packed.
50. If section entropy > 7.0, assume packed/encrypted and unpack before analysis.
51. Check imports: only LoadLibrary + GetProcAddress with no others = manual IAT resolution.
52. Check for forwarded exports — they redirect to functions in other DLLs.
53. Identify ordinal-only imports and resolve them from the exporting DLL's export table.
54. Validate all RVAs in the PE header before dereferencing them in a parser.
55. Check the TimeDateStamp field — it may be zeroed/faked in protected binaries.
56. Identify the entry point section — entry in non-.text section suggests packing.
57. Check IMAGE_OPTIONAL_HEADER.Subsystem to determine if target is GUI, console, or driver.
58. Always check the CLR Runtime Header — if present, the binary is .NET managed code.
59. Check base relocation directory size — zero in a DLL that must rebase = missing relocations.
60. Verify SizeOfImage matches the actual mapped image before scanning.

## C++ Internals

61. Recover RTTI structures before attempting to reconstruct class hierarchies.
62. Always read vtable[-1] to find the Complete Object Locator (COL) before naming classes.
63. Verify COL signature (1 for x64, 0 for x86) before trusting RTTI data.
64. Verify COL.pSelf RVA resolves back to the COL itself — required for x64 COL validation.
65. Extract class names from TypeDescriptor.name (mangled, starts with `.?AV` or `.?AU`).
66. Demangle all MSVC names before using them — use UnDecorateSymbolName or undname.exe.
67. Recover constructors before inferring class field layouts.
68. The constructor initializes all fields — it is the primary source for struct layout.
69. Always map `[this + offset] = value` assignments in constructors to named struct fields.
70. Track vtable slot indices — slot 0 is the first virtual function after the destructor entries.
71. Identify MSVC virtual destructor pattern: two consecutive slots (scalar and vector delete).
72. Never assume vtable slot N is a specific function without verifying the function pointer.
73. For multiple inheritance, expect multiple vptrs in the object — one per base with virtuals.
74. Identify thunks in secondary vtables — they adjust `this` before jumping to the real method.
75. Recover the full class hierarchy from _RTTIClassHierarchyDescriptor before assuming inheritance.
76. Check _RTTIBaseClassDescriptor.PMD.pdisp — non-negative means virtual base inheritance.
77. Verify that inferred inheritance matches the vtable structure before committing to it.
78. Distinguish abstract classes (contain __purecall slots) from concrete classes.
79. Track all vtable addresses in a class hierarchy — derived classes have richer vtables.
80. When a vtable slot points outside .text or .rdata, investigate — it may be injected or corrupted.

## Dynamic Analysis

81. Always apply anti-debug bypasses before starting meaningful dynamic analysis.
82. Patch PEB.BeingDebugged (offset 0x002) to 0 immediately after the system breakpoint.
83. Patch PEB.NtGlobalFlag (offset 0x0BC on x64) to 0 to hide the debug heap.
84. Patch heap ForceFlags and Flags to clear debug heap indicators.
85. Use hardware breakpoints (DR0-DR3) for targets that check for INT3 (0xCC) in their code.
86. Never single-step through regions guarded by timing-based anti-debug — use run-to-cursor.
87. Set breakpoints at all TLS callbacks before running.
88. Prefer run-to-cursor (F4) over single-step (F7) for large code regions.
89. Always verify that binary behavior under the debugger matches behavior without a debugger.
90. When attaching to a running process, check for NtGlobalFlag corruption from the debug heap.
91. Use conditional breakpoints to log calls without interrupting execution.
92. Capture register state at every function entry of interest — document RCX, RDX, R8, R9.
93. Follow RCX on entry to every C++ method — it is always `this` in MSVC x64.
94. Verify vtable identity by reading `[RCX-8]` (the COL pointer) at each virtual call.
95. When a function crashes, check the faulting address — it reveals the type of bad access.
96. Check the call stack at every crash — it shows the path to the fault.
97. Use memory access breakpoints to find every location that reads or writes a specific field.
98. Never conclude a function is safe without testing edge cases (null inputs, boundary values).
99. Validate dynamic findings by running the same scenario multiple times.
100. Document every function entry breakpoint condition and the arguments observed.

## Static Analysis

101. Always run FLIRT signatures on a new binary before manual analysis.
102. Do not manually analyze functions recognized by FLIRT — name them and move on.
103. Prefer cross-references over assumptions when determining function purpose.
104. Follow XREFs upward until reaching a well-understood context before naming a function.
105. Never name a function from a single XREF — find at least two independent call sites.
106. Always check what a function returns before assigning a name.
107. Verify argument count and types from the call site, not just the callee.
108. Mark every function as you understand it — incomplete understanding is worse than none.
109. Use repeatable comments in IDA so context propagates to all callers.
110. Identify all global variables before starting class reconstruction.
111. Distinguish global pointers (8 bytes, .data) from global arrays and embedded structs.
112. Check every reference to a global pointer — it may be the root of a pointer chain.
113. When strings appear in a function, verify they are used directly — not just referenced for logging.
114. Look for error strings near bounds checks to identify security-critical validation code.
115. Cross-reference every virtual function slot to find all callers — some bypass the vtable.
116. Identify devirtualized calls (direct calls to functions that are also in a vtable).
117. Always check for inlined copies of security-critical functions.
118. Never assume a function is only called from known callers — check for function pointer tables.
119. Identify command/message dispatch tables: arrays of function pointers indexed by ID.
120. Annotate dispatch table entries individually — each index corresponds to a command.

## Pattern Scanning

121. Always wildcard all relative operand bytes (call/jmp targets, LEA displacements).
122. Never include absolute address bytes in a pattern without wildcarding them.
123. Test every pattern against at least three binary versions before shipping it.
124. Verify pattern uniqueness — use PatternScanAll and confirm exactly one match.
125. A pattern with fewer than 12 bytes is too short — extend it in both directions.
126. Prefer patterns from function prologues — they are more stable than internal code.
127. Avoid patterns that include loop exit conditions — branch byte encodings can vary.
128. Scan only MEM_COMMIT + PAGE_EXECUTE_* regions — never scan the full address space.
129. Restrict module-specific patterns to that module's executable sections only.
130. When a pattern stops matching after an update, diff the old and new function bytes to find the change.

## Hooks & Patches

131. Verify calling convention before writing a hook function.
132. Match the exact function signature (return type, argument types, register usage).
133. In MSVC x64, `this` is always RCX — never omit it from the hook signature.
134. Prefer per-object vtable hooks over global vtable patches — they are less detectable.
135. When patching .rdata (global vtable), use VirtualProtect PAGE_READWRITE and restore afterward.
136. Document every patch: address, original bytes, new bytes, reason.
137. Never hook a function without saving and calling the original — broken behavior is worse than no hook.
138. Verify that the trampoline to the original function preserves all non-volatile registers.
139. IAT hooks are detectable by integrity scanning — prefer inline hooks or per-object VMT hooks.
140. Test hooks under all expected call conditions, not just the happy path.

## Data Recovery

141. Recover all global singletons before mapping class interactions.
142. A global pointer written once at startup and read everywhere = singleton pattern.
143. Recover enum values from switch statement case labels — each case is an enum constant.
144. Annotate all recovered enum values with their names before analyzing dispatch logic.
145. Recover struct sizes from allocation calls: `HeapAlloc(heap, 0, SIZE)` tells you the size.
146. Verify struct size against the largest known field offset + field size.
147. Identify all factory functions — they return typed pointers that reveal class identity.
148. Cross-reference every `operator new` call to find all heap-allocated class types.
149. Recover string tables before analyzing localization or command parsing code.
150. Document all recovered offsets in a version-tagged table for future update tracking.

## Workflow & Documentation

151. Maintain an analysis log — record every finding, confidence level, and evidence.
152. Use confidence levels: HIGH (RTTI/PDB confirmed), MEDIUM (2+ signals), LOW (1 signal).
153. Never commit a name to the database at LOW confidence without noting the uncertainty.
154. Always save the IDA database before making bulk renames.
155. Version the IDA database by binary hash — never overwrite a previous version's IDB.
156. When returning to a binary after a break, re-read your analysis log before continuing.
157. Keep naming conventions consistent: `ClassName__MethodName` for MSVC C++ methods.
158. Prefix unknown functions with `sub_` until confirmed — do not invent names.
159. Use `possible_` prefix for medium-confidence names to signal uncertainty.
160. Document every vtable address with its class name and slot count.
161. Document every struct: field offsets, types, size, source of evidence for each field.
162. Record the binary version, hash (SHA-256), and compile timestamp in every analysis document.
163. Track every anti-debug bypass applied — they become required in future sessions.
164. Export all recovered names before closing a session — names can be imported to future IDBs.
165. Reproduce every finding independently before marking it as confirmed.

## Security & Mitigations

166. Check CFG status before attempting vtable or indirect call hooks.
167. Register hook targets with SetProcessValidCallTargets if CFG is enabled.
168. Never bypass DEP by marking data pages executable without understanding the consequence.
169. Check for stack cookies (__security_cookie) in target functions before stack-based exploits.
170. Identify all SEH frames and their handler addresses before modifying exception flow.
171. Check .pdata for all functions that have registered exception handlers.
172. Identify VEH (Vectored Exception Handlers) registered at startup — they may hide anti-debug.
173. When CFG is present, do not overwrite vtable pointers without a valid CFG bypass strategy.
174. Verify that any injected shellcode region is registered as a valid CFG call target.
175. Check for SafeSEH on x86 targets — exception handlers must be in the SafeSEH table.

## Performance & Correctness

176. Never scan the entire process address space — it is slow and hits guard pages.
177. Cache module base addresses — GetModuleHandle calls have overhead if repeated millions of times.
178. Use hardware breakpoints instead of software breakpoints in performance-sensitive code paths.
179. Minimize the number of VirtualQuery calls in a scan — batch region checks.
180. Profile pattern scan time on the target binary — if > 50ms, restrict the scan region.
181. Verify that all pointer reads are atomic where concurrent modification is possible.
182. Test all recovered pointer chains after binary updates before using them in production.
183. Validate hook installation in a test scenario before deploying to production.
184. Always test edge cases: null objects, empty collections, zero-length strings.
185. Document all known limitations of recovered patterns, offsets, and hooks.

## Related Material

### Knowledge
- [common-instructions](knowledge/assembly/common-instructions.md)
- [compiler-patterns](knowledge/assembly/compiler-patterns.md)
- [exceptions](knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](prompts/analyze_binary.md)
- [analyze_crash](prompts/analyze_crash.md)
- [analyze_memory](prompts/analyze_memory.md)

