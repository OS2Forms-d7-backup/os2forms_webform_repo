<?php
/**
 * The webform resource definition.
 *
 * @return array
 */

function _webform_node_export_resource_definition() {

  // Define the resources.
  $resources = array();

  // Get all the webform types.
  $types = webform_variable_get('webform_node_types');

  // Iterate through the webform types.
  foreach ($types as $type) {
    // Add the resource type.
    $resources[$type . '_node_export'] = array(
      'operations' => array(
        'retrieve' => array(
          'callback' => 'webform_node_export_service_get_resource',
          'args' => array(
            array(
              'name' => 'uuid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'string',
              'description' => 'The uuid of the node to get',
            ),
          ),
          'access callback' => 'webform_node_export_service_resource_access',
          'access arguments' => array('view', $type),
          'access arguments append' => TRUE,
        ),
        'create' => array(
          'file' => array('type' => 'inc', 'module' => 'webform_node_export_service', 'name' => 'resources/webform_node_export_resource'),
          'callback' => 'webform_node_export_service_resource_create',
          'args' => array(
            array(
              'name' => 'params',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'Node export params.',
              'type' => 'string',
              'default value' => array(),
            ),
           ),// args
          'access callback' => 'webform_node_export_service_resource_access',
          'access arguments' => array('create', $type),
          'access arguments append' => TRUE,
        ),// create
//        'update' => array(
//          'file' => array('type' => 'inc', 'module' => 'webform_node_export_service', 'name' => 'resources/webform_node_export_resource'),
//          'callback' => 'webform_node_export_service_resource_update',
//          'args' => array(
//            array(
//              'name' => 'uuid',
//              'optional' => FALSE,
//              'source' => array('path' => 0),
//              'type' => 'string',
//              'description' => 'The uuid of the node to get',
//            ),
//            array(
//              'name' => 'node',
//              'optional' => FALSE,
//              'source' => 'data',
//              'description' => 'The node data to update',
//              'type' => 'array',
//            ),
//          ),
//          'access callback' => 'webform_node_export_service_resource_access',
//          'access arguments' => array('update', $type),
//          'access arguments append' => TRUE,
//        ),
//        'delete' => array(
//          'file' => array('type' => 'inc', 'module' => 'webform_node_export_service', 'name' => 'resources/webform_node_export_resource'),
//          'callback' => 'webform_node_export_service_resource_delete',
//          'args' => array(
//            array(
//              'name' => 'uuid',
//              'optional' => FALSE,
//              'source' => array('path' => 0),
//              'type' => 'string',
//            ),
//          ),
//          'access callback' => 'webform_node_export_service_resource_access',
//          'access arguments' => array('delete', $type),
//          'access arguments append' => TRUE,
//        ),
        'index' => array(
          'file' => array('type' => 'inc', 'module' => 'webform_node_export_service', 'name' => 'resources/webform_node_export_resource'),
          'help' => t('Return all webforms.'),
          'callback' => '_webform_node_export_resource_index',
          'args' => array(
            array(
              'name' => 'page',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'The zero-based index of the page to get, defaults to 0.',
              'default value' => 0,
              'source' => array('param' => 'page'),
            ),
            array(
              'name' => 'fields',
              'optional' => TRUE,
              'type' => 'string',
              'description' => 'The fields to get.',
              'default value' => '*',
              'source' => array('param' => 'fields'),
            ),
            array(
              'name' => 'parameters',
              'optional' => TRUE,
              'type' => 'array',
              'description' => 'Parameters array',
              'default value' => array(),
              'source' => array('param' => 'parameters'),
            ),
            array(
              'name' => 'pagesize',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Number of records to get per page.',
              'default value' => variable_get('services_node_index_page_size', 20),
              'source' => array('param' => 'pagesize'),
            ),
            array(
              'name' => 'options',
              'optional' => TRUE,
              'type' => 'array',
              'description' => 'Additional query options.',
              'default value' => array(
                'orderby' => array(
                  'sticky' => 'DESC',
                  'created' => 'DESC'
                )
              ),
              'source' => array('param' => 'options'),
            ),
          ),
          'access arguments' => array('access content'),
        ),// index
      ),
    );
  }

  // Return the resources.
  return $resources;
}

