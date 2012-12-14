<?php

/**
 * A handler to provide a field that is constructed by the administrator using PHP.
 *
 * @ingroup views_field_handlers
 */
class project_tag_handler_field extends views_handler_field {

  /**
   * Implements views_object#option_definition().
   *
   * @todo: Choose the terms field.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['project_tag_field'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Implements views_handler#options_form().
   */
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);


    $form['project_tag_field']['#type'] = 'select';
    $form['project_tag_field']['#title'] = t('Source field');
    $form['project_tag_field']['#description'] = t('Choose the source tags field to use.');
    foreach ($this->view->display_handler->get_handlers('field') as $field => $handler) {
      // Not self!
      if ($field == $this->field) {
        continue;
      }

      $title = (empty($handler->options['ui_name']))
        ? t('@group: @title', array('@group' => $handler->definition['group'], '@title' => $handler->definition['title']))
        : $handler->options['ui_name'];
      $form['project_tag_field']['#options'][$handler->handler_type . '_' . $field] = check_plain($title);
    }
    $form['project_tag_field']['#required'] = TRUE;
    $form['project_tag_field']['#default_value'] = $this->options['project_tag_field'];
  }

  /**
   * Implements views_handler_field#query().
   *
   * @see views_php_views_pre_execute()
   */
  function query() {
    // Provide a field alias but don't actually alter the query.
    $this->field_alias = 'project_tag_' . $this->position;
  }

  /**
   * Implements views_handler_field#render().
   */
  function render($values) {
    $value = NULL;
    if (!empty($this->options['project_tag_field'])) {
      $tags = explode('+', $this->view->args[0]);
      $project = $tags[1];

      if (!empty($project)) {
        foreach ($values->{$this->options['project_tag_field']} as $tag) {
          if ($tag['raw']['tid'] == $project) {
            $value = check_plain($tag['rendered']['#markup']);
          }
        }
      }
    }
    return $value;
  }
}
