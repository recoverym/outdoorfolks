<?php

/**
 * @file
 * Rules integration for Outdoorfolks.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_action_info().
 */
function outdoorfolks_rules_action_info() {
  $actions = array(
      'outdoorfolks_create_activation_codes' => array(
          'label' => t('Create activation codes'),
          'group' => t('Outdoorfolks custom actions'),
          'parameter' => array(
              //
              'product' => array(
                  'type' => 'commerce_product',
                  'label' => t('Product'),
                  'description' => t("Product added to the cart."),
              ),
              'order_line_item' => array(
                  'type' => 'commerce_line_item',
                  'label' => t('Order line item'),
                  'description' => t("Order line item."),
              ),
          ),
      ),
      'outdoorfolks_set_reg_prov' => array(
          'label' => t('Set Regione - Provincia from Address on User Profiles'),
          'group' => t('Outdoorfolks custom actions'),
          'parameter' => array(
              //
              'user' => array(
                  'type' => 'user',
                  'label' => t('User'),
                  'description' => t('User.'),
              		'save'=>TRUE,
              ),
              //
              'profile' => array(
                  'type' => 'profile2',
                  'label' => t('Profile'),
                  'description' => t("Profile"),
              		'save'=>TRUE,
              ),
          ),
      ),
      'outdoorfolks_set_node_reg_prov' => array(
          'label' => t('Set Regione - Provincia from Geolocation on Nodes'),
          'group' => t('Outdoorfolks custom actions'),
      		'parameter' => array(
      				//
      				'node' => array(
      						'type' => 'node',
      						'label' => t('Node'),
      						'description' => t('Node.'),
      						'save'=>TRUE,
      				),
      		),
      ),

  );
  return $actions;
}

/**
 *
 */
function outdoorfolks_create_activation_codes($product,$line_item) {


 //if(!empty($line_item->field_activation_codes[LANGUAGE_NONE]) && ){

    //array_shift($line_item->field_activation_codes[LANGUAGE_NONE]);
    $line_item->field_activation_codes[LANGUAGE_NONE]=array();

    for ($i=0;$i<$line_item->quantity;$i++){
      $code = $line_item->line_item_id . "-" . $line_item->created . "-" . $i;
      $value = array(
          'code' => $code,
          'activated' => 0,
      );

      array_push($line_item->field_activation_codes[LANGUAGE_NONE],$value);
    }

    commerce_line_item_save($line_item);

  //}
 // $wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
}

/**
 *
 */
function outdoorfolks_set_reg_prov($user,$profile) {

  $vid = 6;
  if(!empty($profile->field_indirizzo['und'][0]['administrative_area'])){
    $province = $profile->field_indirizzo['und'][0]['administrative_area'];
  }
  $tree = taxonomy_get_tree($vid);

  foreach ($tree as $element) {
  	if($element->depth == 1){
   		 if($element->description == $province){
      		$tid = $element->tid;
    		}
  	}

  }

  $profile->field_regione_e_provincia['und'][0]['tid'] = $tid;
  //profile2_save($profile);
}

/**
 *
 */
function outdoorfolks_set_node_reg_prov($node) {

  $vid=6;
  $debug=0;
  $handler = 'google';
  $options['language'] = 'it';

  switch ($node->type){
  	case "display_proposta":
  		if(isset($node->field_posizione_offerta)){
  			$lat=$node->field_posizione_offerta['und'][0]['lat'];
  			$lon=$node->field_posizione_offerta['und'][0]['lon'];

  			//$result = geocoder_rules_reverse_geocode('google', $lat, $lon, 'it');

  			$address = geocoder_reverse($handler, $lat, $lon, $options);

  			foreach ( $address->data['geocoder_address_components'] as $component ) {
  				if ( isset( $component->types ) ) {
  					// Street Number
  					if ( in_array( 'street_number' , $component->types ) ) $result->street_number = $component->long_name;

  					// Road
  					if ( in_array( 'route' , $component->types ) ) $result->route = $component->long_name;

  					// City
  					if ( in_array( 'locality' , $component->types ) ) $result->locality = $component->long_name;

  					// State || Province or similar based on country polical boundries.
  					if ( in_array( 'administrative_area_level_1' , $component->types ) ) $result->region = $component->long_name;
  					if ( in_array( 'administrative_area_level_1' , $component->types ) ) $result->region_abbr = $component->short_name;

  					// County or similar based on country polical boundries.
  					if ( in_array( 'administrative_area_level_2' , $component->types ) ) $result->county = $component->long_name;
  					if ( in_array( 'administrative_area_level_2' , $component->types ) ) $result->county_abbr = $component->short_name;

  					// Township or similar based on country polical boundries.
  					if ( in_array( 'administrative_area_level_3' , $component->types ) ) $result->township = $component->long_name;

  					// Postal Code
  					if ( in_array( 'postal_code' , $component->types ) ) $result->postal_code = $component->long_name;

  					// Country
  					if ( in_array( 'country' , $component->types ) ) $result->country = $component->long_name;
  					if ( in_array( 'country' , $component->types ) ) $result->country_abbr = $component->short_name;
  				}
  			}

  			$tree = taxonomy_get_tree($vid);

  			foreach ($tree as $element) {
  				if($element->depth == 1){
  					if($element->description == $result->county_abbr || $element->name == $result->county){
  						$node->field_regione_e_provincia['und'][0]['tid'] = $element->tid;

  						//node_submit($node);
  						//node_save($node);
  					}
  				}

  			}
  		}
  	break;
  	case "luogo":
  		/*if(isset($node->field_location)){
  			$lat=$node->field_location['und'][0]['lat'];
  			$lon=$node->field_location['und'][0]['lon'];

  			$result = geocoder_rules_reverse_geocode('google', $lat, $lon, 'it');

  			$tree = taxonomy_get_tree($vid);

  			foreach ($tree as $element) {
  				if($element->description == $result['province_s']){

  					// $node->field_regione_e_provincia['und'][0]['tid'] = $element->parents[0];
  					//$node->field_regione_e_provincia['und'][1]['tid'] = $element->tid;
  					// node_submit($luogo);
  					//node_save($node);
  					$debug=0;
  				}

  			}
  		}*/
  	break;

  }

   // }
  //}
}


// geocoder_rules_reverse_geocode($handler, $lat, $long, $language);

/*  if(!empty($profile->field_indirizzo['und'][0]['administrative_area'])){
 $province = $profile->field_indirizzo['und'][0]['administrative_area'];
}
$tree = taxonomy_get_tree($vid);

foreach ($tree as $element) {
if($element->description == $province){
$tid = $element->tid;
}

}

$profile->field_regione_e_provincia['und'][0]['tid'] = $tid;
profile2_save($profile);*/


/**
 * @}
 */
