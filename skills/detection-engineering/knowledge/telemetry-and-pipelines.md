---
title: Telemetry and Detection Pipelines
skill: detection-engineering
category: knowledge
difficulty: intermediate
tags: [pe, gui, debug]
updated: 2026-07-05
---
# Telemetry and Detection Pipelines

## Overview
Telemetry forms the nervous system of a detection program. It provides the raw evidence that rule engines and analysts use to infer suspicious activity.

## Theory
A detection pipeline usually moves from collection to normalization to evaluation to alerting. Each stage should preserve metadata such as source, time, host identity, and confidence.

## Internal Architecture
Common pipeline stages:
- collectors such as ETW, event logs, Sysmon, network sensors, or custom agents
- normalization and enrichment
- rule evaluation and correlation
- alert generation and response routing

## Practical Workflow
1. Identify the signal source.
2. Define the event schema and necessary enrichment.
3. Implement or configure the collector.
4. Validate the pipeline end to end.
5. Review cost, latency, and operational impact.

## Common Mistakes
- missing host or process context in events
- losing correlation fields during normalization
- creating detections that cannot be tested meaningfully

## Best Practices
- preserve rich event metadata
- keep the pipeline observable and debuggable
- correlate signals rather than relying on single events

## Related Material

### Knowledge
- [detection-engineering-fundamentals](detection-engineering-fundamentals.md)

### Patterns
- [monitoring-loop](../patterns/monitoring-loop.md)

### Recipes
- [design-detection-pipeline](../recipes/design-detection-pipeline.md)

### Playbooks
- [analyze-detection-pipeline](../playbooks/analyze-detection-pipeline.md)

### References
- [references](../references/references.md)

### Rules
- [style](../rules/style.md)

### Prompts
- [design-prompt](../prompts/design-prompt.md)

### Checklists
- [validation-checklist](../checklists/validation-checklist.md)

## Practical Guidance

- Define telemetry schemas early and enforce them at collection time.
- Instrument timestamps and unique identifiers to correlate events across systems.

## Tools & Pipelines

- Use message queues (Kafka, RabbitMQ) for high-throughput telemetry ingestion.
- Use parsers and normalizers to produce canonical events for rule engines.

## Validation Checklist

- Confirm event schemas are versioned and backward-compatible.
- Verify end-to-end latency and loss characteristics under load.

