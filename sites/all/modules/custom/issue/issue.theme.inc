<?php include "old.issue.theme.inc";

/*
 *
 */

/**
 * Theme issue description
 *
 * @param $text
 * @param int $charcount
 * @return string
 */
function theme_issue_description($text, $charcount = 2500)
{
  $text = trim($text);
  if (strlen($text) > $charcount) {
    $trimmed = nl2br(substr($text, 0, $charcount)) . '<div id="new-ellipse"><a>... more</a></div>';
    $extended = nl2br(substr($text, $charcount));
  } else {
    $trimmed = nl2br($text);
    $extended = '';
  }
  return '<span>' . $trimmed . '</span><span id="extended-issue-description">' . $extended . '</span>';
}

/**
 * Preprocess for "issue_arguments" theme
 *
 * @param $vars
 */
function issue_arguments_preprocess(&$vars)
{
  $vars['charts'] = theme('issue_charts', $vars['node']);

  drupal_add_js('misc/collapse.js');
  drupal_add_js(drupal_get_path('module', 'issue') . "/argument.forms.js");
  $vars['arguments'] = theme('issue_arguments_content', $vars['node']);
}

/**
 * @return string
 */
function theme_issue_arguments_content($node)
{
  // arguments form
  if (user_is_logged_in()) {
    $form = drupal_get_form('argument_form', $node);
  } else {
    $form =
      '<div class="' . theme('user_login_modal_class', true) . '" align="center">' .
        '<b>' . t('Please log in to participate in the debate') . '</b>
      </div>';
  }
  return theme('issue_arguments_content_wrapper', $node, $form);
}