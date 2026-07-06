# Self Test Report

This report simulates an AI retrieval pass using only repository metadata and index information.

- retrieval readiness score: 67 / 100

## Query Validation
- **C++**: matched 21 candidate documents, missing expected 1 docs
  - missing: reverse-engineering/knowledge/cpp/stl.md
- **Assembly**: matched 8 candidate documents, missing expected 1 docs
  - missing: reverse-engineering/knowledge/assembly/calling-conventions.md
- **Windows Internals**: matched 8 candidate documents, missing expected 2 docs
  - missing: kernel/knowledge/kernel-architecture.md
  - missing: reverse-engineering/knowledge/windows/object-manager.md
- **Binary Analysis**: matched 5 candidate documents, missing expected 2 docs
  - missing: binary-analysis/knowledge/pe.md
  - missing: binary-analysis/recipes/analyze-binary.md
- **Reverse Engineering**: matched 23 candidate documents, missing expected 1 docs
  - missing: analysis-engine/decision-tree.md
- **Debugging**: matched 26 candidate documents, all expected docs available
- **Game Engines**: matched 4 candidate documents, all expected docs available
- **Game Security**: matched 5 candidate documents, missing expected 1 docs
  - missing: anti-cheat/knowledge/architecture.md
- **Anti-Cheat**: matched 44 candidate documents, all expected docs available
- **Drivers**: matched 9 candidate documents, missing expected 1 docs
  - missing: kernel/knowledge/driver-model.md
- **Kernel**: matched 147 candidate documents, all expected docs available
- **Hypervisor**: matched 9 candidate documents, missing expected 1 docs
  - missing: hypervisor/knowledge/virtualization-fundamentals.md
- **Networking**: matched 37 candidate documents, all expected docs available
- **Cryptography**: matched 32 candidate documents, all expected docs available
- **GUI Engineering**: matched 1 candidate documents, missing expected 1 docs
  - missing: gui-engineering/knowledge/imgui-architecture.md
- **Dear ImGui**: matched 8 candidate documents, all expected docs available
- **Malware Analysis**: matched 7 candidate documents, all expected docs available

## Path Quality
- MCP skill count: 24
- MCP routing routes: 24

## Issues
- Missing expected doc for C++: reverse-engineering/knowledge/cpp/stl.md
- Missing expected doc for Assembly: reverse-engineering/knowledge/assembly/calling-conventions.md
- Missing expected doc for Windows Internals: kernel/knowledge/kernel-architecture.md
- Missing expected doc for Windows Internals: reverse-engineering/knowledge/windows/object-manager.md
- Missing expected doc for Binary Analysis: binary-analysis/knowledge/pe.md
- Missing expected doc for Binary Analysis: binary-analysis/recipes/analyze-binary.md
- Missing expected doc for Reverse Engineering: analysis-engine/decision-tree.md
- Missing expected doc for Game Security: anti-cheat/knowledge/architecture.md
- Missing expected doc for Drivers: kernel/knowledge/driver-model.md
- Missing expected doc for Hypervisor: hypervisor/knowledge/virtualization-fundamentals.md
- Missing expected doc for GUI Engineering: gui-engineering/knowledge/imgui-architecture.md

## Notes
- This test uses keyword/title matching and related_document metadata to approximate retrieval. It does not execute a full language model query.
- Real AI retrieval may still need explicit cross-links in text for best results.