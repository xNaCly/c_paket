# cpak 📦
fast and efficient package manager for the c programming language

## Features:
- managing modules
- bootstraping projects with templates 
- global/linked dependencies 

## Documentation:
### Getting started:

```sh
git clone https://github.com/xnacly/c_paket
cd c_paket
make all
cpak version
```
This should print the following:
```
debug: cpak-alpha-0.0.1
```

### Commandline reference:
#### Version
```bash
cpak version
cpak v
```
prints the version and exits
#### Help
```bash
cpak help
cpak h
cpak help <command>
cpak h <command>
```
prints usage and help either for cpak or for a cpak command
#### Init
```bash
cpak init
cpak i
```
This command initalises a new cpak project, creates a `cpak_project.conf` file
#### Bootstrap
```bash
cpak bootstrap <template>
cpak b <template>
```
copies all the files specified in the `$XDG_CONFIG_HOME/cpak/templates/<template>` directory into the current dir.
#### Add
```bash
cpak add <module>
cpak a <module>
```
installs the specifed module and links to its source in `$PWD/cpak_modules`
#### Remove
```bash
cpak remove <module>
cpak r <module>
```
uninstalls the specifed module and removes the link to its source from `$PWD/cpak_modules`
#### Upgrade
```bash
cpak upgrade <module>
cpak u <module>
```
upgrades the specified module to the newest version

### Global configuration
The default config file can be found after first run in `$XDG_CONFIG_HOME/cpak`. This config currently includes the following content:

```bash
# cpak global config

# specify if the output of cpak should be colored
colors=true

# specify if the installed modules should be stored globaly or locally
storeModulesGlobal=true
```

#### Templates
To use templates and boostrap new project use the `cpak bootstrap <template_name>` command, this will create a new cpak project with the following file structure:

```
.
├── main.c
└── Makefile
```

The contents of the bootstraped project is specifed in `$XDG_CONFIG_HOME/cpak/templates/<template_name>`.
To use custom templates simply create a new folder with your template including files you want in your template.
For reference view the `default` template in the above mentioned directory.

### Error codes:

```
warning: <error_description>, err: <error_code>
error: <warning_description>, err: <error_code>
```

#### Specific Errorcodes and their meaning:

[Link to Source](https://github.com/xNaCly/c_paket/blob/master/src/core/cpak_utils.h#L12-L30=);

```c
// Argument is unknown to cpak
UNKNOWN_ARGUMENT = 1437,
// not enough arguments passed to cpak 
NOT_ENOUGH_ARGUMENTS = 1438,
// cpak can't find your specifed template
TEMPLATE_MISSING = 1439,
// cpak can't find its config file
CONF_MISSING_CONFIG = 1440,
// cpak found an unknown key in its config file
CONF_UNKNOWN_KEY = 1441,
// cpak found an unknown value for a key in its config file
CONF_UNKNOWN_VALUE = 1442,
// cpak can't find a project config in the current directory
P_MISSING_CONFIG = 1443,
```

## FAQ:
### Why should I use 'cpak'?
Cpak makes it easy for the developer to manage packages for c projects, because it allows devs to store projects dependencies globally or inside a project.
It also enables a templating and boostraping toolkit. Cpak features a extensive documentation and a very verbose logging system to warn the users of: malformatted config files and several other nuances.

### How do you handle modules?
cpak installs modules globaly, therefore all modules are stored in `$XDG_CONTENT_HOME/cpak` and are softlinked to the `cpak_modules` folder in the current cpak project.
This has several positive effects on the developer experience:
- decrease load on the file system by not storing multiple versions of code in multiple places
- keep dependencies up to date regardless of the project they are used in
- make dependecy managment easier for the developer

### How do I do 'x'?
Please take a look at the documentation featuring possible error codes you could encounter, global as well as project config files and how the templating toolkit works.
If you can't find what your looking for, feel free to create a new [Issue](https://github.com/xNaCly/c_paket/issues).

### What does 'cpak' mean?
Cpak is a composition of c and Paket [pa'keːt]. Paket is german and can be translated to Package, therefore cpak means as much as C package.

### How do I contribute?
Take a look at [Contributing](/CONTRIBUTING.md).
