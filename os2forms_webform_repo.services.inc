<?php
/**
 * @file
 * os2forms_webform_repo.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function os2forms_webform_repo_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'os2forms_webform_repo';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'os2forms_repo';
  $endpoint->authentication = array(
    'services_basic_auth' => 'services_basic_auth',
  );
  $endpoint->server_settings = array();
  $endpoint->resources = array(
    'user' => array(
      'operations' => array(
        'index' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'webform_node_export' => array(
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
        'create' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['os2forms_webform_repo'] = $endpoint;

  return $export;
}