/**
 * Creates a new webform based on submitted values.
 *
 * Note that this function uses drupal_execute() to create new nodes,
 * which may require very specific formatting. The full implications of this
 * are beyond the scope of this comment block. The Googles are your friend.
 *
 * @param $params
 *   Array or params:
 *     $params['node_export_data'] = Node export data in string (any format).
 * @return
 *   An associative array contained the new node's nid and, if applicable,
 *   the fully qualified URI to this resource.
 *
 * @see node_export_import()
 */
function webform_node_export_service_resource_create($params) {
  module_load_include('inc', 'services', 'resources/node_resource');

  $nid = NULL;

  // Prepare and create a new node.
  $import = node_export_import($params['node_export_data']);
  if ($import['success']) {
    // We expect only one node to be imported.
    $nid  = reset($import['nids']);
  }

  // Return the webform resource that was created.
  if ($nid) {
    return _node_resource_retrieve($nid);
  } else {
    return $import['output'];
  }
}

/**
 * Updates a new webform based on submitted values.
 *
 * Note that this function uses drupal_execute() to create new nodes,
 * which may require very specific formatting. The full implications of this
 * are beyond the scope of this comment block. The Googles are your friend.
 *
 * @param $uuid
 *   UUID of the webform we're editing.
 * @param $node
 *   Array representing the attributes a node edit form would submit.
 * @return
 *   The node's nid.
 *
 * @see drupal_execute()
 */
//function webform_node_export_service_resource_update($uuid, $webform) {
//
//  // Load the node if it exists.
//  if ($node = webform_node_export_service_resource_load($uuid)) {
//
//    // Now update any values.
//    webform_node_export_service_webform_prepare($webform, $node);
//
//    // Update the webform.
//    webform_node_update($node);
//
//    // Return the webform resource that was updated.
//    return webform_node_export_service_get_resource(node_load($node->nid, NULL, TRUE));
//  }
//  else {
//    return services_error(t('@uuid could not be found', array('@uuid' => $uuid)), 404);
//  }
//}

/**
 * Delete a node given its nid.
 *
 * @param $nid
 *   Node ID of the node we're deleting.
 * @return
 *   The node's nid.
 */
//function webform_node_export_service_resource_delete($uuid) {
//  if ($node = webform_node_export_service_resource_load($uuid)) {
//    node_delete($node->nid);
//    return TRUE;
//  }
//  else {
//    return services_error(t('@uuid could not be found', array('@uuid' => $uuid)), 404);
//  }
//}

/**
 * Return an array of optionally paged nids based on a set of criteria.
 *
 * An example request might look like
 *
 * http://domain/endpoint/node?fields=nid,vid&parameters[nid]=7&parameters[uid]=1
 *
 * This would return an array of objects with only nid and vid defined, where
 * nid = 7 and uid = 1.
 *
 * @param $page
 *   Page number of results to return (in pages of 20).
 * @param $fields
 *   The fields you want returned.
 * @param $parameters
 *   An array containing fields and values used to build a sql WHERE clause
 *   indicating items to retrieve.
 * @param $page_size
 *   Integer number of items to be returned.
 * @param $options
 *   Additional query options.
 * @return
 *   An array of node objects.
 *
 * @see _node_resource_index().
 */
function _webform_node_export_resource_index($page, $fields, $parameters, $page_size, $options = array()) {
  $node_select = db_select('node', 't');
  $node_select = $node_select->addTag('node_access');

  // Limiting to webform only.
  $parameters['type'] = 'webform';

  // Adding connection to os2forms_webform_repo_webforms.
  $node_select->leftJoin('os2forms_webform_repo_webforms', 'repo', 'repo.nid = t.nid');
  $node_select->fields('repo', array('readonly'));

  services_resource_build_index_query($node_select, $page, $fields, $parameters, $page_size, 'node', $options);

  if (!user_access('administer nodes')) {
    $node_select->condition('status', 1);
  }

  $results = services_resource_execute_index_query($node_select);

  return services_resource_build_index_list($results, 'node', 'nid');
}
