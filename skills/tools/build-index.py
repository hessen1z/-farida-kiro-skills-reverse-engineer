"""Build combined indexes by reading meta/*.json and emitting a merged summary to stdout.
"""
import json
import os

ROOT = os.path.join(os.path.dirname(__file__), '..')
META = os.path.join(ROOT, 'meta')


def load(name):
    p = os.path.join(META, name)
    if os.path.exists(p):
        return json.load(open(p, 'r', encoding='utf-8'))
    return {}

if __name__ == '__main__':
    out = {
        'skills': load('skills.json'),
        'workflows': load('workflows.json'),
        'patterns': load('patterns.json'),
        'examples': load('examples.json')
    }
    print(json.dumps(out, indent=2))
