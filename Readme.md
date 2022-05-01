# c_paket 📦
fast and efficient package manager for the c programming language

## Features:
- install and remove modules from projects
- linked dependencies from `$XDG_CONTENT_DIR/c_paket`, thus no duplicate modules
- bootstraping projects with configurations stored in `$XDG_CONFIG_HOME/c_paket` (Makefiles, .gitignores)

## Links:
- [Documentation](./docs/index.md)
- [Commandline argument documentation](./docs/usage.md)
- [Templating and project bootstrap documentation](./docs/project.md)

## Getting started:

```sh
git clone https://github.com/xnacly/c_paket
cd c_paket
make install
cpak --version
```

This should print the following:

```
cpak, c_paket - v0.0.1
```

