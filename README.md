# LibreSkies

This repository is a lightweight starter to host the LibreSkies project on GitHub. It contains a short set of instructions for GitHub Copilot and contributors to follow the project's coding conventions.

See `COPILOT_INSTRUCTIONS.md` for the coding style rules Copilot (and contributors) should follow.

Quick start

- Initialize the repo (if you haven't already):
  - `git init`
  - `git add .`
  - `git commit -m "Initial commit: add README and Copilot instructions"`

Files added

- `COPILOT_INSTRUCTIONS.md` — explicit instructions for Copilot/code generation.
- `.gitignore` — minimal ignores for common artifacts.

Notes

- These files are intentionally minimal. If you want repository templates for specific languages (C#, TypeScript, Python), I can add language-specific editorconfig or linter configs to enforce these rules automatically.

Personal style preferences

- You can keep personal style preferences locally using a file named `.editorconfig.user`. This file is ignored by the repository and is intended for per-developer preferences (for example, a 40-character line limit). The project will use the committed `.editorconfig` as the shared baseline for repository-wide consistency.

- Important: When editing someone else's file, match that file's style. Do not apply your personal settings to files authored by others. The guidance in `COPILOT_INSTRUCTIONS.md` explains this policy in more detail.

Building the C++ starter (Vulkan/GLFW/GLM/EnTT)

Prerequisites

- CMake 3.16 or newer
- A C++20 capable compiler (MSVC, clang, gcc)
- (Recommended) Vulkan SDK installed if you plan to use Vulkan rendering
- Git

Build (general)

Open PowerShell in the repository root and run:

```powershell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

On success the example runner `LibreSkiesApp` will be produced in the build tree.

Notes

- The CMake configuration will attempt to find the system Vulkan SDK. If Vulkan is not found the example still builds and links GLFW and the header-only libraries (GLM, EnTT) so you can develop without Vulkan initially.
- For Windows Visual Studio generator, use the appropriate `-G` argument to `cmake` (for example `-G "Visual Studio 17 2022"`) or run the commands from a developer prompt.