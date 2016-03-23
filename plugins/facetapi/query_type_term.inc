<?php

/**
 * @file
 * Term query type plugin for the Apache Solr adapter.
 */

/**
 * Plugin for "term" query types.
 */
class IslandoraSolrFacetapiTerm extends FacetapiQueryType implements FacetapiQueryTypeInterface {

  /**
   * Returns the query type associated with the plugin.
   *
   * @return string
   *   The query type.
   */
  static public function getType() {
    return 'term';
  }

  /**
   * Alters the backend's native query object to execute the facet query.
   *
   * As an example, modules that integrate with Apache Solr will set the
   * necessary params for faceting, whereas modules that extend the core Search
   * module will add SQL joins, filter clauses, and COUNT queries in order to
   * implement faceting.
   *
   * @param mixed $query
   *   The backend's native query object.
   */
  public function execute($query) {
    $settings = $this->adapter->getFacet($this->facet)->getSettings();
    $operator = $settings->settings['operator'];
    $ex = (FACETAPI_OPERATOR_OR != $operator) ? '' : "{!ex={$this->facet['field']}}";
    $query->solrParams['facet.field'][] = $ex . $this->facet['field'];

    if (!empty($settings->settings['facet_missing'])) {
      $query->solrParams['f.' . $this->facet['field'] . '.facet.missing'] = 'true';
    }
    // Adds "hard limit" parameter to prevent too many return values.
    $limit = empty($settings->settings['hard_limit']) ? 20 : (int) $settings->settings['hard_limit'];
    $query->solrParams['f.' . $this->facet['field'] . '.facet.limit'] = $limit;

    // Adds "facet mincount" parameter to limit the number of facets.
    if (isset($settings->settings['facet_mincount'])) {
      $count = $settings->settings['facet_mincount'];
      $query->solrParams['f.' . $this->facet['field'] . '.facet.mincount'] = $count;
    }

    $active = $this->adapter->getActiveItems($this->facet);

    // Adds filter based on the operator.
    if (FACETAPI_OPERATOR_OR != $operator) {
      foreach ($active as $value => $item) {
        // Handle facet missing:
        if ($value === '_empty_' && !empty($settings->settings['facet_missing'])) {
          $query->solrParams['fq'][] = $this->facet['field'] . ':' . '[* TO *]';
        }
        elseif (strlen($value)) {
          $query->solrParams['fq'][] = $this->facet['field'] . ':' . $value;
        }
      }
    }
    else {
      // OR facet.
      $local = "{!tag={$this->facet['field']}}";
      $values = array_keys($active);
      if ($values) {
        // Quote any values that have white space or colons.
        foreach ($values as &$v) {
          if (preg_match('/[:\s]/', $v) || strlen($v) == 0) {
            $v = '"' . $v . '"';
          }
        }
        $query->solrParams['fq'][] = $local . $this->facet['field'] . ':' . '(' . implode(' OR ', $values) . ')';
      }
    }
  }

  /**
   * Initializes the facet's build array.
   *
   * @return array
   *   The initialized render array.
   */
  public function build() {
    global $_islandora_solr_queryclass;

    $build = array();
    if ($response = $_islandora_solr_queryclass->islandoraSolrResult) {
      $settings = $this->adapter->getFacet($this->facet)->getSettings();
      if (isset($response['facet_counts']['facet_fields'][$this->facet['field']])) {
        $values = $response['facet_counts']['facet_fields'][$this->facet['field']];
        foreach ($values as $value => $count) {
          // Facet missing may return 0 even if mincount is 1.
          if (empty($settings->settings['facet_mincount']) || $count) {
            $build[$value] = array('#count' => $count);
          }
        }
      }
    }
    return $build;
  }

}
