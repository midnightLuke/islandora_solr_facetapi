# Islandora SOLR Facet API

## Warning: Experimental Module

This module is very much an experiment and probably not in a production-ready
state, bugs and errors are likely.

## Introduction

Replaces the core Islandora facets with the Drupal [facet api](https://www.drupal.org/project/facetapi)
module facets.  These modules are handled in their own UI and are a little more
customizeable, but are wholly different than the Islandora facets.

## Requirements

- [Islandora](https://github.com/islandora/islandora)
- [Islandora SOLR Search](https://github.com/Islandora/islandora_solr_search)
- [Facet API](https://www.drupal.org/project/facetapi)

### Optional

- [Date Facets](https://www.drupal.org/project/date_facets) (for date range facets)

## Installation

Enable the module as usual and navigate to `admin/islandora/search/islandora_solr/facets`
to enable facet api facets.  After you have enabled some facets you will need to
place the facet blocks, they will then appear for searches.

## Configuration

There are a wealth of configuration options available to facet api facets, this
module should support most of them.

## Alternatives

The drupal [sarnia](https://www.drupal.org/project/sarnia) and
[search_api](https://www.drupal.org/project/search_api) modules provide a
powerful alternative to the core islandora solr module, which can then be 
combined with the [facetapi](https://www.drupal.org/project/facetapi) for almost
the exact same solution, however, this would require not using the islandora
solr modules at all.

## Maintainers/Sponsors

Current maintainer:

- [Luke Bainbridge](https://github.com/midnightluke)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
