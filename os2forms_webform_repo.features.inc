<?php
/**
 * @file
 * os2forms_webform_repo.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2forms_webform_repo_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
