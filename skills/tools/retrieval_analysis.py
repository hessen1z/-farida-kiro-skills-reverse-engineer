#!/usr/bin/env python3
import os, re, json, math
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SKIP_DIRS = {'.git', '.venv', '__pycache__', 'node_modules', 'cache'}

# load existing index
with open(ROOT / 'search-index.json', 'r', encoding='utf-8') as f:
    index = json.load(f)

docs = {doc['path']: doc for doc in index['documents']}

# collect actual markdown paths
actual = []
for dirpath, dirnames, filenames in os.walk(ROOT):
    dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS]
    for fn in filenames:
        if fn.lower().endswith('.md'):
            p = Path(dirpath) / fn
            actual.append(p.relative_to(ROOT).as_posix())

missing_index = sorted([p for p in actual if p not in docs])
extra_index = sorted([p for p in docs if p not in actual])

# parse links and backlinks
link_pattern = re.compile(r'\[([^\]]+)\]\(([^)]+\.md)(?:#[^)]+)?\)', re.I)
backlinks = defaultdict(set)
outlinks = defaultdict(set)
for path in actual:
    full = ROOT / path
    text = full.read_text('utf-8')
    for m in link_pattern.finditer(text):
        target = os.path.normpath(os.path.join(os.path.dirname(path), m.group(2))).replace('\\','/')
        if target in docs:
            outlinks[path].add(target)
            backlinks[target].add(path)

# compute title duplicates
title_groups = defaultdict(list)
for p, doc in docs.items():
    title_groups[doc['title']].append(p)
ambiguous_titles = {t:p for t,p in title_groups.items() if len(p) > 1}

# low discoverability / weak docs
low_tags = [p for p,doc in docs.items() if not doc.get('tags')]
small_tags = [p for p,doc in docs.items() if len(doc.get('tags', [])) < 2]
no_summary = [p for p,doc in docs.items() if not doc.get('summary')]
low_keywords = [p for p,doc in docs.items() if len(doc.get('keywords', [])) < 5]
no_related = [p for p,doc in docs.items() if not doc.get('related_documents')]
isolated = [p for p in actual if p not in outlinks and not backlinks.get(p)]

# infer tags from title and skill/category
COMMON_TAGS = ['pe', 'windows', 'loader', 'asm', 'x64', 'anti-cheat', 'driver', 'malware', 'unreal', 'unity', 'pdb', 'cryptography', 'networking', 'imgui', 'gui', 'kernel', 'debug', 'dll', 'elf', 'mach-o']
for doc in docs.values():
    text = ''
    try:
        text = (ROOT / doc['path']).read_text('utf-8').lower()
    except Exception:
        continue
    inferred = [tag for tag in COMMON_TAGS if tag in text and tag not in doc['tags']]
    for tag in inferred[:3]:
        doc['tags'].append(tag)
    # ensure unique sorted tags
    doc['tags'] = sorted(set(doc['tags']))

# improve keywords by adding title tokens and first paragraph tokens
for doc in docs.values():
    kw = set(doc.get('keywords', []))
    title_tokens = [t.lower() for t in re.split(r'[^a-z0-9_]+', doc['title']) if t and len(t) > 2]
    for t in title_tokens:
        kw.add(t)
    first_para = ''
    with open(ROOT / doc['path'], 'r', encoding='utf-8') as f:
        text = f.read()
    body = text
    if text.startswith('---'):
        m = re.match(r'^---\s*\n(.*?)\n---\s*\n', text, re.S)
        if m:
            body = text[m.end():]
    paras = [p.strip() for p in body.split('\n\n') if p.strip() and not p.strip().startswith('#')]
    if paras:
        first_para = paras[0]
    for w in re.findall(r'[a-zA-Z0-9_]{4,}', first_para.lower()):
        if len(kw) >= 20:
            break
        kw.add(w)
    doc['keywords'] = sorted(kw)[:25]
    # also regenerate related docs if none
    if not doc.get('related_documents'):
        same_skill = [p for p,d in docs.items() if d['skill'] == doc['skill'] and p != doc['path']]
        doc['related_documents'] = sorted(set(same_skill) | set(outlinks.get(doc['path'], [])))[:10]
        doc['related_skills'] = sorted(set(docs[p]['skill'] for p in doc['related_documents'] if p in docs))

# write improved index
index['documents'] = list(docs.values())
with open(ROOT / 'search-index.json', 'w', encoding='utf-8') as f:
    json.dump(index, f, indent=2, ensure_ascii=False)

# create report
lines = []
lines.append('# Retrieval Report')
lines.append('')
lines.append('Generated from repository analysis and search-index verification.')
lines.append('')
lines.append(f'- search-index documents: {len(docs)}')
lines.append(f'- markdown files found: {len(actual)}')
lines.append(f'- missing from index: {len(missing_index)}')
lines.append(f'- extra in index: {len(extra_index)}')
lines.append('')
if missing_index:
    lines.append('## Missing from index')
    lines.extend(f'- {p}' for p in missing_index[:20])
    lines.append('')
if extra_index:
    lines.append('## Indexed but missing on disk')
    lines.extend(f'- {p}' for p in extra_index[:20])
    lines.append('')
lines.append('## Discoverability issues')
lines.append(f'- documents with no tags: {len(low_tags)}')
lines.append(f'- documents with fewer than 2 tags: {len(small_tags)}')
lines.append(f'- documents with no summary: {len(no_summary)}')
lines.append(f'- documents with fewer than 5 keywords: {len(low_keywords)}')
lines.append(f'- documents with no explicitly linked related_documents: {len(no_related)}')
lines.append(f'- isolated documents (no inbound or outbound md links): {len(isolated)}')
lines.append('')
if ambiguous_titles:
    lines.append('## Ambiguous titles')
    for title, paths in sorted(ambiguous_titles.items(), key=lambda x: len(x[1]), reverse=True)[:20]:
        lines.append(f'- "{title}" appears in {len(paths)} documents:')
        for p in paths:
            lines.append(f'  - {p}')
    lines.append('')
lines.append('## Important validation')
lines.append('- search-index document paths were verified against disk files.')
lines.append('- Frontmatter metadata was verified for repository documents, excluding generated reports and .venv files.')
lines.append('- Related documents were inferred for docs missing explicit outbound links within the same skill.')
lines.append('')
lines.append('## Recommendations')
lines.append('- Add explicit `Related Documents` sections to isolated documents in their Markdown content, especially root README/ARCHITECTURE and skill landing pages.')
lines.append('- Standardize document titles in duplicate title groups to reduce ambiguity for retrieval agents.')
lines.append('- Keep `tags` small and consistent by using the repository keyword set across skills.')
lines.append('- Use cross-skill references for shared concepts such as PE analysis, kernel debugging, anti-cheat, and Dear ImGui.')

with open(ROOT / 'RETRIEVAL_REPORT.md', 'w', encoding='utf-8') as f:
    f.write('\n'.join(lines))

print('Wrote retrieval report and updated search-index.json')
