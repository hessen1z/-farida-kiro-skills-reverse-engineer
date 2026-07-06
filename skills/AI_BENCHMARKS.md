# AI Benchmarks

This benchmark suite validates the repository as a knowledge source for AI engineering tasks across core domains.

## Benchmark 1: PE Analysis
- Task: Analyze a Windows PE binary and identify loader behavior, import resolution, and potential packer/obfuscation techniques.
- Expected Skills: `binary-analysis`, `reverse-engineering`, `windows-security`, `malware-analysis`
- Expected Documents:
  - `binary-analysis/knowledge/pe.md`
  - `binary-analysis/recipes/analyze-binary.md`
  - `binary-analysis/patterns/import-table.md`
  - `binary-analysis/patterns/export-table.md`
  - `malware-analysis/knowledge/packed-binary-indicators.md`
  - `reverse-engineering/knowledge/windows/loader.md`
- Expected Output:
  - Clear explanation of PE sections, import/exports, loader dependency chain, and suspicious packing behavior.
  - A prioritized list of investigation steps.
- Success Criteria:
  - Identifies imports, exports, resources, and packing/protector evidence.
  - Recommends next actions for unpacking or runtime analysis.

## Benchmark 2: Driver Analysis
- Task: Review a Windows driver and determine its object model, IRP handling, and security posture.
- Expected Skills: `drivers`, `kernel`, `windows-security`
- Expected Documents:
  - `drivers/knowledge/driver-model.md`
  - `kernel/knowledge/object-manager-memory-manager.md`
  - `drivers/recipes/analyze-irp.md`
  - `drivers/patterns/irp-flow.md`
  - `windows-security/knowledge/code-integrity.md`
- Expected Output:
  - Driver entry design, IRP dispatch summary, and potential security implications.
- Success Criteria:
  - Recognizes IRP dispatch patterns, object manager boundaries, and driver security controls.

## Benchmark 3: Reverse Engineering
- Task: Map a binary to type and symbol recovery, including vtables, RTTI, and function naming.
- Expected Skills: `reverse-engineering`, `analysis-engine`, `cpp`
- Expected Documents:
  - `reverse-engineering/prompts/recover_vtable.md`
  - `reverse-engineering/prompts/recover_rtti.md`
  - `analysis-engine/decision-tree.md`
  - `cpp/skill.md`
- Expected Output:
  - Candidate function/class names, vtable layout, and recovery strategy.
- Success Criteria:
  - Produces a credible recovery plan with reference to vtable and RTTI analysis.

## Benchmark 4: Dear ImGui Reconstruction
- Task: Translate a GUI screenshot or binary UI code into a Dear ImGui reconstruction plan.
- Expected Skills: `gui-engineering`, `game-engines`, `system-design`
- Expected Documents:
  - `gui-engineering/knowledge/imgui-architecture.md`
  - `gui-engineering/playbooks/convert-screenshot-to-dear-imgui.md`
  - `game-engines/patterns/plugin-system.md`
  - `system-design/recipes/design-plugin-architecture.md`
- Expected Output:
  - Component mapping to Dear ImGui primitives and a rebuild roadmap.
- Success Criteria:
  - Identifies widgets, layout flow, and reconstruction steps.

## Benchmark 5: Windows Internals Investigation
- Task: Explain how a Windows system call sequence interacts with kernel objects and thread scheduling.
- Expected Skills: `windows-internals`, `kernel`, `debugging`
- Expected Documents:
  - `kernel/knowledge/kernel-architecture.md`
  - `kernel/knowledge/process-thread-manager.md`
  - `kernel/knowledge/interrupts-system-calls.md`
  - `debugging/knowledge/kernel-debugging.md`
- Expected Output:
  - A step-by-step explanation of syscall processing and kernel synchronization.
- Success Criteria:
  - Correctly names kernel components and pathways.

## Benchmark 6: Anti-Cheat Tactical Review
- Task: Assess a game anti-cheat architecture for memory scanning, enforcement, and kernel/user-mode collaboration.
- Expected Skills: `anti-cheat`, `game-security`, `game-engines`
- Expected Documents:
  - `anti-cheat/knowledge/architecture.md`
  - `anti-cheat/patterns/memory-scan.md`
  - `game-security/patterns/tamper-check.md`
  - `game-engines/knowledge/engine-architecture.md`
- Expected Output:
  - A threat modelling summary and recommended detection/enforcement improvements.
- Success Criteria:
  - Identifies key attack surfaces and explains anti-cheat controls.

## Benchmark 7: Networking Security Analysis
- Task: Analyze a multiplayer protocol for reliability, latency, and security tradeoffs.
- Expected Skills: `networking`, `game-engines`, `system-design`
- Expected Documents:
  - `networking/knowledge/multiplayer-networking.md`
  - `networking/recipes/analyze-multiplayer-game.md`
  - `system-design/knowledge/concurrency-and-performance.md`
- Expected Output:
  - An analysis of packet flow, session handling, and security gaps.
- Success Criteria:
  - Recommends concrete improvements for performance and hardening.

## Benchmark 8: Cryptography Review
- Task: Review a data transport design and assess cryptographic primitives, key management, and integrity.
- Expected Skills: `cryptography`, `networking`, `security`
- Expected Documents:
  - `cryptography/knowledge/cryptography-fundamentals.md`
  - `cryptography/recipes/analyze-key-management.md`
  - `cryptography/rules/cryptography-guidelines.md`
- Expected Output:
  - A concise audit of algorithm choices and protocol security.
- Success Criteria:
  - Calls out weak key lifecycle, improper modes, or missing integrity.

## Benchmark 9: Malware Analysis Workflow
- Task: Develop a workflow to triage a suspicious sample using static and dynamic indicators.
- Expected Skills: `malware-analysis`, `binary-analysis`, `debugging`
- Expected Documents:
  - `malware-analysis/knowledge/malware-analysis-fundamentals.md`
  - `malware-analysis/checklists/analysis-checklist.md`
  - `binary-analysis/recipes/recover-imports.md`
- Expected Output:
  - A triage checklist with next-step recommendations.
- Success Criteria:
  - Distinguishes static indicators, dynamic analysis goals, and safe handling.

## Benchmark 10: Kernel Root Cause Diagnosis
- Task: Diagnose a kernel crash from a memory dump and suggest the likely faulty component.
- Expected Skills: `kernel`, `debugging`, `windows-internals`
- Expected Documents:
  - `debugging/recipes/capture-dump.md`
  - `kernel/recipes/analyze-kernel-crash.md`
  - `windows-internals/skill.md`
- Expected Output:
  - A root cause hypothesis and evidence-based next steps.
- Success Criteria:
  - Points to the right subsystem and recommended investigation actions.
