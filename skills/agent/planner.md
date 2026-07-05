Planner

Purpose: Teach the agent how to construct plans from workflows and skills.

Key steps
1. Load `meta/workflows.json` to find matching workflow templates.
2. Translate workflow steps into skill load and action items.
3. Estimate verification costs and expected information gain per step.
4. Produce a prioritized plan with clear verification actions, timelines, and rollbacks.

Output
- A JSON plan with steps, required skills, verification actions, and expected evidence gains.
