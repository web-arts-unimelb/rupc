<?php
/**
 * @file
 */

/**
 * Implements hook_views_data().
 */
function project_tag_views_data() {
  $data['views']['project_tag'] = array(
    'title' => t('Project Tag'),
    'group' => t('Faculty of Arts'),
    'help' => t('Project tag for use in project links.'),
    'field' => array(
      'help' => t('Create a project tag for use in links.'),
      'handler' => 'project_tag_handler_field',
    ),
  );
  return $data;
}
