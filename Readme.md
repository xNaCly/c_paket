# cpak 📦

[![tests](https://github.com/xNaCly/c_paket/actions/workflows/test.yml/badge.svg?branch=master)](https://github.com/xNaCly/c_paket/actions/workflows/test.yml)

Fast and efficient package manager for the c programming language

-   [Features](#features)
-   [FAQ](#faq)
    -   [What does cpak mean?](#what-does-cpak-mean)
    -   [Why should i use cpak](#why-should-i-use-cpak)
    -   [How do you handle modules?](#how-do-you-handle-modules)
    -   [How do i do x?](#how-do-i-do-x)
    -   [How do i contribute?](#how-do-i-contribute)
-   [Documentation](#documentation)
    -   [Prerequisites](#prerequisites)
    -   [Getting Started](#getting-started)
    -   [Building a Project with a Dependency](#building-a-project-with-a-dependency)
    -   [Commandline reference](#commandline-reference)
        -   [Version](#version)
        -   [Help](#help)
        -   [Config](#config)
        -   [Boostrap](#bootstrap)
        -   [Add](#add)
        -   [Remove](#remove)
        -   [Upgrade](#upgrade)
    -   [Global Configuration](#global-configuration)
        -   [Keys](#keys)
            -   [Colors](#colors)
            -   [StoreModulesGlobal](#storemodulesglobal)
        -   [Templates](#templates)

## Features:

-   managing modules
-   bootstraping projects with templates
-   global and linked or local dependencies
-   installing modules using their source from github using your already existing git configuration

## FAQ:

### What does 'cpak' mean?

Cpak is a composition of c and Paket [pa'keːt]. Paket is german and can be translated to Package, therefore cpak means
as much as C package.

### Why should I use 'cpak'?

Cpak is a source based package manager, therfore making it easy for the developer to manage packages for c projects, by allowing devs to store project dependencies
globally or inside a project. It also enables a templating/bootstraping toolkit. Cpak features a extensive
documentation and a very verbose logging system to warn the users of malformatted config files and several other
nuances.

### How do you handle modules?

Cpak installs modules globally, therefore all modules are either stored in `$CPAK_MODULE_HOME`, `$XDG_DATA_HOME/.cpak` or `$HOME/.cpak` and are soft linked to the
`cpak_modules` folder in the current cpak project. This has several positive effects on the developer experience:

-   decreases load on the file system by not storing multiple versions of code in multiple places
-   keeps dependencies up to date regardless of the project they are used in
-   makes dependency management easier for the developer

Cpak also allows the User to install packages in each project in the `cpak_modules` folder by changing [StoreModulesGlobal](#StoreModulesGlobal) to false in the config.

### How do I do 'x'?

Please take a look at the documentation laying out all features, arguments and possible error codes you would encounter on your daily use, global configuration as well
as project config files and how the templating toolkit works. If you can't find what your looking for, feel free to
create a new [Issue](https://github.com/xNaCly/c_paket/issues).

### How do I contribute?

Take a look at [Contributing](/CONTRIBUTING.md).

## Documentation:

### Prerequisites:
Cpak uses git to download and sync modules/repos/code, therefore a git executable is required for cpak to work.
Cpak assumes being using on a *nix like system with core utils installed, the following are required:
- mkdir
- ln
- unlink
- cp


### Getting started:

```sh
git clone https://github.com/xnacly/c_paket
cd c_paket
make install
cpak
```

This should print the following:

![image](https://user-images.githubusercontent.com/47723417/173002456-898113dd-3046-41c6-be02-15705de81e51.png)

### Building a project with a dependency
1. Create a new project 

```sh
mkdir project
cd project
```

2. Add a dependency to your project:

```sh
cpak add xnacly/libxutil
```

![image](https://user-images.githubusercontent.com/47723417/173005466-3d82a6fd-155e-47ea-94d7-8a24765a181c.png)



3. Create a C file:
```c
#include <stdio.h>
#include <stdlib.h>
#include "cpak_modules/libxutil/xstring.h"

int main(void){
    char *str1 = "Hello World";
    char *str2 = "Hello World";

    if(s_is_equal(str1, str2)){
        printf("String 'str1' and 'str2' are equal!\n");
    }

    return EXIT_SUCCESS;
}
```

4. Add the installed dependency to your build tool chain by passing the to the imported header file corresponding c source files in the module folder to the compiler like so:

```bash
gcc cpak_modules/libxutil/xstring.c ./main.c -o ./main.out
```

5. Run the Binary:
```bash
./main.out
```

```
$: String 'str1' and 'str2' are equal!
```

### Command line reference:

#### Version

```bash
cpak version
cpak v
```

Prints the version and exits

#### Help

```bash
cpak help
cpak h
cpak help <command>
cpak h <command>
```

Prints usage and help either for cpak or for a cpak command

#### Config

```bash
cpak config
cpak c
```

Generates the default config as well as the default template in `$CPAK_CONFIG_HOME` or `$XDG_CONFIG_HOME`.


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

Installs the specified module and links to its source in `$PWD/cpak_modules`

#### Remove

```bash
cpak remove <module>
cpak r <module>
```

Uninstalls the specified module and removes the link to its source from `$PWD/cpak_modules`

#### Upgrade

```bash
cpak upgrade <module>
cpak u <module>
```

Upgrades the specified module to the newest version


### Global configuration

The default config file can be found after first run in `$XDG_CONFIG_HOME/cpak`. This config currently includes the
following content:

![image](https://user-images.githubusercontent.com/47723417/173001784-246d2763-88b2-4dfa-8d3d-75aab5b90604.png)

#### Keys

##### Colors
This key specifies if cpaks logging and output should be colored.

`color=true / false`

##### StoreModulesGlobal
This key specifies if cpak should install modules globally or in the current directory.

`storeModulesGlobal=true / false`


#### Templates

To use templates and boostrap new project use the `cpak bootstrap <template_name>` command. Here, we use
`cpak b default`, this will create a new cpak project with the following file structure:

```
.
└── .gitignore
```

The contents of the bootstraped project is specified in `$XDG_CONFIG_HOME/cpak/templates/<template_name>`. To use custom
templates simply create a new folder with your template including files you want in your template. For reference view
the `default` template in the above mentioned directory.

### Error codes:

```
warning: <error_description>, err: <error_code>
error: <warning_description>, err: <error_code>
```
