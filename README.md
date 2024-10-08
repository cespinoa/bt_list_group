![](../../BootstrapToolbox.png)

# BOOTSTRAP TOOLBOX LIST GROUP 
## INTRODUCCÍON
El módulo Bootstrap Toolbox Block to Card forma parte de un conjunto de utilidades distribuidas con el módulo [Bootstrap Toolbox](../../README.md).

## CARACTERÍSTICAS

Este módulo contiene

Extiende el formateador label 
Proporciona un estilo de view 


This module provides a method for filtering modules on the modules page as well
as for filtering projects on the update status report.

The supplied filter is simpler than using your browsers find a feature which
searches the entire page. The provided filter will filter modules/projects that
do not meet your input.

Along with the filter textfield there are additional
checkboxes that help to narrow the search more. The modules page contains 3
checkboxes: Enabled, Disabled, and Unavailable. While the first two
are self-explanatory, the latter two can take an explanation. The Required
checkbox affects visibility of modules that are enabled and have other
module(s) that require it also enabled. The Unavailable checkbox affects
visibility of modules that are disabled and depend on module(s) that are
missing.

The update status report filter also contains four checkboxes: Up-to-Date,
Update available, Security update, and Unknown. These directly affect the
visibility of each project; whether it is up-to-date, there is an update
available, a security update is available, or the status is unknown.

For a full description of the module, visit the
[project page](https://www.drupal.org/project/module_filter).

Submit bug reports and feature suggestions, or track changes in the
[issue queue](https://www.drupal.org/project/issues/module_filter).

## Table of contents

- Requirements
- Installation
- Configuration
- Tabs
- Filter operators
- Maintainers

## Requirements

Since jQuery has been removed from Drupal 10 this module now requires [jquery_ui_autocomplete](https://www.drupal.org/project/jquery_ui_autocomplete)

## Installation

To install this module, do the following:

- Extract the tarball that you downloaded from Drupal.org.
- Upload the entire directory and all its contents to your modules directory.

## Configuration

To enable and configure this module do the following:

1. Go to Admin -> Modules, and enable Module Filter.
2. Go to Admin -> Configuration -> User interface -> Module filter, and make
   any necessary configuration changes.

## Tabs

By default Module Filter alters the modules page into tabs (Can be disabled on
configuration page). In the tabs view, each package is converted to a vertical
tab rather than a fieldset which greatly increases the ability to browse them.

There are several benefits to using the tabs view over the standard view for
the modules page. I've listed the key benefits below as well as additional
information that pertains to each.

- The increased ease of browsing between packages.

- Allows all modules to be listed alphabetically outside of their package,
  making it all the easier to find the module by name rather than package it
  happens to be in.

- The operations for a module are moved within the description column giving
  the description more "elbow room".

- Filtering is restricted to within the active tab or globally when no tab is
  selected. By default, no tab is selected which will list all modules. When a
  tab is active, and you want to get back to the 'all' state click on the
  active tab to deselect it.

- The number of enabled modules per tab is shown on the active tab. (Can be
  disabled on configuration page)

- Nice visual aids become available showing what modules are to be
  enabled/disabled and the number of matching modules in each tab when
  filtering. (Can be disabled on configuration page)

- The save configuration button becomes more accessible, either staying at
  the bottom of the window when the tabs exceed past the bottom and at the
  top when scrolling past the tabs. (Can be disabled on configuration page)

- When filtering, tabs that do not contain matches can be hidden. (Can be
  enabled on configuration page)

- Tab states are remembered like individual pages allowing you to move
  forward and backward within your selections via your browsers
  forward/backward buttons.

- When viewing all modules (no active tab) and mousing over modules it's tab
  becomes highlighted to signify which tab it belongs to.


## Filter operators

The modules page's filter has three filter operators available. Filter
operators allow alternative filtering techniques. A filter operator is applied
by typing within the filter textfield 'operator:' (where operator is the
operator type) followed immediately with the string to pass to the operator
function (e.g. 'requires:block'). The available operators are:

description:
Filter based on a module's description.

requiredBy:
Filter based on what a module is required by.

requires:
Filter based on what a module requires.

Multiple filters (or queries) can be applied by space delimiting. For example,
the filter string 'description:ctools views' would filter down to modules with
"ctools" in the description and "views" within the module's name. To pass a
space within a single query wrap it within double quotes (e.g. 'requires:"chaos
tools"' or '"bulk export"').

## Maintainers

[//]: # cSpell:disable
[//]: # Do not want to add these names, just ignore to the end of this file.
- greenSkin ([greenSkin](https://www.drupal.org/u/greenskin))
- Andrey Troeglazov ([andrey.troeglazov](https://www.drupal.org/u/andreytroeglazov))
- Stephen Mustgrave ([smustgrave](https://www.drupal.org/u/smustgrave))
