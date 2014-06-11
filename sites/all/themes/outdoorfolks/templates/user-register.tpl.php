<?php
/**
 * @file
 * Outdoorfolks theme implementation to display a user registration page.
 */
?>

<?php
  print render($form['form_id']);
  print render($form['form_build_id']);
?>
<div class="grid-24 user-register personal-data">
<?php print render($form['message']);?>

<?php if (isset($form['personal_data'])): ?>
  <div class="form-item">
    <?php print render($form['personal_data']);?>
    <?php print render($form['personal_data']['#description']);?>
  </div>
<?php endif; ?>
 <div class="form-content">
  <?php
    print render($form['field_first_name']);
    print render($form['field_last_name']);
    print render($form['account']['mail']);
  ?>
  </div>
</div>

<div class="grid-24 user-register other-data">

<?php if (isset($form['other_data'])): ?>
  <div class="form-item">
    <?php print render($form['other_data']);?>
    <?php print render($form['other_data']['#description']);?>
  </div>
<?php endif; ?>
  <div class="form-content">
  <?php
    print render($form['profile_service_provider']);
    print render($form['profile_partner']);
   ?>
    <div class="form-links">
    <?php
      if (isset($form['partner_registration'])):
        print render($form['partner_registration']);
        print render($form['partner_registration']['#description']);
      endif;

      print render($form['terms_of_use']);
      print drupal_render($form['actions']);
    ?>
    </div>
  </div>
</div>