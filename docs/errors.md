# Errors:
## Anatomy of an cpak error / warning:
### Error

```
warning: <error_description>, err: <error_code>
error: <warning_description>, err: <error_code>
```

## Specific Errorcodes and their meaning:
[Link to Source](https://github.com/xNaCly/c_paket/blob/master/src/core/c_p_util.h#L11);

```conf
CONF_MISSING_CONFIG=1440,   # cpak cant find the config
CONF_UNKNOWN_KEY=1441,      # a key in the config is unknown
CONF_UNKNOWN_VALUE=1442,    # a value in the conig is unknown
P_MISSING_CONFIG = 1443,    # cpak cant find the project config
P_MISSING_NAME = 1444,      # project name undefined in project config
P_MISSING_VERSION = 1445,   # project version is undefined in project config
```

