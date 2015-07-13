<?php

/**
 * @file
 * Contains front form implementations.
 */

/**
 * Form builder for register-to-class page and block.
 *
 * @see
 *   danscluj_general_menu()
 *   danscluj_general_block_view()
 */
function danscluj_general_register_to_class_form($form, &$form_state) {
  global $language;
  $form['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#description' => t('Enter your first name'),
    '#required' => TRUE,
  );

  $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#description' => t('Enter your last name'),
    '#required' => TRUE,
  );

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail'),
    '#description' => t('Enter your email address'),
    '#required' => TRUE,
  );

  $form['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#description' => t('Enter your phone number'),
    '#required' => TRUE,
  );

  $vocabulary = taxonomy_vocabulary_machine_name_load('course_category');
  $terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid, 'language' => $language->language));

  foreach ($terms as $term) {
    $option = $term->name;
    $options[$term->tid] = $option;
  }

  $form['category'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => $options,
    '#description' => t('Choose the type of course you would like to register to.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Register'),
  );

  return $form;
}

/**
 * Validation handler for 'danscluj_general_register_to_class_form'.
 */
function danscluj_general_register_to_class_form_validate($form, &$form_state) {
  // Email validation.
  if (!valid_email_address($form_state['values']['email'])) {
    form_error($form['email'], t('Please enter a valid email address'));
  }

  // Numeric validation for phones.
  if (!ctype_digit($form_state['values']['phone'])) {
    form_error($form['phone'], t('Please enter a valid phone number'));
  }

  // Text validation for names.
  $validation_first_name = preg_match('/\\d/', $form_state['values']['first_name']);
  $validation_last_name = preg_match('/\\d/', $form_state['values']['last_name']);
  if ($validation_first_name > 0) {
    form_error($form['first_name'], t('Please enter valid name'));
  }

  if ($validation_last_name > 0) {
    form_error($form['last_name'], t('Please enter valid name'));
  }
}

/**
 * Submit handler for 'danscluj_general_register_to_class_form'.
 */
function danscluj_general_register_to_class_form_submit($form, &$form_state) {
  $node = menu_get_object();

  $category = (isset($node) && !empty($node)) ?
    taxonomy_term_load($node->field_categorie_curs[LANGUAGE_NONE][0]['tid']) :
    taxonomy_term_load($form_state['values']['category']);

  $node = entity_create('node', array('type' => 'class_register'));
  // Specify the author
  $node->uid = 1;
  $node->status = NODE_NOT_PUBLISHED;
  // Create a Entity Wrapper of that new Entity
  $entity = entity_metadata_wrapper('node', $node);

  $first_name = check_plain($form_state['values']['first_name']);
  $last_name = check_plain($form_state['values']['last_name']);
  $email = check_plain($form_state['values']['email']);
  $phone = check_plain($form_state['values']['phone']);
  // Specify the title
  $entity->title =  $first_name . ' ' . $last_name;

  // Add field data... SO MUCH BETTER!
  $entity->field_email = $email;
  $entity->field_phone = $phone;
  $entity->field_categorie_curs = $category;
  // Save the node.
  $entity->save();
}
