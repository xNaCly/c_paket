# Errors:

## Anatomy of an cpak error / warning:

### Error

```
warning: <error_description>, err: <error_code>
error: <warning_description>, err: <error_code>
```

## Specific Errorcodes and their meaning:

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

