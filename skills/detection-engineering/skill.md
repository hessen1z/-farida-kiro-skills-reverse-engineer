---
name: detection-engineering
version: 1.0
priority: high
requires:
  - shared
  - analysis-engine
  - windows-internals
  - malware-analysis
  - windows-security
tags:
  - detection
  - telemetry
  - defense
  - monitoring
  - windows
description: Defensive detection engineering skill covering telemetry collection, rule design, behavioral detection, correlation, alerting, and validation.
---

# Detection Engineering Skill

## Purpose
Teach the AI how professional detection systems are designed for defensive security, endpoint protection, anti-cheat systems, and operating system monitoring. This skill focuses exclusively on defensive engineering and the design of scalable detection pipelines.

## Scope
This skill covers:
- detection engineering fundamentals and lifecycle
- telemetry collection, event processing, and pipeline design
- ETW, Windows Event Logs, Sysmon concepts, and process monitoring
- behavioral detection, signature-based detection, heuristic detection, and correlation
- false-positive reduction, confidence scoring, alert prioritization, and validation

## What this skill provides
- a practical model for building detection pipelines
- defensive guidance for telemetry design and alert generation
- references to patterns, recipes, playbooks, examples, and quality validation methods

## Prerequisites
- `shared` — documentation and templates
- `analysis-engine` — reasoning and evidence-based verification
- `windows-internals` — monitoring-relevant OS behavior
- `malware-analysis` — threat behavior and defensive interpretation
- `windows-security` — hardening and protection mechanisms

## Used by
- `windows-security` — for monitoring and defense coverage
- `anti-cheat` — for runtime integrity and telemetry concepts
- `malware-analysis` — for translation of behaviors into detections

## Related Skills
- `malware-analysis` — behavior and threat context
- `windows-security` — security controls and system hardening
- `networking` — network telemetry and protocol monitoring
- `cryptography` — detection of suspicious key-management or certificate behavior

## Entry Conditions
- A defensive telemetry or detection design problem needs architecture and workflow guidance.
- A monitoring pipeline or alerting problem requires rule, correlation, or validation design.

## Exit Conditions
- The detection approach is documented with telemetry sources, rule logic, validation steps, and alert handling guidance.

## Related Material

- Knowledge: [detection-engineering-fundamentals](knowledge/detection-engineering-fundamentals.md)
- Patterns: [monitoring-loop](patterns/monitoring-loop.md)
- Recipes: [design-detection-pipeline](recipes/design-detection-pipeline.md)
- Playbooks: [analyze-detection-pipeline](playbooks/analyze-detection-pipeline.md)
- References: [references](references/references.md)
- Rules: [style](rules/style.md)
- Prompts: [design-prompt](prompts/design-prompt.md)
- Checklists: [validation-checklist](checklists/validation-checklist.md)

