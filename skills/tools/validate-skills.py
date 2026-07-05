"""Validate skill JSON files against schemas in meta/schema/.
Simple validator that checks required keys exist.
"""
import json
import os

ROOT = os.path.join(os.path.dirname(__file__), '..')
META = os.path.join(ROOT, 'meta')
SCHEMA = os.path.join(META, 'schema')


def validate_skill(skill_obj):
    required = ['requires', 'provides']
    errors = []
    for r in required:
        if r not in skill_obj:
            errors.append(f"missing required key: {r}")
    return errors


if __name__ == '__main__':
    path = os.path.join(META, 'skills.json')
    if not os.path.exists(path):
        print('meta/skills.json not found')
        raise SystemExit(1)
    skills = json.load(open(path, 'r', encoding='utf-8'))
    ok = True
    for name, obj in skills.items():
        errs = validate_skill(obj)
        if errs:
            ok = False
            print(f"Skill {name} errors:")
            for e in errs:
                print(' -', e)
    if ok:
        print('All skills validated (basic checks).')
