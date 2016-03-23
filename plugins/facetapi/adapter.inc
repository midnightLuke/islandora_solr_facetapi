<?php

/**
 * Facet API adapter for the Islandora SOLR module.
 */
class IslandoraSolrFacetapiAdapter extends FacetapiAdapter {

  public function searchExecuted() {
    global $_islandora_solr_queryclass;
    return islandora_solr_results_page($_islandora_solr_queryclass);
  }

  public function suppressOutput($realm_name) {
    return false;
  }

  /**
   * Hook that allows the backend to initialize its query object for faceting.
   *
   * @param mixed $query
   *   The backend's native object.
   */
  public function initActiveFilters($query) {
    $query->solrParams['fq'] = array();
    $enabled_facets = facetapi_get_enabled_facets($this->info['name']);
    if ($enabled_facets) {
      $query->solrParams['facet'] = 'true';
      $query->solrParams['facet.sort'] = 'count';
      $query->solrParams['facet.mincount'] = '1';
    }
  }

  /**
   * Returns the search keys.
   */
  public function getSearchKeys() {
    global $_islandora_solr_queryclass;
    return $_islandora_solr_queryclass->solrQuery;
  }

  /**
   * Returns the search path.
   *
   * @return string
   *   A string containing the search path.
   *
   * @todo D8 should provide an API function for this.
   */
  public function getSearchPath() {
    global $_islandora_solr_queryclass;

    if (empty($_islandora_solr_queryclass->solrQuery)) {
      return 'islandora/search';
    } else {
    return 'islandora/search/' . $_islandora_solr_queryclass->solrQuery;
    }
  }
}
