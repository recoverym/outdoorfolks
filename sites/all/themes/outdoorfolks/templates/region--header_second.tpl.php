<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <?php if (arg(0) == 'search' || arg(0) == 'marketplace'): ?>
      <?php if (empty($title)) : ?>
       <?php $title = drupal_get_title(); ?>
     <?php endif; ?>
     <h1 id='page-title' class='title'><?php print ($title); ?></h1>
    <?php endif; ?>
	<?php print $content; ?>
  </div>
</div>
