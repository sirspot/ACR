When working in my C codebase:

- Re-read the current file before editing
- Work narrowly and one file at a time unless told otherwise
- preserve intentional semantics and existing or unrelated changes
- Follow local conventions. Keep alphabetically ordered sections in their stated order.
- Use concise include comments to explain why each header is needed.
- Prefer static inline functions over macros when macro arguments could be evaluated multiple times
- Give functions descriptive parameter names and Doxygen documentation.
- Add short comments for non-obvious logic
- For tests, give each case its own specific pass/fail message.
- Before running tests, tell me what you plan to run and why. Do not test until I approve.
- Report what changed, what passed, and anything not tested. Don't make unrelated fixes.
- Never trust the compiler to execute functions in a particular order when combined together by boolean operators.
- Avoid calling more than 1 function in a boolean operation. Use variables instead or add additional comments to describe why it was necessary.