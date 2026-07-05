"""Find duplicate entries in meta JSON files (e.g., duplicate example entries).
"""
import json
import os
from collections import Counter

ROOT = os.path.join(os.path.dirname(__file__), '..')
META = os.path.join(ROOT, 'meta')

if __name__ == '__main__':
    examples = json.load(open(os.path.join(META, 'examples.json'), 'r', encoding='utf-8'))
    paths = [v.get('path') for v in examples.values()]
    dup = [p for p, c in Counter(paths).items() if c > 1]
    if dup:
        print('Duplicate example paths:')
        for d in dup:
            print(' -', d)
    else:
        print('No duplicate examples found.')
