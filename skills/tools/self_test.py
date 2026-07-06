#!/usr/bin/env python3
import json, pathlib, re
from collections import defaultdict

ROOT = pathlib.Path(__file__).resolve().parent.parent

# load search index and MCP artifacts
search = json.loads((ROOT / 'search-index.json').read_text('utf-8'))
with open(ROOT / 'MCP_INDEX.json', 'r', encoding='utf-8') as f:
    mcp_index = json.load(f)
with open(ROOT / 'MCP_SKILL_MAP.json', 'r', encoding='utf-8') as f:
    mcp_skill_map = json.load(f)
with open(ROOT / 'MCP_ROUTING.json', 'r', encoding='utf-8') as f:
    mcp_routing = json.load(f)

# build name lookup
title_to_docs = defaultdict(list)
path_to_doc = {}
for doc in search['documents']:
    title_to_docs[doc['title'].lower()].append(doc['path'])
    path_to_doc[doc['path']] = doc

queries = [
    ('C++', ['cpp/skill.md', 'reverse-engineering/knowledge/cpp/exceptions.md', 'reverse-engineering/knowledge/cpp/stl.md']),
    ('Assembly', ['reverse-engineering/knowledge/assembly/common-instructions.md', 'reverse-engineering/knowledge/assembly/calling-conventions.md']),
    ('Windows Internals', ['kernel/knowledge/kernel-architecture.md', 'windows-internals/skill.md', 'reverse-engineering/knowledge/windows/object-manager.md']),
    ('Binary Analysis', ['binary-analysis/knowledge/pe.md', 'binary-analysis/recipes/analyze-binary.md']),
    ('Reverse Engineering', ['reverse-engineering/skill.md', 'analysis-engine/decision-tree.md']),
    ('Debugging', ['debugging/skill.md', 'debugging/knowledge/debugging.md']),
    ('Game Engines', ['game-engines/skill.md', 'game-engines/knowledge/engine-architecture.md']),
    ('Game Security', ['game-security/skill.md', 'anti-cheat/knowledge/architecture.md']),
    ('Anti-Cheat', ['anti-cheat/skill.md', 'anti-cheat/patterns/memory-scan.md']),
    ('Drivers', ['drivers/skill.md', 'kernel/knowledge/driver-model.md']),
    ('Kernel', ['kernel/skill.md', 'kernel/knowledge/kernel-architecture.md']),
    ('Hypervisor', ['hypervisor/skill.md', 'hypervisor/knowledge/virtualization-fundamentals.md']),
    ('Networking', ['networking/skill.md', 'networking/knowledge/networking-overview.md']),
    ('Cryptography', ['cryptography/skill.md', 'cryptography/knowledge/cryptography-fundamentals.md']),
    ('GUI Engineering', ['gui-engineering/skill.md', 'gui-engineering/knowledge/imgui-architecture.md']),
    ('Dear ImGui', ['gui-engineering/knowledge/imgui-architecture.md', 'gui-engineering/playbooks/convert-screenshot-to-dear-imgui.md']),
    ('Malware Analysis', ['malware-analysis/skill.md', 'malware-analysis/knowledge/malware-analysis-fundamentals.md']),
]

reports = []
missing_docs = []
for query, expected in queries:
    matched = []
    # candidate docs by keyword in title or tags
    q = query.lower()
    for doc in search['documents']:
        if q in doc['title'].lower() or q in ' '.join(doc['tags']).lower() or q in doc['summary'].lower():
            matched.append(doc['path'])
    hits = set(matched)
    expected_missing = [p for p in expected if p not in hits]
    reports.append((query, len(hits), expected_missing, hits))
    if expected_missing:
        missing_docs.extend([(query, p) for p in expected_missing])

# evaluate retrieval quality
score = 100
issues = []
if missing_docs:
    score -= min(50, len(missing_docs) * 3)
    for query, path in missing_docs:
        issues.append(f'Missing expected doc for {query}: {path}')

# check cross-ref density for selected skills
cross_ref_issues = []
for skill_entry in mcp_skill_map['skills']:
    docs = skill_entry['documents']
    if len(docs) > 10:
        linked = sum(1 for p in docs if path_to_doc.get(p, {}).get('related_documents'))
        if linked < len(docs) * 0.5:
            cross_ref_issues.append((skill_entry['skill'], len(docs), linked))
            score -= 2

if cross_ref_issues:
    issues.append('Low related_documents density in skills: ' + ', '.join(f"{s}: {l}/{linked}" for s,l,linked in cross_ref_issues))

# detect isolated root docs
isolated = []
for doc in search['documents']:
    if doc['path'] in ['README.md', 'ARCHITECTURE.md', 'SYSTEM.md']:
        if not doc['related_documents']:
            isolated.append(doc['path'])
            score -= 1

lines = [
    '# Self Test Report',
    '',
    'This report simulates an AI retrieval pass using only repository metadata and index information.',
    '',
    f'- retrieval readiness score: {max(0, score)} / 100',
    '',
    '## Query Validation',
]
for query, hits, missing, hits_set in reports:
    lines.append(f'- **{query}**: matched {hits} candidate documents' + (f', missing expected {len(missing)} docs' if missing else ', all expected docs available'))
    if missing:
        for p in missing:
            lines.append(f'  - missing: {p}')
lines.append('')
lines.append('## Path Quality')
lines.append(f'- MCP skill count: {len(mcp_skill_map["skills"])}')
lines.append(f'- MCP routing routes: {len(mcp_routing["routes"])}')
lines.append('')
lines.append('## Issues')
if issues:
    for issue in issues:
        lines.append(f'- {issue}')
else:
    lines.append('- no major retrieval issues detected in the simulated pass')
lines.append('')
lines.append('## Notes')
lines.append('- This test uses keyword/title matching and related_document metadata to approximate retrieval. It does not execute a full language model query.')
lines.append('- Real AI retrieval may still need explicit cross-links in text for best results.')

with open(ROOT / 'SELF_TEST_REPORT.md', 'w', encoding='utf-8') as f:
    f.write('\n'.join(lines))
print('Wrote SELF_TEST_REPORT.md')
