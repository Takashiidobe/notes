# Mise

Mise is a package manager that's backwards compatible with asdf.

You can use it to install versions of many popular programming
languages.

## Usage

List all available plugins:

    mise plugins list-all

Install a plugin:

    mise plugins add name

List runtime versions available for install:

    mise ls-remote name

Install a specific version of a package:

    mise install name@version

Set global version for a package:

    mise use --global name@version

Set local version for a package:

    mise use name@version

Set environment variable in configuration:

    mise set variable=value
