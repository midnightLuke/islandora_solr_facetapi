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
}
