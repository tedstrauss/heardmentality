<div class="following_page">
  <?php if ($users) : ?>
    <?php $param = $code == 'following' ? 'requestee' : 'requester'; ?>

    <?php foreach ($users as $item) : ?>
      <?php
      $account = $item->{$param};
      $account->viewlink = 'user/profile/view/' . $account->name;
      ?>

      <div class="one_person clearfix">
        <?php print theme('follower_button', $account); ?>

        <div class="name_wrapper">
          <?php print l('<img class="following-user-2" src="' . user_profile_image($account) . '">', $account->viewlink, array(
              'html' => true,
            )); ?>
          <span class="name din">
			  <?php print l($account->name, $account->viewlink); ?>
			</span>
        </div>
      </div>

    <?php endforeach; ?>

  <?php else : ?>

    <?php
    global $user;
    if ($user->uid == $uid) {
      print $code == 'following' ? t('You\'re not following anyone from the Heard yet. You can follow users by clicking the \'Follow\' button on their profile pages.') : t('No users from the Heard follow you yet');
    }
    else {
      print t('No users found');
    }
    ?>

  <?php endif; ?>

</div>
