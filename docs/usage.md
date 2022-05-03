# Command line reference

## Commands:

### `init`
This command initalises a new cpak project, creates a `cpak_project.conf` file
### `boot <template>`
copies all the files specified in the `$XDG_CONFIG_HOME/cpak/templates/<template>` directory into the current dir.
### `install <module>`
installs the specifed module and links to its source in `$PWD/cpak_modules`
### `remove <module>`
uninstalls the specifed module and removes the link to its source from `$PWD/cpak_modules`
### `upgrade <module>`
tries to upgrade the specified module to the newest version
