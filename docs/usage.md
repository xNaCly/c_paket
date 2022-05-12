# Command line reference

## Commands:

### `init` / `i`
This command initalises a new cpak project, creates a `cpak_project.conf` file
### `bootstrap <template>` / `b <template>`
copies all the files specified in the `$XDG_CONFIG_HOME/cpak/templates/<template>` directory into the current dir.
### `install <module>` / `i <module>`
installs the specifed module and links to its source in `$PWD/cpak_modules`
### `remove <module>` / `r <module>`
uninstalls the specifed module and removes the link to its source from `$PWD/cpak_modules`
### `upgrade <module>` / `u <module>`
tries to upgrade the specified module to the newest version
