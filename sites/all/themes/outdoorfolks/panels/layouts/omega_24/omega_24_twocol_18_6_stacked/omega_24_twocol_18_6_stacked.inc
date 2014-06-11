<?php

/**
 * Implements hook_panels_layouts().
*/
 $plugin = array(
    'title' => t('Two Column 18-6 stacked'),
    'category' => t('Omega: 24 Column Grid'),
    'icon' => 'omega_24_twocol_18_6_stacked.png',
    'theme' => 'omega_24_twocol_18_6_stacked',
    'admin css' => '../omega_panels_admin_24.css',
    'regions' => array(
        'left' => t('Left side'),
        'right' => t('Right side'),
        'bottom' => t('Bottom')
    ),
  );

