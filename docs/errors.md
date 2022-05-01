# Errors:
## Anatomy of an cpak error / warning:
### Error

```
warning: Project name is undefined!, err: 1444
warning: Project version is undefined!, err: 1445
error: Can't read or can't find config, err: 1443
```

## Specific Errorcodes and their meaning:
[Link to Source](https://github.com/xNaCly/c_paket/blob/master/src/core/c_p_util.h#L11);

```sh
P_MISSING_CONFIG = 1443,    # if the project has no config file (error)
P_MISSING_NAME = 1444,      # if the project config has no name (warning) 
P_MISSING_VERSION = 1445    # if the project has no version     (warning) 
```

