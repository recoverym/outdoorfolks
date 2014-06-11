<?php

/**
 * @file
 * CTools wizard implementation.
 */

/**
 * Registration wizard callback.
 */
function step_wizard($step = STEP_REGISTER) {
  ctools_include('wizard');
  ctools_include('object-cache');

  $form_info = array(
    'id' => 'step',
    'path' => 'user/register/%step',
    'show trail' => variable_get('step_show_trail', TRUE),
    'show back' => variable_get('step_show_back', FALSE),
    'return path' => variable_get('step_return_path', '<front>'),
    'next text' => t(variable_get('step_button_next', 'Continue')),
    'back text' => t(variable_get('step_button_back', 'Back')),
    'finish text' => t(variable_get('step_button_finish', 'Finish')),
    'forms' => step_get_steps(),
  );

  // Pass data to all wizard steps.
  $form_state[StepCache::CTOOLS_NAMESPACE] = StepCache::get('data');
  if ($step != STEP_REGISTER) {
    $form_state['user'] = user_load($form_state[StepCache::CTOOLS_NAMESPACE]['uid']);
  }

  drupal_alter('step_wizard', $form_info, $form_state);

  // Return a CTools multi-step form.
  return ctools_wizard_multistep_form($form_info, $step, $form_state);
}

/**
 * Returns a list of form information suitable to be used in CTools wizard.
 *
 * @return array
 *   An associative array having step ID as keys and form data as values.
 */
function step_get_steps() {
  $return = array();

  foreach (variable_get('step_steps', step_default()) as $id => $step) {
    $return[$id] = array(
      'title' => $step['title'],
      'form id' => $id == STEP_REGISTER ? 'user_register_form' : "step_step_$id",
    );
  }

  return $return;
}

/**
 * CTools wizard step callback.
 */
function step_step($form, &$form_state) {
  // Hide back button when we're on the next step to 'register'. We cannot enter
  // again basic data of an user.
  if ($form_state['form_info']['show back'] && $form_state['previous'] == STEP_REGISTER) {
    unset($form['buttons']['previous']);
  }

  // Workaround CTools "Back" button submit behaviour. CTools doesn't allow
  // saving of data in the current step when hitting "Back" button. We just want
  // to save the values too, in this case.
  if ($form_state['form_info']['show back']) {
    unset($form['buttons']['previous']['#submit']);
    $form['buttons']['previous']['#limit_validation_errors'] = FALSE;
  }

  // Add description, if case.
  step_add_description($form, $form_state);

  return $form;
}

/**
 * Callback executed when the 'next' button is clicked.
 */
function step_next(&$form_state) {
  // Fill the cache only in the first step.
  if ($form_state['step'] == STEP_REGISTER) {
    StepCache::set('data', $form_state['values']);
  }
}

/**
 * Callback executed when the entire form submission is finished.
 */
function step_finish(&$form_state) {
  StepCache::clear('data');
}
