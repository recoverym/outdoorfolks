<?php

/**
 * @file
 * Multi-Step Registration administrative functionality.
 */

/**
 * Create new empty registration step.
 *
 * @param array $values
 *   Values to be set on creation.
 *
 * @return \stdClass
 *   A registration step array.
 */
function step_create(array $values = array()) {
  $defaults = array(
    'id' => '',
    'title' => '',
    'description' => array(
      'value' => '',
      'format' => filter_default_format(),
    ),
    'weight' => 0,
  );

  // Apply some defaults and return.
  return drupal_array_merge_deep($defaults, $values);
}

/**
 * Save a registration step.
 *
 * @param array $step
 *   Array that should be saved or updated.
 */
function step_save(array $step) {
  $steps = variable_get('step_steps', step_default());

  $steps[$step['id']] = $step;

  step_order($steps);

  // Save the whole list.
  variable_set('step_steps', $steps);
}

/**
 * Reorder registration steps based on weight.
 *
 * @param array $steps
 *   The list of registration steps to be saved.
 */
function step_order(array &$steps) {
  // Save the 'register' step to be always prepended.
  $register = $steps[STEP_REGISTER];
  unset($steps[STEP_REGISTER]);

  // Order remaining steps by weight.
  uasort($steps, 'drupal_sort_weight');

  // Rebuild the whole list with 'register' first.
  $steps = array(STEP_REGISTER => $register) + $steps;
}

/**
 * Form API builder function for list of registration steps.
 */
function step_list_form($form, $form_state) {
  $form['steps'] = array(
    '#tree' => TRUE,
    '#weight' => 0,
  );

  foreach (variable_get('step_steps', step_default()) as $id => $step) {

    $form['steps'][$id] = array(
      'title' => array(
        '#markup' => check_plain($step['title']),
      ),
      'id' => array(
        '#markup' => check_plain($id),
      ),
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => $step['weight'],
        '#delta' => 10,
        '#title_display' => 'invisible',
        '#attributes' => array(
          'class' => array('step-weight'),
        ),
      ),
    );

    $actions = array();
    $actions[] = array(
      'title' => t('Edit'),
      'href' => 'admin/config/people/step/' . $id . '/edit',
    );

    if ($id != STEP_REGISTER) {
      $actions[] = array(
        'title' => t('Delete'),
        'href' => 'admin/config/people/step/' . $id . '/delete',
      );
    }

    $form['steps'][$id]['actions']['#markup'] = theme(
      'links__ctools_dropbutton',
      array(
        'links' => $actions,
        'attributes' => array('class' => array('links', 'inline')),
      )
    );
  }

  $form['step_show_trail'] = array(
    '#type' => 'checkbox',
    '#title' => t('Wizard trail'),
    '#description' => t('Displays the wizard trail. The trail can be customized by theming <code>ctools_wizard_trail__step</code>.'),
    '#default_value' => variable_get('step_show_trail', TRUE),
    '#weight' => 10,
  );

  $form['step_show_back'] = array(
    '#type' => 'checkbox',
    '#title' => t('Back button'),
    '#description' => t('Adds a "Back" button.'),
    '#default_value' => variable_get('step_show_back', FALSE),
    '#weight' => 20,
  );

  $form['step_return_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect on Finish'),
    '#description' => t('The system path where the user will be redirected after finishing the wizard. Defaults to frontpage <code><front></code>.'),
    '#default_value' => variable_get('step_return_path', '<front>'),
    '#weight' => 30,
  );

  $form['step_show_description'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the registration description on top of each step form.'),
    '#description' => t('The output can be themed by implementing <code>step_description</code> theme.'),
    '#default_value' => variable_get('step_show_description', FALSE),
    '#weight' => 40,
  );

  if (STEP_PROFILE2) {
    $form['step_profile2_type_fieldset'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show each Profile2 type form in a fieldset.'),
      '#description' => t('By default, each profile form is enclosed into a "fieldset" container.'),
      '#default_value' => variable_get('step_profile2_type_fieldset', TRUE),
      '#weight' => 50,
    );
  }

  $form['buttons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Button labels'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 60,
  );

  $form['buttons']['step_button_next'] = array(
    '#type' => 'textfield',
    '#title' =>  t('Next button (untranslated)'),
    '#default_value' => variable_get('step_button_next', 'Continue'),
  );

  $form['buttons']['step_button_back'] = array(
    '#type' => 'textfield',
    '#title' =>  t('Back button (untranslated)'),
    '#default_value' => variable_get('step_button_back', 'Back'),
  );

  $form['buttons']['step_button_finish'] = array(
    '#type' => 'textfield',
    '#title' =>  t('Finish button (untranslated)'),
    '#default_value' => variable_get('step_button_finish', 'Finish'),
  );

  $form['actions'] = array(
    '#type' => 'actions',
    '#weight' => 1000,
  );


  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));

  return $form;
}

