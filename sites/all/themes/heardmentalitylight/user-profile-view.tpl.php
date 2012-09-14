<?php print theme('follower_button', $user); ?>
<h2 class="din"><?php print $user->name; ?></h2>

<div class="user-info">
  <p><?php print t($rank); ?></p>


  <p class="bio">
    <?php print $settings['bio']; ?>
  </p>
  <?php if($settings['mywebsite']): ?>
  <span class="URL block"><strong><?php print t('Web'); ?>:</strong> <a href="<?php print $settings['mywebsite']; ?>" target="_blank"><?php print $settings['mywebsite']; ?></a></span>
  <?php endif; ?>
  <?php if($settings['email']): ?>
  <span class="URL block"><strong><?php print t('Email'); ?>:</strong> <?php print $settings['email']; ?></span>
  <?php endif; ?>
  <?php if($settings['twitter']): ?>
  <span class="URL block"><strong><?php print t('Twitter'); ?>:</strong> <a href="<?php print $settings['twitter']; ?>" target="_blank"><?php print $settings['twitter']; ?></a></span>
  <?php endif; ?>
  <?php if($settings['facebook']): ?>
  <span class="URL block"><strong><?php print t('Facebook'); ?>:</strong> <a href="<?php print $settings['facebook']; ?>" target="_blank"><?php print $settings['facebook']; ?></a></span>
  <?php endif; ?>
  <?php if($settings['other_links']):
  foreach($settings['other_links'] as $name => $url) {?>
    <span class="URL block"><strong><?php print ucwords(t($name)); ?>:</strong> <a href="<?php print $url; ?>" target="_blank"><?php print $url; ?></a></span>
    <?php }?>
  <?php endif; ?>

</div>