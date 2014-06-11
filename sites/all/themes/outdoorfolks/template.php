<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 *
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */


/**
 * Implements template_process_html().
 *
 */
function outdoorfolks_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

function outdoorfolks_process_region(&$vars){
 // $vars['wrapper_attributes'] = isset($vars['wrapper_attributes_array']) ? drupal_attributes($vars['wrapper_attributes_array']) : '';
}

function outdoorfolks_preprocess_zone(&$vars){
 // $vars['wrapper_attributes'] = isset($vars['wrapper_attributes_array']) ? drupal_attributes($vars['wrapper_attributes_array']) : '';
}

function outdoorfolks_preprocess_region(&$vars) {
  $theme = alpha_get_theme();

  if ($vars['elements']['#region'] == 'content') {
    //$vars['breadcrumb'] = $theme->page['breadcrumb'];
  }
}



/*function outdoorfolks_commerce_add_to_cart_confirmation_message($variables) {
  $message = '<div class="added-product-title clearfix">' . t('Item successfully added to your cart') . '</div>';
  $message .= '<div class="button-wrapper">';
  $message .= '<div class="button checkout">' . l(t('Go to checkout'), 'cart') . '</div>';
  $message .= '<div class="button continue"><span class="commerce-add-to-cart-confirmation-close">' . t('Continue shopping') . '</span></div>';
  $message .= '</div>';
  $message .= $variables['view'];
  return '<div class="message-inner">' . $message . '<a class="commerce-add-to-cart-confirmation-close" href="#"><span class="element-invisible">' . t('Close') . '</span></a></div>';
}*/


/**
 * Implements template_process_page().
 */
function outdoorfolks_process_page(&$variables) {
  // Hook into color.module.
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
  if(arg(0)=='search' || arg(0)=='marketplace'){
    $variables['title_hidden'] = TRUE;
  }
  if (arg(0) == 'user') {
    switch (arg(1)) {
      case 'register':
        $variables['title'] = t('Create a new account');
        break;
      case 'password':
        $variables['title'] = t('Retrieve lost password');
        break;
      case 'login':
        $variables['title'] = t('User login');
        break;
    }
  }
  if (arg(0) == 'thank-you'){
    $variables['title_hidden'] = TRUE;
  }
}

/*Implements template_preprocess_search_result*/
function outdoorfolks_preprocess_search_result(&$variables) {

  global $language;
  $debug=1;

  switch ($language->language){
    case 'it':
      if(!empty($variables['result']['fields']['sm_activities_it'])){
        $activities= $variables['result']['fields']['sm_activities_it'];
        $variables['sm_activities'] = $activities;
      }
      if(!empty($variables['result']['fields']['sm_attivita_it'])){
        $activity= $variables['result']['fields']['sm_attivita_it'];
        $variables['sm_attivita'] = $activity;
      }
      if(!empty($variables['result']['fields']['sm_regprov_it'])){
        $regprov= $variables['result']['fields']['sm_regprov_it'];
        $variables['sm_regprov'] = $regprov;
      }
     break;
     case 'en':
        if(!empty($variables['result']['fields']['sm_activities_en'])){
          $activities= $variables['result']['fields']['sm_activities_en'];
          $variables['sm_activities'] = $activities;
        }
        if(!empty($variables['result']['fields']['sm_attivita_en'])){
          $activity= $variables['result']['fields']['sm_attivita_en'];
          $variables['sm_attivita'] = $activity;
        }
        if(!empty($variables['result']['fields']['sm_regprov_en'])){
          $regprov= $variables['result']['fields']['sm_regprov_en'];
          $variables['sm_regprov'] = $regprov;
        }
       break;
    }
  /*$handler = 'google';
  $options = array();
  $options['language'] = $language;
  $pieces = explode(",", $variables['result']['fields']['geos_field_posizione_offerta']);
  $lat = $pieces[0];
  $long = $pieces[1];
  $address = geocoder_reverse($handler, $lat, $long, $options);*/

  if(!empty($variables['result']['fields']['ss_field_immagine_prodotto_uri'])){
    $image_uri= $variables['result']['fields']['ss_field_immagine_prodotto_uri'];
    $variables['ss_field_immagine_prodotto_uri'] = $image_uri;
  }

  if(!empty($variables['result']['fields']['ss_field_image_uri'])){
    $image_uri= $variables['result']['fields']['ss_field_image_uri'];
    $variables['ss_field_image_uri'] = $image_uri;
  }

  if(!empty($variables['result']['fields']['zs_view_mode_teaser'])){
    $view_mode= $variables['result']['fields']['zs_view_mode_teaser'];
    $variables['zs_view_mode_teaser'] = $view_mode;
  }

  /*if(!empty($variables['result']['fields']['iss_commerce_price'])){
    $price= $variables['result']['fields']['iss_commerce_price'];
    $variables['iss_commerce_price'] = $price;
  }*/

  /*if(!empty($variables['result']['fields']['sm_denominazione_provider'][0])){
    $denominazione= $variables['result']['fields']['sm_denominazione_provider'][0];
    $path= drupal_get_path_alias('user/' . $variables['result']['uid']);
    $label=t('Provided by ');
    $denominazione_formatted = $label .'<a href="'.$path.'">'. $denominazione .'</a>';
    $variables['ss_denominazione_provider'] = $denominazione_formatted;
  }*/

  if(!empty($variables['result']['fields']['sm_price'])){
    $price= $variables['result']['fields']['sm_price'];
    $variables['sm_price'] = $price;
  }

  //$variables['geom_field_location'] = $variables['result']['fields']['geom_field_location'];
}

