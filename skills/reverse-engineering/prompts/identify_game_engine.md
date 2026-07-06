---
title: Prompt: Identify Game Engine
skill: reverse-engineering
category: prompts
difficulty: intermediate
tags: [pe, asm, x64, unreal, unity, dll]
updated: 2026-07-05
---
# Prompt: Identify Game Engine

## Objective
Determine which game engine powers a target game binary. Identify engine version, rendering API, scripting layer, and core subsystem patterns. Map engine-specific classes and memory layouts to enable faster reverse engineering.

## Methodology

### Step 1 — File-Level Signals
Check before loading in a disassembler:
1. Embedded strings in .rdata: engine name, version numbers, copyright strings.
2. Section names: `.upx`, `.bss` is normal; unusual: `.vmp`, `.themida`.
3. Imports: DirectX (d3d11.dll, d3d12.dll), OpenGL (opengl32.dll), Vulkan (vulkan-1.dll).
4. Known DLLs shipped alongside: `PhysX3_x64.dll`, `steam_api64.dll`, `fmod.dll`.
5. Resources: icon style and manifest may reveal Unity/Unreal branding.

### Step 2 — String Signatures Per Engine

**Unreal Engine 4/5:**
```
"LogInit:", "LogEngine:", "UObject", "UWorld", "AActor"
"GEngine", "GWorld", "UGameInstance"
"Unreal Engine", "Epic Games", ".uasset", ".pak"
RTTI: .?AVUObject@@, .?AVAActor@@, .?AVUWorld@@
```

**Unity:**
```
"UnityEngine", "UnityPlayer.dll" present
"Assembly-CSharp.dll" (managed code)
"il2cpp" or "mono" in strings/imports
Class names: "MonoBehaviour", "GameObject", "Transform"
```

**CryEngine / CRYENGINE:**
```
"CrySystem", "CryPhysics", "CryRender"
RTTI: .?AVCSystem@@, .?AVIEntity@@
```

**Source Engine:**
```
"valve", "gameinfo.txt", "hl2", "portal2"
VTable patterns: IClientEntity, C_BaseEntity, CBasePlayer
```

**id Tech (id Software):**
```
"idLib", "idSoftware", "DOOM", "Quake"
RTTI: .?AWidClass@@, .?AWidEntity@@
```

**Godot:**
```
"GodotEngine", ".pck" extension, "res://"
```

### Step 3 — Import Pattern Analysis

| DLLs Present                     | Engine Hint              |
|----------------------------------|--------------------------|
| PhysX3Common_x64.dll             | Unreal Engine            |
| UnityPlayer.dll                  | Unity                    |
| mono-2.0-bdwgc.dll               | Unity (Mono scripting)   |
| GameOverlayRenderer64.dll        | Steam (any engine)       |
| fmod.dll / fmodstudio.dll        | FMOD audio (cross-engine)|
| bink2w64.dll                     | Bink video (cross-engine)|
| d3d11.dll only                   | DX11 engine              |
| d3d12.dll present                | Modern DX12 engine       |
| vulkan-1.dll                     | Vulkan renderer          |

### Step 4 — RTTI-Based Engine Detection

**Unreal Engine 4/5 RTTI fingerprint:**
- Classes with `U` prefix: `UObject`, `UWorld`, `UGameEngine`, `ULevel`
- Classes with `A` prefix: `AActor`, `ACharacter`, `APawn`, `APlayerController`
- Classes with `F` prefix (non-polymorphic, may have no RTTI): `FVector`, `FRotator`
- Global: `GUObjectArray` (array of all UObjects in memory)

**UE4 GUObjectArray pattern:**
```asm
; In UObjectBaseUtility::GetLinker or similar:
lea rax, [rip + GUObjectArray_rva]
mov rcx, [rax]         ; FUObjectArray*
; or
mov rax, cs:GUObjectArray
```

**Unity IL2CPP fingerprint:**
- No MSVC RTTI (managed code structures)
- `il2cpp.h` style type metadata in binary
- Function `il2cpp_resolve_icall`, `il2cpp_object_new` in imports or exports

### Step 5 — Unreal Engine Specific Recovery

If Unreal Engine confirmed:

**GEngine** (UGameEngine singleton):
- Find string `"UGameEngine"` → nearby code initializes GEngine.
- Pattern: `mov cs:GEngine, rax` after `new UGameEngine`.

**GWorld** (UWorld pointer):
- Find `"LoadMap"` string → function references GWorld.
- Or: `UWorld::GetWorld()` virtual → returns GWorld.

