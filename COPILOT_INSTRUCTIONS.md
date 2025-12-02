Copilot and Contributor Instructions — LibreSkies

Purpose

These instructions tell GitHub Copilot (and human contributors) the preferred coding style for this repository. Apply these rules in generated and edited code.

Primary rules

1) Use PascalCase
- Use PascalCase for all types, classes, methods, properties, and variables.
- Examples:
  - Class: `FlightController`
  - Method: `CalculateTrajectory`
  - Variable: `CurrentAltitude`

2) Opening braces on a new line (Allman style)
- Put the opening brace on the next line for types, methods, properties, and control blocks.
- Example shape:

  public class FlightPlanner
  
  {
      public void PlanFlight()
      
      {
          // implementation
      }
  }

3) Do not add comments
- Avoid adding comments in generated code. Prefer clear, self-explanatory names and small functions.
- If documentation is needed, add README or external docs rather than inline comments.

4) Do not abbreviate variable names
- Use full descriptive names. Avoid abbreviations or short names except for well-known constants (e.g., PI).
- Example: use `MaximumAllowedSpeed` instead of `maxSpd`.

Additional guidance

- Keep functions small and focused. If a function grows beyond a screenful, split it into smaller well-named helper functions.
- Prefer immutability where reasonable and avoid global state.

When uncertain

- If Copilot proposes code that doesn't follow these instructions, edit the suggestions to conform before accepting.
- If a proposed change improves readability while slightly deviating from these rules, discuss it in a PR and document the decision.

This file is the authoritative guidance for in-repository Copilot usage and contributor style. Update it by pull request if you want to evolve the rules.