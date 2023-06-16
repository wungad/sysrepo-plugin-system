<h1 align="center">
    Sysrepo Plugin System
</h1>

<p align="center">
    <a href="/../../commits/" title="Last Commit"><img src="https://img.shields.io/github/last-commit/telekom/sysrepo-plugin-system?style=flat"></a>
    <a href="/../../issues" title="Open Issues"><img src="https://img.shields.io/github/issues/telekom/sysrepo-plugin-system?style=flat"></a>
    <a href="./LICENSE" title="License"><img src="https://img.shields.io/badge/License-BSD%203--Clause-blue.svg?style=flat"></a>
</p>

<p align="center">
  <a href="#development">Development</a> •
  <a href="#documentation">Documentation</a> •
  <a href="#support-and-feedback">Support</a> •
  <a href="#how-to-contribute">Contribute</a> •
  <a href="#contributors">Contributors</a> •
  <a href="#licensing">Licensing</a>
</p>

The goal of this project is to provide a method of configuring generic Linux systems using the Sysrepo NETCONF server implementation. 
## About this component

This Sysrepo plugin is based on the `ietf-system` YANG module which provides "configuration and identification of some common system properties within a device containing a NETCONF server". More information about the specific YANG module can be found in [RFC 7317: A YANG Data Model for System Management](https://datatracker.ietf.org/doc/html/rfc7317).


## Development

Besides the usual C development environment, the following additional dependencies are required:

* libyang
* sysrepo
* [sysrepo-plugins-common library](https://github.com/telekom/sysrepo-plugins-common)
* [umgmt library](https://github.com/sartura/umgmt)

The following software is additionally required on the target system:

* systemd
* ntpd

### Branches
The project uses 2 main branches `main` and `devel`. Other branches should not be cloned. In `main` there are files of the last official release. Any latest improvements and changes, which were tested at least briefly are found in `devel`. On every new release, `devel` is merged into `main`.

This means that when only stable official releases are to be used, either `main` can be used or specific releases downloaded. If all the latest bugfixes should be applied, `devel` branch is the one to be used. Note that whenever a new issue is created and it occurs on the `main` branch, the first response will likely be to use `devel` before any further provided support. Also, when creating a **Pull Request**, the target branch should always be set to `devel`.

### Build

First clone the repository:

```
$ git clone https://github.com/telekom/sysrepo-plugin-system
$ git submodule init
$ git submodule update
```

Next, create a build directory and generate the build recipes using CMake:

```
$ mkdir build
$ cd build
$ cmake ..
```

If systemd is present on the system an additional cmake flag is required:
```
$ mkdir build
$ cd build
$ cmake -DSYSTEMD_IFINDEX=1 ..
```
note: SYSTEMD_IFINDEX cmake flag is the index of the interface you wish to configure DNS on (to get a list of indexes for all interfaces, use: `ip link`)

If augeas/augyang configuration is needed (only supported for `ntp` container and the `hostname` leaf node), the augeas specific plugin can be built by providing the CMake option:
```
$ mkdir build
$ cd build
$ cmake -DSYSTEMD_IFINDEX=1 -DENABLE_AUGEAS_PLUGIN=ON ..
```

After configuring the build process with CMake, run the make command to build the plugin:
```
$ make -j
```

### Build artifacts

Plugin will be built as a standalone application and also as a `sysrepo-plugind` module. For example, for the main ietf-system plugin there are two build artifacts:
- **ietf-system-plugin**: standalone application
- **libsrplg-ietf-system.so**: `sysrepo-plugind` module which exposes the plugin init and cleanup callbacks and can be installed by invoking the following command: `sysrepo-plugind -P libsrplg-ietf-system.so`

### Sysrepo/YANG requirements

The plugin requires the `iana-crypt-hash` and `ietf-system` YANG modules to be loaded into the Sysrepo datastore. This can be achieved by invoking the following commands:

```
$ sysrepoctl -i ../yang/iana-crypt-hash@2014-08-06.yang
$ sysrepoctl -i ../yang/ietf-system@2014-08-06.yang
```

The plugin also requires some features from `ietf-system` YANG module to be enabled. This can be achieved by invoking the following commands:

```
$ sysrepoctl --change ietf-system --enable-feature timezone-name
$ sysrepoctl --change ietf-system --enable-feature ntp
$ sysrepoctl --change ietf-system --enable-feature authentication
$ sysrepoctl --change ietf-system --enable-feature local-users
```

## Code of Conduct

This project has adopted the [Contributor Covenant](https://www.contributor-covenant.org/) in version 2.0 as our code of conduct. Please see the details in our [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md). All contributors must abide by the code of conduct.

## Working Language

We decided to apply _English_ as the primary project language.

Consequently, all content will be made available primarily in English. We also ask all interested people to use English as language to create issues, in their code (comments, documentation etc.) and when you send requests to us. The application itself and all end-user facing content will be made available in other languages as needed.

## Documentation

The full documentation for the Sysrepo system plugin can be found in the [documentation directory](../docs).

## Support and Feedback

The following channels are available for discussions, feedback, and support requests:

| Type               | Channel                                                                                                                                                                                            |
| ------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Issues**         | <a href="/../../issues/new/choose" title="General Discussion"><img src="https://img.shields.io/github/issues/telekom/sysrepo-plugin-system?style=flat-square"></a> </a>                            |
| **Other Requests** | <a href="mailto:opensource@telekom.de" title="Email Open Source Team"><img src="https://img.shields.io/badge/email-Open%20Source%20Team-green?logo=mail.ru&style=flat-square&logoColor=white"></a> |

## How to Contribute

Contribution and feedback is encouraged and always welcome. For more information about how to contribute, the project structure, as well as additional contribution information, see our [Contribution Guidelines](./CONTRIBUTING.md). By participating in this project, you agree to abide by its [Code of Conduct](./CODE_OF_CONDUCT.md) at all times.

## Contributors

Our commitment to open source means that we are enabling -in fact encouraging- all interested parties to contribute and become part of its developer community.

## Licensing

Copyright (C) 2021 Deutsche Telekom AG.

Licensed under the **BSD 3-Clause License** (the "License"); you may not use this file except in compliance with the License.

You may obtain a copy of the License by reviewing the file [LICENSE](./LICENSE) in the repository.

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the [LICENSE](./LICENSE) for the specific language governing permissions and limitations under the License.