**UObject Array (GUObjectArray):**
- FUObjectArray contains: `ObjObjects` (TArray of FUObjectItem).
- Each FUObjectItem: `UObject*` + flags.
- Total object count in `ObjLastNonGCIndex`.

**Actor iteration:**
```
GWorld → UWorld.PersistentLevel (ULevel*) → ULevel.Actors (TArray<AActor*>)
GWorld → UWorld.Levels (TArray<ULevel*>) → each level's Actors
```

**Common UE4 offsets (approximate — always verify for target version):**
```
UObject:
  +0x00  vptr
  +0x08  ObjectFlags (EObjectFlags)
  +0x10  InternalIndex (int32, index into GUObjectArray)
  +0x18  ClassPrivate (UClass*)
  +0x20  NamePrivate  (FName)
  +0x28  OuterPrivate (UObject*)

AActor:
  (inherits UObject)
  +0x158 RootComponent (USceneComponent*)

USceneComponent:
  (inherits UActorComponent)
  +0x1C0 RelativeLocation (FVector)  ← x,y,z floats
  +0x1CC RelativeRotation (FRotator)
  +0x1D8 RelativeScale3D  (FVector)
```

### Step 6 — Unity IL2CPP Specific Recovery

If Unity IL2CPP confirmed:

1. Find `GameAssembly.dll` — this is the compiled IL2CPP module.
2. Obtain `il2cpp-metadata.dat` from the game's data folder.
3. Use Il2CppDumper tool to generate a `dump.cs` with all class/method definitions.
4. Apply the generated `script.py` in IDA to auto-name all functions.

Key Il2CPP structures:
```
Il2CppObject:
  +0x00  Il2CppClass* klass
  +0x08  MonitorData*  monitor

Il2CppString:
  +0x00  Il2CppObject  (inherited)
  +0x10  int32_t       length
  +0x14  Il2CppChar[]  chars   (UTF-16)
```

### Step 7 — Source Engine Specific Recovery

If Source Engine confirmed:
- `client.dll` and `engine.dll` are the primary targets.
- IClientEntityList → `GetClientEntity(int index)` → C_BaseEntity*.
- C_BaseEntity virtual function table is large (300+ slots in TF2/CS:GO era).
- Key offsets: m_vecOrigin, m_iHealth, m_iTeamNum (available in netvar tables).

NetVar discovery:
```
RecvTable → RecvProp[] → propName + offset
Find: "DT_BasePlayer" → "m_iHealth" → offset = 0x???
```

## Checklist
- [ ] Engine identified from strings/imports/DLLs
- [ ] Engine version determined (major.minor from version strings)
- [ ] Rendering API identified (DX11/DX12/Vulkan/OpenGL)
- [ ] Physics middleware identified (PhysX/Havok/Bullet)
- [ ] Scripting layer identified (IL2CPP/Mono/Blueprint/Lua)
- [ ] Engine-specific global singletons located
- [ ] Core class hierarchy sketched (World, Entity, Player chain)
- [ ] Known engine offsets verified for target build

## Expected Output
```
Engine:    Unreal Engine 5.1 (confirmed by string "Unreal Engine 5" + PhysX + RTTI)
Renderer:  DirectX 12 (d3d12.dll present)
Physics:   Chaos (UE5 built-in)
Audio:     MetaSound (UE5 built-in)
Scripting: Blueprint + C++ (no IL2CPP/Mono)

Key Globals:
  GEngine     RVA: 0x04B2A3C8  (UGameEngine*)
  GWorld      RVA: 0x04B2A3D0  (UWorld*)
  GUObjectArray RVA: 0x04B2A3D8

Object chain to local player:
  GWorld → +0x1F8 → GameState → +0x2A0 → PlayerArray[0] → +0x2C0 → Pawn → ...
```

## Common Mistakes
- Misidentifying engine version from strings (strings can be old leftover resources).
- Assuming UE4 offsets work on UE5 — major structural differences exist.
- Forgetting IL2CPP requires Il2CppDumper for all class/method names.
- Not accounting for stripped engine builds (some studios strip even engine class names).
- Using community-published offsets without verifying them on the exact build hash.

## Related Material

### Knowledge
- [common-instructions](../knowledge/assembly/common-instructions.md)
- [compiler-patterns](../knowledge/assembly/compiler-patterns.md)
- [exceptions](../knowledge/cpp/exceptions.md)

### Prompts
- [analyze_binary](analyze_binary.md)
- [analyze_crash](analyze_crash.md)
- [analyze_memory](analyze_memory.md)

