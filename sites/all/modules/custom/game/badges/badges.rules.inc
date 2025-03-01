<?php

/**
 * Implementation of hook_rules_event_info()
 *
 * @return array
 */
function badges_rules_event_info() {
  return array(
    'badges_grant' => array(
      'label'     => t('User Got the Badge'),
      'module'    => 'Badges',
      'arguments' => array(
        'user'  => array(
          'type'  => 'user',
          'label' => t('User')
        ),
        'badge' => array(
          'type'  => 'string',
          'label' => t('Badge machine name')
        ),
      ),
    ),
  );
}

/**
 * Implementation of hook_rules_action_info()
 *
 * @return array
 */
function badges_rules_action_info() {
  return array(
    'badges_grant_badge_rules_action' => array(
      'label'     => t('Grant the Badges to User'),
      'arguments' => array(
        'user' => array(
          'type'  => 'user',
          'label' => t('User')
        ),
      ),
      'module'    => 'Badges Module',
    ),
  );
}

/**
 * @param       $type
 * @param       $user
 * @param array $vars
 * @param array $settings
 */
function badges_grant_badge_rules_action($user, $settings = array()) {
  foreach ($settings['badges'] as $badge => $status) {
    if ($status !== 0) {
      badges_grant($user->uid, $badge);
    }
  }
}

/**
 * Settings form
 */
function badges_grant_badge_rules_action_form($settings = array(), &$form) {
  $badges = badges_list();
  $options = array();

  foreach ($badges as $name => $info) {
    $options[$name] = $info['name'] . ' (' . $info['info'] . ')';
  }

  $form['settings']['badges'] = array(
    '#type'          => 'checkboxes',
    '#options'       => $options,
    '#title'         => t('Badges'),
    '#default_value' => isset($settings['badges']) ? $settings['badges'] : array(),
  );
}
