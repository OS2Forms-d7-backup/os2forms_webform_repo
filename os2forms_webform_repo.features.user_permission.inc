<?php
/**
 * @file
 * os2forms_webform_repo.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function os2forms_webform_repo_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'OS2Forms webform repo user' => 'OS2Forms webform repo user',
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'OS2Forms webform repo user' => 'OS2Forms webform repo user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'export nodes'.
  $permissions['export nodes'] = array(
    'name' => 'export nodes',
    'roles' => array(
      'OS2Forms webform repo user' => 'OS2Forms webform repo user',
      'administrator' => 'administrator',
    ),
    'module' => 'node_export',
  );

  // Exported permission: 'use PHP to import nodes'.
  $permissions['use PHP to import nodes'] = array(
    'name' => 'use PHP to import nodes',
    'roles' => array(
      'OS2Forms webform repo user' => 'OS2Forms webform repo user',
      'administrator' => 'administrator',
    ),
    'module' => 'node_export',
  );

  return $permissions;
}
