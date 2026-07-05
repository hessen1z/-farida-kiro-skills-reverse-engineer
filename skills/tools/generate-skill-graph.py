"""Generate an in-memory skill dependency graph from meta/ JSON files.
Produces a DAG printed as JSON to stdout; does not write persistent files.
"""
import json
import os
from collections import defaultdict, deque

ROOT = os.path.join(os.path.dirname(__file__), '..')
META = os.path.join(ROOT, 'meta')


def load_json(name):
    path = os.path.join(META, name)
    if not os.path.exists(path):
        return {}
    with open(path, 'r', encoding='utf-8') as f:
        return json.load(f)


def build_graph(skills, dependencies):
    graph = {k: set(v) for k, v in dependencies.items()} if dependencies else {}
    # ensure all skills present
    for k in skills.keys():
        graph.setdefault(k, set())
    return graph


if __name__ == '__main__':
    skills = load_json('skills.json')
    deps = load_json('dependencies.json')
    graph = build_graph(skills, deps)
    # detect cycles (simple)
    # Kahn's algorithm
    indeg = {k: 0 for k in graph}
    for k, outs in graph.items():
        for v in outs:
            indeg[v] = indeg.get(v, 0) + 1
    q = deque([k for k, d in indeg.items() if d == 0])
    order = []
    while q:
        n = q.popleft()
        order.append(n)
        for m in graph.get(n, []):
            indeg[m] -= 1
            if indeg[m] == 0:
                q.append(m)
    out = {'graph': {k: list(v) for k, v in graph.items()}, 'load_order': order}
    print(json.dumps(out, indent=2))
