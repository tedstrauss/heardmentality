<?php include "page_up.tpl.php"; ?>

<div class="container">

  <?php if ($tabs): ?>
  <div class="tabs"><?php print $tabs; ?></div>
  <?php endif; ?>

  <div class="eleven columns">

    <?php if ($_title = drupal_set_subtitle()) : ?>
    <h2 class="dinbold page-title"><?php print $_title; ?></h2>
    <?php endif; ?>

    <?php if ($content_top) : ?>
    <div class="grey-box clearfix full" id="region-content-top">
      <?php print $content; ?>
    </div>
    <?php endif; ?>

    <?php if ($content) : ?>
      <?php if (!$content_nowrap) : ?>
        <div class="<?php print ($content_class) ? $content_class : 'white-box'; ?> clearfix full" id="region-content">
      <?php endif; ?>
        <?php print $content; ?>
      <?php if (!$content_nowrap) : ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>

    <?php if ($content_bottom) : ?>
    <div class="white-box clearfix full" id="region-content-bottom">
      <?php print $content_bottom; ?>
    </div>
    <?php endif; ?>

  </div>

  <div class="five columns">

    <?php if ($right) : ?>
      <?php print $right; ?>
    <?php endif; ?>

  </div>

</div>

<?php include "page_dn.tpl.php"; ?>