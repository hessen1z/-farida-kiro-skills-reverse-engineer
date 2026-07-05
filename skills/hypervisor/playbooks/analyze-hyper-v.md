# Analyze Hyper-V Playbook

## Objective
Review Hyper-V configuration, partition isolation, and synthetic device communication to validate guest-host boundaries.

## Steps
1. Identify the Hyper-V partition manager and active partitions.
2. Verify VMBus connectivity and synthetic device bindings.
3. Inspect the hypervisor scheduler and virtual processor allocation.
4. Review Hyper-V memory isolation settings and secure kernel status.
5. Document host-guest communication and resource sharing policies.

## Common Scenarios
- guest boot failures under Hyper-V
- Hyper-V partition configuration errors
- synthetic device or VMBus communication failures
- secure kernel or VBS partition issues

## Best Practices
- verify Hyper-V role and required hardware virtualization support.
- avoid changing partition config without a controlled test environment.
- maintain separate analysis for Hyper-V host and guest state.

## Outcome
- confirmed Hyper-V partition and device topology
- validated guest communication channels and isolation
- documented Hyper-V-specific constraints for analysis

## Related Material

### Knowledge
- [hyper-v-vbs](../knowledge/hyper-v-vbs.md)
- [hypervisor-architecture](../knowledge/hypervisor-architecture.md)
- [virtualization-fundamentals](../knowledge/virtualization-fundamentals.md)

### Patterns
- [ept-management](../patterns/ept-management.md)
- [hypervisor-patterns](../patterns/hypervisor-patterns.md)

### Recipes
- [analyze-ept](../recipes/analyze-ept.md)
- [analyze-hypervisor](../recipes/analyze-hypervisor.md)
- [analyze-vbs](../recipes/analyze-vbs.md)

### Playbooks
- [analyze-hypervisor](analyze-hypervisor.md)
- [analyze-vbs](analyze-vbs.md)

### Examples
- [ept-layout](../examples/ept-layout.md)
- [vm-entry-exit](../examples/vm-entry-exit.md)

### References
- [references](../references/references.md)

### Rules
- [hypervisor-guidelines](../rules/hypervisor-guidelines.md)

### Prompts
- [hypervisor-analysis](../prompts/hypervisor-analysis.md)
- [vbs-analysis](../prompts/vbs-analysis.md)
- [vmcs-analysis](../prompts/vmcs-analysis.md)

### Checklists
- [checklist](../checklists/checklist.md)

