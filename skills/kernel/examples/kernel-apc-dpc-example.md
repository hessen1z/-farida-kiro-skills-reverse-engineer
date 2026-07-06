---
title: Kernel APC and DPC Example
skill: kernel
category: examples
difficulty: intermediate
tags: [pe, driver, gui, kernel, debug]
updated: 2026-07-05
---
# Kernel APC and DPC Example

This document demonstrates how to inspect and validate kernel-mode deferred work using Asynchronous Procedure Calls (APC) and Deferred Procedure Calls (DPC). It provides background, a worked example, diagnostics steps, verification checklist, common mistakes, and remediation guidance.

## Background

- DPCs run at `DISPATCH_LEVEL` and are intended for short, non-blocking deferred work that originates from an ISR or other high-IRQL context.
- APCs execute in thread context and can perform operations that require lower IRQL (including paging and user-mode interaction).
- Mixing pageable operations or long-running work inside DPCs leads to system instability, priority inversion, and deadlocks.

Key constraints:
- DPC callbacks must not call pageable functions, acquire mutexes that can block, or perform lengthy computations.
- APCs can be queued to a specific thread and run when that thread enters an alertable wait.

## Scenario

You suspect a kernel component defers work incorrectly (e.g., performs blocking I/O inside a DPC) and want to validate proper separation between ISR, DPC, and APC stages.

## Goals

- Confirm the ISR queues a DPC and that the DPC runs at `DISPATCH_LEVEL`.
- Verify deferred work does not perform pageable access or blocking operations.
- Identify any APCs queued to threads and confirm they execute in thread context.
- Produce a remediation plan if violations are found.

## Minimal Example (illustrative)

This is a small, safe DPC example showing the pattern for deferring work. Real drivers must add error handling and proper synchronization.

```cpp
#include <ntddk.h>

KDPC gDpc;

VOID
DpcRoutine(
        _In_ struct _KDPC* Dpc,
        _In_opt_ PVOID DeferredContext,
        _In_opt_ PVOID SystemArgument1,
        _In_opt_ PVOID SystemArgument2
        )
{
        UNREFERENCED_PARAMETER(Dpc);
        UNREFERENCED_PARAMETER(DeferredContext);
        UNREFERENCED_PARAMETER(SystemArgument1);
        UNREFERENCED_PARAMETER(SystemArgument2);

        // Example: perform short, non-blocking processing at DISPATCH_LEVEL
        // Do NOT call Zw* or other pageable APIs here.
}

VOID
QueueDpcExample()
{
        KeInitializeDpc(&gDpc, DpcRoutine, NULL);
        KeInsertQueueDpc(&gDpc, NULL, NULL);
}
```

## Diagnostics and Investigation Steps

1. Locate the ISR or interrupt registration that calls `KeInsertQueueDpc`.
     - Search for `KeInsertQueueDpc`, `KeInitializeDpc`, and `IoConnectInterruptEx` in driver sources or binaries.
2. Identify the DPC routine and inspect its implementation for disallowed operations.
     - Look for calls to `Zw*`, `MmMapLockedPages`, `KeWaitForSingleObject`, `ExAcquireResource*` that may block.
3. Use live-debugging (WinDbg) to observe IRQL and callstack when the DPC runs.
     - Set a breakpoint on the DPC routine address or use `!kdpc` to list queued DPCs.
4. Verify whether APCs are queued by the DPC or other components by searching for `KeInsertQueueApc` or `KeInitializeApc`.
5. Trace thread contexts to find APC delivery points and ensure APCs run at `PASSIVE_LEVEL`.

## WinDbg Commands (examples)

- List active DPCs: !kdpc
- Show current IRQL: `!thread` and check `IRQL` field
- Break on DPC routine (if symbol available): `bp <Module>!DpcRoutine` and then `g`
- Dump DPC objects and queue: `dt nt!_KDPC` and inspect the queue on each processor
- Show APCs queued to a thread: Use `!thread` and inspect `ApcState` fields

## Verification Checklist

- [ ] Found ISR that inserts the DPC
- [ ] Confirmed DPC handler runs at `DISPATCH_LEVEL`
- [ ] No pageable or blocking APIs in DPC stack
- [ ] Deferred work that requires paging is moved to APC or worker thread
- [ ] APCs (if any) deliver work at `PASSIVE_LEVEL` and complete successfully
- [ ] No IRQL violations or crashes observed during stress test

## Common Mistakes and How to Fix

- Mistake: Calling pageable or user-mode APIs inside DPC.
    - Fix: Move that logic into an APC, work item, or a dedicated kernel thread that runs at `PASSIVE_LEVEL`.
- Mistake: Allocating memory with `ExAllocatePoolWithTag(PagedPool)` and touching it at `DISPATCH_LEVEL`.
    - Fix: Use non-pageable pool for data accessed at high IRQL or change design to access at `PASSIVE_LEVEL`.
- Mistake: Long-running loops or heavy computation in DPC.
    - Fix: Offload to worker threads or split the work into smaller DPC invocations.

## Remediation Example

- If a DPC must perform I/O, change the flow:
    1. DPC queues an APC or signals a non-paged work queue.
 2. APC/worker runs at `PASSIVE_LEVEL` and performs the I/O safely.

## Outcome Evidence (Artifacts to Collect)

- WinDbg logs showing DPC execution frames and IRQL
- Source diff demonstrating removal of blocking calls from DPC
- Test results from stress runs (latency, crash-free duration)

## Related Material

- Knowledge: [irql-apc-dpc](../knowledge/irql-apc-dpc.md), [interrupts-system-calls](../knowledge/interrupts-system-calls.md)
- Patterns: [dispatcher-routines](../patterns/dispatcher-routines.md)
- Recipes: [analyze-kernel-component](../recipes/analyze-kernel-component.md)
- Playbooks: [analyze-kernel-crash](../playbooks/analyze-kernel-crash.md)
- Examples: [kernel-debugging](kernel-debugging.md), [kernel-handle-table-example](kernel-handle-table-example.md)
- References: [references](../references/references.md)


