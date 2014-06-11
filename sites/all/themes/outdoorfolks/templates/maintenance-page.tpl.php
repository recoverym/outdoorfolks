<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
  <meta property="og:title" content="Outdoorfolks - Italian outdoors for active living lovers." />
<meta property="og:type" content="company" />
<meta property="og:site_name" content="Outdoorfolks - Italian outdoors for active living lovers. " />
<meta property="og:description" content="Outdoorfolks è il primo social marketplace per le attività di outdoor recreation in Italia.
Un nuovo modo per gli operatori del settore di connettersi con gli amanti del territorio e della vita all'aria aperta. Una accurata selezione di esperienze da acquistare in modo semplice, trasparente, sicuro e veloce.  
" />
<meta property="og:url" content="www.outdoorfolks.it/signup" />
<meta property="og:image" content="https://launchrock-assets.s3.amazonaws.com/facebook-files/OPTOX9C8_1380019142753.png?_=0" />
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body class="<?php print $classes; ?>">

  <?php print $page_top; ?>

  <div id="page">
  <!-- Begin LaunchRock Widget -->
<div id="lr-widget" rel="OPTOX9C8"></div>
<script type="text/javascript" src="//ignition.launchrock.com/ignition-current.min.js"></script>
<!-- End LaunchRock Widget -->

    <?php if ($sidebar_first): ?>
      <div id="sidebar-first" class="sidebar">
        <?php if ($logo): ?>
          <img id="logo" src="<?php print $logo ?>" alt="<?php print $site_name ?>" />
        <?php endif; ?>
        <?php print $sidebar_first ?>
      </div>
    <?php endif; ?>

    <div id="content" class="clearfix">
      <?php if ($messages): ?>
        <div id="console"><?php print $messages; ?></div>
      <?php endif; ?>
      <?php if ($help): ?>
        <div id="help">
          <?php print $help; ?>
        </div>
      <?php endif; ?>
      <?php print $content; ?>
    </div>

  </div>

  <?php print $page_bottom; ?>

  </body>
</html>
