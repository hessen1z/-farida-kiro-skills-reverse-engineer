# Analyze VBS Playbook

## Objective
Validate Virtualization-Based Security (VBS) protections and secure kernel isolation in a Windows system.

## Steps
1. Check VBS and Secure Kernel status through system configuration and registry.
2. Identify secure kernel partitions and guarded memory regions.
3. Inspect VMBus and hypervisor communication paths for secure services.
4. Verify that normal kernel code cannot access secure kernel memory.
5. Review credential protection mechanisms such as Credential Guard.

## Common Scenarios
- VBS failing to initialize
- secure kernel memory access violations
- credential storage or LSA protection issues
- hypervisor partition isolation problems

## Best Practices
- use hardware-assisted tools and hypervisor logs for VBS analysis.
- do not bypass or disable VBS in an untrusted environment without a controlled test bed.
- clearly separate runtime evidence from configuration state.

## Outcome
- confirmed VBS and secure kernel enforcement
- identified potential misconfigurations or weaknesses
- documented the security boundaries and necessary remediation

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
- [analyze-hyper-v](analyze-hyper-v.md)
- [analyze-hypervisor](analyze-hypervisor.md)

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

