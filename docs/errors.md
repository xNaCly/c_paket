# Errors:

## Anatomy of an cpak error / warning:

### Error

```
warning: <error_description>, err: <error_code>
error: <warning_description>, err: <error_code>
```

## Specific Errorcodes and their meaning:

[Link to Source](https://github.com/xNaCly/c_paket/blob/master/src/core/c_p_util.h#L11);

```c
TEMPLATE_MISSING = 1439,        // cpak can't find your specifed template
CONF_MISSING_CONFIG = 1440,     // cpak can't find its config file
CONF_UNKNOWN_KEY = 1441,        // cpak found an unknown key in its config file
CONF_UNKNOWN_VALUE = 1442,      // cpak found an unknown value for a key in its config file
P_MISSING_CONFIG = 1443,        // cpak can't find a project config in the current directory
P_MISSING_NAME = 1444,          // cpak can't find a name for your project in the project config
P_MISSING_VERSION = 1445,       // cpak can't find a version for your project in the project config
```

