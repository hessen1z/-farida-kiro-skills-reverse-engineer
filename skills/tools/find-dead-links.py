"""Scan markdown files for links that point to missing files referenced in meta/knowledge-index.json.
"""
import json
import os

ROOT = os.path.join(os.path.dirname(__file__), '..')
META = os.path.join(ROOT, 'meta')

if __name__ == '__main__':
    ki = os.path.join(META, 'knowledge-index.json')
    if not os.path.exists(ki):
        print('meta/knowledge-index.json not found')
        raise SystemExit(1)
    idx = json.load(open(ki, 'r', encoding='utf-8'))
    missing = []
    for key, v in idx.items():
        p = os.path.join(ROOT, v.get('path', ''))
        if not os.path.exists(p):
            missing.append((key, v.get('path')))
    if missing:
        print('Missing knowledge files:')
        for k, p in missing:
            print(' -', k, '->', p)
    else:
        print('No missing knowledge files found.')
