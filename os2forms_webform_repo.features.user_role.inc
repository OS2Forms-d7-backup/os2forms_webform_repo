<?php
/**
 * @file
 * os2forms_webform_repo.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function os2forms_webform_repo_user_default_roles() {
  $roles = array();

  // Exported role: OS2Forms webform repo user.
  $roles['OS2Forms webform repo user'] = array(
    'name' => 'OS2Forms webform repo user',
    'weight' => 3,
  );

  return $roles;
}
