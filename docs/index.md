# Documentation
- [Usage](./usage.md)
- [Errors](./errors.md)
- [Templating and project bootstrap documentation](./configuration.md)

## Indepth feature description:
### How cpak handles modules:
cpak installs modules globaly, therefore all modules are stored in `$XDG_CONTENT_HOME/cpak` and are softlinked to the `cpak_modules` folder in the current cpak project.
This has several positive effects on the developer experience:
- decrease load on the file system by not storing multiple versions of code in multiple places
- keep dependencies up to date regardless of the project they are used in
- make dependecy managment easier for the developer

### How cpak allows you to include modules in your project
> write here about installing and including modules and how to build them