/*shows user profile picture next to superfish menu link - my account*/
function outdoorfolks_superfish_menu_item($variables) {
  global $user;
  $element = $variables['element'];
  $properties = $variables['properties'];
  $sub_menu = '';

  $entity = entity_load_single('user', $user->uid);
  if(isset($entity->field_first_name[LANGUAGE_NONE])){
    $first_name = $entity->field_first_name[LANGUAGE_NONE][0]['value'];
  }


  if ($element['item']['link']['menu_name'] == 'menu-user-menu-authenticated-' && $element['item']['link']['href'] == 'user/'.$user->uid.'/dashboard') {
    if(!empty($first_name)){
      $element['item']['link']['title'] = $first_name;
    }
    else{
      $element['item']['link']['title'] = t('user menu');
    }
    // Add 'html' = TRUE to the link options
    $element['localized_options']['html'] = TRUE;
    // Load the user picture file information; Unnecessary if you use theme_user_picture()
    $fid = $user->picture;
    $file = file_load($fid);
    $path = $file ? $file->uri : 'public://default_images/Icon-user.png';
    // I found it necessary to use theme_image_style() instead of theme_user_picture()
    // because I didn't want any extra html, just the image.
    $title = theme('image_style', array('style_name' => 'micro__10x10_', 'path' => $path, 'alt' => $element['item']['link']['title'], 'title' => $element['item']['link']['title'])) . $element['item']['link']['title'];
  } else {
    $title = $element['item']['link']['title'];
  }

  if ($element['below']) {
    $sub_menu .= isset($variables['wrapper']['wul'][0]) ? $variables['wrapper']['wul'][0] : '';
    $sub_menu .= ($properties['megamenu']['megamenu_content']) ? '<ol>' : '<ul>';
    $sub_menu .= $element['below'];
    $sub_menu .= ($properties['megamenu']['megamenu_content']) ? '</ol>' : '</ul>';
    $sub_menu .= isset($variables['wrapper']['wul'][1]) ? $variables['wrapper']['wul'][1] : '';
  }

  $output = '<li' . drupal_attributes($element['attributes']) . '>';
  $output .= ($properties['megamenu']['megamenu_column']) ? '<div class="sf-megamenu-column">' : '';
  $output .= isset($properties['wrapper']['whl'][0]) ? $properties['wrapper']['whl'][0] : '';
  if ($properties['use_link_theme']) {
    $link_variables = array(
        'menu_item' => $element['item'],
        'link_options' => $element['localized_options']
    );
    $output .= theme('superfish_menu_item_link', $link_variables);
  }
  else {
    $output .= l($title, $element['item']['link']['href'], $element['localized_options']);
  }
  $output .= isset($properties['wrapper']['whl'][1]) ? $properties['wrapper']['whl'][1] : '';
  $output .= ($properties['megamenu']['megamenu_wrapper']) ? '<ul class="sf-megamenu"><li class="sf-megamenu-wrapper ' . $element['attributes']['class'] . '">' : '';
  $output .= $sub_menu;
  $output .= ($properties['megamenu']['megamenu_wrapper']) ? '</li></ul>' : '';
  $output .= ($properties['megamenu']['megamenu_column']) ? '</div>' : '';
  $output .= '</li>';

  return $output;
}

function outdoorfolks_theme($existing, $type, $theme, $path){
  $hooks['user_register_form']=array(
      'render element'=>'form',
      'template' =>'templates/user-register',
  );

  return $hooks;
}

function outdoorfolks_preprocess_user_register(&$variables) {
  $variables['form'] = drupal_build_form('user_register_form', user_register_form(array()));
}


/*shows user profile picture next to menu link - my account*/

function outdoorfolks_menu_link(array $variables) {
  global $user;
  $element = $variables['element'];
  $sub_menu = '';

  $entity = entity_load_single('user', $user->uid);
  if(isset($entity->field_first_name[LANGUAGE_NONE])){
    $first_name = $entity->field_first_name[LANGUAGE_NONE][0]['value'];
  }

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $title = '';
  // Check if the user is logged in, that you are in the correct menu,
  // and that you have the right menu item
  if ($element['#theme'] == 'menu_link__sf_menu_user_menu_authenticated_' && $element['#href'] == 'user') {
    if(!empty($first_name)){
      $element['#title'] = $first_name;
    }
    else{
      $element['#title'] = t('user menu');
    }
    // Add 'html' = TRUE to the link options
    $element['#localized_options']['html'] = TRUE;
    // Load the user picture file information; Unnecessary if you use theme_user_picture()
    $fid = $user->picture;
    $file = file_load($fid);
    // I found it necessary to use theme_image_style() instead of theme_user_picture()
    // because I didn't want any extra html, just the image.
    $title = theme('image_style', array('style_name' => 'thumbnail', 'path' => $file->uri, 'alt' => $element['#title'], 'title' => $element['#title'])) . $element['#title'];
  } else {
    $title = $element['#title'];
  }
  $output = l($title, $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

// Add link for Ubuntu font
drupal_add_css('http://fonts.googleapis.com/css?family=Poiret+One|Open+Sans', array('group' => CSS_THEME, 'type' => 'external'));


