<li class="clearfix">
  <?php
  $account = $item['account'];
  $argument = node_load($item['content_id']);
  $node = node_load($argument->field_issue[0]['nid']);
  $vars = $item['vars'];

  if (!empty($argument) && $argument->field_argument_type[0]['value'] == TYPE_RESOURCE) {
    $text = 'posted a reference on the issue';
  } else {
    $text = 'posted an argument on the issue';
  }
  $link = l(
    $node->title . '?',
    $node->path,
    empty($argument) ? array() : array('fragment' => 'forum-block-' . $argument->nid)
  );
  $text2 = $argument->title;
  ?>
  <?php print l(
  sprintf('<img class="following-user listed" src="%s" />', user_profile_image($account)),
  $account->viewlink,
  array('html' => true)
); ?>
<p class="action-item">
  <span class="name">
    <a href="/<?php print $account->viewlink ?>" title="<?php print $account->name ?>">
      <?php print ucwords($account->name) ?>
    </a>
  </span>
  <?php print t($text); ?>
  <?php print $link; ?>
  <?php if ($text2) : ?>
    </p><p class="action-comment-ref"><?php print t($text2) ?>
  <br clear="both">
  <?php endif; ?>
</p>
  <span class="submitted"><?php print $date; ?></span>
</li>