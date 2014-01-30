<?php global $theme_path; ?>

<tr>
  <td style="height: 16px; line-height: 16px; font-size: 14px; font-family: Arial; text-align: center;">

    <?php print l('View this email on website', 'newsletter/' . $data['newsletter']['hash'], array(
      'absolute'   => true,
      'attributes' => array(
        'style' => 'text-decoration: none; color: #333;',
      ),
    )); ?>

    <?php if ($data['uid']) : ?>
      &nbsp;&nbsp;|&nbsp;&nbsp;

      <?php print l('Unsubscribe', 'user/profile/view/' . $data['uid'], array(
        'absolute'   => true,
        'query'      => array('newsletter_action' => 'unsubscribe'),
        'attributes' => array(
          'style' => 'text-decoration: none; color: #333;',
        ),
      )); ?>
    <?php endif; ?>

  </td>
</tr>

<tr>
  <td
    style="background : url(<?php print url($theme_path . '/images/cross_hatch_texture_dark.png', array('absolute' => true)); ?>) repeat scroll 0 0 #A29CAC;border       : solid #A29CAC;border-width : 1px 0;height: 100px;">

    <table>
      <tr>

        <td
          style=""><?php print l('<img style="height: 80px; width: 140px;" title="Heard Mentality Logo" alt="Heard Mentality Logo" src="' . url($theme_path . '/images/hm-logo.png', array('absolute' => true)) . '">', '', array(
            'absolute'   => true,
            'html'       => true,
            'attributes' => array(
              'style' => 'padding: 5px;',
            ),
          )); ?></td>

        <td
          style="width: 100%;text-align: center; font-family: Arial; font-size: 30px; padding-left: 10px;"><?php print l('Heard Mentality Newsletter', '', array(
            'absolute'   => true,
            'attributes' => array(
              'style' => 'text-decoration: none; color: #333;',
            ),
          )); ?></td>

      </tr>
    </table>

  </td>
</tr>