/**
 * Form API submit function for list of registration steps.
 */
function step_list_form_submit($form, $form_state) {
  $values = &$form_state['values'];

  foreach ($values as $key => $value) {
    if (substr($key, 0, 5) == 'step_') {
      variable_set($key, $value);
    }
  }

  $steps = variable_get('step_steps');
  foreach ($values['steps'] as $id => $step) {
    $steps[$id]['weight'] = $step['weight'];
  }
  step_order($steps);
  variable_set('step_steps', $steps);
}

/**
 * Form API form builder. Step form.
 */
function step_form($form, &$form_state, $step = NULL) {
  // Create a new empty step if none was passed.
  $is_new = empty($step);
  if ($is_new) {
    $step = step_create();
  }

  $title = $is_new ? t('Create registration step') : t('Edit @title', array('@title' => $step['title']));
  drupal_set_title($title);

  // Save the preset, we'll use lately.
  $form_state['step'] = $step;

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Register step title'),
    '#description' => t('Human-readable title of register step'),
    '#default_value' => $step['title'],
    '#required' => TRUE,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['id'] = array(
    '#type' => 'machine_name',
    '#default_value' => $step['id'],
    '#disabled' => !$is_new,
    '#maxlength' => 64,
    '#machine_name' => array(
      'exists' => 'step_exists',
      'source' => array('title'),
    ),
    '#required' => TRUE,
  );
  $form['description'] = array(
    '#type' => 'text_format',
    '#title' => t('Register step description'),
    '#description' => t('Full description of this register step'),
    '#default_value' => $step['description']['value'],
    '#format' => $step['description']['format'],
  );

  $form['actions'] = array(
    '#type' => 'action',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => $is_new ? t('Create') : t('Update'),
  );

  return $form;
}

/**
 * Checker for '#machine_name' on step machine name field.
 */
function step_exists($name) {
  // Do not allow 'register' as step machine name.
  if ($name == STEP_REGISTER) {
    return TRUE;
  }

  return step_load($name);
}

/**
 * Submit callback for register step form.
 */
function step_form_submit($form, &$form_state) {
  $values =& $form_state['values'];
  $step = $form_state['step'];

  $step['title'] = $values['title'];
  $step['id'] = $values['id'];
  $step['description'] = $values['description'];

  step_save($step);

  drupal_set_message(t('Registration step %step was saved.', array('%step' => $values['title'])));
  $form_state['redirect'] = 'admin/config/people/step';
}

/**
 * Form API form builder. Deletes step confirmation form.
 */
function step_delete_form($form, &$form_state, $step = NULL) {
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $step['id'],
  );
  $form['title'] = array(
    '#type' => 'value',
    '#value' => $step['title'],
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete the registration step "@title" (@id)?', array('@title' => $step['title'], '@id' => $step['id'])),
    'admin/config/people/step'
  );
}

/**
 * Form API form submit. Deletes a step.
 */
function step_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['id'] != STEP_REGISTER) {
    $steps = variable_get('step_steps');
    unset($steps[$form_state['values']['id']]);
    variable_set('step_steps', $steps);
    drupal_set_message(t('Registration step "@title" (@id) was deleted.', array('@title' => $form_state['values']['title'], '@id' => $form_state['values']['id'])));
  }
  $form_state['redirect'] = 'admin/config/people/step';
}
