#!/usr/bin/env python3
import os, re, json, math
from datetime import date

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
SKIP_DIRS = {'.git', '.venv', '__pycache__', 'node_modules', 'cache'}
KEYWORDS = ['pe','windows','loader','asm','x64','anti-cheat','driver','malware','unreal','unity','pdb','cryptography','networking','imgui','gui','kernel','debug','driver','dll','pe','elf','mach-o']

index = []
files = []
for dirpath, dirnames, filenames in os.walk(ROOT):
    # filter out skip dirs
    dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS]
    for fn in filenames:
        if fn.lower().endswith('.md'):
            files.append(os.path.join(dirpath, fn))

for path in files:
    try:
        with open(path, 'r', encoding='utf-8') as f:
            text = f.read()
    except Exception:
        continue
    rel = os.path.relpath(path, ROOT).replace('\\','/')
    # detect frontmatter
    fm = {}
    m = re.match(r'^---\s*\n(.*?)\n---\s*\n', text, re.S)
    if m:
        body = text[m.end():]
        for line in m.group(1).splitlines():
            if ':' in line:
                k,v = line.split(':',1)
                fm[k.strip()] = v.strip()
    else:
        body = text
    # title
    title = fm.get('title')
    if not title:
        h = re.search(r'^#\s+(.+)$', text, re.M)
        if h:
            title = h.group(1).strip()
        else:
            title = os.path.splitext(os.path.basename(path))[0]
    # summary: first paragraph (non-heading)
    summary = ''
    for para in re.split(r"\n\s*\n", body.strip()):
        p = para.strip()
        if not p:
            continue
        if p.startswith('#') or p.startswith('---'):
            continue
        summary = re.sub(r'\s+', ' ', p)
        break
    # skill & category from rel path
    parts = rel.split('/')
    skill = parts[0] if len(parts) > 1 else 'root'
    category = parts[1] if len(parts) > 2 else (parts[0] if len(parts)>1 else '')
    # tags and keywords
    lowered = text.lower()
    tags = sorted({k for k in KEYWORDS if k in lowered})
    # collect headings as keywords
    headings = re.findall(r'^(?:##+|#)\s*(.+)$', text, re.M)
    keywords = []
    for h in headings:
        for w in re.split(r'[^a-zA-Z0-9_\-]+', h.lower()):
            if w and len(w) > 2 and w not in keywords:
                keywords.append(w)
    # related_documents: local .md links
    links = re.findall(r'\[[^\]]+\]\(([^)]+\.md)\)', text)
    related_documents = []
    related_skills = []
    for l in links:
        lnorm = l.split('#')[0]
        if lnorm.startswith('http'):
            continue
        lpath = os.path.normpath(os.path.join(os.path.dirname(rel), lnorm)).replace('\\','/')
        related_documents.append(lpath)
        lp = lpath.split('/')
        if len(lp) > 1:
            rs = lp[0]
            if rs not in related_skills:
                related_skills.append(rs)
    # difficulty
    diff = fm.get('difficulty')
    if not diff:
        if re.search(r'\b(beginner|introductory)\b', lowered):
            diff = 'beginner'
        elif re.search(r'\b(advanced|expert)\b', lowered):
            diff = 'advanced'
        else:
            diff = 'intermediate'
    # reading time
    words = len(re.findall(r'\w+', body))
    minutes = max(1, int(math.ceil(words / 200.0)))
    reading_time = f"{minutes} min"

    entry = {
        'title': title,
        'path': rel,
        'skill': skill,
        'category': category,
        'tags': tags,
        'keywords': keywords,
        'summary': summary,
        'related_skills': related_skills,
        'related_documents': related_documents,
        'difficulty': diff,
        'estimated_reading_time': reading_time,
    }
    index.append(entry)

# verify existence (already from filesystem)
out_index = {'generated': str(date.today()), 'count': len(index), 'documents': index}
with open(os.path.join(ROOT, 'search-index.json'), 'w', encoding='utf-8') as f:
    json.dump(out_index, f, indent=2, ensure_ascii=False)

# Write report
report_lines = []
report_lines.append(f"Search index generated: {out_index['generated']}")
report_lines.append(f"Document count: {out_index['count']}")
# top tags
from collections import Counter
all_tags = Counter(t for doc in index for t in doc['tags'])
report_lines.append('Top tags:')
for t,c in all_tags.most_common(20):
    report_lines.append(f"- {t}: {c}")
# missing summaries
missing_summary = sum(1 for d in index if not d['summary'])
report_lines.append(f"Documents missing summary: {missing_summary}")
# documents by skill
by_skill = Counter(d['skill'] for d in index)
report_lines.append('Documents per skill (top 20):')
for s,c in by_skill.most_common(20):
    report_lines.append(f"- {s}: {c}")

with open(os.path.join(ROOT, 'SEARCH_INDEX_REPORT.md'), 'w', encoding='utf-8') as f:
    f.write('\n'.join(report_lines))

print(f"Wrote search-index.json ({len(index)} documents) and SEARCH_INDEX_REPORT.md")
