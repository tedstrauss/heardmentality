<?php

function user_profile_edit_options($type, $undefined = false) {
  $list = array(
    'gender' => array(
      t('Gender'),
      t('Male'),
      t('Female')),
    'religion' => array(
      t('Religion'),
      t('Christian (Cath or Prod)'),
      t('Muslim (Suni Shiite)'),
      t('Hindu'),
      t('Jewish'),
      t('Buddhist'),
      t('Other')),
    'ethnicity' => array(
      t('Ethnicity'),
      t('Caucasian'),
      t('Black'),
      t('Asian'),
      t('Indian'),
      t('Semetic'),
      t('Latin'),
      t('Aborigines')),
    'sorient' => array(
      t('Sexual Orientation'),
      t('Straight'),
      t('Gay'),
      t('Bisexual'),
      t('Transgender')),
    'education' => array(
      t('Education'),
      t('No High School'),
      t('High School'),
      t('Technical College'),
      t('University'),
      t('Graduate Degree')),
    'income' => array(
      t('Household Income'),
      t('less than $9,999'),
      t('$10,000 - $19,999'),
      t('$20,000 - $39,999'),
      t('$40,000 - $69,999'),
      t('$70,000 - $99,999'),
      t('$100,000 - $149,999'),
      t('$150,000 - $299,999'),
      t('more than $300,000')),
    'marital' => array(
      t('Marital Status'),
      t('Single'),
      t('Married'),
      t('Divorced'),
      t('Widowed'))
  );
  if (isset($list[$type])) {
    $output = $list[$type];
    if ($undefined) {
      $output[0] = t('undefined');
    }
    return $output;
  }
  return array();
}

