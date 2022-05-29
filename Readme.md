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
    -   [Getting Started](#getting-started)
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
        -   [Templates](#templates)
    -   [Error codes](#error-codes)
        -   [Specific Errorcodes and their meaning](#specific-errorcodes-and-their-meaning)

## Features:

-   managing modules
-   bootstraping projects with templates
-   global/linked dependencies

## FAQ:

### What does 'cpak' mean?

Cpak is a composition of c and Paket [pa'keːt]. Paket is german and can be translated to Package, therefore cpak means
as much as C package.

### Why should I use 'cpak'?

Cpak makes it easy for the developer to manage packages for c projects, by allowing devs to store project dependencies
globally or inside a project. It also enables a templating and bootstraping toolkit. Cpak features a extensive
documentation and a very verbose logging system to warn the users of malformatted config files and several other
nuances.

### How do you handle modules?

Cpak installs modules globally, therefore all modules are stored in `$XDG_CONTENT_HOME/cpak` and are soft linked to the
`cpak_modules` folder in the current cpak project. This has several positive effects on the developer experience:

-   decreases load on the file system by not storing multiple versions of code in multiple places
-   keeps dependencies up to date regardless of the project they are used in
-   makes dependency management easier for the developer

### How do I do 'x'?

Please take a look at the documentation featuring possible error codes you could encounter, global configuration as well
as project config files and how the templating toolkit works. If you can't find what your looking for, feel free to
create a new [Issue](https://github.com/xNaCly/c_paket/issues).

### How do I contribute?

Take a look at [Contributing](/CONTRIBUTING.md).

## Documentation:

### Getting started:

```sh
git clone https://github.com/xnacly/c_paket
cd c_paket
make install
cpak
```

This should print the following:
![image](https://user-images.githubusercontent.com/47723417/170288034-02689782-a955-427c-b697-8abf3f4e8cbb.png)

### Building a project with a dependency
1. Add a dependency to your project:

```sh
cpak add xnacly/xutils
```

2. Create a C file:
```c
#include <stdio.h>
#include <stdlib.h>
#include "../cpak_modules/xutils/xutil.h"

int main(void){
    char *str1 = "Hello World";
    char *str2 = "Hello World";

    if(s_is_equal(str1, str2)){
        printf("String 'str1' and 'str2' are equal!\n");
    }

    return EXIT_SUCCESS;
}
```

3. Add the installed dependency to your build tool chain by passing all c source files in the module folder to the compiler like so:
```bash
gcc cpak_modules/**.c ./main.c -o ./main.out
```
A better alternative is to specify only the included headers and sources by just passing it to the compiler:
```bash
gcc cpak_modules/xutils/xutil.c ./main.c -o ./main.out
```

> A better way of handling this is currently in development!


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

![image](https://user-images.githubusercontent.com/47723417/170292308-f04c81ee-459d-4d30-bde2-38016c98e8eb.png)

#### Keys

##### Colors
`color=true / false`

![image](https://user-images.githubusercontent.com/47723417/170291260-4af97de4-a9c8-4c5f-a593-2fa44bdb2522.png)




#### Templates

To use templates and boostrap new project use the `cpak bootstrap <template_name>` command. Here, we use
`cpak b default`, this will create a new cpak project with the following file structure:

```
.
├── main.c
└── Makefile
```

The contents of the bootstraped project is specified in `$XDG_CONFIG_HOME/cpak/templates/<template_name>`. To use custom
templates simply create a new folder with your template including files you want in your template. For reference view
the `default` template in the above mentioned directory.

### Error codes:

```
warning: <error_description>, err: <error_code>
error: <warning_description>, err: <error_code>
```

#### Specific Error codes and their meaning:

Do not expect this section to be up to date with the source code, if you want to view the current error codes take a look
at [core/cpak_utils.h]()

```c
// Argument is unknown to cpak
UNKNOWN_ARGUMENT = 1437,

// not enough arguments passed to cpak
NOT_ENOUGH_ARGUMENTS = 1438,

// cpak can't find your specifed template
TEMPLATE_MISSING = 1439,

// cpak can't find its config file
CONF_MISSING_CONFIG = 1440,

// cpak's config already exists
CONF_EXISTS = 1441,

// cpak found an unknown key in its config file
CONF_UNKNOWN_KEY = 1442,

// cpak found an unknown value for a key in its config file
CONF_UNKNOWN_VALUE = 1443,

// cpak can't find a project config in the current directory
P_MISSING_CONFIG = 1444,
```
