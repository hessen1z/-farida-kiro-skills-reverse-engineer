"""Simple programmatic loader for the skill library.
Usage:
  from sdk.python import Library
  lib = Library(path_to_skills)
  lib.load('reverse-engineering')
"""
import json
import os

class Library:
    def __init__(self, root=None):
        self.root = root or os.path.join(os.path.dirname(__file__), '..', '..')
        self.meta = os.path.join(self.root, 'meta')
        self.skills = self._load_json('skills.json')
        self.dependencies = self._load_json('dependencies.json')

    def _load_json(self, name):
        p = os.path.join(self.meta, name)
        if os.path.exists(p):
            return json.load(open(p, 'r', encoding='utf-8'))
        return {}

    def load(self, skill_name):
        """Return skill metadata and recursively load prerequisites."""
        if skill_name not in self.skills:
            raise KeyError(f"Unknown skill: {skill_name}")
        order = self._resolve_order(skill_name)
        return {s: self.skills.get(s) for s in order}

    def _resolve_order(self, skill_name):
        seen = set()
        order = []
        def visit(s):
            if s in seen:
                return
            seen.add(s)
            for dep in self.dependencies.get(s, []):
                visit(dep)
            order.append(s)
        visit(skill_name)
        return order

    def find_pattern(self, pattern_name):
        patterns = self._load_json('patterns.json')
        return patterns.get(pattern_name)

if __name__ == '__main__':
    lib = Library()
    print('Available skills:', list(lib.skills.keys()))
