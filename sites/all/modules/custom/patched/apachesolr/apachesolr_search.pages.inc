<?php

/**
 * @file
 *   Provides the page callback for user defined search pages.
 */

/**
 * Returns search results on user defined search pages.
 */
function apachesolr_search_custom_page($page_id, $keys = '', $path_replacer = NULL) {
  $search_page = apachesolr_search_page_load($page_id);
  if (empty($search_page)) {
    drupal_set_message(t('This search page cannot be found'), 'error');
    return drupal_not_found();
  }
  // Add our replacement value in the conditions array
  if (!empty($path_replacer)) {
    $search_page['settings']['apachesolr_search_path_replacer'] = $path_replacer;
  }
  // Replace dynamic path with current path
  $search_page['search_path'] = str_replace('%', $path_replacer, $search_page['search_path']);
  // Retrieve the conditions that apply to this page
  $conditions = apachesolr_search_conditions_default($search_page);
  // Retrieve the results of the search
  $results = apachesolr_search_search_results($keys, $conditions, $search_page);
  // Initiate our build array
  $build = array();
  // Add a custom search form if required
  if (!empty($search_page['settings']['apachesolr_search_search_box'])) {
    // Adds the search form to the page.
    $build['search_form'] = drupal_get_form('apachesolr_search_custom_page_search_form', $search_page, $keys);
  }
  // Build our page and allow modification.
  $build_results = apachesolr_search_search_page_custom($results, $search_page, $build);

  $build_output = NULL;
  foreach($build_results as $build_result) {
    $build_output .= $build_result;
  }
  return $build_output;
}

/**
 * Search for placed on user defined search pages.
 */
function apachesolr_search_custom_page_search_form(&$form_state, $search_page, $keys = '') {
  $form = array();
  // Loads the core Search CSS file, use the core search module's classes.
  drupal_add_css(drupal_get_path('module', 'search') . '/search.css');

  $form = array();
  $form['#id'] = 'search-form';
  //$form['#attributes']['class'][] = 'search-form';
  $form['#search_page'] = $search_page;

  $form['basic']['keys'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter terms'),
    '#default_value' => $keys,
    '#size' => 20,
    '#maxlength' => 255,
  );
  $form['basic']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  $form['basic']['get'] = array(
    '#type' => 'hidden',
    '#default_value' => json_encode(array_diff_key($_GET, array('q' => 1, 'page' => 1, 'solrsort' => 1, 'retain-filters' => 1))),
  );

  $fq = NULL;

  if (apachesolr_has_searched($search_page['env_id'])) {
    $query = apachesolr_current_query($search_page['env_id']);
    // We use the presence of filter query params as a flag for the retain filters checkbox.
    $fq = $query->getParam('fq');
  }

  if ($fq || !empty($form_state['post'])) {
    $form['basic']['retain-filters'] = array(
      '#type' => 'checkbox',
      '#title' => t('Retain current filters'),
      '#default_value' => (int) !empty($_GET['retain-filters']),
    );
  }

  return $form;
}

/**
 * Processes apachesolr_search_custom_page_search_form submissions.
 */
function apachesolr_search_custom_page_search_form_submit(&$form, &$form_state) {
  $search_page = $form['#search_page'];
  $redirect = $search_page['search_path'];
  if (strlen($form_state['values']['keys'])) {
    // Replace keys with their rawurlencoded value
    $keys = str_replace("/","%2f", $form_state['values']['keys']);
    $redirect .= '/' . $keys;
  }

  $get = array();
  if (isset($form_state['values']['get'])) {
    $get = json_decode($form_state['values']['get'], TRUE);
  }
  if (!empty($form_state['values']['retain-filters'])) {
    // Add our saved values
    $get['retain-filters'] = '1';
  }
  else {
    // Remove all filters
    if (!empty($search_page['settings']['apachesolr_search_allow_user_input'])) {
      unset($get['fq']);
    }
    if (module_exists('facetapi')) {
      unset($get['f']);
    }
  }

  // Add the query values into the redirect.
  $form_state['redirect'] = array($redirect, $get);
}