# Configuration and Templating
## Configuration
The default config file can be found after first run in `$XDG_CONFIG_HOME/cpak`. This config currently includes the following content:

```bash
# cpak global config
# specify if the output of cpak should be colored
colors=true
# specify if the installed modules should be stored globaly or locally
storeModulesGlobal=true
```

The cpak throws warnings for the following cases:

- `warning: 'colors=testvalue' is not a known value for key: 'color', err: 1442`
- `warning: 'test' is not a known key value pair, err: 1441`
- `error: Can't read or find cpak config, err: 1440`

## Templates
To use templates and boostrap new project use the `cpak boot <template_name>` command, this will create a new cpak project with the following file structure:

```
.
├── main.c
└── Makefile
```

The contents of the bootstraped project is specifed in `$XDG_CONFIG_HOME/cpak/templates/<template_name>`.
To use custom templates simply create a new folder with your template including files you want in your template.
For reference view the `default` template in the above mentioned directory.
