# Contributing
## Principle & Contribution standard:
- Use only standard lib methods shipped with the language
- Write readable, correct and simple code (**K**eep **I**t **S**imple and **S**tupid)
- Comment incomprehensible code
- Comply with the Conventional Commit Messages [Standard](https://www.conventionalcommits.org/en/v1.0.0/) (in commits and pr's)
- Avoid merge commits (use rebase merging)

## Contribution Guide:

1. [Create an issue](https://github.com/xnacly/c_paket/issues/new) for the
   bug you want to fix or the feature that you want to add.
2. Create your own [fork](https://github.com/xnacly/c_paket) on GitHub, then
   checkout your fork.
3. Write your code in your local copy. It's good practice to create a branch for
   each new issue you work on, although not compulsory.
4. To run the test suite:
   - `make build` to check if cpak still compiles
   - `make run/t_unit` for unit tests
   - `make run/t_cli` for testing cli commands.
5. If the tests pass, you can commit your changes to your fork and then create
   a pull request from there. Make sure to reference your issue from the pull
   request comments by including the issue number e.g. `#123`.
