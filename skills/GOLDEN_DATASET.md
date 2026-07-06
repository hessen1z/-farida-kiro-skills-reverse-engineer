# Golden Dataset Specification

This dataset plan defines a structured collection of artifacts for validating the AI Security Library without including external binaries.

## Purpose
The dataset supports training and benchmarking by providing representative samples across core engineering domains. It does not contain actual files; it describes the required corpus, learning objectives, and validation goals.

## Dataset Categories

### 1. PE Files
- Purpose: Validate PE analysis and loader understanding.
- Required Sample Count: 100
- Expected Learning Objectives:
  - recognize PE headers, imports, exports, and resources
  - identify common packers and obfuscation patterns
  - determine runtime loader behavior and dependency chains
- Validation Goals:
  - ensure the repository supports PE parsing, import/export discovery, and protection analysis
  - verify retrieval of binary-analysis and reverse-engineering documentation

### 2. DLLs
- Purpose: Test shared library analysis and interface reconstruction.
- Required Sample Count: 100
- Expected Learning Objectives:
  - understand export tables and thunking
  - infer calling conventions and API contracts
  - assess binary reuse and compatibility issues
- Validation Goals:
  - validate document coverage for DLL-specific analysis
  - test extraction of exports, imports, and lifetime behavior

### 3. Drivers
- Purpose: Validate kernel-mode analysis and Windows object model understanding.
- Required Sample Count: 20
- Expected Learning Objectives:
  - identify driver entry points and IRP dispatch tables
  - reason about kernel object management and security boundaries
  - detect insecure driver design and code integrity issues
- Validation Goals:
  - confirm retrieval of driver/kernel documentation
  - verify analysis of IRP flow and driver lifecycle

### 4. Crash Dumps
- Purpose: Validate debugging and root cause diagnosis workflows.
- Required Sample Count: 20
- Expected Learning Objectives:
  - analyze stack traces, exception records, and process state
  - map crashes to kernel/user-mode interactions
  - recommend triage steps for hang/crash analysis
- Validation Goals:
  - ensure the repository supports crash dump investigation
  - validate cross-linking between debugging and kernel internals

### 5. Unreal Engine Projects
- Purpose: Validate game-engine and anti-cheat retrieval for Unreal-specific binaries.
- Required Sample Count: 20
- Expected Learning Objectives:
  - identify Unreal file formats, object pipelines, and code loading
  - map game engine architecture to anti-cheat attack surfaces
  - reason about asset loading, plugins, and runtime state
- Validation Goals:
  - check retrieval of Unreal-related game-engine documentation
  - verify coverage for pattern identification and anti-cheat review

### 6. Unity Projects
- Purpose: Validate engine-specific analysis for IL2CPP and managed/native mixing.
- Required Sample Count: 20
- Expected Learning Objectives:
  - understand Unity binary layouts and IL2CPP structures
  - identify game logic, asset loading, and injection risks
  - map Unity-specific behaviors to reverse-engineering strategies
- Validation Goals:
  - verify game-engine and reverse-engineering cross-skill retrieval
  - ensure Unity-specific document coverage is present

### 7. Malware Samples
- Purpose: Validate malicious behavior analysis and detection engineering.
- Required Sample Count: 20
- Expected Learning Objectives:
  - identify static and dynamic malware indicators
  - analyze obfuscation, packing, and persistence techniques
  - recommend detection and containment strategies
- Validation Goals:
  - confirm retrieval of malware-analysis and detection-engineering documentation
  - validate analysis path from indicators to remediation guidance

### 8. Windows Internals Cases
- Purpose: Validate in-depth registry, object manager, scheduler, and memory management knowledge.
- Required Sample Count: 20
- Expected Learning Objectives:
  - explain Windows internals behavior and component relationships
  - analyze system calls, IRQL, and object lifetime
  - connect internals to debugging and kernel analysis
- Validation Goals:
  - verify retrieval quality for Windows internals content
  - ensure corpus links core OS knowledge to practical tasks

### 9. Networking Captures
- Purpose: Validate protocol analysis, multiplayer design, and transport security.
- Required Sample Count: 20
- Expected Learning Objectives:
  - decode session state, packet flow, and protocol semantics
  - evaluate latency, reliability, and authentication issues
  - apply networking best practices to game and service designs
- Validation Goals:
  - confirm networking coverage in search and retrieval
  - validate document pathways for protocol analysis and secure transport

### 10. Dear ImGui UI Cases
- Purpose: Validate GUI reconstruction and frontend tool design.
- Required Sample Count: 20
- Expected Learning Objectives:
  - reconstruct user interfaces using Dear ImGui patterns
  - analyze widget composition and rendering flow
  - design reusable UI components for desktop tools
- Validation Goals:
  - verify GUI engineering and system-design retrieval
  - ensure the repository supports practical UI engineering tasks

## Validation Approach
- Each category should have a canonical set of sample descriptors, not necessarily binary data.
- Use metadata tags and sample annotations to confirm the repository can answer questions about the artifact type.
- Focus on retrieval and reasoning rather than raw file ingestion.

## Dataset Metadata Schema
- `category`: artifact category name
- `purpose`: why the category exists
- `sample_count`: target number of samples
- `learning_objectives`: what the AI should learn
- `validation_goals`: the intended retrieval checks
- `notes`: special considerations for evaluation

## Notes
- This specification is intentionally non-binary and designed for repository validation, not dataset distribution.
- The dataset plan can be implemented by pairing sample descriptions with open-source artifacts or synthetic examples.
