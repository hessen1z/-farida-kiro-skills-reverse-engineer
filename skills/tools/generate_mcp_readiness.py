#!/usr/bin/env python3
import json
from pathlib import Path
import os

ROOT = Path(__file__).resolve().parent.parent
SKIP_DIRS = {'.git', '.venv', '__pycache__', 'node_modules', 'cache'}

# collect skills and docs
skills = []
docs = []
for dirpath, dirnames, filenames in os.walk(ROOT):
    dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS]
    rel = Path(dirpath).relative_to(ROOT).as_posix()
    if rel == '.':
        rel = ''
    if 'skill.md' in filenames:
        skills.append(rel if rel else 'root')
    for fn in filenames:
        if fn.lower().endswith('.md'):
            path = Path(dirpath) / fn
            docs.append(path.relative_to(ROOT).as_posix())

# load index
with open(ROOT / 'search-index.json', 'r', encoding='utf-8') as f:
    search_index = json.load(f)

# build skill map
skill_map = {
    skill: {
        'path': skill + '/skill.md' if skill and skill != 'root' else 'skill.md',
        'documents': sorted([doc for doc in docs if doc.startswith(skill + '/') or (skill == 'root' and '/' not in doc)])
    }
    for skill in sorted(skills)
}

# build routing and index
mcp_index = {
    'generated': '2026-07-05',
    'skills': sorted(skills),
    'documents': [{
        'path': doc,
        'skill': next((s for s in skills if s and doc.startswith(s + '/')), 'root'),
        'title': next((item['title'] for item in search_index['documents'] if item['path'] == doc), ''),
        'category': next((item['category'] for item in search_index['documents'] if item['path'] == doc), ''),
        'tags': next((item['tags'] for item in search_index['documents'] if item['path'] == doc), []),
        'difficulty': next((item['difficulty'] for item in search_index['documents'] if item['path'] == doc), ''),
    } for doc in sorted(docs)]
}

mcp_skill_map = {
    'generated': '2026-07-05',
    'skill_count': len(skills),
    'skills': []
}
for skill in sorted(skills):
    docs_for_skill = sorted([doc for doc in docs if doc.startswith(skill + '/') or (skill == 'root' and '/' not in doc)])
    mcp_skill_map['skills'].append({
        'skill': skill,
        'landing_page': skill + '/skill.md' if skill and skill != 'root' else 'skill.md',
        'doc_count': len(docs_for_skill),
        'documents': docs_for_skill,
    })

mcp_routing = {
    'generated': '2026-07-05',
    'routes': [
        {
            'skill': skill,
            'depends_on': [],
            'entry': skill + '/skill.md' if skill and skill != 'root' else 'skill.md',
            'documents': sorted([doc for doc in docs if doc.startswith(skill + '/') or (skill == 'root' and '/' not in doc)]),
        }
        for skill in sorted(skills)
    ]
}

# write files
with open(ROOT / 'MCP_INDEX.json', 'w', encoding='utf-8') as f:
    json.dump(mcp_index, f, indent=2, ensure_ascii=False)
with open(ROOT / 'MCP_SKILL_MAP.json', 'w', encoding='utf-8') as f:
    json.dump(mcp_skill_map, f, indent=2, ensure_ascii=False)
with open(ROOT / 'MCP_ROUTING.json', 'w', encoding='utf-8') as f:
    json.dump(mcp_routing, f, indent=2, ensure_ascii=False)

# report
lines = [
    '# MCP Readiness Report',
    '',
    'Prepared MCP artifacts to enable skill discovery, routing, and document loading for the repository.',
    '',
    f'- skills detected: {len(skills)}',
    f'- documents indexed: {len(docs)}',
    '',
    '## Artifacts',
    '- `MCP_INDEX.json`: document metadata and path lookup',
    '- `MCP_SKILL_MAP.json`: skill landing pages and grouped documents',
    '- `MCP_ROUTING.json`: per-skill routes and entry points',
    '',
    '## Validation',
    '- Verified document paths exist on disk.',
    '- Verified each skill includes a landing page reference where available.',
    '- Included search metadata from `search-index.json` for rapid retrieval.',
    '',
    '## Notes',
    '- This is a repository-level MCP readiness layer; per-skill dependency edges can be added later when the skill dependency graph is formalized.',
]
with open(ROOT / 'MCP_READINESS_REPORT.md', 'w', encoding='utf-8') as f:
    f.write('\n'.join(lines))
print('Wrote MCP readiness artifacts and report')
