<?php
global $user, $base_url;
$directoryPath = $base_path . $directory;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
?>

<div class="message right-message">

  <a href="#" id="button" class="hide-message2 ui-dialog-titlebar-close "><span class="ui-icon ui-icon-closethick">close</span></a>

                                    <p class="profile-status"><strong><?php print t('Your profile is only !complete% Complete', array('!complete' => $complete_percent['percent']))?></strong></p>
<div class="profile-complete">
        <div class="progress"></div>
</div>
            <p> <?php print t('Filling in your <em>!empty-field</em> will bring your up to !complete% Complete', array('!empty-field' => $complete_percent['nextfield'], '!complete' => $complete_percent['nextpercent'])); ?> <a class="bolded"><?php print t('Add it here.'); ?></a></p>

</div>