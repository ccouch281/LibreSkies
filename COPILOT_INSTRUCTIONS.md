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

Contributor style policy

- New files: When creating a brand-new file, contributors may use their preferred coding style and formatting. This repository tolerates multiple personal styles for new files so long as code is readable and follows the project's high-level expectations (clear names, small functions, performance-conscious design).

- Editing existing files: When modifying an existing file, always follow that file's current style and formatting. Do not reformat or rename symbols to match your personal style in the same commit unless the change is part of a focused, separate style/format PR that clearly documents the scope and is approved by reviewers.

- Copilot behavior: If Copilot suggests code that reflects your personal style while you are editing someone else's file, edit the suggestion to match the file's style before accepting. For new files you create, you may accept suggestions that match your personal preferences.

User-specific preferences and working on other people's files

- Personal preferences: You may keep a local, personal editorconfig named `.editorconfig.user` in your working copy to store your personal formatting preferences (for example, a 40-character line limit). This file is intentionally ignored by the repository and should not be committed.

- When editing someone else's file: Always follow the existing file's style. Detect the file's style by checking the repository `.editorconfig`, the file contents (indentation, brace style, naming), or the project's established conventions. Do not reformat or rename to your personal preferences when modifying another contributor's file — keep changes minimal and style-consistent.

- Accepting Copilot suggestions: If Copilot suggests code that follows your personal `.editorconfig.user` but the file you're editing uses a different style, edit the suggestion to match the file's style before accepting.