function user_profile_edit_form(&$form_state) {
  drupal_add_js(drupal_get_path('module', 'user_profile') . '/user_profile.js');

  drupal_add_js(drupal_get_path('module', 'profiles') . '/js/validate.js');
  drupal_add_js(drupal_get_path('module', 'profiles') . '/js/profile.js');

  global $user;

  $options = array('0' => t(''), '2' => t(''), '1' => t(''));
  $form['#attributes']['enctype'] = "multipart/form-data";
  //$form['#attributes']['onsubmit'] = "return validate_reg();";

//  var_Dump($user); die();

  $form['username'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 20,
    '#description'    => t(' '),
    '#value'          => $user->name,
    '#default_value'  => t('Username'),
    '#id'             => 'username',
    '#required'       => TRUE,
    '#attributes'     => array('class' => 'info validate validate-username', 'blurtext' => t('Username')),
  );
  $form['fname'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 20,
    '#description'    => t(' '),
    '#value'          => $user->real_name,
    '#default_value'  => t('Name'),
    '#id'             => 'name',
    '#attributes'     => array('class' => 'info validate validate-name', 'blurtext' => t('Name')),
  );
  $form['email'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 50,
    '#description'    => t(' '),
    '#value'          => $user->mail,
    '#default_value'  => t('Email'),
    '#id'             => 'email',
    '#required'       => 1,
    '#attributes'     => array('class' => 'info validate validate-email', 'blurtext' => t('Email')),
  );
  $form['gender'] = array(
    '#type'           => 'select',
    '#title'          => t(''),
    '#options'        => user_profile_edit_options('gender'),
    '#description'    => t(' '),
    '#value'          => $user->profile_gender,
    '#default_value'  => 0,
    '#id'             => 'gender',
    '#attributes'     => array('class' => 'info'),
  );
  $form['dob'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 4,
    '#description'    => t(' '),
    '#value'          => $user->profile_dob,
    '#default_value'  => t('Year of Birth'),
    '#id'             => 'dob',
    '#attributes'     => array('class' => 'info validate validate-date-year', 'blurtext' => t('Year Of Birth')),
  );

  $countries = geonames_query('countryinfo');
  $countries_options = array();
  foreach ($countries->results as $country) {
    $countries_options[$country['countrycode']] = $country['countryname'];
  }
  asort($countries_options);

  $form['country'] = array(
    '#type'           => 'select',
    '#value'          => $user->country, # don't translate
    '#default_value'  => 'US', # don't translate
    '#options'        => $countries_options,
    '#id'             => 'country',
    '#attributes'     => array('class' => 'info'),
  );
  $form['zip'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 10,
    '#description'    => t(''),
    '#value'          => $user->profile_zip,
    '#default_value'  => t('Zip code'),
    '#id'             => 'zip',
    '#attributes'     => array('class' => 'info validate validate-not-empty validate-zip', 'blurtext' => t('Zip code')),
  );

  $location = $user->city;
  if ($user->state) {
    $location .= $location ? ', ' : '';
    $location .= $user->state;
  }
  if ($user->country) {
    $location .= $location ? ', ' : '';
    $location .= $user->country;
  }

  $form['city-state-country'] = array(
    '#type'           => 'markup',
    '#value'          => '<span id="cit-stat">' . $location . '</span>'
  );
  $form['state'] = array(
    '#type'           => 'hidden',
    '#value'          => $user->state,
    '#id'             => 'state',
  );
  $form['city'] = array(
    '#type'           => 'hidden',
    '#value'          => $user->city,
    '#id'             => 'city',
  );
  $form['religion'] = array(
    '#type'           => 'select',
    '#title'          => t(''),
    '#options'        => user_profile_edit_options('religion'),
    '#description'    => t(' '),
    '#value'          => $user->profile_religion,
    '#default_value'  => 0,
    '#id'             => 'religion',
    '#attributes'     => array('class' => 'info'),
  );
  $form['ethnic'] = array(
    '#type'           => 'select',
    '#title'          => t(''),
    '#options'        => user_profile_edit_options('ethnicity'),
    '#description'    => t(' '),
    '#value'          => $user->profile_ethnic,
    '#default_value'  => 0,
    '#id'             => 'ethnic',
    '#attributes'     => array('class' => 'info'),
  );
  $form['sorient'] = array(
    '#type'           => 'select',
    '#title'          => t(''),
    '#options'        => user_profile_edit_options('sorient'),
    '#value'          => $user->profile_sorient,
    '#default_value'  => 0,
    '#description'    => t(' '),
    '#id'             => 'sorient',
    '#attributes'     => array('class' => 'info'),
  );
  $form['education'] = array(
    '#type'           => 'select',
    '#title'          => t(''),
    '#options'        => user_profile_edit_options('education'),
    '#description'    => t(' '),
    '#value'          => $user->edu,
    '#default_value'  => 0,
    '#id'             => 'edu',
    '#attributes'     => array('class' => 'info'),
  );
  $form['income'] = array(
    '#type'           => 'select',
    '#title'          => t(''),
    '#options'        => user_profile_edit_options('income'),
    '#description'    => t(' '),
    '#value'          => $user->income,
    '#default_value'  => 0,
    '#id'             => 'income',
    '#attributes'     => array('class' => 'info'),
  );
  $form['marital'] = array(
    '#type'           => 'select',
    '#title'          => t(''),
    '#options'        => user_profile_edit_options('marital'),
    '#description'    => t(' '),
    '#value'          => $user->marital,
    '#default_value'  => 0,
    '#id'             => 'marital',
    '#attributes'     => array('class' => 'info'),
  );
  $form['bio'] = array(
    '#type'           => 'textarea',
    '#title'          => t(''),
    '#value'          => $user->bio,
    '#default_value'  => t('Bio'),
    '#cols'           => '',
    '#rows'           => 1,
    '#description'    => t(''),
    '#id'             => 'bio',
    '#attributes'     => array('class' => 'info validate validate-not-empty', 'blurtext' => t('Bio')),
    '#resizable'      => FALSE,
  );

  $form = $form + get_privacy_form();

  $social = explode('||', $details->social);
  $form['facebook'] = array(
    '#type' => 'textfield',
    '#description' => t(''),
    '#default_value' => variable_get('facebook', $social[0]),
    '#id' => 'face',
    '#attributes' => array('class' => 'info validate validate-url-username'),
  );
  $form['twitter'] = array(
    '#type' => 'textfield',
    '#description' => t(' '),
    '#default_value' => variable_get('twitter', $social[1]),
    '#id' => 'twitter',
    '#attributes' => array('class' => 'info validate validate-url-username'),
  );
  $form['myweb'] = array(
    '#type' => 'textfield',
    '#title' => t(''),
    '#description' => t(''),
    '#default_value' => variable_get('myweb', $details->urls),
    '#id' => 'myweb',
    '#attributes' => array('class' => 'info validate validate-url'),
  );


  $form['merge'] = array('#type' => 'markup', '#value' => '

          <div id="divConnect"></div>
    <script type="text/javascript">
        // show Add Connections Plugin in "divConnect"
        gigya.services.socialize.showAddConnectionsUI(conf, {
			height:65
			,width:175
			,showTermsLink:false //remove trems link
			,hideGigyaLink:true // remove Gigya link
			,useHTML:true  // Use the HTML implementation of the Plugin (rather then Flash implementation)
			,containerID: "divConnect" // The component will embed itself inside the divConnect Div
		});
    </script>
         ');

  //$form['personal_links'] = array('#type' => 'markup', '#value' => '<div class="web-reference-new">');
  $form['notify'] = array(
    '#type' => 'radios',
    '#default_value' => variable_get('notify', $details->notify_etype),
    '#options' => $options,
  );
  // avatar hidden values

  $form['img_avt'] = array('#type' => 'hidden', '#default_value' => variable_get('img_avt', $details->image_avatar));
  //$form['image'] = array('#type' => 'textfield', '#default_value' => variable_get('image', $details->image));
  $form['image'] = array('#type' => 'hidden', '#default_value' => $user->picture);
  $form['current_image'] = array('#type' => 'hidden', '#id' => 'curr_avatar', '#default_value' => '');



  $form['hiddentop'] = array(
    '#type' => 'markup',
    '#value' => '<div id="avatar-profile-ele" class="d-header" style="display:none;background-color:white;width:350px;position:absolute;top:200px;left:350px;"><a href="javascript:void(0)" onclick="jQuery(\'#avatar-profile-ele\').slideToggle();update_avatar();" style="float:right">close[X]</a>');
  $form = $form + inc_avatar_form($form, $form_state);
  $form['hiddenbot'] = array(
    '#type' => 'markup',
    '#value' => '</div>');
  $languages = i18n_language_list();
  $form['default_language'] = array('#type' => 'select',
    '#options' => $languages,
    '#default_value' => $details->language);
  // subscription hidden value
  $form['subscription_email'] = array(
    '#type' => 'textfield',
    '#title' => t(''),
    '#maxlength' => 50,
    '#default_value' => variable_get('email', $user->mail),
    '#id' => 'sub_email',
    '#required' => 1,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
    '#id' => 'update_submit',
    '#attributes' => array('class' => 'submit-issue')
  );
  $form = $form + get_avatar_form();
  return $form;
}

function user_profile_edit_privacy_options() {

}

function user_profile_edit_form_privacy() {
  $form = array();



  return $form;
}


function get_privacy_form() {

  global $user;
  $query = "select * from {user_profile} where uid='$user->uid'";
  $fetch = ExecuteQuery($query, "select");
  $options = array('1' => t(''), '2' => t(''), '3' => t(''), '4' => t(''));
  $noOne = array('4' => t(''));
  $noone_value = 4;
  $query = "select * from {profile_fields} ORDER BY `profile_fields`.`fid` ASC";
  $result = db_query($query);

  $form['username_privacy'] = array(
    '#type' => 'markup',
    '#value' => '<div class="form-wra">&nbsp;
                     <div class="clr"></div>
                     </div>',
  );
  while ($meta = db_fetch_object($result)) {
    $col = $fields[] = $meta->name;
    $list = trim($fetch[0][$col]);

    $sel = db_result(db_query("SELECT $col FROM {privacy_settings} WHERE uid = '%d'", $user->uid));
    $sel = empty($sel) ? '1' : $sel;

    if ($col != 'income') {
      $form[$col . '_privacy'] = array(
        '#type' => 'radios',
        '#default_value' => $noone_value,
        '#value' => variable_get($col . '_privacy', $sel),
        '#options' => $options,
      );
    }
    else {
      $form[$col . '_privacy'] = array(
        '#type' => 'radios',
        '#default_value' => $noone_value,
        '#options' => $noOne,
        '#checked' => TRUE,
      );
    }

    $form['div_down'] = array('#type' => 'markup', '#value' => '
          <div class="clr"></div>
       ');
  }

  $form['activity_privacy'] = array(
    '#type' => 'radios',
    '#default_value' => $noone_value,
    '#value' => variable_get('activity_privacy', $fetch[0]['question_privacy']),
    '#options' => $options,
    '#prefix' => '<br/><br/><br/><div class="form-wra">',
    '#suffix' => '<div class="clr"></div></div>',
  );
  $form['mid_div'] = array('#type' => 'markup', '#value' => '
          <div class="clr"></div>
       ');
  return $form;
}

function get_avatar_form() {
  global $user, $apikey, $theme;
  $form = array();
  drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js');
  drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
  drupal_add_css(drupal_get_path('module', 'avatar_selection') . '/avatar_selection.css');
  drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
  drupal_set_html_head('<script src="http://cdn.gigya.com/JS/socialize.js?apikey=' . $apikey . '" type="text/javascript"></script>');
  drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js';
  $account = load_user($user->uid);
  $data = '
	    var conf =
        {
            APIKey: \'' . $apikey . '\'
        };
var avtar=\'' . $account->avatar . '\';
';
  drupal_add_js($data, 'inline');

  // set the form encoding type

  $form['#attributes']['enctype'] = "multipart/form-data";
  $options = array('1' => t('weekly'), '2' => t('monthly'), '0' => t('never'));
  // add a file upload file
  $form['file_upload'] = array(
    '#type' => 'file',
    '#size' => '10',
    '#prefix' => '<div id="al-msg"></div><div class="avatar-left"><img src="' . UserPicture_small_src($user->uid, 0) . '" /><p>' . t('Select an image file from your computer.<br />(2MBs max)') . '</p>',
    '#suffix' => '</div>',
  );

  $form['oldimg'] = array(
    '#type' => 'hidden',
    '#default_value' => variable_get('oldimg', $user->picture),
    '#id' => 'oldimg',
  );
  $form['avatar_div_close'] = array('#type' => 'markup', '#value' => '<div class="clr"></div>
    </div><div class="clr"></div>');
  return $form;
}

function user_profile_edit_form_validate($form, &$form_state) {
  global $user;
  $step = $form_state['values']['step'];
  $dob = $form_state['values']['dob'];
  $zip = $form_state['values']['zip'];
  $state = $form_state['values']['state'];
  $uname = $form_state['values']['username'];
  $email = $form_state['values']['email'];
  $fname = $form_state['values']['fname'];
  if (!preg_match('/^[A-Za-z0-9_]{5,20}$/i', $uname)) {
    form_set_error('username', t('Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed'));
    $form_state['rebuild'] = TRUE;
  }
  elseif (db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s' AND uid!='%d'", $uname, $user->uid))) {
    form_set_error('username', t('Sorry Username already exists try any other combination'));
    $form_state['rebuild'] = TRUE;
  }

  if (!empty($dob)) {

    if (!is_numeric($dob) || strlen($dob) != '4') {
      form_set_error('dob', t('Year Of Birth should be Numeric & Proper Format Ex : 1986'));
      $form_state['rebuild'] = TRUE;
    }
  }
  if (!empty($zip)) {
    if (!preg_match('/^[0-9A-Za-z ]+?$/i', $zip)) {
      form_set_error('zip', t('Zip Code should be Proper One & Proper Format Ex : 11010'));
      $form_state['rebuild'] = TRUE;
    }
    elseif (empty($state)) {
      form_set_error('zip', t('Kindly Recheck your Zip Code, We find its invalid one! '));
      $form_state['rebuild'] = TRUE;
    }
  }
  if (!valid_email_address($email)) {
    form_set_error('email', t('Your email address "') . $email . t('" appears malformed'));
  }
  elseif (db_result(db_query("SELECT COUNT(*) FROM {users} WHERE mail = '%s' AND uid!='%d'", $email, $user->uid))) {
    form_set_error('email', t('Sorry Email already taken by other user'));
    $form_state['rebuild'] = TRUE;
  }
  if (!empty($fname) && !preg_match('/^([a-zA-Z]+ ){1,2}[a-zA-Z]+$/i', $fname)) {
    form_set_error('fname', t('Full Name should be Alpha Ex : Kevin kumar'));
    $form_state['rebuild'] = TRUE;
  }
}

function user_profile_edit_form_submit($form, &$form_state) {
  global $user;
  krumo($form_state);
  // translate back country code to country name
  $countries = geonames_query('countryinfo');
  $contriesOptions = array();
  foreach ($countries->results as $country) {
    $contriesOptions[$country['countrycode']] = $country['countryname'];
  }
  $form_state['values']['country'] = $contriesOptions[$form_state['values']['country']];

  //profile fields update
  _basic_submit($form, $form_state);
  //privacy update
  _privacy_submit($form, $form_state);
  //avatar update
  _avatar_submit($form, $form_state);
  // follow links update
  //  follow_links_form_submit($form, $form_state);


  /* New SET NOTIFY LOG */
  $variable = array();
  set_notify_log($user->uid, '', 'update_profile', $variable);
  /* New SET NOTIFY LOG */


  drupal_set_message(t('Your profile info has been updated'), 'success');
}