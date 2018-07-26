<?php

/**
 * Inserts or updates webform settings.
 *
 * @param $nid
 * @param $readonly
 */
function os2forms_webform_repo_insert_update_webform_settings($nid, $readonly) {
  $result = os2forms_webform_repo_get_webform_settings($nid);

  if (!empty($result)) {
    db_update('os2forms_webform_repo_webforms')
      ->fields(array('readonly' => $readonly))
      ->condition('nid', $nid)
      ->execute();
  }
  else {
    db_insert('os2forms_webform_repo_webforms')
      ->fields(array(
        'nid' => $nid,
        'readonly' => $readonly
      ))
      ->execute();
  }
}

/**
 * Fetches webform settings.
 *
 * @param $nid
 *
 * @return mixed
 */
function os2forms_webform_repo_get_webform_settings($nid) {
  $result = db_select('os2forms_webform_repo_webforms', 'f')
    ->fields('f')
    ->condition('nid', $nid)
    ->execute()
    ->fetchAll();

  if (!empty($result) && is_array($result)) {
    return reset($result);
  }
}