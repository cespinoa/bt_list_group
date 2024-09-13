<?php

/**
 * @file
 * Include files for functions and hooks related to field formatter
 */


/**
 * Implements hook_field_formatter_third_party_settings_form().
 */
function bt_list_group_field_formatter_third_party_settings_form(FormatterInterface $plugin, FieldDefinitionInterface $field_definition, $view_mode, $form, FormStateInterface $form_state) {
  $element = [];

  /* @var \Drupal\bt_list_group\Service\InitialSettingsService $initialSettings */
  $initialSettings = \Drupal::service('bt_list_group.initial');
  
  if (in_array($plugin->getPluginId(), $initialSettings->getFormatters())) {
    
    $settings = $plugin->getThirdPartySetting('bt_list_group','settings');
    

    $element['settings'] = [
      '#type' => 'details',
      '#title' => 'Bootstrap Toolbox List Group',
    ];
    
    $element['settings']['list_group'] = [
      '#type' => 'checkbox',
      '#title' => t('Display as a bootstrap list group'),
      '#default_value' => $settings['list_group'],
    ];
    
    $element['settings']['display_as_a_card'] = [
      '#type' => 'checkbox',
      '#title' => t('Display as a bootstrap card'),
      '#default_value' => $settings['display_as_a_card'],
      '#states' => [
        'visible' => [
          ':input[name="fields[' . $field_definition->getName() . '][settings_edit_form][third_party_settings][bt_list_group][list_group]"]' => ['checked' => TRUE],
        ],
      ],
    ];
    
    $element['settings']['use_label_as_card_header'] = [
      '#type' => 'checkbox',
      '#title' => t('Display label as card_header'),
      '#default_value' => $settings['use_label_as_card_header'],
      '#states' => [
        'visible' => [
          ':input[name="fields[' . $field_definition->getName() . '][settings_edit_form][third_party_settings][bt_list_group][display_as_a_card]"]' => ['checked' => TRUE],
        ],
      ],
    ];
    
  }
    
  return $element;
}


/**
 * Implements hook_field_formatter_settings_summary_alter().
 */
function bt_list_group_field_formatter_settings_summary_alter(&$summary, $context) {
  /* @var \Drupal\bt_list_group\Service\InitialSettingsService $initialSettings */
  $initialSettings = \Drupal::service('bt_list_group.initial');
  if(in_array($context['formatter']->getPluginId(), $initialSettings->getFormatters())) {
    if($context['formatter']->getThirdPartySetting('bt_list_group', 'settings')) {
      $settings = $context['formatter']->getThirdPartySetting('bt_list_group', 'settings');
      if($settings['list_group']){
        $summary[] = t('Display as a bootstrap list group');
        if($settings['display_as_a_card']){
          $summary[] = t('Display as a bootstrap card');
          if($settings['use_label_as_card_header']){
            $summary[] = t('Use label as card header');
          }
        }
      }
    } 
  }
}

/**
 *
 * Process the field with third_party_settings 
 * 
 * Implements hook_preprocess_HOOK() for field templates.
 */
function bt_list_group_preprocess_field(&$variables){
  if(array_key_exists('#third_party_settings', $variables['element']) 
        && array_key_exists('bt_list_group',$variables['element']['#third_party_settings'])
        && array_key_exists('settings',$variables['element']['#third_party_settings']['bt_list_group'])
        && $variables['element']['#third_party_settings']['bt_list_group']['settings']['list_group']){
          
    if(count($variables['items'])){
      if(gettype($variables['attributes'])!='object'){
        $variables['attributes'] =  new \Drupal\Core\Template\Attribute();
      }
      $variables['attributes']->addClass('list-group');
      if($variables['element']['#third_party_settings']['bt_list_group']['settings']['display_as_a_card']){
        $variables['attributes']->addClass('card');
        $variables['label_class'] = 'card-header';
        if($variables['element']['#third_party_settings']['bt_list_group']['settings']['use_label_as_card_header']){
          $variables['label_display'] = 'above';
          $variables['label_hidden'] = FALSE;
        }
      }
      if($variables['items'][0]['content']['#type']=='link'){
        foreach($variables['items'] as $delta=>$item){
          $variables['items'][$delta]['attributes']->addClass('list-group-item list-group-item-action');
        }
      }
    }
    $previousClasses = implode(' ',$variables['attributes']->getClass()->value());
    $variables['attributes']->addClass($previousClasses);
  }
  
}


