import json, pathlib, re
root = pathlib.Path(r'c:/Users/hshs/.kiro/skills')
search = root / 'search-index.json'
print('search-index exists', search.exists())
if search.exists():
    data = json.loads(search.read_text('utf-8'))
    print('count', data.get('count'))
md_files = list(root.rglob('*.md'))
print('md count', len(md_files))
missing = []
for p in md_files:
    text = p.read_text('utf-8')
    if not text.lstrip().startswith('---'):
        missing.append(str(p.relative_to(root)).replace('\\','/'))
print('missing fm', len(missing))
print('sample missing', missing[:10])
field_counts = {'title':0,'skill':0,'category':0,'difficulty':0,'tags':0,'updated':0}
for p in md_files:
    text = p.read_text('utf-8')
    if text.lstrip().startswith('---'):
        m = re.match(r'^---\s*\n(.*?)\n---\s*\n', text, re.S)
        if m:
            for line in m.group(1).splitlines():
                if ':' in line:
                    k = line.split(':',1)[0].strip()
                    if k in field_counts:
                        field_counts[k] += 1
print(field_counts)
