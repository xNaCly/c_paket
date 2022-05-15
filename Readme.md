# cpak 📦
fast and efficient package manager for the c programming language

- [Features](#features)
- [FAQ](#faq)
  - [Why should i use cpak](#why-should-i-use-cpak)
  - [How do you handle modules?](#how-do-you-handle-modules)
  - [How do i do x?](#how-do-i-do-x)
  - [What does cpak mean?](#what-does-cpak-mean)
  - [How do i contribute?](#how-do-i-contribute)
- [Documentation](#documentation)
  - [Getting Started](#getting-started)
  - [Commandline reference](#commandline-reference)
    - [Version](#version)
    - [Help](#help)
    - [Init](#init)
    - [Boostrap](#bootstrap)
    - [Add](#add)
    - [Remove](#remove)
    - [Upgrade](#upgrade)
  - [Project config]()
  - [Global Configuration](#global-configuration)
    - [Templates](#templates)
  - [Error codes](#error-codes)
    - [Specific Errorcodes and their meaning](#specific-errorcodes-and-their-meaning)

## Features:
- managing modules
- bootstraping projects with templates 
- global/linked dependencies 

## FAQ:
### Why should I use 'cpak'?
Cpak makes it easy for the developer to manage packages for c projects, by allowing devs to store project dependencies globally or inside a project.
It also enables a templating and bootstraping toolkit. Cpak features a extensive documentation and a very verbose logging system to warn the users of malformatted config files and several other nuances.

### How do you handle modules?
cpak installs modules globaly, therefore all modules are stored in `$XDG_CONTENT_HOME/cpak` and are softlinked to the `cpak_modules` folder in the current cpak project.
This has several positive effects on the developer experience:

- decreases load on the file system by not storing multiple versions of code in multiple places
- keeps dependencies up to date regardless of the project they are used in
- makes dependecy managment easier for the developer

### How do I do 'x'?
Please take a look at the documentation featuring possible error codes you could encounter, global configuration as well as project config files and how the templating toolkit works.
If you can't find what your looking for, feel free to create a new [Issue](https://github.com/xNaCly/c_paket/issues).

### What does 'cpak' mean?
Cpak is a composition of c and Paket [pa'keːt]. Paket is german and can be translated to Package, therefore cpak means as much as C package.

### How do I contribute?
Take a look at [Contributing](/CONTRIBUTING.md).

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
info: cpak-alpha-0.0.1
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
Prints usage and help either for cpak or for a cpak command

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
Copies all the files specified in the `$XDG_CONFIG_HOME/cpak/templates/<template>` directory into the current dir.

#### Add
```bash
cpak add <module>
cpak a <module>
```
Installs the specifed module and links to its source in `$PWD/cpak_modules`

#### Remove
```bash
cpak remove <module>
cpak r <module>
```
Uninstalls the specifed module and removes the link to its source from `$PWD/cpak_modules`

#### Upgrade
```bash
cpak upgrade <module>
cpak u <module>
```
Upgrades the specified module to the newest version


### Project Config:
The project config is a file found in a directory after `cpak init` was ran in it.
The following shows a simple example what a `cpak_project.conf` file could look like:

```config
# cpak config file

# name of the project
name=example_app
# project description
description=a very simple program
# version of the project 
version=v0.0.1
# author of the project
author=https://github.com/xnacly
# dependencies, seperated by whitespace 
deps=xnacly/pgme xnacly/xc
```

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
To use templates and boostrap new project use the `cpak bootstrap <template_name>` command.
Here, we use `cpak b default`, this will create a new cpak project with the following file structure:

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

