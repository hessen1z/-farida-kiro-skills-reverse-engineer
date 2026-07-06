#!/usr/bin/env python3
import os, re
from datetime import date

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
SKIP_DIRS = {'.git', '.venv', '__pycache__', 'node_modules', 'cache'}
KEYWORDS = ['pe','windows','loader','asm','x64','anti-cheat','driver','malware','unreal','unity','pdb','cryptography','networking','imgui','gui','kernel','debug','dll','elf','mach-o']

modified = []
for dirpath, dirnames, filenames in os.walk(ROOT):
    dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS]
    for fn in filenames:
        if not fn.lower().endswith('.md'):
            continue
        path = os.path.join(dirpath, fn)
        with open(path, 'r', encoding='utf-8') as f:
            text = f.read()
        if text.lstrip().startswith('---'):
            continue
        # extract title
        title = None
        m = re.search(r'^#\s+(.+)$', text, re.M)
        if m:
            title = m.group(1).strip()
        else:
            title = os.path.splitext(fn)[0]
        rel = os.path.relpath(path, ROOT).replace('\\','/')
        parts = rel.split('/')
        skill = parts[0] if len(parts) > 1 else 'root'
        category = parts[1] if len(parts) > 2 else ''
        lowered = text.lower()
        tags = [k for k in KEYWORDS if k in lowered]
        # difficulty inference
        if re.search(r'\b(beginner|introductory)\b', lowered):
            diff = 'beginner'
        elif re.search(r'\b(advanced|expert)\b', lowered):
            diff = 'advanced'
        else:
            diff = 'intermediate'
        fm = {
            'title': title,
            'skill': skill,
            'category': category,
            'difficulty': diff,
            'tags': tags,
            'updated': str(date.today())
        }
        # build YAML frontmatter
        try:
            import yaml
            fm_text = '---\n' + yaml.dump(fm, default_flow_style=False, sort_keys=False) + '---\n\n'
        except Exception:
            # fallback simple YAML
            lines = ['---']
            for k,v in fm.items():
                if isinstance(v, list):
                    lines.append(f"{k}: [{', '.join(v)}]")
                else:
                    lines.append(f"{k}: {v}")
            lines.append('---\n')
            fm_text = '\n'.join(lines)
        new_text = fm_text + text
        with open(path, 'w', encoding='utf-8') as f:
            f.write(new_text)
        modified.append(rel)

# write report
rep = os.path.join(ROOT, 'METADATA_REPORT.md')
with open(rep, 'w', encoding='utf-8') as f:
    f.write(f"Added frontmatter to {len(modified)} documents\n\n")
    for p in modified:
        f.write(f"- {p}\n")
print(f"Wrote METADATA_REPORT.md (modified {len(modified)})")
