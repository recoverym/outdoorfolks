<?php

/**
 * @file
 * Builds profile-specific register, login, and password forms.
 */

/**
 * Page callback: Displays a user login form.
 *
 * Path: [path-setting]/login
 *
 * @param object $profiles
 *   Object containing single row from outdoorfolks_step_registration_get_profiles() database
 *   result.
 *
 * @see outdoorfolks_step_registration_menu()
 */
function _outdoorfolks_step_registration_user_login($profile) {
  module_load_include('pages.inc', 'user', 'user');
  $output = user_page();
  _outdoorfolks_step_registration_set_title($profile, 'login_title');
  return $output;
}

/**
 * Page callback: Displays a user registration form.
 *
 * Path: [path-setting]/register
 *
 * @param object object $profiles
 *   Object containing single row from outdoorfolks_step_registration_get_profiles() database
 *   result.
 *
 * @see outdoorfolks_step_registration_menu()
 */
function _outdoorfolks_step_registration_user_register($profile) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_register_form');
  _outdoorfolks_step_registration_set_title($profile, 'register_title');
  return $output;
}

/**
 * Page callback: Displays the forgot password form.
 *
 * Path: [path-setting]/password
 *
 * @param object $profiles
 *   Object containing single row from outdoorfolks_step_registration_get_profiles() database
 *   result.
 *
 * @see outdoorfolks_step_registration_menu()
 */
function _outdoorfolks_step_registration_user_password($profile) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_pass');
  _outdoorfolks_step_registration_set_title($profile, 'password_title');
  return $output;
}

/**
 * Sets page title for registration, login, and forgot password pages.
 *
 * @param object $profiles
 *   Object containing single row from outdoorfolks_step_registration_get_profiles() database
 *   result.
 *
 * @param string $key
 *   Array key for 'misc' array. This will determine the title settings.
 */
function _outdoorfolks_step_registration_set_title($profile, $key) {
  // Look for custom title in foremost profile, according to weight.
  if (isset($profile)) {
      $title = $profile;
  }
  // Set default title.
  else {
    $title = 'User account';
  }
  // Set title. See http://drupal.org/node/1800116 for use of t().
  drupal_set_title(t($title));
}